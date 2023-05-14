#include "CAN_App.h"

extern osEventFlagsId_t getCarDataHandle;

#if Receiver
//0X5F0
//	uint8_t oilTemp;
//	uint8_t oilPressure;
//	uint8_t throttlePosition;
//	float lowBatVol;
//  uint16_t lambda1;
//	uint8_t ecu_Temp;
//	uint8_t gear;
//  uint8_t engineTemp;
//  uint8_t FrontSpeed
void motec_ECU_decode()
{
	carType = 1; 
	
	racingCarData.lmotorSpeed = motec_CanFrame[1][0] << 8 | motec_CanFrame[1][1];   //发动机转速
	racingCarData.throttlePosition = (motec_CanFrame[1][2] << 8 |motec_CanFrame[1][3]) / 10; //节气门开度
	racingCarData.engineTemp = (motec_CanFrame[2][0] << 8 | motec_CanFrame[2][1]) / 10;  //发动机温度
	racingCarData.lambda1 = (motec_CanFrame[2][2] << 8 | motec_CanFrame[2][3]) / 1000;  //氧传感器信号
	racingCarData.oilTemp = (motec_CanFrame[3][6] << 8 | motec_CanFrame[3][7]) / 10;  //机油温度
	racingCarData.oilPressure = (motec_CanFrame[4][0] << 8 | motec_CanFrame[4][1]) / 10;  //机油压力
	racingCarData.lowBatVol = (motec_CanFrame[6][4] << 8 | motec_CanFrame[6][5]) / 10;  //低压电池电压
	racingCarData.ecu_Temp = (motec_CanFrame[6][6] << 8 | motec_CanFrame[6][7]) / 10;  //ECU温度
	racingCarData.gear = (motec_CanFrame[14][0] << 8 | motec_CanFrame[14][1]);    //挡位
	

	/****************************通过齿比、挡位和发动机转速关系换算车速****************************/
	switch(racingCarData.gear)
	{
		case 0:
			racingCarData.FrontSpeed = 0;
			break;
		case 1:
			racingCarData.FrontSpeed = racingCarData.lmotorSpeed * 1.44 * 60 / 1000 / 2.615 / 3.27;
			break;
		case 2:
			racingCarData.FrontSpeed = racingCarData.lmotorSpeed * 1.44 * 60 / 1000 / 1.857 / 3.27;
			break;
		case 3:
			racingCarData.FrontSpeed = racingCarData.lmotorSpeed * 1.44 * 60 / 1000 / 1.565 / 3.27;
			break;
		case 4:
			racingCarData.FrontSpeed = racingCarData.lmotorSpeed * 1.44 * 60 / 1000 / 1.350 / 3.27;
			break;
	}
}

void decodeCanData(uint32_t canID, uint8_t *canData)
{
	
	
	switch(canID)
	{
		case 0x211:
			carType = 0; //电车
			racingCarData.FrontSpeed = canData[0];
			racingCarData.PedalTravel = canData[1];
			racingCarData.brakeTravel = canData[2];
			racingCarData.carTravel = canData[3];
			racingCarData.l_motor_torque = canData[4] + canData[5] * 256;
			racingCarData.r_motor_torque = canData[6] + canData[7] * 256;
			break;
		
		case 0x212:
			racingCarData.lmotorSpeed = (canData[0] + canData[1]*256)/2 - 10000;
			racingCarData.lmotorTemp = canData[2] - 50;
			racingCarData.mcu1Temp = canData[3] - 50;
      racingCarData.rmotorSpeed = (canData[4] + canData[5]*256)/2 - 10000;
			racingCarData.rmotorTemp = canData[6] - 50;
			racingCarData.mcu2Temp = canData[7] - 50;
			break;
		
		case 0x213:
			racingCarData.batAlarm = canData[0];
			racingCarData.batTemp = canData[1] - 40;
			racingCarData.batLevel = canData[2];
			racingCarData.batVol = (canData[3] + canData[4] * 256) / 10;
			racingCarData.gearMode = canData[5];
			racingCarData.carMode = canData[6];
			break;	
	}	
}

