#ifndef __BSP_BC260Y_H__
#define __BSP_BC260Y_H__

#include "stdio.h"
#include "string.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_CAN.h"

#define RXBUFFERSIZE  256     //�������ֽ���

extern char RxBuffer1[RXBUFFERSIZE];   //��������
extern char RxBuffer3[RXBUFFERSIZE];   //��������
extern char Buffer[RXBUFFERSIZE];   //��������
extern uint8_t aRxBuffer1;   //�����жϻ���
extern uint8_t aRxBuffer3;   //�����жϻ���
extern uint8_t Uart1_Rx_Cnt;  //���ջ������
extern uint8_t Uart3_Rx_Cnt;  //���ջ������
extern uint8_t okFlag;
extern uint8_t MQTTinitOkFlag;

extern struct RacingCarData racingCarData;

uint8_t BC260Y_init();
uint8_t MQTT_Init();
uint8_t mqttServiceStartup();
void jsonPack();

#endif //__BSP_BC260Y_H__

