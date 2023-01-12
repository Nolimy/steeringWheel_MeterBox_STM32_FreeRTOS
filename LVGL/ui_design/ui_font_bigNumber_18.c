/*******************************************************************************
 * Size: 18 px
 * Bpp: 1
 * Opts: --bpp 1 --size 18 --font C:\Users\zhaip\Documents\SquareLine\assets\big-numbers.ttf -o C:\Users\zhaip\Documents\SquareLine\assets\ui_font_bigNumber_18.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_BIGNUMBER_18
#define UI_FONT_BIGNUMBER_18 1
#endif

#if UI_FONT_BIGNUMBER_18

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0030 "0" */
    0x7f, 0xbf, 0xfe, 0x1f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0x40, 0x90, 0x2e, 0x1f, 0x87, 0xe1,
    0xf8, 0x7e, 0x1f, 0x87, 0xff, 0xdf, 0xe0,

    /* U+0031 "1" */
    0x5f, 0xff, 0xf, 0xff, 0x50,

    /* U+0032 "2" */
    0x7f, 0x8f, 0xf0, 0x1c, 0x7, 0x1, 0xc0, 0x70,
    0x1c, 0x7, 0x3f, 0x9f, 0xce, 0x3, 0x80, 0xe0,
    0x38, 0xe, 0x3, 0x80, 0xff, 0x1f, 0xe0,

    /* U+0033 "3" */
    0xff, 0x7f, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3,
    0x7d, 0x7e, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3,
    0x7f, 0xff,

    /* U+0034 "4" */
    0x80, 0x70, 0x3e, 0x1f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0x7f, 0x8f, 0xe0, 0x1c, 0x7, 0x1,
    0xc0, 0x70, 0x1c, 0x7, 0x0, 0xc0, 0x10,

    /* U+0035 "5" */
    0x7f, 0xbf, 0xce, 0x3, 0x80, 0xe0, 0x38, 0xe,
    0x3, 0x80, 0x7f, 0xf, 0xe0, 0x1c, 0x7, 0x1,
    0xc0, 0x70, 0x1c, 0x7, 0x3f, 0xdf, 0xe0,

    /* U+0036 "6" */
    0x7f, 0xbf, 0xce, 0x3, 0x80, 0xe0, 0x38, 0xe,
    0x3, 0x80, 0x7f, 0x1f, 0xee, 0x1f, 0x87, 0xe1,
    0xf8, 0x7e, 0x1f, 0x87, 0xff, 0xdf, 0xe0,

    /* U+0037 "7" */
    0x7f, 0x8f, 0xf1, 0xfc, 0x7, 0x1, 0xc0, 0x70,
    0x1c, 0x7, 0x0, 0x80, 0x0, 0x18, 0x7, 0x1,
    0xc0, 0x70, 0x1c, 0x7, 0x0, 0xc0, 0x10,

    /* U+0038 "8" */
    0x7f, 0xbf, 0xfe, 0x1f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0x7f, 0x9f, 0xee, 0x1f, 0x87, 0xe1,
    0xf8, 0x7e, 0x1f, 0x87, 0xff, 0xdf, 0xe0,

    /* U+0039 "9" */
    0x7f, 0xbf, 0xfe, 0x1f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0x7f, 0x8f, 0xe0, 0x1c, 0x7, 0x1,
    0xc0, 0x70, 0x1c, 0x7, 0x3f, 0xdf, 0xe0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 288, .box_w = 10, .box_h = 18, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 23, .adv_w = 288, .box_w = 2, .box_h = 18, .ofs_x = 8, .ofs_y = 0},
    {.bitmap_index = 28, .adv_w = 288, .box_w = 10, .box_h = 18, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 51, .adv_w = 288, .box_w = 8, .box_h = 18, .ofs_x = 5, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 288, .box_w = 10, .box_h = 18, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 92, .adv_w = 288, .box_w = 10, .box_h = 18, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 288, .box_w = 10, .box_h = 18, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 288, .box_w = 10, .box_h = 18, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 288, .box_w = 10, .box_h = 18, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 288, .box_w = 10, .box_h = 18, .ofs_x = 4, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 48, .range_length = 10, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t ui_font_bigNumber_18 = {
#else
lv_font_t ui_font_bigNumber_18 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_BIGNUMBER_18*/

