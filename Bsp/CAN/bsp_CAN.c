#include "bsp_CAN.h"
#include "string.h"
#include "bsp_BC260Y.h"
#include "ui.h"
#include "cmsis_os2.h"

#define  SPEED_RATIO  4 	//�����ٱ�
#define  PI  3.14	       	//Բ����
#define  WHEEL_R  0.2286	   	//���ְ뾶
#define  NUM_OF_TEETH 20.0    //���̳���


uint8_t upSpeedFlag = 1;
uint8_t uploadFlag = 1;
struct RacingCarData racingCarData;
extern osEventFlagsId_t getCarDataHandle;

void CANFilter_Config(void)//���۷�ɶ�Ҷ��յ�ȫ�ա�
{
    CAN_FilterTypeDef  sFilterConfig;
    
    sFilterConfig.FilterBank = 0;                       //CAN��������ţ���Χ0-27
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;   //CAN������ģʽ������ģʽ���б�ģʽ
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;  //CAN�������߶ȣ�16λ��32λ
    sFilterConfig.FilterIdHigh = 0x000 << 5;			//32λ�£��洢Ҫ����ID�ĸ�16λ
    sFilterConfig.FilterIdLow = 0x0000;					//32λ�£��洢Ҫ����ID�ĵ�16λ
    sFilterConfig.FilterMaskIdHigh = 0x0000;			//����ģʽ�£��洢��������
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = 0;				//����ͨ����������ƥ��󣬴洢���ĸ�FIFO
    sFilterConfig.FilterActivation = ENABLE;    		//���������
    sFilterConfig.SlaveStartFilterBank = 0;
    
    if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK) {
        printf("CAN Filter Config Fail!\r\n");
        Error_Handler();
    }
    printf("CAN Filter Config Success!\r\n");

}

/***���պ���***/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	uint8_t  data[8];
	HAL_StatusTypeDef	status;
	
	if (hcan == &hcan1) {	

		status = HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxMessage, data);

		if (HAL_OK == status){   
			#if Receiver
			decodeCanData(RxMessage.StdId, data);
			
			osEventFlagsSet(getCarDataHandle, 0x07); // 0000 0111
			//lv_event_send(ui_speedMeter, SPEED_CHANGED, NULL);
			uploadFlag = 1;
			#endif
		}
	}
}
void CAN1_Send(uint32_t CAN_ID, uint8_t *CAN_DATA)
{
	//uint8_t data[4] = {0x01, 0x02, 0x03, 0x04};
    
  TxMessage.IDE = CAN_ID_STD;     //����ID����
	TxMessage.StdId = CAN_ID;        //����ID��
  TxMessage.RTR = CAN_RTR_DATA;   //���ô�������֡
	TxMessage.DLC = 8;              //�������ݳ���
    
	if (HAL_CAN_AddTxMessage(&hcan1, &TxMessage, CAN_DATA, (uint32_t*)CAN_TX_MAILBOX0) != HAL_OK) {
        printf("CAN send test data fail!\r\n");
        Error_Handler();
    }
    printf("CAN send test data success!\r\n");
		
}
void CanFilterInit()
{
	usartTxFlag = 1;
	printf("----- CAN Test Board #1 -----\r\n");
	CANFilter_Config();
    
    /* 2. CAN Start */
	if (HAL_CAN_Start(&hcan1) != HAL_OK) {
			printf("CAN Start Fail\r\n");
			Error_Handler();
	}
	printf("CAN Start Success\r\n");
	
	/* 3. Enable CAN RX Interrupt */
	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
			printf("CAN_IT_RX_FIFO0_MSG_PENDING Enable Fail\r\n");
			Error_Handler();
	}
	printf("CAN_IT_RX_FIFO0_MSG_PENDING Enable Success\r\n");
}

