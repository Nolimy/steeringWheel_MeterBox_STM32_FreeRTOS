#ifndef _APPLICATIONVAR_H_
#define _APPLICATIONVAR_H_

#include "main.h"

struct appStatus_t{
	uint8_t standByStatus; //待机模式   1为待机模式
	uint8_t canOpenStatus; //实车模式   1为实车模式
	uint8_t simhubStatus;  //模拟器模式 1为模拟器模式
	uint8_t initOK_Flag;      //初始化位   默认为0
};


extern struct appStatus_t appStatus;





#endif //_APPLICATIONVAR_H_
