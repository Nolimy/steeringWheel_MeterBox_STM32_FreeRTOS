#ifndef _SH_DATA_H_
#define _SH_DATA_H_

#include "main.h"
//#include "jansson.h"
	

struct SH_CarData
{
	uint16_t speed;
	uint16_t rpm;
	uint8_t  *Gear;
	uint8_t fuel;
	uint8_t lfBrake;
	uint8_t rfBrake;
};


extern struct SH_CarData sh_CarData;
void json_analysis(char *Buf);

#endif // _SH_DATA_H_
