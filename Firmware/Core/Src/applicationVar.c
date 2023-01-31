#include "applicationVar.h"


struct appStatus_t appStatus;


#define  SPEED_RATIO  4 	//主减速比
#define  PI  3.14	       	//圆周率
#define  WHEEL_R  0.2286	   	//车轮半径
#define  NUM_OF_TEETH 20.0    //码盘齿数


uint8_t upSpeedFlag = 1;
uint8_t uploadFlag = 1;
struct RacingCarData racingCarData;

char RxBuffer1[RXBUFFERSIZE];   //接收数据
char RxBuffer3[RXBUFFERSIZE];   //接收数据
uint8_t aRxBuffer1;   //接收中断缓冲
uint8_t aRxBuffer3;   //接收中断缓冲
char Buffer[RXBUFFERSIZE];
uint8_t Uart1_Rx_Cnt = 0;  //接收缓冲计数
uint8_t Uart3_Rx_Cnt = 0;  //接收缓冲计数
uint8_t okFlag = 0; //是否查询OK字符标志位
uint8_t MQTTinitOkFlag = 0; //初始化是否OK标志位


struct SH_CarData sh_CarData  ;//__attribute__((section(".CCM_RAM")));