#include "applicationVar.h"


struct appStatus_t appStatus;


#define  SPEED_RATIO  4 	//�����ٱ�
#define  PI  3.14	       	//Բ����
#define  WHEEL_R  0.2286	   	//���ְ뾶
#define  NUM_OF_TEETH 20.0    //���̳���


uint8_t upSpeedFlag = 1;
uint8_t uploadFlag = 1;
struct RacingCarData racingCarData;

char RxBuffer1[RXBUFFERSIZE];   //��������
char RxBuffer3[RXBUFFERSIZE];   //��������
uint8_t aRxBuffer1;   //�����жϻ���
uint8_t aRxBuffer3;   //�����жϻ���
char Buffer[RXBUFFERSIZE];
uint8_t Uart1_Rx_Cnt = 0;  //���ջ������
uint8_t Uart3_Rx_Cnt = 0;  //���ջ������
uint8_t okFlag = 0; //�Ƿ��ѯOK�ַ���־λ
uint8_t MQTTinitOkFlag = 0; //��ʼ���Ƿ�OK��־λ


struct SH_CarData sh_CarData  ;//__attribute__((section(".CCM_RAM")));