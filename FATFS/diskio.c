/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "bsp_spi_bus.h"
#include "bsp_spi_flash.h"
#include "usart.h"
/* Definitions of physical drive number for each drive */

#define DEV_FLASH 0  /* Physical drive number to identify the drive */


#define FLASH_SECTOR_SIZE    4096          //单个扇区大小 Bytes
#define FLASH_BLOCK_SIZE    16*4096				 //每个BLOCK有16个扇区 sector
#define FLASH_SECTOR_COUNT   16*32         //指扇区的数量 每个block有16个sector,共32个block，内存大小为2MBytes

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;

	switch (pdrv) {
	case DEV_FLASH :
		

		// translate the reslut code here

		return RES_OK;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = RES_NOTRDY;


	if(pdrv == DEV_FLASH) 
	{
		
		bsp_InitSPIBus();
	  bsp_InitSFlash();
		
		if(sf_ReadID() != 0)
		{
			printf("FLASH ID is :%d\n",sf_ReadID());
			stat = RES_OK;
		}
		// translate the reslut code here
		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;

	if(pdrv == DEV_FLASH) {
		// translate the arguments here
		sf_ReadBuffer((uint8_t *)buff, sector<<12, count<<12);

		// translate the reslut code here

		return RES_OK;

	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;

	if (pdrv == DEV_FLASH) {
		// translate the arguments here
		
		sf_WriteBuffer((uint8_t *)buff, sector<<12, count<<12);
		// translate the reslut code here

		return RES_OK;

	
	}

	return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	int result;

	if (pdrv == DEV_FLASH) {
		switch(cmd)
		{
			case CTRL_SYNC:	return RES_OK;//确保设备已经完成挂起的写操作
			case GET_SECTOR_COUNT: *(DWORD * )buff = FLASH_SECTOR_COUNT;//获取扇区数
											return RES_OK;
			case GET_SECTOR_SIZE: *(DWORD * )buff = FLASH_SECTOR_SIZE;//获取扇区大小
											return RES_OK;
			case GET_BLOCK_SIZE: *(DWORD * )buff = FLASH_BLOCK_SIZE;//获取块大小
											return RES_OK;
		}
		
		// Process of the command for the RAM drive

		return res;

	}

	return RES_PARERR;
}

