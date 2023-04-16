#include "bsp_CAN.h"
#include "string.h"
#include "bsp_BC260Y.h"
#include "ui.h"
#include "cmsis_os2.h"
#include "applicationVar.h"

#define LY9_VCU  1
#define LY8_M800 0






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

/***�����ж�***/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	uint8_t  RxData[8];
	uint8_t static Counter = 0;  //֡������
	uint8_t i;
	
	HAL_StatusTypeDef	status;
	
	if (hcan == &hcan1) {	

		status = HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxMessage, RxData);

		if (HAL_OK == status){ 
			
			/************�л���ʾģʽ************/
			appStatus.standByStatus = 0; //�رմ���ģʽ
			appStatus.canOpenStatus = 1; //��ʵ��ģʽ
			appStatus.simhubStatus  = 0; //�ر�ģ����ģʽ
	
			
			if(RxMessage.StdId == 0x5F0)
			{
				/************֡����������18�Զ����㣬����Խ��************/
				if(Counter == 18) 
				{
					/************һ�鱨�Ľ�����ϣ����ձ�־λ��0���ȴ���һ�鱨��ͷ����************/
					frameEofFlag = 0;
					
					/************�յ�CAN���ģ�������Ӧ��־λ��FreeRTOS��Ӧ�¼�************/
					osEventFlagsSet(getCarDataHandle, 0x0f); // 0000 1111   //
					
				}
				/************�ж��Ƿ�Ϊ����ͷ�������ǣ������������************/
				if(RxData[4] == 0XFC && RxData[5] == 0XFB && RxData[6] == 0XFA) 
				{
					/************�����������************/
					Counter = 0;
					frameEofFlag = 1; //��ʾ���յ���֡����ͷ������ʱ��ʼ�����µ�һ֡���ġ�
				}					
				
				/************���յ���֡�洢��֡������************/
				if(frameEofFlag && (Counter >= 0 && Counter <=17))
				{
					for(i=0; i<8; i++){
						motec_CanFrame[Counter][i] = RxData[i];
					}
					/************���¼�����************/
					Counter++;
				}		
			}	
			/************��MQTT��ʼ���ɹ���4Gģ�鿪ʼ�����ϱ�************/
			if(MQTTinitOkFlag)
				uploadFlag = 1;				
		}
	}
}
//if(HAL_GPIO_ReadPin(INPUT9_GPIO_Port, INPUT9_Pin) == RESET) 
//if(HAL_GPIO_ReadPin(INPUTA_GPIO_Port, INPUTA_Pin) == RESET) 
void CAN1_Send(uint32_t CAN_ID, uint8_t *CAN_DATA)
{
	//uint8_t data[4] = {0x01, 0x02, 0x03, 0x04};
    
  TxMessage.IDE = CAN_ID_STD;     //����ID����
	TxMessage.StdId = CAN_ID;        //����ID��
  TxMessage.RTR = CAN_RTR_DATA;   //���ô�������֡
	TxMessage.DLC = 8;              //�������ݳ���
    
	if (HAL_CAN_AddTxMessage(&hcan1, &TxMessage, CAN_DATA, (uint32_t*)CAN_TX_MAILBOX0) != HAL_OK) {
        //printf("CAN send test data fail!\r\n");
        Error_Handler();
    }
    //printf("CAN send test data success!\r\n");
		
}
/*10��KEY��Ӧ10Bit���ݣ��ӵ�λ������1*/
void keyControlCanSend()
{
	canControlData[0] = 000;
	canControlData[1] = 0x00;
	if(HAL_GPIO_ReadPin(INPUT1_GPIO_Port, INPUT1_Pin) == RESET) canControlData[0] |= 0x01 << 0; 
	if(HAL_GPIO_ReadPin(INPUT2_GPIO_Port, INPUT2_Pin) == RESET) canControlData[0] |= 0x01 << 1;
	if(HAL_GPIO_ReadPin(INPUT3_GPIO_Port, INPUT3_Pin) == RESET) canControlData[0] |= 0x01 << 2;
	if(HAL_GPIO_ReadPin(INPUT4_GPIO_Port, INPUT4_Pin) == RESET) canControlData[0] |= 0x01 << 3;
	if(HAL_GPIO_ReadPin(INPUT5_GPIO_Port, INPUT5_Pin) == RESET) canControlData[0] |= 0x01 << 4;
	if(HAL_GPIO_ReadPin(INPUT6_GPIO_Port, INPUT6_Pin) == RESET) canControlData[0] |= 0x01 << 5;
	if(HAL_GPIO_ReadPin(INPUT7_GPIO_Port, INPUT7_Pin) == RESET) canControlData[0] |= 0x01 << 6;
	if(HAL_GPIO_ReadPin(INPUT8_GPIO_Port, INPUT8_Pin) == RESET) canControlData[0] |= 0x01 << 7;
	if(HAL_GPIO_ReadPin(INPUT9_GPIO_Port, INPUT9_Pin) == RESET) canControlData[1] |= 0x01 << 0;
	if(HAL_GPIO_ReadPin(INPUTA_GPIO_Port, INPUTA_Pin) == RESET) canControlData[1] |= 0x01 << 1;
	
	CAN1_Send(0X155, canControlData);
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
	racingCarData.gearMode = 2; //0:�յ�  1:���� 2��ǰ����
	racingCarData.carMode = 2;//�ٶ�ģʽ
	racingCarData.batTemp = 40;//����¶� 40���϶�
	racingCarData.batLevel = 100;//������ص��� 100%
	racingCarData.batVol = 450;//������ص�ѹ450V
	racingCarData.batAlarm = 0;//�޸澯
	
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
	racingCarData.rmotorSpeed = racingCarData.lmotorSpeed;
	
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
	
	racingCarData.lmotorTemp = 40; //�����¶�   1Byte 0~150���϶� offset:-50
	racingCarData.mcu1Temp = 40;   //���������1�¶� 1Byte 0~150���϶� offset:-50
	racingCarData.rmotorTemp = 40; //�ҵ���¶�   1Byte 0~150���϶� offset:-50
	racingCarData.mcu2Temp = 40;   //���������2�¶� 1Byte 0~150���϶� offset:-50
	
	canDataPack();
}
//����CANЭ����Ҫ���͵��г�����
void canDataPack()
{
	/****************************ID:0X211****************************/
	carData[0] = racingCarData.FrontSpeed;
	carData[1] = racingCarData.PedalTravel;
	carData[2] = racingCarData.brakeTravel;
	carData[3] = racingCarData.carTravel;
	carData[4] = racingCarData.l_motor_torque % 256;
	carData[5] = racingCarData.l_motor_torque >> 8;
	carData[6] = racingCarData.r_motor_torque % 256;
	carData[7] = racingCarData.r_motor_torque >> 8;
	CAN1_Send(0X211, carData);
	memset(carData,0x00,sizeof(carData)); //�������
	/****************************ID:0X211****************************/
	
	/****************************ID:0X212****************************/
	uint8_t carData[8];
	//	LeftMotorRPM = (CAN_Re_0_M06[0] + CAN_Re_0_M06[1]*256)/2 - 10000;
	carData[0] = ((racingCarData.lmotorSpeed + 10000) * 2) % 256; //ת�� �Ͱ�λ
	carData[1] = ((racingCarData.lmotorSpeed + 10000) * 2) >> 8;  //ת�� �߰�λ
	carData[2] = racingCarData.lmotorTemp + 50;//�����¶�   1Byte 0~150���϶� offset:-50
	carData[3] = racingCarData.mcu1Temp + 50;  //���������1�¶� 1Byte 0~150���϶� offset:-50
	carData[4] = ((racingCarData.rmotorSpeed + 10000) * 2) % 256; //ת�� �Ͱ�λ
	carData[5] = ((racingCarData.rmotorSpeed + 10000) * 2) >> 8;  //ת�� �߰�λ
	carData[6] = racingCarData.rmotorTemp + 50;//�ҵ���¶�   1Byte 0~150���϶� offset:-50
	carData[7] = racingCarData.mcu2Temp + 50;  //����������¶� 1Byte 0~150���϶� offset:-50
	CAN1_Send(0X212, carData);
	memset(carData,0x00,sizeof(carData)); //�������
	/****************************ID:0X212****************************/
	        
	/****************************ID:0X213****************************/
	carData[0] = racingCarData.batAlarm;//��ظ澯  0~4 �޸澯��0 һ���澯��1�������أ� �����澯��2 �����澯��3
	carData[1] = racingCarData.batTemp + 40;//����¶�  0-160  offset:-40
	carData[2] = racingCarData.batLevel;//��ص���  0-100
	carData[3] = racingCarData.gearMode;//��λ��Ϣ  1Bit
	carData[4] = racingCarData.carMode;//��������ģʽ  1Bit 1:ת��ģʽ 2���ٶ�ģʽ
	carData[6] = racingCarData.batVol * 10 % 256;//��ص�ѹ  0-900 Resolution = 0.1 LSB�ں��λ
	carData[5] = racingCarData.batVol * 10 >> 8;
	CAN1_Send(0X213, carData);
	memset(carData,0x00,sizeof(carData)); //�������
	/****************************ID:0X213****************************/
	

}
#endif

