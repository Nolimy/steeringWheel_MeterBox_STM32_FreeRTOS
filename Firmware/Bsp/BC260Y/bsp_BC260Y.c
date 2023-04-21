#include "bsp_BC260Y.h"
#include "cmsis_os2.h"

/*ʧ�ܣ� 0  �ɹ� �� 1  */
uint8_t cmdToBC26Y(char *strSource, char *strTarget, uint8_t okCheck)
{
	char *strBuffer;
	uint8_t i = 0;
	memset(Buffer,0x00,sizeof(Buffer)); //�������
	if(okCheck == 0)
	{
		strBuffer = NULL;
		printf("%s\r\n", strSource);
		osDelay(500);
		while(strBuffer == NULL && i<10)
		{
			strBuffer = strstr((const char*)Buffer,(const char*)strTarget);
			usartTxFlag = 1;
			printf("Buffer is %s\r\n",Buffer);
			//printf("strBuffer %s\r\n",strBuffer);
			memset(Buffer,0x00,sizeof(Buffer)); //�������
			usartTxFlag = 2;
			printf("%s\r\n", strSource);
			osDelay(300);
			i++;
			//printf("sending %s\r\n",strSource);		
		}
		if(i >= 5)
		{
			usartTxFlag = 1;
			printf("%s init ERROR \r\n",strSource);
			return 0;
		}
		else
		{
			usartTxFlag = 1;
			printf("%s init OK \r\n",strSource);
			return 1;
		}
	}
	else
	{
		while(okFlag != 1 && i<5)
		{
			usartTxFlag = 2;
			printf("%s\r\n", strSource);
			osDelay(400);
			usartTxFlag = 1;
			printf("sending %s\r\n",strSource);	
			i++;
		}
		if(i >= 5)
		{
			usartTxFlag = 1;
			printf("%s init ERROR \r\n",strSource);
			okFlag = 0;
			return 0;
		}
		else
		{
			usartTxFlag = 1;
			okFlag = 0;
			printf("%s init OK \r\n",strSource);
			return 1;
		}				
	}
}

//��������AT�������η��ͳ�ȥ��Ȼ���ж�buffer��������Ҫ�Ĺؼ��֡�
//return 0:ʧ��  1���ɹ�
uint8_t BC260Y_init()
{
	uint16_t failueCount = 0;
	//4Gģ�鿪��
	HAL_GPIO_WritePin(PWR_4G_GPIO_Port, PWR_4G_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RST_4G_GPIO_Port, RST_4G_Pin, GPIO_PIN_SET);
	osDelay(500);
	HAL_GPIO_WritePin(RST_4G_GPIO_Port, RST_4G_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PWR_4G_GPIO_Port, PWR_4G_Pin, GPIO_PIN_RESET);
	usartTxFlag = 1;
	printf("waiting for connecting.");
	while(!BC260Y_ConnectFlag)//�ȴ�IP����
	{
		printf(".");
		failueCount++;
		if(failueCount > 1000)
		{	
			printf("\n BC260Y Connected Failed!\n");
			
			break;
		}
		osDelay(300);
	}
  //���ݻ���  
	memset(Buffer,0x00,sizeof(Buffer)); //�������
//	cmdToBC26Y("AT+CIMI","460",0);
//	cmdToBC26Y("AT+QSCLK = 0",NULL, 1);
//	cmdToBC26Y("AT+CSQ","CSQ",0);
	return cmdToBC26Y("AT+CIMI","460",0) \
		& cmdToBC26Y("AT+QSCLK = 0",NULL, 1) \
		& cmdToBC26Y("AT+CSQ","CSQ",0); //��0�򷵻�ʧ�� ȫ1��ɹ�
}
//AT+QMTOPEN=0,"82.156.207.102",1883
//AT+QMTCONN=0,"BC260Y","lingyun","lingyun666"
uint8_t MQTT_Init()
{
	usartTxFlag = 2;
	printf("AT+QMTOPEN=0,\"82.156.207.102\",1883\r\n");
	usartTxFlag = 1;
	printf("\n Waiting for the MQTT client Open");
	while(!QMOPEN_Flag)
	{
		printf(".");
		osDelay(200);
	}
	printf("\r\n");
	printf("\nQMTOPEN OK.\r\n");
	osDelay(500);
	
	
	usartTxFlag = 2;
	printf("AT+QMTCONN=0,\"BC260Y\",\"lingyun\",\"lingyun666\"\r\n");
	usartTxFlag = 1;
	printf("\n Waiting for the MQTT client Conncet");
	while(!QMCONN_Flag)
	{
		printf(".");
		osDelay(200);
	}
	printf("\r\n");
	printf("MQTT Conncet OK.\r\n");
//	cmdToBC26Y("AT+QMTCONN=0,\"BC260Y\",\"lingyun\",\"lingyun666\"", "N: 0,0", 0);
	
	return 1;
//	return cmdToBC26Y("AT+QMTOPEN=0,\"82.156.207.102\",1883", "N: 0,0", 0)\
//					& cmdToBC26Y("AT+QMTCONN=0,\"BC260Y\",\"lingyun\",\"lingyun666\"", "N: 0,0", 0)\
//					& cmdToBC26Y("AT+QMTPUB=0,0,0,1,\"hello\",11,\"hello world\"","0,0,0", 0);
}
uint8_t mqttServiceStartup()
{
	uint8_t initFlag;
	
	//   �������ж�
	//HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer1, 1);
  HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer3, 1);
	
	//ʹ��BC260Y
	initFlag = BC260Y_init();
	
	if(initFlag == 1)
	{
		//LED1_Pin
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);  //���ͣ����ơ�
		usartTxFlag = 1;
		printf("*********************BC260Y INIT OK*********************\r\n");
		
		initFlag = MQTT_Init();
		if(initFlag == 1)
		{
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);  //���ͣ����ơ�
			usartTxFlag = 1;
			printf("*********************MQTT INIT OK*********************\r\n");
			return 1;
		}
		
		else
		{
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);  //���ߣ���ơ�
			usartTxFlag = 1;
			printf("*********************MQTT Init Failure!*********************\r\n");
			return 0;
		}	
		//return 1;
	}
	
	else
	{
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);    //���ߣ���ơ�
		usartTxFlag = 1;
		printf("*********************BC260Y Init Failure!*********************\r\n");
		return 0;
	}	
	
	
}
//������Ϣ QOS = 0
void MQTT_Pubdata(char *json)
{
	char pubStr[300]; 
	char overCh = 0x1a;
	sprintf(pubStr,"AT+QMTPUB=0,0,0,1,\"hello\",%d,\"%s\"\r\n",strlen(json),json);
	usartTxFlag = 2;
	printf("%s",pubStr);//��������
	
	usartTxFlag = 1;
	printf("send %s",pubStr);//��������
	memset(pubStr,0x00,sizeof(pubStr)); //�������
//	HAL_Delay(10);
//	printf("%s\r\n",json);
//	printf("%c", overCh);
}
//FrontSpeed,PedalTravel,batAlarm,MotorSpeed,batTemp,batLevel,gearMode,carMode,time_Count,batVol,carTravel,mcu1Temp,mcu2Temp,breakTravel,lmotorTemp,rmotorTemp,lmotorSpeed,rmotorSpeed,motorTemp


