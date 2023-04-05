#ifndef _APPLICATIONVAR_H_
#define _APPLICATIONVAR_H_

#include "main.h"


#define RXBUFFERSIZE  16     //最大接收字节数

struct appStatus_t{
	uint8_t standByStatus; //待机模式   1为待机模式
	uint8_t canOpenStatus; //实车模式   1为实车模式
	uint8_t simhubStatus;  //模拟器模式 1为模拟器模式
	uint8_t initOK_Flag;      //初始化位   默认为0
};


struct RacingCarData
{

	//ID:0X211
	uint8_t FrontSpeed;          //前轮车速 在这里作为参考车速 1Byte
	uint8_t PedalTravel;         //油门踏板开度    1Byte
	uint8_t brakeTravel;         //刹车踏板开度    1Byte
	uint8_t carTravel;           //车辆跑动距离    1Byte
	uint16_t l_motor_torque;      //左电机目标转矩  2Byte
  uint16_t r_motor_torque;      //右电机目标转矩  2Byte

	//ID:0X213
	uint8_t batAlarm;            //电池告警  0~4 无告警：0 一级告警：1（最严重） 二级告警：2 三级告警：3
	uint8_t batTemp;               //电池温度  0-160  offset:-40
	uint8_t batLevel;            //电池电量  0-100
	uint16_t batVol;              //电池电压  0-900
	uint8_t gearMode;            //挡位信息  1Bit
	uint8_t carMode;             //车辆运行模式  1Bit 1:转矩模式 2：速度模式

	//ID:0X212
	uint16_t lmotorSpeed;         //左电机转速  2Bit offset -10000rpm 分辨率:0.5
	uint8_t lmotorTemp;          //左电机温度   1Byte 0~150摄氏度 offset:-50
	uint8_t mcu1Temp;            //电机控制器1温度 1Byte 0~150摄氏度 offset:-50
	uint16_t rmotorSpeed;         //右电机转速  2Bit offset -10000rpm 分辨率:0.5
	uint8_t rmotorTemp;          //右电机温度
	uint8_t mcu2Temp;            //电机控制器2温度
	

};

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

struct Motec_Data {
  uint8_t Header1;
  uint8_t Header2;
  uint8_t Header3;
  uint8_t Data_Length;
  uint16_t RPM;
  uint16_t Throttle_Position;
  uint16_t Mainfold_Pressure;
  uint16_t Air_Temperature;
  uint16_t Engine_Temperature;
  uint16_t Lambda1;
  uint16_t Lambda2;
  uint16_t Exhaust_Mainfold_Pressure;
  uint16_t Mass_Air_Flow;
  uint16_t Fuel_Temperature;
  uint16_t Fuel_Pressure;
  uint16_t Oil_Temperature;
  uint16_t Oil_Pressure;
  uint16_t Gear_Voltage;
  uint16_t Knock_Voltage;
  uint16_t Gear_Shift_Force;
  uint16_t Exhaust_Gas_Temp_1;
  uint16_t Exhaust_Gas_Temp_2;
  uint16_t User_Channel_1;
  uint16_t User_Channel_2;
  uint16_t User_Channel_3;
  uint16_t User_Channel_4;
  uint16_t Battery_Volt;
  uint16_t ECU_Temperature;
  uint16_t Speed_1;
  uint16_t Speed_2;
  uint16_t Speed_3;
  uint16_t Speed_4;
  uint16_t Drive_Speed;
  uint16_t Ground_Speed;
  uint16_t Slip;
  uint16_t Aim_Slip;
  uint16_t Launch_RPM;
  uint16_t Lambda_1_Short_term_trim;
  uint16_t Lambda_2_Short_term_trim;
  uint16_t Lambda_1_Long_term_trim;
  uint16_t Lambda_2_Long_term_trim;
  uint16_t Aim_Lambda_1;
  uint16_t Aim_Lambda_2;
  uint16_t Fuel_Cut_Level;
  uint16_t Ignition_Cut_Level;
  uint16_t Ignition_Advance;
  uint16_t Load_Point;
  uint16_t Efficiency_Point;
  uint16_t Fuel_Used;
  uint16_t AUX_1;
  uint16_t AUX_2;
  uint16_t AUX_3;
  uint16_t AUX_4;
  uint16_t AUX_5;
  uint16_t AUX_6;
  uint16_t AUX_7;
  uint16_t AUX_8;
  uint16_t Fuel_Actual_Pulse_Width;
  uint16_t Fuel_Effective_Pulse_Width;
  uint16_t Fuel_Injector_Duty_Cycle;
  uint16_t Gear;
  uint16_t Sync_Position;
  uint16_t Fuel_Comp_1;
  uint16_t Fuel_Comp_2;
  uint16_t DEG_1;
  uint16_t DEG_2;
  uint16_t DEG_3;
  uint16_t DEG_4;
  uint16_t DEG_5;
  uint16_t DEG_6;
  uint16_t DEG_7;
  uint16_t DEG_8;
  uint16_t DEG_9;
  uint16_t DEG_10;
  uint16_t DEG_11;
  uint16_t DEG_12;
  uint16_t DEG_13;
  uint16_t DEG_14;
  uint16_t DEG_15;
  uint16_t DEG_16;
  uint16_t SFG_1;
  uint16_t SFG_2;
  uint16_t SFG_3;
  uint16_t SFG_4;
  uint16_t SFG_5;
  uint16_t SFG_6;
  uint16_t SFG_7;
  uint16_t SFG_8;
  uint8_t CRC_1;
  uint8_t CRC_2;
  uint8_t CRC_3;
  uint8_t CRC_4;
};

union ECU_Data;

extern struct RacingCarData racingCarData;
extern struct appStatus_t appStatus;
extern uint8_t uploadFlag;

extern char RxBuffer1[RXBUFFERSIZE];   //接收数据
extern char RxBuffer3[RXBUFFERSIZE];   //接收数据
extern char Buffer[RXBUFFERSIZE];   //接收数据
extern uint8_t aRxBuffer1;   //接收中断缓冲
extern uint8_t aRxBuffer3;   //接收中断缓冲
extern uint8_t Uart1_Rx_Cnt;  //接收缓冲计数
extern uint8_t Uart3_Rx_Cnt;  //接收缓冲计数
extern uint8_t okFlag;
extern uint8_t MQTTinitOkFlag;


extern uint8_t BC260Y_ConnectFlag;  //BC260Y联网标志位
extern uint8_t QMOPEN_Flag; //MQTT服务器打开状态位，0未打开，1打开。
extern uint8_t QMCONN_Flag; //MQTT服务器连接状态位，0未连接，1连接。
extern uint8_t QMPUBF_Flag; //MQTT消息发布失败位，该位置1则重新连接MQTT服务器

#endif //_APPLICATIONVAR_H_