#if Receiver
//0X5F0

void motec_ECU_decode()
{
	carType = 1; 
			
			racingCarData.EngOil_temp = (motec_CanFrame[3][6] << 8 | motec_CanFrame[3][7]) / 10;  //�����¶�
			racingCarData.EngOil_presure = (motec_CanFrame[4][0] << 8 | motec_CanFrame[4][1]) / 10;  //����ѹ��
			racingCarData.lmotorSpeed = motec_CanFrame[1][0] << 8 | motec_CanFrame[1][1];   //������ת��
			racingCarData.gearMode = (motec_CanFrame[14][0] << 8 |motec_CanFrame[14][1]);    //��λ
			racingCarData.Throttle_Angel = (motec_CanFrame[1][2] << 8 |motec_CanFrame[1][3]) / 10; //�����ſ���
			switch(racingCarData.gearMode)
			{
				case 0:
					racingCarData.FrontSpeed = 0;
					break;
				case 1:
					racingCarData.FrontSpeed = racingCarData.lmotorSpeed / 2.615 / (36 / 11);
					break;
				case 2:
					racingCarData.FrontSpeed = racingCarData.lmotorSpeed / 1.857 / (36 / 11);
					break;
				case 3:
					racingCarData.FrontSpeed = racingCarData.lmotorSpeed / 1.565 / (36 / 11);
					break;
				case 4:
					racingCarData.FrontSpeed = racingCarData.lmotorSpeed / 1.350 / (36 / 11);
					break;
			}
}

