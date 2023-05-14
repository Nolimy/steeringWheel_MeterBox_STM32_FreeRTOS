#include "bsp_BC260Y.h"
#include "MQTT_App.h"


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
	
	//   开串口中断
	//HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer1, 1);
  HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer3, 1);
	
	//使能BC260Y
	initFlag = BC260Y_init();
	
	if(initFlag == 1)
	{
		//LED1_Pin
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);  //拉低，亮灯。
		usartTxFlag = 1;
		printf("*********************BC260Y INIT OK*********************\r\n");
		
		initFlag = MQTT_Init();
		if(initFlag == 1)
		{
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);  //拉低，亮灯。
			usartTxFlag = 1;
			printf("*********************MQTT INIT OK*********************\r\n");
			return 1;
		}
		
		else
		{
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);  //拉高，灭灯。
			usartTxFlag = 1;
			printf("*********************MQTT Init Failure!*********************\r\n");
			return 0;
		}	
		//return 1;
	}
	
	else
	{
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);    //拉高，灭灯。
		usartTxFlag = 1;
		printf("*********************BC260Y Init Failure!*********************\r\n");
		return 0;
	}	
	
	
}
//发布消息 QOS = 0
void MQTT_Pubdata(char *json)
{
	char pubStr[300]; 
	char overCh = 0x1a;
	sprintf(pubStr,"AT+QMTPUB=0,0,0,1,\"hello\",%d,\"%s\"\r\n",strlen(json),json);
	usartTxFlag = 2;
	printf("%s",pubStr);//发布主题
	
	usartTxFlag = 1;
	printf("send %s",pubStr);//发布主题
	memset(pubStr,0x00,sizeof(pubStr)); //清空数组
//	HAL_Delay(10);
//	printf("%s\r\n",json);
//	printf("%c", overCh);
}


//FrontSpeed,PedalTravel,batAlarm,MotorSpeed,batTemp,batLevel,gearMode,carMode,time_Count,batVol,carTravel,mcu1Temp,mcu2Temp,breakTravel,lmotorTemp,rmotorTemp,lmotorSpeed,rmotorSpeed,motorTemp


//油车数据
//	uint8_t oilTemp;
//	uint8_t oilPressure;
//	uint8_t throttlePosition;
//	float lowBatVol;
//  uint16_t lambda1;
//	uint8_t ecu_Temp;
//	uint8_t gear;
//  uint8_t engineTemp;
//  uint8_t FrontSpeed
void jsonPack(void)//json打包 分段 heap太小一次性打包不下
{
	
	char json0[] = "{\"cSpeed\": %d,\"Pos\": %d,\"bAlarm\": %d,\"lmSpeed\": %d,\"rmSpeed\": %d,\"bTemp\": %d,\"bLevel\": %d,\"gMode\": %d,\"cMode\": %d,\"lmTorque\":%d,\"rmTorque\":%d,\"batVol\": %d,\"carDistce\": %d,\"mcu1Temp\": %d,\"mcu2Temp\": %d,\"brakeTravel\": %d,\"lmoTemp\": %d,\"rmoTemp\": %d}";
	char t_json[300];
	
	if(racingCarData.lowBatVol < 12.0)
		racingCarData.batAlarm = 1;
	else 
		racingCarData.batAlarm = 0;
	
	//打包数据
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
	memset(t_json,0x00,sizeof(t_json)); //清空数组98
}
