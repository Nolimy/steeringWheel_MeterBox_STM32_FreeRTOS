/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "main.h"
#include "cmsis_os.h"
#include "can.h"
#include "crc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_LCD.h"
#include "bsp_BC260Y.h"
#include "bsp_WS2812B.h"
#include "bsp_CAN.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "ui.h" 

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SPI_FATFS_DEBUG 0
#define LVGL_DEBUG 1

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#if SPI_FATFS_DEBUG 
#include "spi.h"
#include "lv_port_fs.h"
#include "ff.h"
uint8_t errorCode,formatSTAT,i;
FATFS fs;//�ļ�ϵͳ����
FIL fp;//�ļ�����
BYTE work[4096];
extern LV_ATTRIBUTE_MEM_ALIGN uint8_t ui_img_splash_png_data[];
char *write_text="FATFS test success!!!!";
unsigned int write_bytes=0;
char read_buff[8192];
unsigned int read_bytes=0;
#endif

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#if SPI_FATFS_DEBUG
void SPI_FLASH_WriteTest()
{
	if(!f_open(&fp,"0:test.txt",FA_CREATE_ALWAYS | FA_WRITE))
	{
		printf("open file success!\n");
	}
	else printf("open file failure!\n");
	
	if(!f_write(&fp,(char*)ui_img_splash_png_data,strlen((char*)ui_img_splash_png_data),&write_bytes))
	{
		printf("write success,write_bytes=%d\n",write_bytes);
	}
	else printf("write failure!\n");
 	if(!f_close(&fp))
	{
		printf("close success!\n");
	}
	else printf("close failure!\n");
	if(!f_open(&fp,"0:test.txt",FA_READ))
	{
		printf("open file success!\n");
	}
	else printf("open file failure!\n");
	if(!f_read(&fp,(char*)read_buff,sizeof(read_buff),&read_bytes))
	{
		printf("read success,write_bytes=%d\n",read_bytes);
		printf("test.txt content is :%s\n",read_buff);
	}
	else printf("read failure!\n");
	if(!f_close(&fp))
	{
		printf("close success!\n");
	}
	else printf("close failure!\n");
}
#endif

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

//	uint8_t barUpdataFlag = 1;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_FSMC_Init();
  MX_CRC_Init();
  MX_TIM3_Init();
  MX_SPI3_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_CAN1_Init();
  MX_USART3_UART_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	//   LVGL����ʱ���ж�
	HAL_TIM_Base_Start_IT(&htim3);	
	//����ģ�鿪��
	HAL_GPIO_WritePin(BLT_IN_GPIO_Port, BLT_IN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BLT_OUT_GPIO_Port, BLT_OUT_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BLT_RST_GPIO_Port, BLT_RST_Pin, GPIO_PIN_SET);	
	CanFilterInit();
	//MQTTinitOkFlag = mqttServiceStartup();
	//ws2812_blue(1);
	//HAL_Delay(1000);
	//ws2812_blue(2); 
	//HAL_Delay(500);
	//ws2812_blue(1);
	LCD_Init();
	LCD_Clear(BLACK);
#if LVGL_DEBUG	
	lv_init();
	lv_port_disp_init();  // lvgl��ʾ�ӿڳ�ʼ��,����lv_init()�ĺ���
	//lv_port_fs_init();
	//lv_bmp_init();
	ui_init();
	
	lv_event_send(ui_iotStatus, MQTT_INIT_OK, NULL);
#endif
#if SPI_FATFS_DEBUG
	formatSTAT = f_mkfs("0:",0,work,sizeof work);
	printf("format stat is :%d\n",formatSTAT);
	errorCode = f_mount(&fs,"0:",1);
	
	if(!errorCode)//�����ⲿFLASH)
	{
		printf("mount success!\n");
	}
	else
	{
		printf("Mount Failed!!!errorCode:%d\r\n",errorCode);
	}
	SPI_FLASH_WriteTest();
#endif
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if(barFlag == 1)
			sendEventCode();	
#if LVGL_DEBUG		
		lv_task_handler(); // lvgl��������	
#endif
		HAL_Delay(1);
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM2 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM2) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
	if (htim == (&htim3))
  {	
		lv_tick_inc(1);//lvgl��1ms�ж�
			//printf("tick\n");
  }
  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