/*
struct RacingCarData
{

	//ID:0X193
	uint8_t FrontSpeed;          //ǰ�ֳ��� ��������Ϊ�ο����� 1Byte
	uint8_t PedalTravel;         //����̤�忪��    1Byte
	uint8_t brakeTravel;         //ɲ��̤�忪��    1Byte
	uint8_t carTravel;           //�����ܶ�����    1Byte
	uint16_t l_motor_torque;      //����Ŀ��ת��  2Byte
  uint16_t r_motor_torque;      //�ҵ��Ŀ��ת��  2Byte

	//ID:0X196 
	uint8_t batAlarm;            //��ظ澯  0~4 �޸澯��0 һ���澯��1�������أ� �����澯��2 �����澯��3
	uint8_t batTemp;               //����¶�  0-160  offset:-40
	uint8_t batLevel;            //��ص���  0-100
	uint16_t batVol;              //��ص�ѹ  0-900
	uint8_t gearMode;            //��λ��Ϣ  1Bit
	uint8_t carMode;             //��������ģʽ  1Bit 1:ת��ģʽ 2���ٶ�ģʽ
	//ID:0X191
	uint16_t lmotorSpeed;         //����ת��  2Bit offset -10000rpm �ֱ���:0.5
	//ID:0X192
	uint8_t lmotorTemp;          //�����¶�   1Byte 0~150���϶� offset:-50
	uint8_t mcu1Temp;            //���������1�¶� 1Byte 0~150���϶� offset:-50
	//ID:0X194	
	uint16_t rmotorSpeed;         //�ҵ��ת��  2Bit offset -10000rpm �ֱ���:0.5
	//ID:0X195
	uint8_t rmotorTemp;          //�ҵ���¶�
	uint8_t mcu2Temp;            //���������2�¶�
	
	
};
*/


#if Transmitter
void carDataUpdate()//ģ�������ܶ�����
{
	//ID:0X196
	racingCarData.gearMode = 2; //0:�յ�  1:���� 2��ǰ����
	racingCarData.carMode = 2;//�ٶ�ģʽ
	racingCarData.batTemp = 40;//����¶� 40���϶�
	racingCarData.batLevel = 100;//������ص��� 100%
	racingCarData.batVol = 450;//������ص�ѹ450V
	racingCarData.batAlarm = 0;//�޸澯
	
	//ID:0X191
	if(upSpeedFlag)
	{
		racingCarData.lmotorSpeed+=100;         //����ת��  2Bit offset -10000rpm �ֱ���:0.5
		if(racingCarData.lmotorSpeed == 6000)
			upSpeedFlag = 0;
	}
	else
	{
		racingCarData.lmotorSpeed-=100;
		if(racingCarData.lmotorSpeed == 0)
			upSpeedFlag = 1;
	}
	//ID:0X194
	racingCarData.rmotorSpeed = racingCarData.lmotorSpeed;
	
	//	//ID:0X193
//	uint8_t FrontSpeed;          //ǰ�ֳ��� ��������Ϊ�ο����� 1Byte
//	uint8_t PedalTravel;         //����̤�忪��    1Byte
//	uint8_t brakeTravel;         //ɲ��̤�忪��    1Byte
//	uint8_t carTravel;           //�����ܶ�����    1Byte
//	uint16_t l_motor_torque      //����Ŀ��ת��  2Byte
//  uint16_t r_motor_torque      //�ҵ��Ŀ��ת��  2Byte
	//ID:0X193
	racingCarData.FrontSpeed = (int)(racingCarData.lmotorSpeed/SPEED_RATIO*PI*2*WHEEL_R*3.6/60);  //��ת�ٻ���Ϊ����
	if(upSpeedFlag)
	{
		racingCarData.l_motor_torque = 1000;
		racingCarData.r_motor_torque = racingCarData.l_motor_torque;
		racingCarData.PedalTravel = 100; //����̤�忪��Ϊ100 ����
		racingCarData.brakeTravel = 0;
	}
		
	else
	{
		racingCarData.l_motor_torque = 0;
		racingCarData.r_motor_torque = racingCarData.l_motor_torque;
		racingCarData.PedalTravel =0;
		racingCarData.brakeTravel = 40;
	}
	racingCarData.carTravel+=5;
	
	//ID:0X192
	racingCarData.lmotorTemp = 40; //�����¶�   1Byte 0~150���϶� offset:-50
	racingCarData.mcu1Temp = 40;   //���������1�¶� 1Byte 0~150���϶� offset:-50
	//ID:0X195
	racingCarData.rmotorTemp = 40; //�ҵ���¶�   1Byte 0~150���϶� offset:-50
	racingCarData.mcu2Temp = 40;   //���������2�¶� 1Byte 0~150���϶� offset:-50
	
	canDataPack();
}
//����CANЭ����Ҫ���͵��г�����
void canDataPack()
{
	//ID:0X191
	uint8_t carData[8];
	//	LeftMotorRPM = (CAN_Re_0_M06[0] + CAN_Re_0_M06[1]*256)/2 - 10000;
	carData[0] = ((racingCarData.lmotorSpeed + 10000) * 2) % 256; //ת�� �Ͱ�λ
	carData[1] = ((racingCarData.lmotorSpeed + 10000) * 2) >> 8;  //ת�� �߰�λ
	CAN1_Send(0X191, carData);
	memset(carData,0x00,sizeof(carData)); //�������

	//ID:0X194
	//	LeftMotorRPM = (CAN_Re_0_M06[0] + CAN_Re_0_M06[1]*256)/2 - 10000;
	carData[0] = ((racingCarData.rmotorSpeed + 10000) * 2) % 256; //ת�� �Ͱ�λ
	carData[1] = ((racingCarData.rmotorSpeed + 10000) * 2) >> 8;  //ת�� �߰�λ
	CAN1_Send(0X194, carData);
	memset(carData,0x00,sizeof(carData)); //�������
	
	//ID:0X192      
	carData[0] = racingCarData.lmotorTemp + 50;//�����¶�   1Byte 0~150���϶� offset:-50
	carData[1] = racingCarData.mcu1Temp + 50;  //���������1�¶� 1Byte 0~150���϶� offset:-50
	CAN1_Send(0X192, carData);
	memset(carData,0x00,sizeof(carData)); //�������
	
	//ID:0X195
	carData[0] = racingCarData.rmotorTemp + 50;//�ҵ���¶�   1Byte 0~150���϶� offset:-50
	carData[1] = racingCarData.mcu2Temp + 50;  //����������¶� 1Byte 0~150���϶� offset:-50
	CAN1_Send(0X195, carData);
	memset(carData,0x00,sizeof(carData)); //�������
	        
	//ID:0X196
	carData[0] = racingCarData.batAlarm;//��ظ澯  0~4 �޸澯��0 һ���澯��1�������أ� �����澯��2 �����澯��3
	carData[1] = racingCarData.batTemp + 40;//����¶�  0-160  offset:-40
	carData[2] = racingCarData.batLevel;//��ص���  0-100
	carData[3] = racingCarData.gearMode;//��λ��Ϣ  1Bit
	carData[4] = racingCarData.carMode;//��������ģʽ  1Bit 1:ת��ģʽ 2���ٶ�ģʽ
	carData[6] = racingCarData.batVol * 10 % 256;//��ص�ѹ  0-900 Resolution = 0.1 LSB�ں��λ
	carData[5] = racingCarData.batVol * 10 >> 8;
	CAN1_Send(0X196, carData);
	memset(carData,0x00,sizeof(carData)); //�������
	
	//ID:0X193
	carData[0] = racingCarData.FrontSpeed;
	carData[1] = racingCarData.PedalTravel;
	carData[2] = racingCarData.brakeTravel;
	carData[3] = racingCarData.carTravel;
	carData[4] = racingCarData.l_motor_torque % 256;
	carData[5] = racingCarData.l_motor_torque >> 8;
	carData[6] = racingCarData.r_motor_torque % 256;
	carData[7] = racingCarData.r_motor_torque >> 8;
	CAN1_Send(0X193, carData);
	memset(carData,0x00,sizeof(carData)); //�������
}
#endif

