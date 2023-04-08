#include "applicationVar.h"


struct appStatus_t appStatus;


#define  SPEED_RATIO  4 	//主减速比
#define  PI  3.14	       	//圆周率
#define  WHEEL_R  0.2286	   	//车轮半径
#define  NUM_OF_TEETH 20.0    //码盘齿数



uint8_t motec_CanFrame[18][8];
uint8_t carType;//驾驶车辆类型：0.电车 1.油车
uint8_t upSpeedFlag = 1;
uint8_t uploadFlag = 0;  //接收CAN报文上传标志位，只有接收到CAN报文该变量会置1
struct RacingCarData racingCarData;
uint8_t canControlData[8];  //按键控制，CAN报文数组

char RxBuffer1[RXBUFFERSIZE];   //接收数据
char RxBuffer3[RXBUFFERSIZE];   //接收数据
uint8_t aRxBuffer1;   //接收中断缓冲
uint8_t aRxBuffer3;   //接收中断缓冲
char Buffer[RXBUFFERSIZE];
uint8_t Uart1_Rx_Cnt = 0;  //接收缓冲计数
uint8_t Uart3_Rx_Cnt = 0;  //接收缓冲计数
uint8_t okFlag = 0; //是否查询OK字符标志位

uint8_t BC260Y_ConnectFlag = 0;  //BC260Y联网标志位
uint8_t QMOPEN_Flag = 0; //MQTT服务器打开状态位，0未打开，1打开。
uint8_t QMCONN_Flag = 0; //MQTT服务器连接状态位，0未连接，1连接。
uint8_t QMPUBF_Flag = 0; //MQTT消息发布失败位，该位置1则重新连接MQTT服务器
uint8_t MQTTinitOkFlag = 0; //初始化是否OK标志位

struct SH_CarData sh_CarData  ;//__attribute__((section(".CCM_RAM")));