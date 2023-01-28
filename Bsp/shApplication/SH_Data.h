#ifndef _SH_DATA_H_
#define _SH_DATA_H_

#include "main.h"
//#include "jansson.h"
	

struct SH_CarData
{
	uint16_t speed;
	uint16_t rpm;
	uint16_t redRpm;
	uint8_t  *Gear;
	uint8_t fuel;
	uint8_t *bLapTime;
	uint8_t *cLapTime;
	uint8_t lap;
	uint8_t brake;
	uint8_t throttle;
	
};


extern struct SH_CarData sh_CarData;
extern uint8_t get_data_flag;
extern uint8_t buf[];
extern uint32_t data_nums;
void json_analysis(char *Buf);
void SH_Set_Data();
#endif // _SH_DATA_H_
