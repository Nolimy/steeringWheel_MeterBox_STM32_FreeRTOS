#ifndef _BSP_USB_COMPOSITE_H_
#define _BSP_USB_COMPOSITE_H_

#include "usb_device.h"
#include "stdio.h"
#include "stdarg.h"

void usb_printf(const char *format, ...);
void USB_ControlData_Send();
 
#endif  //_BSP_USB_COMPOSITE_H_
