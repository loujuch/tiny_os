#ifndef __INCLUDE_PRINT_H_
#define __INCLUDE_PRINT_H_

#include "stdint.h"

#define COLOR_BLACK 0x0
#define COLOR_BLUE 0x1
#define COLOR_GREEN 0x2
#define COLOR_CYAN 0x3
#define COLOR_RED 0x4
#define COLOR_FUCHSINE 0x5
#define COLOR_BROWN 0x6
#define COLOR_WHITE 0x7

#define COLOR_HIGH_LIGHT 0x8

#define COLOR_BLACK_BG 0x00
#define COLOR_BLUE_BG 0x10
#define COLOR_GREEN_BG 0x20
#define COLOR_CYAN_BG 0x30
#define COLOR_RED_BG 0x40
#define COLOR_FUCHSINE_BG 0x50
#define COLOR_BROWN_BG 0x60
#define COLOR_WHITE_BG 0x70

#define COLOR_FLASH 0x80

void put_colorful_char(uint8_t char_ascii, uint8_t color);
void put_char(uint8_t char_ascii);
uint32_t put_str(const char *str);
void put_uint32(uint32_t num);

void scroll_line();
void cls();

void get_cursor(uint8_t *w, uint8_t *h);
void set_cursor(uint8_t w, uint8_t h);

#endif