#ifndef __INCLUDE_STRING_H_
#define __INCLUDE_STRING_H_

#include "stdint.h"

void memset(void *dst, uint8_t val, uint32_t size);
void memcpy(void *dst, void *src, uint32_t size);
int32_t memcmp(void *left, void *right, uint32_t size);

uint32_t strlen(const char *str);
int32_t strcmp(const char *left, const char *right);
char *strcpy(char *dst, const char *src);
char *strcat(char *det, const char *src);
uint32_t strchrs(const char *str, const char ch);
char *strchr(const char *str, const char ch);
char *strrchr(const char *str, const char ch);

#endif