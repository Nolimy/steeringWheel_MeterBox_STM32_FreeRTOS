#ifndef __BSP_BC260Y_H__
#define __BSP_BC260Y_H__

#include "stdio.h"
#include "string.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_CAN.h"
#include "applicationVar.h"





//extern struct RacingCarData racingCarData;

uint8_t BC260Y_init();
uint8_t MQTT_Init();
uint8_t mqttServiceStartup();
void jsonPack();

#endif //__BSP_BC260Y_H__

