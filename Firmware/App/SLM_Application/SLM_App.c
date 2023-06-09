#include "SLM_App.h"
#include "applicationVar.h"
#include "cmsis_os2.h"

void RPM_LED_Shine()
{
	uint16_t ledNums, i;
	ws2812_init(12);
	#if canOPEN
	#endif
	
	if(appStatus.canOpenStatus)
	{
		ledNums = racingCarData.lmotorSpeed / 1250;
	
		for(i = 0; i < ledNums; i++)//逐个点亮LED
		{
			ws2812_set_RGB(i*25, (12-i)*5, (12-i)*2, i);//RGB
		}
		while(ledNums>10)
		{
			ws2812_green(ledNums);//RGB
			osDelay(80);
			ws2812_init(12);
			osDelay(80);
			ledNums = racingCarData.lmotorSpeed / 1250;
		}
	}
	
	if(appStatus.simhubStatus)
	{
		ledNums = sh_CarData.rpm / (sh_CarData.redRpm / 12);
	
		for(i = 0; i < ledNums; i++)//逐个点亮LED
		{
			ws2812_set_RGB(i*25, (12-i)*5, (12-i)*2, i);//RGB
		}
		while(ledNums>10 &&(sh_CarData.rpm > sh_CarData.redRpm) )
		{
			ws2812_red(ledNums);//RGB
			osDelay(80);
			ws2812_init(12);
			osDelay(80);
			ledNums = sh_CarData.rpm / (sh_CarData.redRpm / 12);
		}
	}
	
	if(appStatus.standByStatus)
	{
		ws2812_blue(12);//RGB
	}
	
	
}