#include "SH_Data.h"
#include "Bsp_USB_CDC.h"

struct SH_CarData sh_CarData;
#include "jsmn.h"

//½âÎöÊı¾İ
//USB Received {"RPM":0,"SPEED":0,"GEAR":"N","FUEL":0,"LFBRAKE":0,"RFBRAKE":0,}

jsmntok_t token[128]; /* We expect no more than 128 JSON tokens */
jsmn_parser p;

char *stopStr;


static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}
 

uint8_t	parse_data(jsmn_parser *p, char *string)
{
	int r;
	int i;
	
	r = jsmn_parse(p, string, strlen(string), token, sizeof(token) / sizeof(token[0])); 
	
	if(r < 0)
	{
		usb_printf("Failed to parse JSON: %d\n", r);
		return 1;
	}
	
	
	/* Assume the top-level element is an object */
  if (r < 1 || token[0].type != JSMN_OBJECT) {
    printf("Object expected\n");
    return 1;
  }
	
	/* Loop over all keys of the root object */
  for (i = 1; i < r; i++) {
    if (jsoneq(string, &token[i], "R") == 0) {
      /* We may use strndup() to fetch string value */
			sh_CarData.rpm = strtol(string + token[i + 1].start, &stopStr, 10);
//      usb_printf("- Name: %.*s\n", token[i + 1].end -token[i + 1].start,
//             string + token[i + 1].start);
      i++;
    } else if (jsoneq(string, &token[i], "S") == 0) {
			sh_CarData.speed = strtol(string + token[i + 1].start, &stopStr, 10);
//      usb_printf("- Admin: %.*s\n", token[i + 1].end - token[i + 1].start,
//             string + token[i + 1].start);
      i++;
    } else if (jsoneq(string, &token[i], "G") == 0) {
      /* We may want to do strtol() here to get numeric value */
			//sh_CarData.Gear = (uint8_t *)(string + token[i + 1].start);
			//sprintf((char *)sh_CarData.Gear, "%.*s", token[i + 1].end - token[i + 1].start,
      //       string + token[i + 1].start);
			sh_CarData.Gear = (uint8_t *)(string + token[i + 1].start);
            usb_printf("- Gear: %.*s\n", token[i + 1].end - token[i + 1].start,
             string + token[i + 1].start);
      i++;
    } else if (jsoneq(string, &token[i], "F") == 0){
			sh_CarData.fuel = strtol(string + token[i + 1].start, &stopStr, 10);
//      usb_printf("- HeiHei: %.*s\n", token[i + 1].end - token[i + 1].start,
//             string + token[i + 1].start);
			i++;
    } else if (jsoneq(string, &token[i], "L") == 0){
				sh_CarData.lfBrake = strtol(string + token[i + 1].start, &stopStr, 10);
//      usb_printf("- HeiHei: %.*s\n", token[i + 1].end - token[i + 1].start,
//             string + token[i + 1].start);
			i++;
		} else if (jsoneq(string, &token[i], "R") == 0){
				sh_CarData.rfBrake = strtol(string + token[i + 1].start, &stopStr, 10);
//      usb_printf("- HeiHei: %.*s\n", token[i + 1].end - token[i + 1].start,
//             string + token[i + 1].start);
			i++;
		} 
		else if (jsoneq(string, &token[i], "B") == 0) {
      /* We may want to do strtol() here to get numeric value */
			sh_CarData.bLapTime = (uint8_t *)(string + token[i + 1].start);
            usb_printf("- BestTime: %.*s\n", token[i + 1].end - token[i + 1].start,
             string + token[i + 1].start);
      i++;
    } 
		else if (jsoneq(string, &token[i], "C") == 0) {
      /* We may want to do strtol() here to get numeric value */
			sh_CarData.cLapTime = (uint8_t *)(string + token[i + 1].start);
            usb_printf("- CurrentTime: %.*s\n", token[i + 1].end - token[i + 1].start,
             string + token[i + 1].start);
      i++;
    }
	}
	return 0;
}

void json_analysis(char *Buf)
{
	jsmn_init(&p);
	parse_data(&p, Buf);
//	json_error_t error;
//  json_t *root;
//  json_t *status;
//	
//	root = json_loads((const char *)Buf, 0, &error);
//	if(json_is_object(root))
//	{
//		sh_CarData.speed = json_integer_value(json_object_get(root, "SP"));
//		sh_CarData.rpm = json_integer_value(json_object_get(root, "RP"));
//		sh_CarData.cLapTime = (uint8_t *)json_string_value(json_object_get(root, "CT"));
//		//sh_CarData.bLapTime = (uint8_t *)json_string_value(json_object_get(root, "BT"));
//		sh_CarData.Gear = (uint8_t *)json_string_value(json_object_get(root, "GE"));
//		//sh_CarData.fuel = json_integer_value(json_object_get(root, "FU"));
//	}
//	
//	else
//	{
//		usb_printf("root format error:%d-%s\r\n", error.line, error.text);
//	}
	
}




