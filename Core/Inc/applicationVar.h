#ifndef _APPLICATIONVAR_H_
#define _APPLICATIONVAR_H_

#include "main.h"

struct appStatus_t{
	uint8_t standByStatus; //����ģʽ   1Ϊ����ģʽ
	uint8_t canOpenStatus; //ʵ��ģʽ   1Ϊʵ��ģʽ
	uint8_t simhubStatus;  //ģ����ģʽ 1Ϊģ����ģʽ
	uint8_t initOK_Flag;      //��ʼ��λ   Ĭ��Ϊ0
};


extern struct appStatus_t appStatus;





#endif //_APPLICATIONVAR_H_
