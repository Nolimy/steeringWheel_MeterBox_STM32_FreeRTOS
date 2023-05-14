#ifndef _MQTT_APP_H_
#define _MQTT_APP_H_

#include "main.h"
#include "bsp_BC260Y.h"


uint8_t MQTT_Init();
uint8_t mqttServiceStartup();
void jsonPack();

#endif // _MQTT_APP_H_