#endif



/***接收中断***/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	uint8_t  RxData[8];
	uint8_t static Counter = 0;  //帧计数器
	uint8_t i;
	
	HAL_StatusTypeDef	status;
	
	if (hcan == &hcan1) {	

		status = HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxMessage, RxData);

		if (HAL_OK == status){ 
			
			/************切换显示模式************/
			appStatus.standByStatus = 0; //关闭待机模式
			appStatus.canOpenStatus = 1; //打开实车模式
			appStatus.simhubStatus  = 0; //关闭模拟器模式
	
			
			
			if(RxMessage.StdId == 0x5F0)
			{
				/************帧计数器到达18自动清零，避免越界************/
				if(Counter == 18 && motec_CanFrame[0][4] == 0XFC && motec_CanFrame[0][5] == 0XFB && motec_CanFrame[0][6] == 0XFA && motec_CanFrame[14][2] == 0x01 && motec_CanFrame[14][3] == 0xf4) 
				{
					/************一组报文接收完毕，接收标志位置0，等待新一组报文头部。************/
					frameEofFlag = 0;
					
					/************解析CAN报文************/
					motec_ECU_decode(); //完整解析上一组CAN报文
					
					/************清零************/
					memset(motec_CanFrame, 0x00, sizeof(motec_CanFrame));
					
				}
				/************判断是否为报文头部，若是，则计数器清零************/
				if(RxData[4] == 0XFC && RxData[5] == 0XFB && RxData[6] == 0XFA) 
				{
					/************则计数器清零************/
					Counter = 0;
					frameEofFlag = 1; //表示接收到了帧报文头部，此时开始接收新的一帧报文。
				}					
				
				/************将收到的帧存储到帧缓存区************/
				if(frameEofFlag && (Counter >= 0 && Counter <=17))
				{
					for(i=0; i<8; i++){
						motec_CanFrame[Counter][i] = RxData[i];
					}
					/************更新计数器************/
					Counter++;
				}		
			}
			else if(RxMessage.StdId == 0x211 || RxMessage.StdId == 0x212 || RxMessage.StdId == 0x213)
				decodeCanData(RxMessage.StdId, RxData);
			
			/************收到CAN报文，发送相应标志位，FreeRTOS响应事件************/
			osEventFlagsSet(getCarDataHandle, 0x0f); // 0000 1111   //
			
			/************若MQTT初始化成功则4G模块开始数据上报************/
			if(MQTTinitOkFlag)
				uploadFlag = 1;				
		}
	}
}