void decodeCanData(uint32_t canID, uint8_t *canData)
{
	
	
	switch(canID)
	{
		case 0x211:
			carType = 0; //�糵
			racingCarData.FrontSpeed = canData[0];
			racingCarData.PedalTravel = canData[1];
			racingCarData.brakeTravel = canData[2];
			racingCarData.carTravel = canData[3];
			racingCarData.l_motor_torque = canData[4] + canData[5] * 256;
			racingCarData.r_motor_torque = canData[6] + canData[7] * 256;
			break;
		
		case 0x212:
			racingCarData.lmotorSpeed = (canData[0] + canData[1]*256)/2 - 10000;
			racingCarData.lmotorTemp = canData[2] - 50;
			racingCarData.mcu1Temp = canData[3] - 50;
      racingCarData.rmotorSpeed = (canData[4] + canData[5]*256)/2 - 10000;
			racingCarData.rmotorTemp = canData[6] - 50;
			racingCarData.mcu2Temp = canData[7] - 50;
			break;
		
		case 0x213:
			racingCarData.batAlarm = canData[0];
			racingCarData.batTemp = canData[1] - 40;
			racingCarData.batLevel = canData[2];
			racingCarData.batVol = (canData[3] + canData[4] * 256) / 10;
			racingCarData.gearMode = canData[5];
			racingCarData.carMode = canData[6];
			break;	
	}	
}
#endif
