/*
*********************************************************************************************************
*
*	模块名称 : SPI总线驱动
*	文件名称 : bsp_spi_bus.h
*	版    本 : V1.0
*	说    明 : 头文件
*
*
*********************************************************************************************************
*/


#ifndef __BSP_SPI_BUS_H
#define __BSP_SPI_BUS_H

#include "main.h"

void bsp_InitSPIBus(void);
void bsp_spiTransfer(void);
void bsp_InitSPIParam(uint32_t _BaudRatePrescaler, uint32_t _CLKPhase, uint32_t _CLKPolarity);

void bsp_SpiBusEnter(void);
void bsp_SpiBusExit(void);
uint8_t bsp_SpiBusBusy(void);

#define	SPI_BUFFER_SIZE		(4 * 1024)				/* 4KBytes */

extern uint8_t g_spiTxBuf[SPI_BUFFER_SIZE];
extern uint8_t g_spiRxBuf[SPI_BUFFER_SIZE];
extern uint32_t g_spiLen;

extern uint8_t g_spi_busy;

#endif
