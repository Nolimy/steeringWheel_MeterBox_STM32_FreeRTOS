// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.3.3
// PROJECT: SquareLine_Project


#include "ui.h"
#include "ui_helpers.h"
#include "ui_comp.h"

uint32_t LV_EVENT_GET_COMP_CHILD;

typedef struct {
    uint32_t child_idx;
    lv_obj_t * child;
} ui_comp_get_child_t;

lv_obj_t * ui_comp_get_child(lv_obj_t * comp, uint32_t child_idx)
{
    ui_comp_get_child_t info;
    info.child = NULL;
    info.child_idx = child_idx;
    lv_event_send(comp, LV_EVENT_GET_COMP_CHILD, &info);
    return info.child;
}

void get_component_child_event_cb(lv_event_t * e)
{
    lv_obj_t ** c = lv_event_get_user_data(e);
    ui_comp_get_child_t * info = lv_event_get_param(e);
    info->child = c[info->child_idx];
}

void del_component_child_event_cb(lv_event_t * e)
{
    lv_obj_t ** c = lv_event_get_user_data(e);
    lv_mem_free(c);
}


// COMPONENT speedMeter

lv_obj_t * ui_speedMeter_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_speedMeter;
    cui_speedMeter = lv_arc_create(comp_parent);
    lv_obj_set_width(cui_speedMeter, 177);
    lv_obj_set_height(cui_speedMeter, 177);
    lv_obj_set_x(cui_speedMeter, -129);
    lv_obj_set_y(cui_speedMeter, -13);
    lv_obj_set_align(cui_speedMeter, LV_ALIGN_CENTER);
    lv_arc_set_range(cui_speedMeter, 0, 120);
    lv_arc_set_value(cui_speedMeter, 0);
    lv_arc_set_bg_angles(cui_speedMeter, 90, 0);

    lv_obj_t * cui_SpeedMeterNum;
    cui_SpeedMeterNum = lv_label_create(cui_speedMeter);
    lv_obj_set_width(cui_SpeedMeterNum, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_SpeedMeterNum, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(cui_SpeedMeterNum, 0);
    lv_obj_set_y(cui_SpeedMeterNum, -10);
    lv_obj_set_align(cui_SpeedMeterNum, LV_ALIGN_CENTER);
    lv_label_set_text(cui_SpeedMeterNum, "000");
    lv_obj_set_style_text_color(cui_SpeedMeterNum, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_SpeedMeterNum, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(cui_SpeedMeterNum, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(cui_SpeedMeterNum, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_SpeedMeterNum, &ui_font_bigNumber40, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_speedUnit;
    cui_speedUnit = lv_label_create(cui_speedMeter);
    lv_obj_set_width(cui_speedUnit, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_speedUnit, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(cui_speedUnit, 0);
    lv_obj_set_y(cui_speedUnit, 23);
    lv_obj_set_align(cui_speedUnit, LV_ALIGN_CENTER);
    lv_label_set_text(cui_speedUnit, "KMH");
    lv_obj_set_style_text_color(cui_speedUnit, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_speedUnit, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_SPEEDMETER_NUM);
    children[UI_COMP_SPEEDMETER_SPEEDMETER] = cui_speedMeter;
    children[UI_COMP_SPEEDMETER_SPEEDMETERNUM] = cui_SpeedMeterNum;
    children[UI_COMP_SPEEDMETER_SPEEDUNIT] = cui_speedUnit;
    lv_obj_add_event_cb(cui_speedMeter, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_speedMeter, del_component_child_event_cb, LV_EVENT_DELETE, children);
    return cui_speedMeter;
}