//�ͳ�����
//	uint8_t oilTemp;
//	uint8_t oilPressure;
//	uint8_t throttlePosition;
//	float lowBatVol;
//  uint16_t lambda1;
//	uint8_t ecu_Temp;
//	uint8_t gear;
//  uint8_t engineTemp;
//  uint8_t FrontSpeed
void jsonPack(void)//json��� �ֶ� heap̫Сһ���Դ������
{
	
	char json0[] = "{\"cSpeed\": %d,\"Pos\": %d,\"bAlarm\": %d,\"lmSpeed\": %d,\"rmSpeed\": %d,\"bTemp\": %d,\"bLevel\": %d,\"gMode\": %d,\"cMode\": %d,\"lmTorque\":%d,\"rmTorque\":%d,\"batVol\": %.01f,\"carDistce\": %d,\"mcu1Temp\": %d,\"mcu2Temp\": %d,\"brakeTravel\": %d,\"lmoTemp\": %d,\"rmoTemp\": %d}";
	char t_json[300];
	
	if(racingCarData.lowBatVol < 12.0)
		racingCarData.batAlarm = 1;
	else 
		racingCarData.batAlarm = 0;
	
	//�������
	sprintf(t_json, json0, \
	racingCarData.FrontSpeed,\
	racingCarData.throttlePosition, \
	racingCarData.batAlarm, \
	racingCarData.lmotorSpeed, \
	racingCarData.rmotorSpeed, \
	racingCarData.ecu_Temp, \
	racingCarData.batLevel, \
	racingCarData.gear, \
	racingCarData.carMode, \
	racingCarData.l_motor_torque, \
	racingCarData.r_motor_torque, \
	racingCarData.lowBatVol, \
	racingCarData.carTravel, \
	racingCarData.oilTemp, \
	racingCarData.engineTemp, \
	racingCarData.brakeTravel, \
	racingCarData.oilPressure, \
	racingCarData.lambda1);

	
	MQTT_Pubdata(t_json);
	memset(t_json,0x00,sizeof(t_json)); //�������98
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		if(Uart1_Rx_Cnt >= 255)  //����ж�
			{
				Uart1_Rx_Cnt = 0;
				memset(RxBuffer1,0x00,sizeof(RxBuffer1));
				HAL_UART_Transmit(&huart1, (uint8_t *)"stack Over Flow\r\n", 10,0xFFFF);
			}
			else
			{
				RxBuffer1[Uart1_Rx_Cnt++] = aRxBuffer1;   //��������ת��

				if((RxBuffer1[Uart1_Rx_Cnt-1] == 0x0A)&&(RxBuffer1[Uart1_Rx_Cnt-2] == 0x0D)) //�жϽ���λ
				{
					//HAL_UART_Transmit(&huart1, (uint8_t *)&RxBuffer1, Uart1_Rx_Cnt,0xFFFF); //���յ�����Ϣ���ͳ�ȥ
					HAL_UART_Transmit(&huart3, (uint8_t *)&RxBuffer1, Uart1_Rx_Cnt,0xFFFF); //���յ�����Ϣ���ͳ�ȥ
		      //while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//���UART���ͽ���
					while(HAL_UART_GetState(&huart3) == HAL_UART_STATE_BUSY_TX);//���UART���ͽ���
					Uart1_Rx_Cnt = 0;
					memset(RxBuffer1,0x00,sizeof(RxBuffer1)); //�������
				}
			}

			HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer1, 1);   //�ٿ��������ж�

	}
	if(huart->Instance == USART3)
	{
			//if(Uart3RxOverFlag == 0)
			{
				if(Uart3_Rx_Cnt >= 255)  //����ж�
				{
					Uart3_Rx_Cnt = 0;
					memset(RxBuffer3,0x00,sizeof(RxBuffer3));
					HAL_UART_Transmit(&huart3, (uint8_t *)"stack Over Flow\r\n", 10,0xFFFF);
				}
				else
				{
					RxBuffer3[Uart3_Rx_Cnt++] = aRxBuffer3;   //��������ת��
					if((RxBuffer3[Uart3_Rx_Cnt-1] == 0x0A)&&(RxBuffer3[Uart3_Rx_Cnt-2] == 0x0D)&&Uart3_Rx_Cnt!=2) //�жϽ���λ\r\n
					{
						if(strcmp((const char*)RxBuffer3,(const char*)"\r\n") == 0 ||strcmp((const char*)RxBuffer3,(const char*)" ") == 0 || strlen(RxBuffer3) == 0)
						{
							//������Ч�ַ���
							memset(RxBuffer3,0x00,sizeof(RxBuffer3)); //�������
							HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer3, 1);   //�ٿ��������ж�
						}
						if(strstr((const char*)RxBuffer3, (const char*)"IP")) //�ж��Ƿ�����
						{
							BC260Y_ConnectFlag = 1;
							memset(RxBuffer3,0x00,sizeof(RxBuffer3)); //�������
							HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer3, 1);   //�ٿ��������ж�
						}
						
						if(strstr((const char*)RxBuffer3, (const char*)"OPEN: 0,0")) //�ж�MQTT�������Ƿ��
						{
							QMOPEN_Flag = 1;
							memset(RxBuffer3,0x00,sizeof(RxBuffer3)); //�������
							HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer3, 1);   //�ٿ��������ж�
						}
						
						if(strstr((const char*)RxBuffer3, (const char*)"CONN")) ////�ж�MQTT�������Ƿ�����
						{
							QMCONN_Flag = 1;
							memset(RxBuffer3,0x00,sizeof(RxBuffer3)); //�������
							HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer3, 1);   //�ٿ��������ж�
						}
						
						if(strstr((const char*)RxBuffer3, (const char*)"T: 0,6")) ////�ж��Ƿ�����Ϣ����ʧ��
						{
							QMPUBF_Flag = 1;
							QMCONN_Flag = 0;
							QMOPEN_Flag = 0;
							memset(RxBuffer3,0x00,sizeof(RxBuffer3)); //�������
							HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer3, 1);   //�ٿ��������ж�
						}
						
						if(strstr((const char*)RxBuffer3, (const char*)"OK"))	
						{
							okFlag = 1;
							memset(RxBuffer3,0x00,sizeof(RxBuffer3)); //�������
							HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer3, 1);   //�ٿ��������ж�
						}
						if(RxBuffer3[0] == 0x0D && RxBuffer3[1] == 0x0A)
						{
							RxBuffer3[0] = '-';
							RxBuffer3[1] = '-';
							strcpy(Buffer, RxBuffer3);
						}
						//HAL_UART_Transmit(&huart1, (uint8_t *)&RxBuffer3, Uart3_Rx_Cnt,0xFFFF); //���յ�����Ϣ���ͳ�ȥ
						//			while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//���UART���ͽ���
						Uart3_Rx_Cnt = 0;
						//memset(RxBuffer3,0x00,sizeof(RxBuffer3)); //�������
					}
				}
			HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer3, 1);   //�ٿ��������ж�
		}

		
	}
}

