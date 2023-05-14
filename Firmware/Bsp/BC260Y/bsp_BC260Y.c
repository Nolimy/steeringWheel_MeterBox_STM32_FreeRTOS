#include "bsp_BC260Y.h"


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

