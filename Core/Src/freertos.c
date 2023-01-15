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
/* Definitions for iotUploadTask */
osThreadId_t iotUploadTaskHandle;
const osThreadAttr_t iotUploadTask_attributes = {
  .name = "iotUploadTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for LVGL_Task */
osThreadId_t LVGL_TaskHandle;
const osThreadAttr_t LVGL_Task_attributes = {
  .name = "LVGL_Task",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for LVGL_Meter */
osThreadId_t LVGL_MeterHandle;
const osThreadAttr_t LVGL_Meter_attributes = {
  .name = "LVGL_Meter",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for LVGL_Lap_Timer */
osThreadId_t LVGL_Lap_TimerHandle;
const osThreadAttr_t LVGL_Lap_Timer_attributes = {
  .name = "LVGL_Lap_Timer",
  .stack_size = 128 * 4,
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

/* USER CODE END FunctionPrototypes */

void Start_IotUploadTask(void *argument);
void Start_LVGL_Task(void *argument);
void Start_LVGL_Meter(void *argument);
void Start_LVGL_Lap_Timer(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

	lvgl_mutexHandle = osMutexNew(&lvgl_mutex_attributes);
	
	iotUploadTaskHandle = osThreadNew(Start_IotUploadTask, NULL, &iotUploadTask_attributes);
	
	LVGL_TaskHandle = osThreadNew(Start_LVGL_Task, NULL, &LVGL_Task_attributes);
	
	LVGL_MeterHandle = osThreadNew(Start_LVGL_Meter, NULL, &LVGL_Meter_attributes);
	
	LVGL_Lap_TimerHandle = osThreadNew(Start_LVGL_Lap_Timer, NULL, &LVGL_Lap_Timer_attributes);
	
	getCarDataHandle = osEventFlagsNew(&getCarData_attributes);
  /* USER CODE END Init */

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
//#define UPLOAD_EVENT (0x01 << 0)//设置事件掩码的位 0 
//#define GUI_UPDATE_EVENT (0x01 << 1)//设置事件掩码的位 1
//#define LED_EVENT (0x01 << 2)//设置事件掩码的位 1

  /* USER CODE BEGIN Start_IotUploadTask */
	uint32_t r_event;
  /* Infinite loop */
  for(;;)
  {
		r_event = osEventFlagsWait(getCarDataHandle,             /* 事件对象句柄 */ 
                              UPLOAD_EVENT,    /* 接收任务感兴趣的事件 */ 
                              osFlagsWaitAll,           /* 退出时清除事件位，同时满足感兴趣的所有事件 */ 
                              osWaitForever);           /* 指定超时事件,一直等 */ 
		//5fps
		if(r_event)
			uploadCarData();
    //osDelay(200);
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
  /* Infinite loop */
  for(;;)
  {
		osMutexWait(lvgl_mutexHandle,     /* 互斥量句柄 */ 
                          osWaitForever); 
		if(barFlag == 1)
			sendEventCode();		
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
  /* Infinite loop */
  for(;;)
  {
		 osMutexWait(lvgl_mutexHandle,     /* 互斥量句柄 */ 
                          osWaitForever); 
		
		//更新计时器时间显示
		
		
		osMutexRelease(lvgl_mutexHandle); //释放互斥量
		
    osDelay(1);
  }
  /* USER CODE END Start_LVGL_Lap_Timer */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

