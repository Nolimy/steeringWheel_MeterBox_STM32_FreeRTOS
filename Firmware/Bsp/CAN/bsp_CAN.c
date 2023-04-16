#include "bsp_CAN.h"
#include "string.h"
#include "bsp_BC260Y.h"
#include "ui.h"
#include "cmsis_os2.h"
#include "applicationVar.h"

#define LY9_VCU  1
#define LY8_M800 0






extern osEventFlagsId_t getCarDataHandle;

void CANFilter_Config(void)//无论发啥我都照单全收。
{
    CAN_FilterTypeDef  sFilterConfig;
    
    sFilterConfig.FilterBank = 0;                       //CAN过滤器编号，范围0-27
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;   //CAN过滤器模式，掩码模式或列表模式
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;  //CAN过滤器尺度，16位或32位
    sFilterConfig.FilterIdHigh = 0x000 << 5;			//32位下，存储要过滤ID的高16位
    sFilterConfig.FilterIdLow = 0x0000;					//32位下，存储要过滤ID的低16位
    sFilterConfig.FilterMaskIdHigh = 0x0000;			//掩码模式下，存储的是掩码
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = 0;				//报文通过过滤器的匹配后，存储到哪个FIFO
    sFilterConfig.FilterActivation = ENABLE;    		//激活过滤器
    sFilterConfig.SlaveStartFilterBank = 0;
    
    if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK) {
        printf("CAN Filter Config Fail!\r\n");
        Error_Handler();
    }
    printf("CAN Filter Config Success!\r\n");

}

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
				if(Counter == 18) 
				{
					/************一组报文接收完毕，接收标志位置0，等待新一组报文头部。************/
					frameEofFlag = 0;
					
					/************收到CAN报文，发送相应标志位，FreeRTOS响应事件************/
					osEventFlagsSet(getCarDataHandle, 0x0f); // 0000 1111   //
					
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
			/************若MQTT初始化成功则4G模块开始数据上报************/
			if(MQTTinitOkFlag)
				uploadFlag = 1;				
		}
	}
}
//if(HAL_GPIO_ReadPin(INPUT9_GPIO_Port, INPUT9_Pin) == RESET) 
//if(HAL_GPIO_ReadPin(INPUTA_GPIO_Port, INPUTA_Pin) == RESET) 
void CAN1_Send(uint32_t CAN_ID, uint8_t *CAN_DATA)
{
	//uint8_t data[4] = {0x01, 0x02, 0x03, 0x04};
    
  TxMessage.IDE = CAN_ID_STD;     //设置ID类型
	TxMessage.StdId = CAN_ID;        //设置ID号
  TxMessage.RTR = CAN_RTR_DATA;   //设置传送数据帧
	TxMessage.DLC = 8;              //设置数据长度
    
	if (HAL_CAN_AddTxMessage(&hcan1, &TxMessage, CAN_DATA, (uint32_t*)CAN_TX_MAILBOX0) != HAL_OK) {
        //printf("CAN send test data fail!\r\n");
        Error_Handler();
    }
    //printf("CAN send test data success!\r\n");
		
}
/*10个KEY对应10Bit数据，从低位依次置1*/
void keyControlCanSend()
{
	canControlData[0] = 000;
	canControlData[1] = 0x00;
	if(HAL_GPIO_ReadPin(INPUT1_GPIO_Port, INPUT1_Pin) == RESET) canControlData[0] |= 0x01 << 0; 
	if(HAL_GPIO_ReadPin(INPUT2_GPIO_Port, INPUT2_Pin) == RESET) canControlData[0] |= 0x01 << 1;
	if(HAL_GPIO_ReadPin(INPUT3_GPIO_Port, INPUT3_Pin) == RESET) canControlData[0] |= 0x01 << 2;
	if(HAL_GPIO_ReadPin(INPUT4_GPIO_Port, INPUT4_Pin) == RESET) canControlData[0] |= 0x01 << 3;
	if(HAL_GPIO_ReadPin(INPUT5_GPIO_Port, INPUT5_Pin) == RESET) canControlData[0] |= 0x01 << 4;
	if(HAL_GPIO_ReadPin(INPUT6_GPIO_Port, INPUT6_Pin) == RESET) canControlData[0] |= 0x01 << 5;
	if(HAL_GPIO_ReadPin(INPUT7_GPIO_Port, INPUT7_Pin) == RESET) canControlData[0] |= 0x01 << 6;
	if(HAL_GPIO_ReadPin(INPUT8_GPIO_Port, INPUT8_Pin) == RESET) canControlData[0] |= 0x01 << 7;
	if(HAL_GPIO_ReadPin(INPUT9_GPIO_Port, INPUT9_Pin) == RESET) canControlData[1] |= 0x01 << 0;
	if(HAL_GPIO_ReadPin(INPUTA_GPIO_Port, INPUTA_Pin) == RESET) canControlData[1] |= 0x01 << 1;
	
	CAN1_Send(0X155, canControlData);
}
void CanFilterInit()
{
	usartTxFlag = 1;
	printf("----- CAN Test Board #1 -----\r\n");
	CANFilter_Config();
    
    /* 2. CAN Start */
	if (HAL_CAN_Start(&hcan1) != HAL_OK) {
			printf("CAN Start Fail\r\n");
			Error_Handler();
	}
	printf("CAN Start Success\r\n");
	
	/* 3. Enable CAN RX Interrupt */
	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
			printf("CAN_IT_RX_FIFO0_MSG_PENDING Enable Fail\r\n");
			Error_Handler();
	}
	printf("CAN_IT_RX_FIFO0_MSG_PENDING Enable Success\r\n");
}

