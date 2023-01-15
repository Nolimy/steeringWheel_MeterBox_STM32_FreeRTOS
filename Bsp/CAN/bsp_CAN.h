#ifndef __BSP_CAN_H__
#define __BSP_CAN_H__

#include "can.h"
#include "main.h"
#include "stdio.h"
#include "usart.h"


static CAN_TxHeaderTypeDef        TxMessage;    //CAN发送的消息的消息头
static CAN_RxHeaderTypeDef        RxMessage;    //CAN接收的消息的消息头

void CAN1_Send(uint32_t CAN_ID, uint8_t *CAN_DATA);

void CANFilter_Config(void);
void CanFilterInit(void);
void uploadCarData();

#define Transmitter 0
#define Receiver    1

#define UPLOAD_EVENT (0x01 << 0)//设置事件掩码的位 0 
#define GUI_UPDATE_EVENT (0x01 << 1)//设置事件掩码的位 1
#define LED_EVENT (0x01 << 2)//设置事件掩码的位 1

#if Transmitter
void carDataUpdate();
void canDataPack();
#endif

#if Receiver
void decodeCanData(uint32_t canID, uint8_t *canData);
#endif
struct RacingCarData
{

	//ID:0X193
	uint8_t FrontSpeed;          //前轮车速 在这里作为参考车速 1Byte
	uint8_t PedalTravel;         //油门踏板开度    1Byte
	uint8_t brakeTravel;         //刹车踏板开度    1Byte
	uint8_t carTravel;           //车辆跑动距离    1Byte
	uint16_t l_motor_torque;     //左电机目标转矩  2Byte
  uint16_t r_motor_torque;     //右电机目标转矩  2Byte

	//ID:0X196 
	uint8_t batAlarm;            //电池告警  0~4 无告警：0 一级告警：1（最严重） 二级告警：2 三级告警：3 1Byte
	uint8_t batTemp;             //电池温度  0-160  offset:-40  1Byte
	uint8_t batLevel;            //电池电量  0-100  1Byte
	uint16_t batVol;              //电池电压  0-900  2Byte
	uint8_t gearMode;            //挡位信息  1Bit   1Byte
	uint8_t carMode;             //车辆运行模式  1Bit
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
extern struct RacingCarData racingCarData;
extern uint8_t uploadFlag;
#endif //__BSP_CAN_H__
