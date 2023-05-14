#include "bsp_CAN.h"
#include "string.h"
#include "bsp_BC260Y.h"
#include "ui.h"
#include "applicationVar.h"


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
        Error_Handler();
    }
		
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

