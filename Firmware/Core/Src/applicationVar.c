#include "applicationVar.h"


struct appStatus_t appStatus;


#define  SPEED_RATIO  4 	//�����ٱ�
#define  PI  3.14	       	//Բ����
#define  WHEEL_R  0.2286	   	//���ְ뾶
#define  NUM_OF_TEETH 20.0    //���̳���



uint8_t motec_CanFrame[18][8];
uint8_t carType;//��ʻ�������ͣ�0.�糵 1.�ͳ�
uint8_t upSpeedFlag = 1;
uint8_t uploadFlag = 0;  //����CAN�����ϴ���־λ��ֻ�н��յ�CAN���ĸñ�������1
struct RacingCarData racingCarData;
uint8_t canControlData[8];  //�������ƣ�CAN��������

char RxBuffer1[RXBUFFERSIZE];   //��������
char RxBuffer3[RXBUFFERSIZE];   //��������
uint8_t aRxBuffer1;   //�����жϻ���
uint8_t aRxBuffer3;   //�����жϻ���
char Buffer[RXBUFFERSIZE];
uint8_t Uart1_Rx_Cnt = 0;  //���ջ������
uint8_t Uart3_Rx_Cnt = 0;  //���ջ������
uint8_t okFlag = 0; //�Ƿ��ѯOK�ַ���־λ

uint8_t BC260Y_ConnectFlag = 0;  //BC260Y������־λ
uint8_t QMOPEN_Flag = 0; //MQTT��������״̬λ��0δ�򿪣�1�򿪡�
uint8_t QMCONN_Flag = 0; //MQTT����������״̬λ��0δ���ӣ�1���ӡ�
uint8_t QMPUBF_Flag = 0; //MQTT��Ϣ����ʧ��λ����λ��1����������MQTT������
uint8_t MQTTinitOkFlag = 0; //��ʼ���Ƿ�OK��־λ

struct SH_CarData sh_CarData  ;//__attribute__((section(".CCM_RAM")));