#if Transmitter
void carDataUpdate()//模拟汽车跑动数据
{
	racingCarData.gearMode = 2; //0:空挡  1:倒挡 2：前进挡
	racingCarData.carMode = 2;//速度模式
	racingCarData.batTemp = 40;//电池温度 40摄氏度
	racingCarData.batLevel = 100;//动力电池电量 100%
	racingCarData.batVol = 450;//动力电池电压450V
	racingCarData.batAlarm = 0;//无告警
	
	if(upSpeedFlag)
	{
		racingCarData.lmotorSpeed+=100;         //左电机转速  2Bit offset -10000rpm 分辨率:0.5
		if(racingCarData.lmotorSpeed == 6000)
			upSpeedFlag = 0;
	}
	else
	{
		racingCarData.lmotorSpeed-=100;
		if(racingCarData.lmotorSpeed == 0)
			upSpeedFlag = 1;
	}
	racingCarData.rmotorSpeed = racingCarData.lmotorSpeed;
	
	racingCarData.FrontSpeed = (int)(racingCarData.lmotorSpeed/SPEED_RATIO*PI*2*WHEEL_R*3.6/60);  //由转速换算为车速
	if(upSpeedFlag)
	{
		racingCarData.l_motor_torque = 1000;
		racingCarData.r_motor_torque = racingCarData.l_motor_torque;
		racingCarData.PedalTravel = 100; //油门踏板开度为100 踩死
		racingCarData.brakeTravel = 0;
	}
		
	else
	{
		racingCarData.l_motor_torque = 0;
		racingCarData.r_motor_torque = racingCarData.l_motor_torque;
		racingCarData.PedalTravel =0;
		racingCarData.brakeTravel = 40;
	}
	racingCarData.carTravel+=5;
	
	racingCarData.lmotorTemp = 40; //左电机温度   1Byte 0~150摄氏度 offset:-50
	racingCarData.mcu1Temp = 40;   //电机控制器1温度 1Byte 0~150摄氏度 offset:-50
	racingCarData.rmotorTemp = 40; //右电机温度   1Byte 0~150摄氏度 offset:-50
	racingCarData.mcu2Temp = 40;   //电机控制器2温度 1Byte 0~150摄氏度 offset:-50
	
	canDataPack();
}
//按照CAN协议打包要发送的行车数据
void canDataPack()
{
	/****************************ID:0X211****************************/
	carData[0] = racingCarData.FrontSpeed;
	carData[1] = racingCarData.PedalTravel;
	carData[2] = racingCarData.brakeTravel;
	carData[3] = racingCarData.carTravel;
	carData[4] = racingCarData.l_motor_torque % 256;
	carData[5] = racingCarData.l_motor_torque >> 8;
	carData[6] = racingCarData.r_motor_torque % 256;
	carData[7] = racingCarData.r_motor_torque >> 8;
	CAN1_Send(0X211, carData);
	memset(carData,0x00,sizeof(carData)); //清空数组
	/****************************ID:0X211****************************/
	
	/****************************ID:0X212****************************/
	uint8_t carData[8];
	//	LeftMotorRPM = (CAN_Re_0_M06[0] + CAN_Re_0_M06[1]*256)/2 - 10000;
	carData[0] = ((racingCarData.lmotorSpeed + 10000) * 2) % 256; //转速 低八位
	carData[1] = ((racingCarData.lmotorSpeed + 10000) * 2) >> 8;  //转速 高八位
	carData[2] = racingCarData.lmotorTemp + 50;//左电机温度   1Byte 0~150摄氏度 offset:-50
	carData[3] = racingCarData.mcu1Temp + 50;  //电机控制器1温度 1Byte 0~150摄氏度 offset:-50
	carData[4] = ((racingCarData.rmotorSpeed + 10000) * 2) % 256; //转速 低八位
	carData[5] = ((racingCarData.rmotorSpeed + 10000) * 2) >> 8;  //转速 高八位
	carData[6] = racingCarData.rmotorTemp + 50;//右电机温度   1Byte 0~150摄氏度 offset:-50
	carData[7] = racingCarData.mcu2Temp + 50;  //电机控制器温度 1Byte 0~150摄氏度 offset:-50
	CAN1_Send(0X212, carData);
	memset(carData,0x00,sizeof(carData)); //清空数组
	/****************************ID:0X212****************************/
	        
	/****************************ID:0X213****************************/
	carData[0] = racingCarData.batAlarm;//电池告警  0~4 无告警：0 一级告警：1（最严重） 二级告警：2 三级告警：3
	carData[1] = racingCarData.batTemp + 40;//电池温度  0-160  offset:-40
	carData[2] = racingCarData.batLevel;//电池电量  0-100
	carData[3] = racingCarData.gearMode;//挡位信息  1Bit
	carData[4] = racingCarData.carMode;//车辆运行模式  1Bit 1:转矩模式 2：速度模式
	carData[6] = racingCarData.batVol * 10 % 256;//电池电压  0-900 Resolution = 0.1 LSB在后八位
	carData[5] = racingCarData.batVol * 10 >> 8;
	CAN1_Send(0X213, carData);
	memset(carData,0x00,sizeof(carData)); //清空数组
	/****************************ID:0X213****************************/
	

}
#endif