#if Receiver


void decodeCanData(uint32_t canID, uint8_t *canData)
{
	switch(canID)
	{
		case 0x191:
			racingCarData.lmotorSpeed = (canData[0] + canData[1]*256)/2 - 10000;
			break;
		case 0x192:
			racingCarData.lmotorTemp = canData[0] - 50;
			racingCarData.mcu1Temp = canData[1] - 50;
			break;
		case 0x193:
			racingCarData.FrontSpeed = canData[0];
			racingCarData.PedalTravel = canData[1];
			racingCarData.brakeTravel = canData[2];
			racingCarData.carTravel = canData[3];
			racingCarData.l_motor_torque = canData[4] + canData[5] * 256;
			racingCarData.r_motor_torque = canData[6] + canData[7] * 256;
			break;
		case 0x194:
			racingCarData.rmotorSpeed = (canData[0] + canData[1]*256)/2 - 10000;
			break;
		case 0x195:
			racingCarData.rmotorTemp = canData[0] - 50;
			racingCarData.mcu2Temp = canData[1] - 50;
			break;
		case 0x196:
			racingCarData.batAlarm = canData[0];
			racingCarData.batTemp = canData[1] - 40;
			racingCarData.batLevel = canData[2];
			racingCarData.gearMode = canData[3];
			racingCarData.carMode = canData[4];
			racingCarData.batVol = (canData[6] + canData[5] * 256) / 10;
			break;	
	}	
}

void uploadCarData()
{
		if(uploadFlag)
		{
			usartTxFlag = 1;
			//printf("task1\r\n");
			jsonPack();
			uploadFlag = 0;
		}
}
#endif
