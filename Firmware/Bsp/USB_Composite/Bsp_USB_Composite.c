#include "Bsp_USB_Composite.h"
#include "usbd_cdc_acm_if.h"
#include "usbd_hid_mouse.h"

extern USBD_HandleTypeDef hUsbDevice;
int flag = 0;
struct joyStick_HID_t{
	uint8_t button_group0;
	uint8_t button_group1;
};
struct joyStick_HID_t joyStick_HID;

void usb_printf(const char *format, ...)
{
	va_list args;
	uint32_t length;
	uint8_t buff[128];
	
	va_start(args, format);
	length = vsnprintf((char *)buff, 128, (char *)format, args);
	
	va_end(args);
	CDC_Transmit(NULL, buff, length);
	
}

void USB_ControlData_Send()
{
	joyStick_HID.button_group0 = 0x00;
	joyStick_HID.button_group1 = 0x00;
	if(HAL_GPIO_ReadPin(INPUT1_GPIO_Port, INPUT1_Pin) == RESET) joyStick_HID.button_group0 |= 0x01 << 0; 
	if(HAL_GPIO_ReadPin(INPUT2_GPIO_Port, INPUT2_Pin) == RESET) joyStick_HID.button_group0 |= 0x01 << 1;
	if(HAL_GPIO_ReadPin(INPUT3_GPIO_Port, INPUT3_Pin) == RESET) joyStick_HID.button_group0 |= 0x01 << 2;
	if(HAL_GPIO_ReadPin(INPUT4_GPIO_Port, INPUT4_Pin) == RESET) joyStick_HID.button_group0 |= 0x01 << 3;
	if(HAL_GPIO_ReadPin(INPUT5_GPIO_Port, INPUT5_Pin) == RESET) joyStick_HID.button_group0 |= 0x01 << 4;
	if(HAL_GPIO_ReadPin(INPUT6_GPIO_Port, INPUT6_Pin) == RESET) joyStick_HID.button_group0 |= 0x01 << 5;
	if(HAL_GPIO_ReadPin(INPUT7_GPIO_Port, INPUT7_Pin) == RESET) joyStick_HID.button_group0 |= 0x01 << 6;
	if(HAL_GPIO_ReadPin(INPUT8_GPIO_Port, INPUT8_Pin) == RESET) joyStick_HID.button_group0 |= 0x01 << 7;
	if(HAL_GPIO_ReadPin(INPUT9_GPIO_Port, INPUT9_Pin) == RESET) joyStick_HID.button_group1 |= 0x01 << 0;
	if(HAL_GPIO_ReadPin(INPUTA_GPIO_Port, INPUTA_Pin) == RESET) joyStick_HID.button_group1 |= 0x01 << 1;
	
	USBD_HID_Mouse_SendReport(&hUsbDevice, (uint8_t*)&joyStick_HID, sizeof(struct joyStick_HID_t));
}



