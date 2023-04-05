#ifndef __MOTEC_ECU_CAN_H__
#define __MOTEC_ECU_CAN_H__

#include "bsp_CAN.h"




#if Transmitter
void carDataUpdate();
void canDataPack();
#endif

#if Receiver
void decodeCanData(uint32_t canID, uint8_t *canData);
#endif

#endif //__MOTEC_ECU_CAN_H__
