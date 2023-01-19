#include "SH_Data.h"
#include "Bsp_USB_CDC.h"
#include "jsmn.h"

//½âÎöÊı¾İ
//USB Received {"RPM":0,"SPEED":0,"GEAR":"N","FUEL":0,"LFBRAKE":0,"RFBRAKE":0,}

jsmntok_t token[128]; /* We expect no more than 128 JSON tokens */
jsmn_parser p;
struct SH_CarData sh_CarData;
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
    if (jsoneq(string, &token[i], "RPM") == 0) {
      /* We may use strndup() to fetch string value */
			sh_CarData.rpm = strtol(string + token[i + 1].start, &stopStr, 10);
//      usb_printf("- Name: %.*s\n", token[i + 1].end -token[i + 1].start,
//             string + token[i + 1].start);
      i++;
    } else if (jsoneq(string, &token[i], "SPE") == 0) {
			sh_CarData.speed = strtol(string + token[i + 1].start, &stopStr, 10);
//      usb_printf("- Admin: %.*s\n", token[i + 1].end - token[i + 1].start,
//             string + token[i + 1].start);
      i++;
    } else if (jsoneq(string, &token[i], "GE") == 0) {
      /* We may want to do strtol() here to get numeric value */
			//sh_CarData.Gear = (uint8_t *)(string + token[i + 1].start);
			//sprintf((char *)sh_CarData.Gear, "%.*s", token[i + 1].end - token[i + 1].start,
      //       string + token[i + 1].start);
			sh_CarData.Gear = (uint8_t *)(string + token[i + 1].start);
            usb_printf("- Gear: %.*s\n", token[i + 1].end - token[i + 1].start,
             string + token[i + 1].start);
      i++;
    } else if (jsoneq(string, &token[i], "FUE") == 0){
			sh_CarData.fuel = strtol(string + token[i + 1].start, &stopStr, 10);
//      usb_printf("- HeiHei: %.*s\n", token[i + 1].end - token[i + 1].start,
//             string + token[i + 1].start);
			i++;
    } else if (jsoneq(string, &token[i], "LFB") == 0){
				sh_CarData.lfBrake = strtol(string + token[i + 1].start, &stopStr, 10);
//      usb_printf("- HeiHei: %.*s\n", token[i + 1].end - token[i + 1].start,
//             string + token[i + 1].start);
			i++;
		} else if (jsoneq(string, &token[i], "RFB") == 0){
				sh_CarData.rfBrake = strtol(string + token[i + 1].start, &stopStr, 10);
//      usb_printf("- HeiHei: %.*s\n", token[i + 1].end - token[i + 1].start,
//             string + token[i + 1].start);
			i++;
		}
	}
	return 0;
}


void json_analysis(char *Buf)
{
	jsmn_init(&p);
	parse_data(&p, Buf);
}




