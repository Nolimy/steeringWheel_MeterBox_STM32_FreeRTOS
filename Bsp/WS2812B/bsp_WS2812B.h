#ifndef  _BSP_WS2812B_H
#define _BSP_WS2812B_H
#include "stdint.h"


void ws2812_set_RGB(uint8_t R, uint8_t G, uint8_t B, uint16_t num);

void ws2812_init(uint8_t led_nums);
void ws2812_example(void);
extern void ws2812_blue(uint8_t led_nums);
extern void ws2812_red(uint8_t led_nums);
extern void ws2812_green(uint8_t led_nums);




#endif

