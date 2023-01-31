#include "bsp_LCD.h" 
//#include "usart.h"	 
#include "fsmc.h"	
#include "gpio.h"	

_lcd_dev lcddev;

uint16_t  POINT_COLOR;//Ĭ�Ϻ�ɫ
uint16_t  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ
//д�Ĵ���
//LCD_Reg:�Ĵ������
//LCD_RegValue:Ҫд���ֵ
void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{
    LCD_WRITE_REG(LCD_Reg);
    LCD_WRITE_DATA(LCD_RegValue);
}


//���Ĵ���
//LCD_Reg:�Ĵ������
//����ֵ:������ֵ
uint16_t LCD_ReadReg(uint16_t LCD_Reg)
{
    LCD_WRITE_REG(LCD_Reg);        //д��Ҫ���ļĴ�����
    return LCD_READ_DATA();
}

//��ʼдGRAM
void LCD_WriteRAM_Prepare(void)
{
    LCD_WRITE_REG(0x2C);
}
//RGB_Code:��ɫֵ
void LCD_WriteRAM(uint16_t RGB_Code)
{
    LCD_WRITE_DATA(RGB_Code);      //дʮ��λGRAM
}

//��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
//ͨ���ú���ת��
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ
uint16_t LCD_BGR2RGB(uint16_t c)
{
    uint16_t  r,g,b,rgb;
    b=(c>>0)&0x1f;
    g=(c>>5)&0x3f;
    r=(c>>11)&0x1f;
    rgb=(b<<11)+(g<<5)+(r<<0);
    return(rgb);
}

uint16_t LCD_ReadPoint(uint16_t x,uint16_t y)
{
    uint16_t r=0,g=0,b=0;
    if(x>=lcddev.width||y>=lcddev.height)return 0;	//�����˷�Χ,ֱ�ӷ���
    LCD_SetCursor(x,y);
    if(lcddev.id==0X9341||lcddev.id==0X6804||lcddev.id==0X5310||lcddev.id==0X1963)LCD_WRITE_REG(0X2E);//9341/6804/3510/1963 ���Ͷ�GRAMָ��
    else if(lcddev.id==0X5510)LCD_WRITE_REG(0X2E00);	//5510 ���Ͷ�GRAMָ��
    else LCD_WRITE_REG(0X22);      		 			//����IC���Ͷ�GRAMָ��
    if(lcddev.id==0X9320)HAL_Delay(1);
    r=LCD_READ_DATA();								//dummy Read
    if(lcddev.id==0X1963)return r;					//1963ֱ�Ӷ��Ϳ���
    r=LCD_READ_DATA();  		  						//ʵ��������ɫ
    if(lcddev.id==0X9341||lcddev.id==0X5310||lcddev.id==0X5510)		//9341/NT35310/NT35510Ҫ��2�ζ���
    {
        //opt_delay(2);
        b=LCD_READ_DATA();
        g=r&0XFF;		//����9341/5310/5510,��һ�ζ�ȡ����RG��ֵ,R��ǰ,G�ں�,��ռ8λ
        g<<=8;
    }
    if(lcddev.id==0X9325||lcddev.id==0X4535||lcddev.id==0X4531||lcddev.id==0XB505||lcddev.id==0XC505)return r;	//�⼸��ICֱ�ӷ�����ɫֵ
    else if(lcddev.id==0X9341||lcddev.id==0X5310||lcddev.id==0X5510)return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));//ILI9341/NT35310/NT35510��Ҫ��ʽת��һ��
    else return LCD_BGR2RGB(r);						//����IC
}

//���ù��λ��
//Xpos:������
//Ypos:������
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
    LCD_WRITE_REG(0x2A);
    LCD_WRITE_DATA(Xpos >> 8);
    LCD_WRITE_DATA(Xpos & 0XFF);
    LCD_WRITE_REG(0x2B);
    LCD_WRITE_DATA(Ypos >> 8);
    LCD_WRITE_DATA(Ypos & 0XFF);
}

//��������
//color:Ҫ���������ɫ
void LCD_Clear(uint16_t color)
{
    uint32_t index = 0;
    uint32_t totalpoint = 480;
    totalpoint *= 320;    //�õ��ܵ���

    LCD_SetCursor(0x00, 0x0000);    //���ù��λ��
    LCD_WriteRAM_Prepare();         //��ʼд��GRAM

    for (index = 0; index < totalpoint; index++)
    {
        LCD_WRITE_DATA(color);
    }
}

