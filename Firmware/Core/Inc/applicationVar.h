#ifndef _APPLICATIONVAR_H_
#define _APPLICATIONVAR_H_

#include "main.h"


#define RXBUFFERSIZE  16     //�������ֽ���

struct appStatus_t{
	uint8_t standByStatus; //����ģʽ   1Ϊ����ģʽ
	uint8_t canOpenStatus; //ʵ��ģʽ   1Ϊʵ��ģʽ
	uint8_t simhubStatus;  //ģ����ģʽ 1Ϊģ����ģʽ
	uint8_t initOK_Flag;      //��ʼ��λ   Ĭ��Ϊ0
};


struct RacingCarData
{

	//ID:0X211
	uint8_t FrontSpeed;          //ǰ�ֳ��� ��������Ϊ�ο����� 1Byte
	uint8_t PedalTravel;         //����̤�忪��    1Byte
	uint8_t brakeTravel;         //ɲ��̤�忪��    1Byte
	uint8_t carTravel;           //�����ܶ�����    1Byte
	uint16_t l_motor_torque;      //����Ŀ��ת��  2Byte
  uint16_t r_motor_torque;      //�ҵ��Ŀ��ת��  2Byte

	//ID:0X213
	uint8_t batAlarm;            //��ظ澯  0~4 �޸澯��0 һ���澯��1�������أ� �����澯��2 �����澯��3
	uint8_t batTemp;               //����¶�  0-160  offset:-40
	uint8_t batLevel;            //��ص���  0-100
	uint16_t batVol;              //��ص�ѹ  0-900
	uint8_t gearMode;            //��λ��Ϣ  1Bit
	uint8_t carMode;             //��������ģʽ  1Bit 1:ת��ģʽ 2���ٶ�ģʽ

	//ID:0X212
	uint16_t lmotorSpeed;         //����ת��  2Bit offset -10000rpm �ֱ���:0.5
	uint8_t lmotorTemp;          //�����¶�   1Byte 0~150���϶� offset:-50
	uint8_t mcu1Temp;            //���������1�¶� 1Byte 0~150���϶� offset:-50
	uint16_t rmotorSpeed;         //�ҵ��ת��  2Bit offset -10000rpm �ֱ���:0.5
	uint8_t rmotorTemp;          //�ҵ���¶�
	uint8_t mcu2Temp;            //���������2�¶�
	

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

extern char RxBuffer1[RXBUFFERSIZE];   //��������
extern char RxBuffer3[RXBUFFERSIZE];   //��������
extern char Buffer[RXBUFFERSIZE];   //��������
extern uint8_t aRxBuffer1;   //�����жϻ���
extern uint8_t aRxBuffer3;   //�����жϻ���
extern uint8_t Uart1_Rx_Cnt;  //���ջ������
extern uint8_t Uart3_Rx_Cnt;  //���ջ������
extern uint8_t okFlag;
extern uint8_t MQTTinitOkFlag;


extern uint8_t BC260Y_ConnectFlag;  //BC260Y������־λ
extern uint8_t QMOPEN_Flag; //MQTT��������״̬λ��0δ�򿪣�1�򿪡�
extern uint8_t QMCONN_Flag; //MQTT����������״̬λ��0δ���ӣ�1���ӡ�
extern uint8_t QMPUBF_Flag; //MQTT��Ϣ����ʧ��λ����λ��1����������MQTT������

#endif //_APPLICATIONVAR_H_
