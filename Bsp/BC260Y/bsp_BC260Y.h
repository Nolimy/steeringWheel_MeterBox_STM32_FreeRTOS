#ifndef __BSP_BC260Y_H__
#define __BSP_BC260Y_H__

#include "stdio.h"
#include "string.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_CAN.h"

#define RXBUFFERSIZE  256     //最大接收字节数

extern char RxBuffer1[RXBUFFERSIZE];   //接收数据
extern char RxBuffer3[RXBUFFERSIZE];   //接收数据
extern char Buffer[RXBUFFERSIZE];   //接收数据
extern uint8_t aRxBuffer1;   //接收中断缓冲
extern uint8_t aRxBuffer3;   //接收中断缓冲
extern uint8_t Uart1_Rx_Cnt;  //接收缓冲计数
extern uint8_t Uart3_Rx_Cnt;  //接收缓冲计数
extern uint8_t okFlag;
extern uint8_t MQTTinitOkFlag;

extern struct RacingCarData racingCarData;

uint8_t BC260Y_init();
uint8_t MQTT_Init();
uint8_t mqttServiceStartup();
void jsonPack();

#endif //__BSP_BC260Y_H__

