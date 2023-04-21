/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "bsp_LCD.h"
#include "bsp_BC260Y.h"
//#include "bsp_WS2812B.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "ui.h" 
#include "tim.h"
#include "bsp_WS2812B.h"
#include "SH_Data.h"
#include "usbd_cdc_acm_if.h"
#include "usb_device.h"
#include "Bsp_USB_Composite.h"
#include "applicationVar.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
void uploadCarData()
{
		uint16_t failureCount = 0;
		if(QMPUBF_Flag) //�ϴ�����ʧ�ܣ����������ӷ�����
		{
			usartTxFlag = 1;
			printf("\r\n **********Message Publish Failed!Reconnceting the client.!**********\r\n");
			
			
			osDelay(500);
			memset(RxBuffer3,0x00,sizeof(RxBuffer3)); //�������
			usartTxFlag = 2;
			printf("AT+QMTOPEN=0,\"82.156.207.102\",1883\r\n");
			usartTxFlag = 1;
			printf("\n Waiting for the MQTT client Open");
			while(!QMOPEN_Flag)
			{
				printf(".");
				failureCount++;
				osDelay(200);
				if(failureCount > 30)  //��ʱ��ȴ���һ������
					return;
			}
			printf("\r\n");
			printf("\nQMTOPEN OK.\r\n");
			failureCount = 0;
			osDelay(500);
			
			memset(RxBuffer3,0x00,sizeof(RxBuffer3)); //�������
			usartTxFlag = 2;
			printf("AT+QMTCONN=0,\"BC260Y\",\"lingyun\",\"lingyun666\"\r\n");
			usartTxFlag = 1;
			printf("\n Waiting for the MQTT client Conncet");
			while(!QMCONN_Flag)
			{
				printf(".");
				failureCount++;
				osDelay(200);
				if(failureCount > 60) //��ʱ��ȴ���һ������
					return;
			}
			printf("\r\n");
			printf("MQTT Conncet OK.\r\n");
			failureCount = 0;
			osDelay(500);
			
			QMPUBF_Flag = 0;
		}
		else  //��������ʱ�ϴ�0
		{
			if(uploadFlag)
				jsonPack();
			uploadFlag = 0;
		}
}
/* USER CODE END Variables */
/* Definitions for iotUploadTask */
osThreadId_t iotUploadTaskHandle;
const osThreadAttr_t iotUploadTask_attributes = {
  .name = "iotUploadTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for LVGL_Task */
osThreadId_t LVGL_TaskHandle;
const osThreadAttr_t LVGL_Task_attributes = {
  .name = "LVGL_Task",
  .stack_size = 512 * 18,
  .priority = (osPriority_t) osPriorityRealtime2,
};
/* Definitions for LVGL_Meter */
osThreadId_t LVGL_MeterHandle;
const osThreadAttr_t LVGL_Meter_attributes = {
  .name = "LVGL_Meter",
  .stack_size = 512 * 8,
  .priority = (osPriority_t) osPriorityRealtime1,
};
/* Definitions for LVGL_Lap_Timer */
osThreadId_t LVGL_Lap_TimerHandle;
const osThreadAttr_t LVGL_Lap_Timer_attributes = {
  .name = "LVGL_Lap_Timer",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime1,
};
/* Definitions for BC260Y_init */
osThreadId_t BC260Y_initHandle;
const osThreadAttr_t BC260Y_init_attributes = {
  .name = "BC260Y_init",
  .stack_size = 512 * 8,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for RPM_LED_Task */
osThreadId_t RPM_LED_TaskHandle;
const osThreadAttr_t RPM_LED_Task_attributes = {
  .name = "RPM_LED_Task",
  .stack_size = 128 * 8,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for lvgl_mutex */
osMutexId_t lvgl_mutexHandle;
const osMutexAttr_t lvgl_mutex_attributes = {
  .name = "lvgl_mutex"
};
/* Definitions for getCarData */
osEventFlagsId_t getCarDataHandle;
const osEventFlagsAttr_t getCarData_attributes = {
  .name = "getCarData"
};
/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern struct SH_CarData sh_CarData;
/* USER CODE END FunctionPrototypes */

void Start_IotUploadTask(void *argument);
void Start_LVGL_Task(void *argument);
void Start_LVGL_Meter(void *argument);
void Start_LVGL_Lap_Timer(void *argument);
void Start_BC260Y_init(void *argument);
void Start_RPM_LED(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	
	lvgl_mutexHandle = osMutexNew(&lvgl_mutex_attributes);
	
	LVGL_TaskHandle = osThreadNew(Start_LVGL_Task, NULL, &LVGL_Task_attributes);
	
	LVGL_MeterHandle = osThreadNew(Start_LVGL_Meter, NULL, &LVGL_Meter_attributes);
	
	LVGL_Lap_TimerHandle = osThreadNew(Start_LVGL_Lap_Timer, NULL, &LVGL_Lap_Timer_attributes);	
	
	BC260Y_initHandle = osThreadNew(Start_BC260Y_init, NULL, &BC260Y_init_attributes);
	
	RPM_LED_TaskHandle = osThreadNew(Start_RPM_LED, NULL, &RPM_LED_Task_attributes);
	
	getCarDataHandle = osEventFlagsNew(&getCarData_attributes);
  /* USER CODE END Init */
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/**
  * @}
  */

/**
  * @}
  */
}

/* USER CODE BEGIN Header_Start_IotUploadTask */
/**
  * @brief  Function implementing the iotUploadTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Start_IotUploadTask */
void Start_IotUploadTask(void *argument)
{
  /* USER CODE BEGIN Start_IotUploadTask */
	uint32_t r_event;
  /* Infinite loop */
  for(;;)
  {
		r_event = osEventFlagsWait(getCarDataHandle,             /* �¼������� */ 
                              UPLOAD_EVENT,    /* �����������Ȥ���¼� */ 
                              osFlagsWaitAll,           /* �˳�ʱ����¼�λ��ͬʱ�������Ȥ�������¼� */ 
                              osWaitForever);           /* ָ����ʱ�¼�,һֱ�� */ 
		//������̺�ɾ������ʼ��MQTT�Ľ���
		osThreadTerminate(BC260Y_initHandle);
		
		if(r_event)
		{
			//osMutexWait(lvgl_mutexHandle,     /* ��������� */ 
       //                   osWaitForever); 
			//5fps
			uploadCarData();
			
			//osMutexRelease(lvgl_mutexHandle);
		}
			
    osDelay(200);
  }
  /* USER CODE END Start_IotUploadTask */
}

/* USER CODE BEGIN Header_Start_LVGL_Task */
/**
* @brief Function implementing the LVGL_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_LVGL_Task */
void Start_LVGL_Task(void *argument)
{
  /* USER CODE BEGIN Start_LVGL_Task */
	/* init code for USB_DEVICE */
	MX_CAN1_Init();
	HAL_TIM_Base_Start_IT(&htim3);	
	CanFilterInit();
	MX_USB_DEVICE_Init();
	appStatus.initOK_Flag = 0;
	appStatus.standByStatus = 1; //�򿪴���ģʽ
	appStatus.canOpenStatus = 0; //�ر�ʵ��ģʽ
	appStatus.simhubStatus  = 0; //�ر�ģ����ģʽ	
	ws2812_blue(12);//RGB
  /* Infinite loop */
  for(;;)
  {
		
		osMutexWait(lvgl_mutexHandle,     /* ��������� */ 
                          osWaitForever); 
		
		
		if(barFlag == 1)
		{
			sendEventCode();	
		}
		/*************ģ����ģʽ���USB����������**************/
		if(appStatus.simhubStatus)
			USB_ControlData_Send();	
		
		//json_analysis((char *)pRx);
		lv_task_handler(); // lvgl��������	
		
		osMutexRelease(lvgl_mutexHandle);
    osDelay(1);
  }
  /* USER CODE END Start_LVGL_Task */
}

/* USER CODE BEGIN Header_Start_LVGL_Meter */
/**
* @brief Function implementing the LVGL_Meter thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_LVGL_Meter */
void Start_LVGL_Meter(void *argument)
{
  /* USER CODE BEGIN Start_LVGL_Meter */
	
  uint32_t r_event;
  /* Infinite loop */
  for(;;)
  {
		r_event = osEventFlagsWait(getCarDataHandle,             /* �¼������� */ 
                              GUI_UPDATE_EVENT,    					/* �����������Ȥ���¼� */ 
                              osFlagsWaitAll,           /* �˳�ʱ����¼�λ��ͬʱ�������Ȥ�������¼� */ 
                              osWaitForever);           /* ָ����ʱ�¼�,һֱ�� */ 
		//��ȡ�¼���״̬
		
		if(r_event)
		//���½�����ʾ
		{
			osMutexWait(lvgl_mutexHandle,     /* ��������� */ 
                          osWaitForever); 
			if(appStatus.canOpenStatus)
			{
				/*************ʵ��ģʽ������������CAN���ķ��ͺ���**************/
				if(appStatus.canOpenStatus)
				{
					keyControlCanSend();
					
				}
				appStatus.simhubStatus = 0;
				meterAnimation();
				if(carType == 0) //�糵
				{
					lv_label_set_text_fmt(ui_speedNum, "%03d", racingCarData.FrontSpeed);
					lv_label_set_text_fmt(ui_rpmNum, "%04d", racingCarData.rmotorSpeed);
					lv_label_set_text_fmt(ui_batTemp, "%03d", racingCarData.batVol);
					lv_label_set_text_fmt(ui_lMotorTemp, "%02d", racingCarData.lmotorTemp);
					lv_label_set_text_fmt(ui_rMotorTemp, "%02d", racingCarData.rmotorTemp);
					
					lv_bar_set_value(ui_socValue, racingCarData.batLevel, LV_ANIM_ON);
					if(racingCarData.gearMode == 0)
						lv_label_set_text(ui_gearLable, "N");
					else if(racingCarData.gearMode == 1)
						lv_label_set_text(ui_gearLable, "R");
					else
						lv_label_set_text(ui_gearLable, "D");
					if(racingCarData.carMode == 0)
					{
						lv_obj_set_style_text_color(ui_speedMode, lv_color_hex(0x6464F1), LV_PART_MAIN | LV_STATE_DEFAULT);
						lv_obj_set_style_text_opa(ui_speedMode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
						lv_obj_set_style_text_font(ui_speedMode, &ui_font_icon_bettery, LV_PART_MAIN | LV_STATE_DEFAULT);
						
						lv_obj_set_style_text_color(ui_ecoMode, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
						lv_obj_set_style_text_opa(ui_ecoMode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
						lv_obj_set_style_text_font(ui_ecoMode, &ui_font_icon_bettery, LV_PART_MAIN | LV_STATE_DEFAULT);
					}
					else
					{
						lv_obj_set_style_text_color(ui_speedMode, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
						lv_obj_set_style_text_opa(ui_speedMode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
						lv_obj_set_style_text_font(ui_speedMode, &ui_font_icon_bettery, LV_PART_MAIN | LV_STATE_DEFAULT);
						
						lv_obj_set_style_text_color(ui_ecoMode, lv_color_hex(0x80FF80), LV_PART_MAIN | LV_STATE_DEFAULT);
						lv_obj_set_style_text_opa(ui_ecoMode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
						lv_obj_set_style_text_font(ui_ecoMode, &ui_font_icon_bettery, LV_PART_MAIN | LV_STATE_DEFAULT);
					}
				}
				else if(carType == 1) //�ͳ�
				{
					lv_label_set_text_fmt(ui_speedNum, "%03d", racingCarData.FrontSpeed);   //����
					lv_label_set_text_fmt(ui_rpmNum, "%04d", racingCarData.lmotorSpeed);    //������ת��
					lv_label_set_text_fmt(ui_batTemp, "%.1f", racingCarData.lowBatVol);     //��ѹ��ص�ѹ
					lv_label_set_text_fmt(ui_lMotorTemp, "%02d", racingCarData.oilTemp);    //�����¶�
					lv_label_set_text_fmt(ui_rMotorTemp, "%02d", racingCarData.oilPressure);//����ѹ��
					
					lv_bar_set_value(ui_socValue, racingCarData.throttlePosition, LV_ANIM_ON);
					if(racingCarData.gear == 0)
						lv_label_set_text(ui_gearLable, "N");
					else if(racingCarData.gear == 1)
						lv_label_set_text(ui_gearLable, "1");
					else if(racingCarData.gear == 2)
						lv_label_set_text(ui_gearLable, "2");
					else if(racingCarData.gear == 3)
						lv_label_set_text(ui_gearLable, "3");
					else if(racingCarData.gear == 4)
						lv_label_set_text(ui_gearLable, "4");
					else if(racingCarData.gear == 5)
						lv_label_set_text(ui_gearLable, "5");
					if(racingCarData.carMode == 0)
					{
						lv_obj_set_style_text_color(ui_speedMode, lv_color_hex(0x6464F1), LV_PART_MAIN | LV_STATE_DEFAULT);
						lv_obj_set_style_text_opa(ui_speedMode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
						lv_obj_set_style_text_font(ui_speedMode, &ui_font_icon_bettery, LV_PART_MAIN | LV_STATE_DEFAULT);
						
						lv_obj_set_style_text_color(ui_ecoMode, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
						lv_obj_set_style_text_opa(ui_ecoMode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
						lv_obj_set_style_text_font(ui_ecoMode, &ui_font_icon_bettery, LV_PART_MAIN | LV_STATE_DEFAULT);
					}
					else
					{
						lv_obj_set_style_text_color(ui_speedMode, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
						lv_obj_set_style_text_opa(ui_speedMode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
						lv_obj_set_style_text_font(ui_speedMode, &ui_font_icon_bettery, LV_PART_MAIN | LV_STATE_DEFAULT);
						
						lv_obj_set_style_text_color(ui_ecoMode, lv_color_hex(0x80FF80), LV_PART_MAIN | LV_STATE_DEFAULT);
						lv_obj_set_style_text_opa(ui_ecoMode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
						lv_obj_set_style_text_font(ui_ecoMode, &ui_font_icon_bettery, LV_PART_MAIN | LV_STATE_DEFAULT);
					}
				}
			}
			if(appStatus.simhubStatus)
			{
				appStatus.canOpenStatus = 0;
				SH_Set_Data();
				meterAnimation();
				lv_label_set_text_fmt(ui_speedNum, "%03d", sh_CarData.speed);
				lv_label_set_text_fmt(ui_rpmNum, "%04d", sh_CarData.rpm);
				lv_label_set_text_fmt(ui_batTemp, "%03d", sh_CarData.lap);
				lv_label_set_text_fmt(ui_lMotorTemp, "%03d", sh_CarData.throttle);
				lv_label_set_text_fmt(ui_rMotorTemp, "%03d", sh_CarData.brake);
				lv_label_set_text_fmt(ui_bespLapTime, "%.*s", 8, sh_CarData.bLapTime);
				lv_label_set_text_fmt(ui_lapTime, "%.*s", 8, sh_CarData.cLapTime);
				lv_bar_set_value(ui_socValue, sh_CarData.fuel, LV_ANIM_ON);
				lv_label_set_text_fmt(ui_gearLable, "%.*s", 1, sh_CarData.Gear);
			}
			osMutexRelease(lvgl_mutexHandle);
		}
		
//		
    //osDelay(50);
  }
  /* USER CODE END Start_LVGL_Meter */
}

/* USER CODE BEGIN Header_Start_LVGL_Lap_Timer */
/**
* @brief Function implementing the LVGL_Lap_Timer thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_LVGL_Lap_Timer */
void Start_LVGL_Lap_Timer(void *argument)
{
  /* USER CODE BEGIN Start_LVGL_Lap_Timer */
	
	for(;;)
	{
		 osMutexWait(lvgl_mutexHandle,     /* ��������� */ 
													osWaitForever); 
		//���¼�ʱ��ʱ����ʾ
		if(appStatus.canOpenStatus)
			lv_label_set_text_fmt(ui_lapTime, "%02d:%02d:%02d", min, sec, msec);
		osMutexRelease(lvgl_mutexHandle); //�ͷŻ�����
		
		osDelay(1);
	}
	
  /* Infinite loop */
  
  /* USER CODE END Start_LVGL_Lap_Timer */
}

/* USER CODE BEGIN Header_Start_BC260Y_init */
/**
* @brief Function implementing the BC260Y_init thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_BC260Y_init */
void Start_BC260Y_init(void *argument)
{
  /* USER CODE BEGIN Start_BC260Y_init */
	uint32_t r_event;
  /* Infinite loop */
  for(;;)
  {
		r_event = osEventFlagsWait(getCarDataHandle,             /* �¼������� */ 
                              MQTT_INIT,    					/* �����������Ȥ���¼� */ 
                              osFlagsWaitAll,           /* �˳�ʱ����¼�λ��ͬʱ�������Ȥ�������¼� */ 
                              osWaitForever);           /* ָ����ʱ�¼�,һֱ�� */ 
		//��ȡ�¼���״̬
		
		if(r_event)
		//���½�����ʾ
		 {
		//osMutexWait(lvgl_mutexHandle,     /* ��������� */ 
		//                      osWaitForever); 
		//ִ��MQTT��ʼ��
			MQTTinitOkFlag = mqttServiceStartup();
		//�����ϴ�����
			if(MQTTinitOkFlag)
				iotUploadTaskHandle = osThreadNew(Start_IotUploadTask, NULL, &iotUploadTask_attributes);
		//��MQTT��ʼ��������͸�UI
			lv_event_send(ui_iotStatus, MQTT_INIT_OK, NULL);
		
			osThreadSuspend(BC260Y_initHandle);
		}
		//osThreadExit();
		
		//osMutexRelease(lvgl_mutexHandle); //�ͷŻ�����
		
		//osDelay(100);
	}
	
  /* Infinite loop */
  
  /* USER CODE END Start_BC260Y_init */
}

/* USER CODE BEGIN Header_Start_RPM_LED */
/**
* @brief Function implementing the RPM_LED_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_RPM_LED */
void Start_RPM_LED(void *argument)
{
  /* USER CODE BEGIN Start_RPM_LED */
	uint32_t r_event;
  /* Infinite loop */
  for(;;)
  {
		r_event = osEventFlagsWait(getCarDataHandle,             /* �¼������� */ 
                              UPLOAD_EVENT,    /* �����������Ȥ���¼� */ 
                              osFlagsWaitAll,           /* �˳�ʱ����¼�λ��ͬʱ�������Ȥ�������¼� */ 
                              osWaitForever);           /* ָ����ʱ�¼�,һֱ�� */ 
		//osMutexWait(lvgl_mutexHandle,     /* ��������� */ 
    //                      osWaitForever); 
		if(r_event)
		{
				//if(appStatus.canOpenStatus)
			//keyControlCanSend();
					//motec_ECU_decode();
				
				RPM_LED_Shine();
		}
			
		
		//osMutexRelease(lvgl_mutexHandle); //�ͷŻ�����
    //osDelay(10);
  }
  /* USER CODE END Start_RPM_LED */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

