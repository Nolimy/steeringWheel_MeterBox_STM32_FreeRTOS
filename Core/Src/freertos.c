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
#include "usbd_cdc_if.h"
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

/* USER CODE END Variables */
#if canOPEN
/* Definitions for iotUploadTask */
osThreadId_t iotUploadTaskHandle;
const osThreadAttr_t iotUploadTask_attributes = {
  .name = "iotUploadTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for LVGL_Lap_Timer */
osThreadId_t LVGL_Lap_TimerHandle;
const osThreadAttr_t LVGL_Lap_Timer_attributes = {
  .name = "LVGL_Lap_Timer",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for BC260Y_init */
osThreadId_t BC260Y_initHandle;
const osThreadAttr_t BC260Y_init_attributes = {
  .name = "BC260Y_init",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime1,
};
#endif
/* Definitions for LVGL_Task */
osThreadId_t LVGL_TaskHandle;
const osThreadAttr_t LVGL_Task_attributes = {
  .name = "LVGL_Task",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for LVGL_Meter */
osThreadId_t LVGL_MeterHandle;
const osThreadAttr_t LVGL_Meter_attributes = {
  .name = "LVGL_Meter",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for RPM_LED_Task */
osThreadId_t RPM_LED_TaskHandle;
const osThreadAttr_t RPM_LED_Task_attributes = {
  .name = "RPM_LED_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
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

extern void MX_USB_DEVICE_Init(void);
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
	
	#if canOPEN
	LVGL_Lap_TimerHandle = osThreadNew(Start_LVGL_Lap_Timer, NULL, &LVGL_Lap_Timer_attributes);
	
	BC260Y_initHandle = osThreadNew(Start_BC260Y_init, NULL, &BC260Y_init_attributes);
	
	#endif
	
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
	MX_USB_DEVICE_Init();
  /* Infinite loop */
  for(;;)
  {
		osMutexWait(lvgl_mutexHandle,     /* 互斥量句柄 */ 
                          osWaitForever); 
		if(barFlag == 1)
		{
			sendEventCode();	
		}
				
		//json_analysis((char *)pRx);
		lv_task_handler(); // lvgl的事务处理	
		
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
		r_event = osEventFlagsWait(getCarDataHandle,             /* 事件对象句柄 */ 
                              GUI_UPDATE_EVENT,    					/* 接收任务感兴趣的事件 */ 
                              osFlagsWaitAll,           /* 退出时清除事件位，同时满足感兴趣的所有事件 */ 
                              osWaitForever);           /* 指定超时事件,一直等 */ 
		//获取事件组状态
		
		if(r_event)
		//更新界面显示
		{
			osMutexWait(lvgl_mutexHandle,     /* 互斥量句柄 */ 
                          osWaitForever); 
			#if canOPEN
			
			meterAnimation();
			lv_label_set_text_fmt(ui_speedNum, "%03d", racingCarData.FrontSpeed);
			lv_label_set_text_fmt(ui_rpmNum, "%04d", racingCarData.rmotorSpeed);
			lv_label_set_text_fmt(ui_batTemp, "%03d", racingCarData.batTemp);
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
			#endif
			#if simhubOPEN
			meterAnimation();
			lv_label_set_text_fmt(ui_speedNum, "%03d", sh_CarData.speed);
			lv_label_set_text_fmt(ui_rpmNum, "%04d", sh_CarData.rpm);
			//lv_label_set_text_fmt(ui_batTemp, "%03d", racingCarData.batTemp);
			lv_label_set_text_fmt(ui_lMotorTemp, "%02d", sh_CarData.lfBrake);
			lv_label_set_text_fmt(ui_rMotorTemp, "%02d", sh_CarData.rfBrake);
			lv_label_set_text_fmt(ui_bespLapTime, "%.*s", 8, sh_CarData.bLapTime);
			//lv_label_set_text(ui_lapTime, (char *)sh_CarData.cLapTime);
			lv_label_set_text_fmt(ui_lapTime, "%.*s", 8, sh_CarData.cLapTime);
			lv_bar_set_value(ui_socValue, sh_CarData.fuel, LV_ANIM_ON);
			lv_label_set_text_fmt(ui_gearLable, "%.*s", 1, sh_CarData.Gear);
			
			
			
			#endif
			
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
#if canOPEN
void Start_LVGL_Lap_Timer(void *argument)
{
  /* USER CODE BEGIN Start_LVGL_Lap_Timer */
  /* Infinite loop */
  for(;;)
  {
		 osMutexWait(lvgl_mutexHandle,     /* 互斥量句柄 */ 
                          osWaitForever); 
		//更新计时器时间显示
		lv_label_set_text_fmt(ui_lapTime, "%02d:%02d:%02d", min, sec, msec);
		osMutexRelease(lvgl_mutexHandle); //释放互斥量
		
    osDelay(1);
  }
  /* USER CODE END Start_LVGL_Lap_Timer */
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
		r_event = osEventFlagsWait(getCarDataHandle,             /* 事件对象句柄 */ 
                              UPLOAD_EVENT,    /* 接收任务感兴趣的事件 */ 
                              osFlagsWaitAll,           /* 退出时清除事件位，同时满足感兴趣的所有事件 */ 
                              osWaitForever);           /* 指定超时事件,一直等 */ 
		//进入进程后删除掉初始化MQTT的进程
		osThreadTerminate(BC260Y_initHandle);
		
		if(r_event)
		{
			osMutexWait(lvgl_mutexHandle,     /* 互斥量句柄 */ 
                          osWaitForever); 
			//5fps
			uploadCarData();
			
			osMutexRelease(lvgl_mutexHandle);
		}
			
    //osDelay(200);
  }
  /* USER CODE END Start_IotUploadTask */
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
  /* Infinite loop */
  for(;;)
  {
		//osMutexWait(lvgl_mutexHandle,     /* 互斥量句柄 */ 
    //                      osWaitForever); 
		//执行MQTT初始化
		MQTTinitOkFlag = mqttServiceStartup();
		//事件组  发送信号
		//osEventFlagsSet(getCarDataHandle, 0x08); // 0000 1000
		//启动上传进程
		iotUploadTaskHandle = osThreadNew(Start_IotUploadTask, NULL, &iotUploadTask_attributes);
		//将MQTT初始化结果发送给UI
		lv_event_send(ui_iotStatus, MQTT_INIT_OK, NULL);
		
		osThreadSuspend(BC260Y_initHandle);
		//osThreadExit();
		
		//osMutexRelease(lvgl_mutexHandle); //释放互斥量
		
    //osDelay(100);
  }
  /* USER CODE END Start_BC260Y_init */
}
#endif
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
		r_event = osEventFlagsWait(getCarDataHandle,             /* 事件对象句柄 */ 
                              UPLOAD_EVENT,    /* 接收任务感兴趣的事件 */ 
                              osFlagsWaitAll,           /* 退出时清除事件位，同时满足感兴趣的所有事件 */ 
                              osWaitForever);           /* 指定超时事件,一直等 */ 
		//osMutexWait(lvgl_mutexHandle,     /* 互斥量句柄 */ 
    //                      osWaitForever); 
		if(r_event)
			RPM_LED_Shine();
		
		//osMutexRelease(lvgl_mutexHandle); //释放互斥量
    //osDelay(10);
  }
  /* USER CODE END Start_RPM_LED */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

