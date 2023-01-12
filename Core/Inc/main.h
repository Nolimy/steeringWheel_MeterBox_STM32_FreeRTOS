/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOF
#define LED2_Pin GPIO_PIN_7
#define LED2_GPIO_Port GPIOF
#define BLT_IN_Pin GPIO_PIN_8
#define BLT_IN_GPIO_Port GPIOF
#define BLT_OUT_Pin GPIO_PIN_9
#define BLT_OUT_GPIO_Port GPIOF
#define BLT_RST_Pin GPIO_PIN_10
#define BLT_RST_GPIO_Port GPIOF
#define RST_4G_Pin GPIO_PIN_7
#define RST_4G_GPIO_Port GPIOG
#define PWR_4G_Pin GPIO_PIN_8
#define PWR_4G_GPIO_Port GPIOG
#define SPI_CS1_Pin GPIO_PIN_6
#define SPI_CS1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define GPIOA_ODR_Addr    (GPIOA_BASE+20) 
#define GPIOB_ODR_Addr    (GPIOB_BASE+20)
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20)
#define GPIOF_ODR_Addr    (GPIOF_BASE+20)
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) 
#define GPIOH_ODR_Addr    (GPIOH_BASE+20) 
#define GPIOI_ODR_Addr    (GPIOI_BASE+20)
#define GPIOJ_ODR_ADDr    (GPIOJ_BASE+20)
#define GPIOK_ODR_ADDr    (GPIOK_BASE+20) 

#define GPIOA_IDR_Addr    (GPIOA_BASE+16)
#define GPIOB_IDR_Addr    (GPIOB_BASE+16)
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) 
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) 
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) 
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) 
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) 
#define GPIOH_IDR_Addr    (GPIOH_BASE+16) 
#define GPIOI_IDR_Addr    (GPIOI_BASE+16) 
#define GPIOJ_IDR_Addr    (GPIOJ_BASE+16) 
#define GPIOK_IDR_Addr    (GPIOK_BASE+16) 

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n) 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n) 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n) 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n) 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n) 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n) 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n) 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n) 

#define PJout(n)   BIT_ADDR(GPIOJ_ODR_Addr,n)  
#define PJin(n)    BIT_ADDR(GPIOJ_IDR_Addr,n)  

#define PKout(n)   BIT_ADDR(GPIOK_ODR_Addr,n)  
#define PKin(n)    BIT_ADDR(GPIOK_IDR_Addr,n) 

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
