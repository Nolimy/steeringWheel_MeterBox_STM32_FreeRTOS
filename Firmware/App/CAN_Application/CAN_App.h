#ifndef __CAN_APP_H_
#define __CAN_APP_H_

#include "stdio.h"
#include "string.h"
#include "usart.h"
#include "bsp_CAN.h"


#if Transmitter
void carDataUpdate();
void canDataPack();
#endif

#if Receiver
void decodeCanData(uint32_t canID, uint8_t *canData);
#endif

void uploadCarData();
void motec_ECU_decode();
//extern struct RacingCarData racingCarData;



#endif // __CAN_APP_H_

