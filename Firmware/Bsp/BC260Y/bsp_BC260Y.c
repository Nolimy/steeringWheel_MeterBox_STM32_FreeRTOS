#include "bsp_BC260Y.h"


/*失败： 0  成功 ： 1  */
uint8_t cmdToBC26Y(char *strSource, char *strTarget, uint8_t okCheck)
{
	char *strBuffer;
	uint8_t i = 0;
	memset(Buffer,0x00,sizeof(Buffer)); //清空数组
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
			memset(Buffer,0x00,sizeof(Buffer)); //清空数组
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

//方法：将AT命令依次发送出去，然后判断buffer里有无需要的关键字。
//return 0:失败  1：成功
uint8_t BC260Y_init()
{
	uint16_t failueCount = 0;
	//4G模块开机
	HAL_GPIO_WritePin(PWR_4G_GPIO_Port, PWR_4G_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RST_4G_GPIO_Port, RST_4G_Pin, GPIO_PIN_SET);
	osDelay(500);
	HAL_GPIO_WritePin(RST_4G_GPIO_Port, RST_4G_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PWR_4G_GPIO_Port, PWR_4G_Pin, GPIO_PIN_RESET);
	usartTxFlag = 1;
	printf("waiting for connecting.");
	while(!BC260Y_ConnectFlag)//等待IP连接
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
  //数据缓冲  
	memset(Buffer,0x00,sizeof(Buffer)); //清空数组
//	cmdToBC26Y("AT+CIMI","460",0);
//	cmdToBC26Y("AT+QSCLK = 0",NULL, 1);
//	cmdToBC26Y("AT+CSQ","CSQ",0);
	return cmdToBC26Y("AT+CIMI","460",0) \
		& cmdToBC26Y("AT+QSCLK = 0",NULL, 1) \
		& cmdToBC26Y("AT+CSQ","CSQ",0); //有0则返回失败 全1则成功
}
//AT+QMTOPEN=0,"82.156.207.102",1883
//AT+QMTCONN=0,"BC260Y","lingyun","lingyun666"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		if(Uart1_Rx_Cnt >= 255)  //溢出判断
			{
				Uart1_Rx_Cnt = 0;
				memset(RxBuffer1,0x00,sizeof(RxBuffer1));
				HAL_UART_Transmit(&huart1, (uint8_t *)"stack Over Flow\r\n", 10,0xFFFF);
			}
			else
			{
				RxBuffer1[Uart1_Rx_Cnt++] = aRxBuffer1;   //接收数据转存

				if((RxBuffer1[Uart1_Rx_Cnt-1] == 0x0A)&&(RxBuffer1[Uart1_Rx_Cnt-2] == 0x0D)) //判断结束位
				{
					//HAL_UART_Transmit(&huart1, (uint8_t *)&RxBuffer1, Uart1_Rx_Cnt,0xFFFF); //将收到的信息发送出去
					HAL_UART_Transmit(&huart3, (uint8_t *)&RxBuffer1, Uart1_Rx_Cnt,0xFFFF); //将收到的信息发送出去
		      //while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//检测UART发送结束
					while(HAL_UART_GetState(&huart3) == HAL_UART_STATE_BUSY_TX);//检测UART发送结束
					Uart1_Rx_Cnt = 0;
					memset(RxBuffer1,0x00,sizeof(RxBuffer1)); //清空数组
				}
			}

			HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer1, 1);   //再开启接收中断

	}
	if(huart->Instance == USART3)
	{
			//if(Uart3RxOverFlag == 0)
			{
				if(Uart3_Rx_Cnt >= 255)  //溢出判断
				{
					Uart3_Rx_Cnt = 0;
					memset(RxBuffer3,0x00,sizeof(RxBuffer3));
					HAL_UART_Transmit(&huart3, (uint8_t *)"stack Over Flow\r\n", 10,0xFFFF);
				}
				else
				{
					RxBuffer3[Uart3_Rx_Cnt++] = aRxBuffer3;   //接收数据转存
					if((RxBuffer3[Uart3_Rx_Cnt-1] == 0x0A)&&(RxBuffer3[Uart3_Rx_Cnt-2] == 0x0D)&&Uart3_Rx_Cnt!=2) //判断结束位\r\n
					{
						if(strcmp((const char*)RxBuffer3,(const char*)"\r\n") == 0 ||strcmp((const char*)RxBuffer3,(const char*)" ") == 0 || strlen(RxBuffer3) == 0)
						{
							//过滤无效字符串
							memset(RxBuffer3,0x00,sizeof(RxBuffer3)); //清空数组
							HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer3, 1);   //再开启接收中断
						}
						if(strstr((const char*)RxBuffer3, (const char*)"IP")) //判断是否有网
						{
							BC260Y_ConnectFlag = 1;
							memset(RxBuffer3,0x00,sizeof(RxBuffer3)); //清空数组
							HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer3, 1);   //再开启接收中断
						}
						
						if(strstr((const char*)RxBuffer3, (const char*)"OPEN: 0,0")) //判断MQTT服务器是否打开
						{
							QMOPEN_Flag = 1;
							memset(RxBuffer3,0x00,sizeof(RxBuffer3)); //清空数组
							HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer3, 1);   //再开启接收中断
						}
						
						if(strstr((const char*)RxBuffer3, (const char*)"CONN")) ////判断MQTT服务器是否连接
						{
							QMCONN_Flag = 1;
							memset(RxBuffer3,0x00,sizeof(RxBuffer3)); //清空数组
							HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer3, 1);   //再开启接收中断
						}
						
						if(strstr((const char*)RxBuffer3, (const char*)"T: 0,6")) ////判断是否有消息发布失败
						{
							QMPUBF_Flag = 1;
							QMCONN_Flag = 0;
							QMOPEN_Flag = 0;
							memset(RxBuffer3,0x00,sizeof(RxBuffer3)); //清空数组
							HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer3, 1);   //再开启接收中断
						}
						
						if(strstr((const char*)RxBuffer3, (const char*)"OK"))	
						{
							okFlag = 1;
							memset(RxBuffer3,0x00,sizeof(RxBuffer3)); //清空数组
							HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer3, 1);   //再开启接收中断
						}
						if(RxBuffer3[0] == 0x0D && RxBuffer3[1] == 0x0A)
						{
							RxBuffer3[0] = '-';
							RxBuffer3[1] = '-';
							strcpy(Buffer, RxBuffer3);
						}
						//HAL_UART_Transmit(&huart1, (uint8_t *)&RxBuffer3, Uart3_Rx_Cnt,0xFFFF); //将收到的信息发送出去
						//			while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//检测UART发送结束
						Uart3_Rx_Cnt = 0;
						//memset(RxBuffer3,0x00,sizeof(RxBuffer3)); //清空数组
					}
				}
			HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer3, 1);   //再开启接收中断
		}

		
	}
}

