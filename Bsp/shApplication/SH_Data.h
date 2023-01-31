#ifndef _SH_DATA_H_
#define _SH_DATA_H_

#include "main.h"
//#include "jansson.h"
	



extern struct SH_CarData sh_CarData;
extern uint8_t get_data_flag;
extern uint8_t buf[];
extern uint32_t data_nums;
void json_analysis(char *Buf);
void SH_Set_Data();
#endif // _SH_DATA_H_