//����
//x,y:����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(uint16_t x,uint16_t y)
{
    LCD_SetCursor(x,y);		//���ù��λ��
    LCD_WriteRAM_Prepare();	//��ʼд��GRAM
    LCD->LCD_RAM=POINT_COLOR;
}

//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)
//color:Ҫ������ɫ
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{
    uint16_t i,j;
    uint16_t xlen=0;
    uint16_t temp;

    xlen=ex-sx+1;
    for(i=sy; i<=ey; i++)
    {
        LCD_SetCursor(sx,i);      				//���ù��λ��
        LCD_WriteRAM_Prepare();     			//��ʼд��GRAM
        for(j=0; j<xlen; j++)LCD->LCD_RAM=color;	//��ʾ��ɫ
    }

}
//��ָ�����������ָ����ɫ��
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)
//color:Ҫ������ɫ
void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
{
    uint16_t height,width;
    uint16_t i,j;
    width=ex-sx+1; 			//�õ����Ŀ��
    height=ey-sy+1;			//�߶�
    for(i=0; i<height; i++)
    {
        LCD_SetCursor(sx,sy+i);   	//���ù��λ��
        LCD_WriteRAM_Prepare();     //��ʼд��GRAM
        for(j=0; j<width; j++)LCD->LCD_RAM=color[i*width+j]; //д������
    }
}
//����
//x1,y1:�������
//x2,y2:�յ�����
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    uint16_t t;
    int xerr=0,yerr=0,delta_x,delta_y,distance;
    int incx,incy,uRow,uCol;
    delta_x=x2-x1; //������������
    delta_y=y2-y1;
    uRow=x1;
    uCol=y1;
    if(delta_x>0)incx=1; //���õ�������
    else if(delta_x==0)incx=0;//��ֱ��
    else {
        incx=-1;
        delta_x=-delta_x;
    }
    if(delta_y>0)incy=1;
    else if(delta_y==0)incy=0;//ˮƽ��
    else {
        incy=-1;
        delta_y=-delta_y;
    }
    if( delta_x>delta_y)distance=delta_x; //ѡȡ��������������
    else distance=delta_y;
    for(t=0; t<=distance+1; t++ ) //�������
    {
        LCD_DrawPoint(uRow,uCol);//����
        xerr+=delta_x ;
        yerr+=delta_y ;
        if(xerr>distance)
        {
            xerr-=distance;
            uRow+=incx;
        }
        if(yerr>distance)
        {
            yerr-=distance;
            uCol+=incy;
        }
    }
}
//������
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    LCD_DrawLine(x1,y1,x2,y1);
    LCD_DrawLine(x1,y1,x1,y2);
    LCD_DrawLine(x1,y2,x2,y2);
    LCD_DrawLine(x2,y1,x2,y2);
}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void LCD_Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r)
{
    int a,b;
    int di;
    a=0;
    b=r;
    di=3-(r<<1);             //�ж��¸���λ�õı�־
    while(a<=b)
    {
        LCD_DrawPoint(x0+a,y0-b);             //5
        LCD_DrawPoint(x0+b,y0-a);             //0
        LCD_DrawPoint(x0+b,y0+a);             //4
        LCD_DrawPoint(x0+a,y0+b);             //6
        LCD_DrawPoint(x0-a,y0+b);             //1
        LCD_DrawPoint(x0-b,y0+a);
        LCD_DrawPoint(x0-a,y0-b);             //2
        LCD_DrawPoint(x0-b,y0-a);             //7
        a++;
        //ʹ��Bresenham�㷨��Բ
        if(di<0)di +=4*a+6;
        else
        {
            di+=10+4*(a-b);
            b--;
        }
    }
}

