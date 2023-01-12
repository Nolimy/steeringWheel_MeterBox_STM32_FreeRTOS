/*******************************************************************************
 * Size: 30 px
 * Bpp: 1
 * Opts: --bpp 1 --size 30 --font C:\Users\zhaip\Documents\SquareLine\assets\iconfont.ttf -o C:\Users\zhaip\Documents\SquareLine\assets\ui_font_icon_bettery.c --format lvgl -r 0xe60c-0xe7fa --no-compress --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_ICON_BETTERY
#define UI_FONT_ICON_BETTERY 1
#endif

#if UI_FONT_ICON_BETTERY

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+E60C "" */
    0xef, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xfb,
    0xff, 0xff, 0xff, 0xdf, 0xf0, 0xf0, 0xfe, 0xff,
    0x87, 0x87, 0xf7, 0xfc, 0x3c, 0x3f, 0xbf, 0xe1,
    0xe1, 0xfd, 0xe1, 0xf0, 0xff, 0xef, 0xf, 0x87,
    0xff, 0x78, 0x7c, 0x3f, 0xfb, 0xc3, 0xe1, 0xff,
    0xde, 0x1f, 0xf, 0xfe, 0xff, 0x87, 0x87, 0xf7,
    0xfc, 0x3c, 0x3f, 0xbf, 0xe1, 0xe1, 0xfd, 0xff,
    0xf, 0xf, 0xef, 0xff, 0xff, 0xff, 0x7f, 0xff,
    0xff, 0xfb, 0xff, 0xff, 0xff, 0xc0, 0x0, 0x0,
    0xe, 0x0, 0x0, 0x0, 0x70, 0x0, 0x0, 0x3,
    0x80, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0xe0,
    0x0, 0x0, 0x7, 0x0, 0x0, 0x0, 0x38, 0x0,
    0x0, 0x1, 0xc0, 0x0, 0x0, 0xe, 0x0, 0x0,
    0x0, 0x70, 0x0, 0x0, 0x0,

    /* U+E613 "" */
    0x1f, 0xc0, 0x0, 0x3f, 0xfe, 0x0, 0x1f, 0xfc,
    0x70, 0x1f, 0xff, 0x3, 0xff, 0xff, 0xc0, 0x7f,
    0xff, 0xf0, 0x1f, 0xfe, 0xf, 0x87, 0xfe, 0x3,
    0xfd, 0xff, 0x80, 0xff, 0xff, 0x60, 0x3f, 0xf0,
    0x19, 0xff, 0xfc, 0x7, 0xff, 0xff, 0x1, 0xff,
    0xcf, 0xc0, 0xff, 0xf0, 0x7f, 0xff, 0xfc, 0x7,
    0xff, 0xff, 0x1, 0xff, 0xf8, 0xf0, 0x7f, 0xf0,
    0x7, 0x9f, 0xf0, 0x0, 0x3f, 0xf8, 0x0, 0x0,
    0x60,

    /* U+E618 "" */
    0x0, 0x1, 0xfc, 0x0, 0x0, 0x0, 0x0, 0xf,
    0x3f, 0xc0, 0x3c, 0x3f, 0xff, 0x10, 0x0, 0xff,
    0xff, 0xff, 0x43, 0xff, 0xff, 0xff, 0xc7, 0xff,
    0xff, 0x7f, 0xcf, 0xff, 0xff, 0xff, 0x30, 0x0,
    0x3, 0x80,

    /* U+E61B "" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0xf8, 0x0,
    0x3, 0xff, 0x0, 0x1, 0xfc, 0x60, 0x0, 0x7c,
    0xc, 0x0, 0x1e, 0x1, 0x80, 0x7, 0x8, 0x70,
    0x1, 0xc3, 0x8e, 0xf, 0xf0, 0x79, 0x83, 0xfc,
    0xe, 0x70, 0xfb, 0x80, 0xe, 0x38, 0x60, 0x3,
    0x8f, 0xfc, 0x0, 0x61, 0xff, 0x0, 0x1c, 0x30,
    0xe0, 0x7, 0x0, 0xe, 0x1, 0xc0, 0x0, 0xe0,
    0xf0, 0x0, 0x4e, 0x7c, 0x0, 0x3e, 0xff, 0x80,
    0x7, 0xcf, 0x30, 0x1, 0xd8, 0xe6, 0x0, 0x37,
    0xd, 0xc0, 0x7, 0xe1, 0xf0, 0x0, 0xf0, 0x3e,
    0x0, 0x0, 0xf, 0x80, 0x0, 0x1, 0xe0, 0x0,
    0x0, 0x30, 0x0, 0x0,

    /* U+E623 "" */
    0x1f, 0x0, 0x3, 0xe0, 0xff, 0xff, 0xff, 0xcf,
    0xff, 0xff, 0xff, 0xe0, 0x0, 0x0, 0x3, 0x9b,
    0x6c, 0xdb, 0x66, 0x6d, 0xb3, 0x6d, 0x99, 0xb6,
    0xcd, 0xb6, 0x66, 0xdb, 0x36, 0xd9, 0x9b, 0x6c,
    0xdb, 0x66, 0x6d, 0xb3, 0x6d, 0x99, 0xb6, 0xcd,
    0xb6, 0x66, 0xdb, 0x36, 0xd9, 0x9b, 0x6c, 0xdb,
    0x66, 0x6d, 0xb3, 0x6d, 0x99, 0xb6, 0xcd, 0xb6,
    0x66, 0xdb, 0x36, 0xd9, 0x9b, 0x6c, 0xdb, 0x66,
    0x6d, 0xb3, 0x6d, 0x99, 0xb6, 0xcd, 0xb6, 0x66,
    0xdb, 0x36, 0xd9, 0x9b, 0x6c, 0xdb, 0x66, 0x6d,
    0xb3, 0x6d, 0x98, 0x0, 0x0, 0x0, 0xff, 0xff,
    0xff, 0xff, 0x7f, 0xff, 0xff, 0xf8,

    /* U+E63D "" */
    0x7f, 0xff, 0xf9, 0x0, 0x0, 0xa, 0x0, 0x0,
    0x14, 0x0, 0x0, 0x28, 0x1, 0xc0, 0x70, 0x3,
    0x70, 0xe1, 0xfc, 0x1, 0xc0, 0x38, 0x3, 0x80,
    0x0, 0x5, 0x0, 0x0, 0xa, 0x0, 0x0, 0x13,
    0xff, 0xff, 0xc0,

    /* U+E63E "" */
    0x7, 0x80, 0x0, 0x7f, 0x80, 0x3, 0xff, 0x80,
    0x1f, 0xff, 0x80, 0xff, 0xf1, 0x1, 0xff, 0x80,
    0x3, 0xfc, 0x0, 0x11, 0x0, 0xe, 0x0, 0x70,
    0xfc, 0x6, 0x67, 0xf8, 0x10, 0x9f, 0xe0, 0x7a,
    0xff, 0x81, 0x1b, 0xfd, 0xe1, 0xcf, 0xff, 0xe0,
    0x3f, 0xff, 0xc0, 0xfe, 0xff, 0x81, 0xf3, 0xfe,
    0x7, 0x87, 0xfc, 0x10, 0x1f, 0xf1, 0x80, 0x3f,
    0xc0, 0x0, 0x7f, 0x0, 0x0, 0xfc, 0x0, 0x0,

    /* U+E649 "" */
    0x0, 0x3, 0xc0, 0x0, 0x0, 0xff, 0x0, 0x0,
    0x1f, 0xfc, 0x0, 0x0, 0xf8, 0x30, 0x0, 0x7,
    0x0, 0xc0, 0x1c, 0x38, 0x3, 0x1, 0xf1, 0xc0,
    0x8, 0x7f, 0xce, 0x10, 0x61, 0xf7, 0x30, 0xe1,
    0x80, 0x1c, 0xc7, 0xc, 0x0, 0x63, 0x38, 0x30,
    0x1, 0x8d, 0xc1, 0x80, 0xe, 0x3e, 0xe, 0x0,
    0x30, 0x70, 0x70, 0x7f, 0xc1, 0xff, 0x87, 0xfe,
    0x7, 0xf8, 0x38, 0x38, 0x30, 0x1, 0xc1, 0xc0,
    0xc0, 0x6, 0xe, 0x7, 0x0, 0x30, 0x78, 0x18,
    0x0, 0xc3, 0xcc, 0x60, 0x6, 0x1e, 0x31, 0x80,
    0x18, 0x71, 0xce, 0xf8, 0x60, 0x7, 0x3f, 0xe3,
    0x0, 0x38, 0xf8, 0xc, 0x1, 0xc3, 0x80, 0x30,
    0x1e, 0x0, 0x0, 0xc3, 0xf0, 0x0, 0x3, 0xff,
    0x0, 0x0, 0xf, 0xe0, 0x0,

    /* U+E682 "" */
    0x1f, 0x80, 0x7e, 0x7, 0xe0, 0x1f, 0x80, 0x0,
    0x0, 0x1, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff,
    0xf0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0xf, 0x0,
    0x0, 0x3, 0xc0, 0x0, 0x0, 0xf0, 0x0, 0x18,
    0x3c, 0x0, 0x6, 0xf, 0x0, 0x1, 0x83, 0xcf,
    0xf3, 0xfc, 0xf3, 0xfc, 0xff, 0x3c, 0x0, 0x6,
    0xf, 0x0, 0x1, 0x83, 0xc0, 0x0, 0x60, 0xf0,
    0x0, 0x0, 0x3c, 0x0, 0x0, 0xf, 0x0, 0x0,
    0x3, 0xc0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xf7,
    0xff, 0xff, 0xf8,

    /* U+E711 "" */
    0x1, 0xff, 0xf8, 0xf, 0xff, 0xf0, 0x70, 0x1,
    0xc3, 0x80, 0xf, 0xe, 0x0, 0x78, 0x70, 0x1,
    0xc1, 0xc0, 0xf, 0xe, 0x0, 0x38, 0x78, 0x1,
    0xe1, 0xc0, 0xf, 0xe, 0x0, 0x38, 0x3f, 0xc0,
    0xfc, 0x7f, 0x1, 0xf0, 0x1c, 0x3, 0xc0, 0x70,
    0x1f, 0x3, 0xc0, 0x78, 0xe, 0x3, 0xc0, 0x38,
    0x1e, 0x1, 0xc0, 0xf0, 0x7, 0x7, 0x80, 0x3c,
    0x3c, 0x0, 0xe0, 0xe0, 0x3, 0x87, 0x0, 0x1c,
    0x38, 0x0, 0x7f, 0xc0, 0x0, 0xfe, 0x0, 0x0,

    /* U+E712 "" */
    0x7f, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xef, 0xff,
    0xff, 0xfb, 0x80, 0x0, 0xe, 0xe6, 0x0, 0x3,
    0xbb, 0x80, 0xe0, 0xfe, 0xe3, 0x3e, 0x3f, 0xb8,
    0x3f, 0xef, 0xee, 0x7, 0x3b, 0xfb, 0x80, 0x40,
    0xfe, 0x0, 0x0, 0x3b, 0xff, 0xff, 0xfe, 0xff,
    0xff, 0xff, 0x9f, 0xff, 0xff, 0xc0,

    /* U+E71A "" */
    0x1, 0xff, 0x80, 0x0, 0x3f, 0xf0, 0x0, 0x0,
    0x70, 0x0, 0x0, 0xe, 0x0, 0x0, 0x1, 0xc0,
    0x0, 0x3, 0xff, 0xf0, 0x0, 0xff, 0xfe, 0x78,
    0x3f, 0xff, 0xcf, 0xc7, 0xff, 0xf9, 0xf8, 0xff,
    0xff, 0x3f, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1,
    0xff, 0xff, 0xfe, 0x3f, 0xff, 0xcf, 0xc7, 0xff,
    0xf9, 0xf8, 0xff, 0xff, 0x3c, 0x0, 0xff, 0xe7,
    0x80, 0xf, 0xfc, 0x0,

    /* U+E736 "" */
    0xc0, 0x0, 0x0, 0x3, 0xf1, 0x80, 0x0, 0x3,
    0xcf, 0x0, 0x0, 0xc, 0xec, 0x0, 0x0, 0x37,
    0x18, 0x80, 0x0, 0xf8, 0x66, 0x0, 0x4, 0x1e,
    0xfe, 0x0, 0x10, 0x3, 0xff, 0x0, 0x7f, 0xf0,
    0x1f, 0x83, 0x2, 0x0, 0x1f, 0xc, 0xc, 0x0,
    0xc6, 0xf0, 0x37, 0xff, 0x1f, 0xe1, 0x9f, 0xfc,
    0x79, 0xfe, 0x0, 0x1f, 0x3, 0xf0, 0x0, 0x38,
    0x0, 0x0, 0x0, 0x0,

    /* U+E7A7 "" */
    0x7f, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xc,
    0x0, 0x0, 0xc, 0x30, 0x0, 0x0, 0x30, 0xc0,
    0x0, 0x0, 0xc3, 0x18, 0x0, 0x3, 0x3c, 0x60,
    0x0, 0xc, 0xf1, 0x80, 0x0, 0x33, 0xc6, 0x0,
    0x0, 0xcf, 0x18, 0x0, 0x3, 0x3c, 0x60, 0x0,
    0xc, 0xf1, 0x80, 0x0, 0x33, 0xc0, 0x0, 0x0,
    0xc3, 0x0, 0x0, 0x3, 0xc, 0x0, 0x0, 0xc,
    0x3f, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0x80,

    /* U+E7D5 "" */
    0x0, 0x8, 0x0, 0x0, 0xe, 0x0, 0x0, 0xf,
    0x80, 0x0, 0x7, 0xe0, 0x0, 0x6, 0xd0, 0x0,
    0x6, 0x64, 0x0, 0x6, 0x33, 0x0, 0x3, 0x18,
    0xc0, 0x3, 0xc, 0x20, 0x3, 0x6, 0x8, 0x3,
    0x3, 0x6, 0x1, 0x3, 0xc1, 0x81, 0x83, 0x30,
    0x41, 0x87, 0xe, 0x31, 0xbe, 0xcd, 0xed, 0xf0,
    0x3c, 0x1f, 0xe0, 0x0, 0x1, 0xb8, 0x0, 0x3,
    0x86, 0x0, 0x1, 0x1, 0xc0, 0x0, 0x0, 0x30,
    0x3, 0x0, 0xe, 0x6, 0x0, 0x1, 0x86, 0x0,
    0x0, 0x7e, 0x0, 0x0, 0xc, 0x0, 0x0,

    /* U+E7F2 "" */
    0x0, 0x0, 0x7, 0x0, 0x0, 0x0, 0xe, 0x0,
    0x0, 0x0, 0x1c, 0x0, 0x1d, 0xe0, 0x0, 0x0,
    0x38, 0x18, 0x0, 0x0, 0x0, 0x8, 0x62, 0x0,
    0x6d, 0x84, 0xee, 0x5, 0xd9, 0x41, 0x98, 0x1d,
    0x0, 0x20, 0x0, 0x38, 0x0, 0x4e, 0x0, 0x60,
    0x20, 0x18, 0xc0, 0x3, 0x68, 0x3, 0x80, 0x66,
    0x6, 0x0, 0x61, 0xc0, 0x1, 0x98, 0xd8, 0x3,
    0x1, 0x12, 0x78, 0x14, 0xc, 0xc6, 0x60, 0x84,
    0x19, 0x0, 0x2, 0x48, 0xc0, 0x60, 0x4, 0x80,
    0x18, 0xc0, 0x4, 0x18, 0x46, 0x0, 0x1b, 0x30,
    0x30, 0x0, 0x0, 0x18, 0x80, 0x0, 0x26, 0x30,
    0x0, 0x0, 0xc, 0x64, 0x0, 0x0, 0x62, 0x1c,
    0x0, 0x0, 0xce, 0x3b, 0x80, 0x0, 0x18, 0x7,
    0x0, 0x0, 0xc7, 0xe, 0x0, 0x1, 0x8e, 0x8,
    0x0, 0x0, 0x8, 0x0, 0x0,

    /* U+E7FA "" */
    0xff, 0x3e, 0xf, 0x1f, 0xef, 0xc7, 0xfb, 0x1,
    0xc, 0xc3, 0x60, 0x21, 0xb8, 0x7c, 0x8, 0x6,
    0x7, 0x81, 0x0, 0xc0, 0xff, 0xa0, 0x18, 0x1f,
    0xf4, 0x3, 0x3, 0xc0, 0x80, 0x60, 0x78, 0x10,
    0x34, 0xb, 0x1, 0xc, 0xc3, 0x60, 0x11, 0x8c,
    0xcf, 0xf1, 0xe0, 0xf0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 480, .box_w = 29, .box_h = 30, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 109, .adv_w = 480, .box_w = 26, .box_h = 20, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 174, .adv_w = 480, .box_w = 30, .box_h = 9, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 208, .adv_w = 480, .box_w = 27, .box_h = 27, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 300, .adv_w = 480, .box_w = 30, .box_h = 25, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 394, .adv_w = 480, .box_w = 23, .box_h = 12, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 429, .adv_w = 480, .box_w = 22, .box_h = 23, .ofs_x = 5, .ofs_y = 0},
    {.bitmap_index = 493, .adv_w = 480, .box_w = 30, .box_h = 29, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 602, .adv_w = 480, .box_w = 26, .box_h = 23, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 480, .box_w = 22, .box_h = 26, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 749, .adv_w = 480, .box_w = 26, .box_h = 14, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 795, .adv_w = 480, .box_w = 27, .box_h = 20, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 863, .adv_w = 480, .box_w = 30, .box_h = 16, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 923, .adv_w = 480, .box_w = 30, .box_h = 17, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 987, .adv_w = 480, .box_w = 25, .box_h = 25, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 1066, .adv_w = 500, .box_w = 31, .box_h = 30, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1183, .adv_w = 480, .box_w = 27, .box_h = 13, .ofs_x = 1, .ofs_y = 5}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x7, 0xc, 0xf, 0x17, 0x31, 0x32, 0x3d,
    0x76, 0x105, 0x106, 0x10e, 0x12a, 0x19b, 0x1c9, 0x1e6,
    0x1ee
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 58892, .range_length = 495, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 17, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t ui_font_icon_bettery = {
#else
lv_font_t ui_font_icon_bettery = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 30,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_ICON_BETTERY*/

