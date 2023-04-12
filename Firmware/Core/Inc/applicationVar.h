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
	
	//Motec
	uint8_t oil_temp;
	uint8_t oil_presure;
	uint8_t EngOil_temp;
	uint8_t EngOil_presure;
	uint8_t Throttle_Angel;
	uint8_t lowBatVol;
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

extern uint8_t m800_ECU_canData[144];
extern uint8_t carType;//��ʻ�������ͣ�0.�糵 1.�ͳ�
extern uint8_t motec_CanFrame[18][8];
extern struct RacingCarData racingCarData;
extern struct appStatus_t appStatus;
extern uint8_t uploadFlag;
extern uint8_t canControlData[8];  //�������ƣ�CAN��������

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
