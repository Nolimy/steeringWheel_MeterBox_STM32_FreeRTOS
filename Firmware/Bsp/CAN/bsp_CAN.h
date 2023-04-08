#ifndef __BSP_CAN_H__
#define __BSP_CAN_H__

#include "can.h"
#include "main.h"
#include "stdio.h"
#include "usart.h"
#include "applicationVar.h"

static CAN_TxHeaderTypeDef        TxMessage;    //CAN发送的消息的消息头
static CAN_RxHeaderTypeDef        RxMessage;    //CAN接收的消息的消息头

void CAN1_Send(uint32_t CAN_ID, uint8_t *CAN_DATA);

void CANFilter_Config(void);
void CanFilterInit(void);
void uploadCarData();
void keyControlCanSend();
void motec_ECU_decode();
#define Transmitter 0
#define Receiver    1

#define UPLOAD_EVENT (0x01)//设置事件掩码的位 0 
#define GUI_UPDATE_EVENT (0x01 << 1)//设置事件掩码的位 1
#define LED_EVENT (0x01 << 2)//设置事件掩码的位 2
#define MQTT_INIT (0x01 << 3)//设置事件掩码的位 3

#if Transmitter
void carDataUpdate();
void canDataPack();
#endif

#if Receiver
void decodeCanData(uint32_t canID, uint8_t *canData);
#endif

#endif //__BSP_CAN_H__
