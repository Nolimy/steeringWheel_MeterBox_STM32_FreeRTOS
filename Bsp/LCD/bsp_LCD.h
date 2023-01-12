#ifndef _BSP_LCD_H
#define _BSP_LCD_H


#include "fsmc.h"

//LCD��Ҫ������
typedef struct
{
    uint16_t width;			//LCD ���
    uint16_t height;			//LCD �߶�
    uint16_t id;				//LCD ID
    uint8_t  dir;			//���������������ƣ�0��������1��������
    uint16_t	wramcmd;		//��ʼдgramָ��
    uint16_t  setxcmd;		//����x����ָ��
    uint16_t  setycmd;		//����y����ָ��
} _lcd_dev;

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����
//LCD�Ļ�����ɫ�ͱ���ɫ
extern uint16_t  POINT_COLOR;//Ĭ�Ϻ�ɫ
extern uint16_t  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

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


//������ɫ
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
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ

#define LIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)


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

