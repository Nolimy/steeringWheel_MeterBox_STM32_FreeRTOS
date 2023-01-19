#include "Bsp_USB_CDC.h"
#include "usbd_cdc_if.h"


void usb_printf(const char *format, ...)
{
	va_list args;
	uint32_t length;
	uint8_t buff[APP_TX_DATA_SIZE];
	
	va_start(args, format);
	length = vsnprintf((char *)buff, APP_TX_DATA_SIZE, (char *)format, args);
	
	va_end(args);
	CDC_Transmit_FS(buff, length);
	
}




