#include "bsp_WS2812B.h"
#include "tim.h"

#define ONE_PULSE        ((htim1.Init.Period+1)/3*2-1)                          
#define ZERO_PULSE       ((htim1.Init.Period+1)/3-1)                           
#define RESET_PULSE      (80)                           
#define LED_NUMS         (24)                            
#define LED_DATA_LEN     (24)                           
#define WS2812_DATA_LEN  (LED_NUMS*LED_DATA_LEN)    
#define HTIM             htim1
#define CHANNEL          TIM_CHANNEL_1 

uint16_t static RGB_buffur[RESET_PULSE + WS2812_DATA_LEN] = { 0 };

void ws2812_set_RGB(uint8_t R, uint8_t G, uint8_t B, uint16_t num)
{
    //
    uint16_t* p = (RGB_buffur + RESET_PULSE) + (num * LED_DATA_LEN);
    
    for (uint16_t i = 0;i < 8;i++)
    {
        
        p[i]      = (G << i) & (0x80)?ONE_PULSE:ZERO_PULSE;
        p[i + 8]  = (R << i) & (0x80)?ONE_PULSE:ZERO_PULSE;
        p[i + 16] = (B << i) & (0x80)?ONE_PULSE:ZERO_PULSE;

    }
}

void ws2812_init(uint8_t led_nums)
{
	uint16_t num_data;
	num_data = 80 + led_nums * 24;
	for(uint8_t i = 0; i < led_nums; i++)
	{
		ws2812_set_RGB(0x00, 0x00, 0x00, i);
	}
	 HAL_TIM_PWM_Start_DMA(&HTIM,CHANNEL,(uint32_t *)RGB_buffur,(num_data)); 
}

void ws2812_blue(uint8_t led_nums)
{
	uint16_t num_data;
	num_data = 80 + led_nums * 24;
	ws2812_init(12);
	for(uint8_t i = 0; i < led_nums; i++)
	{
		ws2812_set_RGB(0x00, 0x00, 0xFF, i);
	}
	 HAL_TIM_PWM_Start_DMA(&HTIM,CHANNEL,(uint32_t *)RGB_buffur,(num_data));
}

void ws2812_red(uint8_t led_nums)
{
	uint16_t num_data;
	num_data = 80 + led_nums * 24;
	ws2812_init(12);
	for(uint8_t i = 0; i < led_nums; i++)
	{
		ws2812_set_RGB(0xFF, 0x00, 0x00, i);
	}
	 HAL_TIM_PWM_Start_DMA(&HTIM,CHANNEL,(uint32_t *)RGB_buffur,(num_data));
}

void ws2812_green(uint8_t led_nums)
{
	uint16_t num_data;
	num_data = 80 + led_nums * 24;
	ws2812_init(12);
	for(uint8_t i = 0; i < led_nums; i++)
	{
		ws2812_set_RGB(0x00, 0xFF, 0x00, i);
	}
	 HAL_TIM_PWM_Start_DMA(&HTIM,CHANNEL,(uint32_t *)RGB_buffur,(num_data));
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 0);
    HAL_TIM_PWM_Stop_DMA(&htim1,TIM_CHANNEL_1);
}