void LCD_Init()
{
	//NOTE��VCC=3.3V,IOVCC=1.8-3.3V
//*******************ָ��***************************
	HAL_Delay(100);
	/***************************************/ 
	LCD_WRITE_REG(0xF0); //Command Set Control       
	LCD_WRITE_DATA(0xC3);   

	LCD_WRITE_REG(0xF0); //Command Set Control     
	LCD_WRITE_DATA(0x96);   

	LCD_WRITE_REG(0x36);//Memory Data Access Control        
	LCD_WRITE_DATA(0x38);//0x48  0x38   

	LCD_WRITE_REG(0x3A);//Interface Pixel Format        
	LCD_WRITE_DATA(0x05);//65K  

	LCD_WRITE_REG(0xB4); //1-dot Inversion
	LCD_WRITE_DATA(0x01);  //01  1dot   00 column  02 2ot  

	LCD_WRITE_REG(0xB1);//FRMCTR1     
	LCD_WRITE_DATA(0x80);   //FRS[D7-D4], DIVA[D1-D0] 81 for 15Hz
	LCD_WRITE_DATA(0x10);   //RTNA[4:0]

	LCD_WRITE_REG(0xC0);//Power Control 1      
	LCD_WRITE_DATA(0x80);  //AVDD ,AVCL  									   `
	LCD_WRITE_DATA(0x64); //VGH=15V VGL=-10V  

	LCD_WRITE_REG(0xC1);  //Power Control 2        
	LCD_WRITE_DATA(0x13);  //VOP=4.5V

	LCD_WRITE_REG(0xC2); //Power Control 3      
	LCD_WRITE_DATA(0xA7);   

	LCD_WRITE_REG(0xC5);//VCOM Control      
	LCD_WRITE_DATA(0x09);   

	LCD_WRITE_REG(0xE8); //Display Output Ctrl Adjust     
	LCD_WRITE_DATA(0x40);   
	LCD_WRITE_DATA(0x8a);   
	LCD_WRITE_DATA(0x00);   
	LCD_WRITE_DATA(0x00);   
	LCD_WRITE_DATA(0x29);   
	LCD_WRITE_DATA(0x19);   
	LCD_WRITE_DATA(0xA5);   
	LCD_WRITE_DATA(0x33);   

	LCD_WRITE_REG(0xE0);//GAMMA
	LCD_WRITE_DATA(0xF0);
	LCD_WRITE_DATA(0x06);
	LCD_WRITE_DATA(0x0B);
	LCD_WRITE_DATA(0x07);
	LCD_WRITE_DATA(0x06);
	LCD_WRITE_DATA(0x05);
	LCD_WRITE_DATA(0x2E);
	LCD_WRITE_DATA(0x33);	
	LCD_WRITE_DATA(0x47);
	LCD_WRITE_DATA(0x3A);
	LCD_WRITE_DATA(0x17);
	LCD_WRITE_DATA(0x16);
	LCD_WRITE_DATA(0x2E);
	LCD_WRITE_DATA(0x31);

	LCD_WRITE_REG(0xE1);//GAMMA
	LCD_WRITE_DATA(0xF0);
	LCD_WRITE_DATA(0x09);
	LCD_WRITE_DATA(0x0D);
	LCD_WRITE_DATA(0x09);
	LCD_WRITE_DATA(0x08);
	LCD_WRITE_DATA(0x23);
	LCD_WRITE_DATA(0x2E);
	LCD_WRITE_DATA(0x33);
	LCD_WRITE_DATA(0x46);
	LCD_WRITE_DATA(0x38);
	LCD_WRITE_DATA(0x13);
	LCD_WRITE_DATA(0x13);
	LCD_WRITE_DATA(0x2C);
	LCD_WRITE_DATA(0x32);

	LCD_WRITE_REG(0xF0); //Command Set Control     
	LCD_WRITE_DATA(0x3C);   

	LCD_WRITE_REG(0xF0);//Command Set Control      
	LCD_WRITE_DATA(0x69);  

	LCD_WRITE_REG(0x21); //Enter_invert_mode 
 //**********************320*480**********************  
  LCD_WRITE_REG(0x2B);    //320 
	LCD_WRITE_DATA(0x00);   
	LCD_WRITE_DATA(0x00);   
	LCD_WRITE_DATA(0x01);   
	LCD_WRITE_DATA(0x3F);
	
	LCD_WRITE_REG(0x2A);    //480
	LCD_WRITE_DATA(0x00);   
	LCD_WRITE_DATA(0x00);   
	LCD_WRITE_DATA(0x01);   
	LCD_WRITE_DATA(0xDF);  
	

	LCD_WRITE_REG(0x11); // Exit Sleep    
  HAL_Delay(120);  //ms
	LCD_WRITE_REG(0x29);//DISPLAY ON       
  HAL_Delay(50); 
	LCD_WRITE_REG(0x2c); //Write memory start   
	
	LCD_Clear(BLACK);
	   
}
