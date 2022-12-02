#ifndef __INCLUDE_PRINT_H_
#define __INCLUDE_PRINT_H_

#include "stdint.h"

void put_char(uint8_t char_ascii);
uint32_t put_str(const char *str);
void cls();

void get_cursor(uint8_t *w, uint8_t *h);
void set_cursor(uint8_t w, uint8_t h);

#endif