#ifndef _BSP_LCD_H
#define _BSP_LCD_H


#include "fsmc.h"

//LCD重要参数集
typedef struct
{
    uint16_t width;			//LCD 宽度
    uint16_t height;			//LCD 高度
    uint16_t id;				//LCD ID
    uint8_t  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。
    uint16_t	wramcmd;		//开始写gram指令
    uint16_t  setxcmd;		//设置x坐标指令
    uint16_t  setycmd;		//设置y坐标指令
} _lcd_dev;

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数
//LCD的画笔颜色和背景色
extern uint16_t  POINT_COLOR;//默认红色
extern uint16_t  BACK_COLOR; //背景颜色.默认为白色

typedef struct
{
	__IO uint16_t LCD_REG;
	__IO uint16_t LCD_RAM;
} LCD_TypeDef;

#define LCD_BASE        ((uint32_t)(0x64000000 | 0x000FFFFE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)
#define LCD_WRITE_REG(value)  (LCD->LCD_REG = value)
#define LCD_WRITE_DATA(value)  (LCD->LCD_RAM = value)
#define LCD_READ_DATA()  (LCD->LCD_RAM )


//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE         	 0x001F
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色

#define LIGHTGREEN     	 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)


void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);

uint16_t LCD_ReadReg(uint16_t LCD_Reg);

void LCD_WriteRAM_Prepare(void);

void LCD_WriteRAM(uint16_t RGB_Code);

uint16_t LCD_BGR2RGB(uint16_t c);

uint16_t LCD_ReadPoint(uint16_t x,uint16_t y);

void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);

void LCD_Clear(uint16_t color);

void LCD_DrawPoint(uint16_t x,uint16_t y);

void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color);

void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color);

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void LCD_Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r);

void LCD_Init();
#endif

