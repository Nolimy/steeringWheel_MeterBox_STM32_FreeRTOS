// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.3.3
// PROJECT: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

void ui_event_startup(lv_event_t * e);
extern lv_obj_t * ui_startup;
extern lv_obj_t * ui_startupBar;
extern lv_obj_t * ui_startupLogo;
extern lv_obj_t * ui_home;
extern lv_obj_t * ui_logoLable;
extern lv_obj_t * ui_rpmNum;
extern lv_obj_t * ui_rpmUnit;
extern lv_obj_t * ui_gearLable;
extern lv_obj_t * ui_socValue;
extern lv_obj_t * ui_socIcon;
extern lv_obj_t * ui_speedMode;
extern lv_obj_t * ui_ecoMode;
extern lv_obj_t * ui_iotStatus;
extern lv_obj_t * ui_batTemp;
extern lv_obj_t * ui_lMotorTemp;
extern lv_obj_t * ui_rMotorTemp;
extern lv_obj_t * ui_speedNum;
extern lv_obj_t * ui_speedUnitLable;
extern lv_obj_t * ui_bespLapTime;
extern lv_obj_t * ui_lapTime;
extern lv_obj_t * ui_bestLapTimeLable;
extern lv_obj_t * ui_lapTimeLable;
extern lv_obj_t * ui_speedMeter;

extern uint8_t barFlag;

extern uint32_t SPEED_CHANGED;
extern uint32_t MQTT_INIT_OK;

LV_IMG_DECLARE(ui_img_splashmini_png);    // assets\splashmini.png


LV_FONT_DECLARE(ui_font_bigNumber40);
LV_FONT_DECLARE(ui_font_bigNumber_18);
LV_FONT_DECLARE(ui_font_bigNumber_25);
LV_FONT_DECLARE(ui_font_FastOne);
LV_FONT_DECLARE(ui_font_icon_bettery);
LV_FONT_DECLARE(ui_font_PlayFairBig);
LV_FONT_DECLARE(ui_font_PlayFairSmall);


void ui_init(void);
void sendEventCode();



#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