/*
struct RacingCarData
{

	//ID:0X193
	uint8_t FrontSpeed;          //前轮车速 在这里作为参考车速 1Byte
	uint8_t PedalTravel;         //油门踏板开度    1Byte
	uint8_t brakeTravel;         //刹车踏板开度    1Byte
	uint8_t carTravel;           //车辆跑动距离    1Byte
	uint16_t l_motor_torque;      //左电机目标转矩  2Byte
  uint16_t r_motor_torque;      //右电机目标转矩  2Byte

	//ID:0X196 
	uint8_t batAlarm;            //电池告警  0~4 无告警：0 一级告警：1（最严重） 二级告警：2 三级告警：3
	uint8_t batTemp;               //电池温度  0-160  offset:-40
	uint8_t batLevel;            //电池电量  0-100
	uint16_t batVol;              //电池电压  0-900
	uint8_t gearMode;            //挡位信息  1Bit
	uint8_t carMode;             //车辆运行模式  1Bit 1:转矩模式 2：速度模式
	//ID:0X191
	uint16_t lmotorSpeed;         //左电机转速  2Bit offset -10000rpm 分辨率:0.5
	//ID:0X192
	uint8_t lmotorTemp;          //左电机温度   1Byte 0~150摄氏度 offset:-50
	uint8_t mcu1Temp;            //电机控制器1温度 1Byte 0~150摄氏度 offset:-50
	//ID:0X194	
	uint16_t rmotorSpeed;         //右电机转速  2Bit offset -10000rpm 分辨率:0.5
	//ID:0X195
	uint8_t rmotorTemp;          //右电机温度
	uint8_t mcu2Temp;            //电机控制器2温度
	
	
};
*/


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

#if Receiver
//0X5F0

void motec_ECU_decode()
{
	carType = 1; 
			
			racingCarData.EngOil_temp = (motec_CanFrame[3][6] << 8 | motec_CanFrame[3][7]) / 10;  //机油温度
			racingCarData.EngOil_presure = (motec_CanFrame[4][0] << 8 | motec_CanFrame[4][1]) / 10;  //机油压力
			racingCarData.lmotorSpeed = motec_CanFrame[1][0] << 8 | motec_CanFrame[1][1];   //发动机转速
			racingCarData.gearMode = (motec_CanFrame[14][0] << 8 |motec_CanFrame[14][1]);    //挡位
			racingCarData.Throttle_Angel = (motec_CanFrame[1][2] << 8 |motec_CanFrame[1][3]) / 10; //节气门开度
			switch(racingCarData.gearMode)
			{
				case 0:
					racingCarData.FrontSpeed = 0;
					break;
				case 1:
					racingCarData.FrontSpeed = racingCarData.lmotorSpeed / 2.615 / (36 / 11);
					break;
				case 2:
					racingCarData.FrontSpeed = racingCarData.lmotorSpeed / 1.857 / (36 / 11);
					break;
				case 3:
					racingCarData.FrontSpeed = racingCarData.lmotorSpeed / 1.565 / (36 / 11);
					break;
				case 4:
					racingCarData.FrontSpeed = racingCarData.lmotorSpeed / 1.350 / (36 / 11);
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
