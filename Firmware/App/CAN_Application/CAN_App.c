#include "CAN_App.h"

extern osEventFlagsId_t getCarDataHandle;

#if Receiver
//0X5F0
//	uint8_t oilTemp;
//	uint8_t oilPressure;
//	uint8_t throttlePosition;
//	float lowBatVol;
//  uint16_t lambda1;
//	uint8_t ecu_Temp;
//	uint8_t gear;
//  uint8_t engineTemp;
//  uint8_t FrontSpeed
void motec_ECU_decode()
{
	carType = 1; 
	
	racingCarData.lmotorSpeed = motec_CanFrame[1][0] << 8 | motec_CanFrame[1][1];   //������ת��
	racingCarData.throttlePosition = (motec_CanFrame[1][2] << 8 |motec_CanFrame[1][3]) / 10; //�����ſ���
	racingCarData.engineTemp = (motec_CanFrame[2][0] << 8 | motec_CanFrame[2][1]) / 10;  //�������¶�
	racingCarData.lambda1 = (motec_CanFrame[2][2] << 8 | motec_CanFrame[2][3]) / 1000;  //���������ź�
	racingCarData.oilTemp = (motec_CanFrame[3][6] << 8 | motec_CanFrame[3][7]) / 10;  //�����¶�
	racingCarData.oilPressure = (motec_CanFrame[4][0] << 8 | motec_CanFrame[4][1]) / 10;  //����ѹ��
	racingCarData.lowBatVol = (motec_CanFrame[6][4] << 8 | motec_CanFrame[6][5]) / 10;  //��ѹ��ص�ѹ
	racingCarData.ecu_Temp = (motec_CanFrame[6][6] << 8 | motec_CanFrame[6][7]) / 10;  //ECU�¶�
	racingCarData.gear = (motec_CanFrame[14][0] << 8 | motec_CanFrame[14][1]);    //��λ
	

	/****************************ͨ���ݱȡ���λ�ͷ�����ת�ٹ�ϵ���㳵��****************************/
	switch(racingCarData.gear)
	{
		case 0:
			racingCarData.FrontSpeed = 0;
			break;
		case 1:
			racingCarData.FrontSpeed = racingCarData.lmotorSpeed * 1.44 * 60 / 1000 / 2.615 / 3.27;
			break;
		case 2:
			racingCarData.FrontSpeed = racingCarData.lmotorSpeed * 1.44 * 60 / 1000 / 1.857 / 3.27;
			break;
		case 3:
			racingCarData.FrontSpeed = racingCarData.lmotorSpeed * 1.44 * 60 / 1000 / 1.565 / 3.27;
			break;
		case 4:
			racingCarData.FrontSpeed = racingCarData.lmotorSpeed * 1.44 * 60 / 1000 / 1.350 / 3.27;
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
				if(Counter == 18 && motec_CanFrame[0][4] == 0XFC && motec_CanFrame[0][5] == 0XFB && motec_CanFrame[0][6] == 0XFA && motec_CanFrame[14][2] == 0x01 && motec_CanFrame[14][3] == 0xf4) 
				{
					/************һ�鱨�Ľ�����ϣ����ձ�־λ��0���ȴ���һ�鱨��ͷ����************/
					frameEofFlag = 0;
					
					/************����CAN����************/
					motec_ECU_decode(); //����������һ��CAN����
					
					/************����************/
					memset(motec_CanFrame, 0x00, sizeof(motec_CanFrame));
					
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
			else if(RxMessage.StdId == 0x211 || RxMessage.StdId == 0x212 || RxMessage.StdId == 0x213)
				decodeCanData(RxMessage.StdId, RxData);
			
			/************�յ�CAN���ģ�������Ӧ��־λ��FreeRTOS��Ӧ�¼�************/
			osEventFlagsSet(getCarDataHandle, 0x0f); // 0000 1111   //
			
			/************��MQTT��ʼ���ɹ���4Gģ�鿪ʼ�����ϱ�************/
			if(MQTTinitOkFlag)
				uploadFlag = 1;				
		}
	}
}

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