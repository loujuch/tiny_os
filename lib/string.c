#include "string.h"

#include "debug.h"
#include "stdint.h"

void memset(void *dst, uint8_t val, uint32_t size) {
	ASSERT(dst != NULL);
	uint8_t *p_dst = (uint8_t *)dst;
	while(size--) {
		*p_dst++ = val;
	}
}

void memcpy(void *dst, void *src, uint32_t size) {
	ASSERT(dst != NULL);
	ASSERT(src != NULL);
	uint8_t *p_dst = (uint8_t *)dst;
	uint8_t *p_src = (uint8_t *)src;
	while(size--) {
		*p_dst++ = *p_src++;
	}
}

int32_t memcmp(void *left, void *right, uint32_t size) {
	ASSERT(left != NULL);
	ASSERT(right != NULL);
	uint8_t *p_left = (uint8_t *)left;
	uint8_t *p_right = (uint8_t *)right;
	while(size--) {
		if(*p_left != *p_right) {
			return (*p_left > *p_right) ? 1 : -1;
		}
		++p_left;
		++p_right;
	}
	return 0;
}

uint32_t strlen(const char *str) {
	ASSERT(str != NULL);
	char *p = (char *)str;
	while(*p++);
	return p - str - 1;
}

int32_t strcmp(const char *left, const char *right) {
	ASSERT(left != NULL);
	ASSERT(right != NULL);
	while(*left && *left == *right) {
		++left;
		++right;
	}
	return (*left < *right) ? -1 : (*left > right);
}

char *strcpy(char *dst, const char *src) {
	ASSERT(dst != NULL);
	ASSERT(src != NULL);
	char *backup = dst;
	while(*dst++ = *src++);
	return backup;
}

char *strcat(char *dst, const char *src) {
	ASSERT(dst != NULL);
	ASSERT(src != NULL);
	uint32_t size = strlen(dst);
	strcpy(dst + size, src);
	return dst;
}

uint32_t strchrs(const char *str, const char ch) {
	ASSERT(str != NULL);
	uint32_t number = 0;
	while(*str) {
		number += (ch == *str++);
	}
	return number;
}

char *strchr(const char *str, const char ch) {
	ASSERT(str != NULL);
	while(*str && *str != ch) {
		++str;
	}
	return (*str) ? ((char *)str) : NULL;
}

char *strrchr(const char *str, const char ch) {
	ASSERT(str != NULL);
	const char *site = NULL;
	while(*str) {
		if(ch == *str) {
			site = str;
		}
		++str;
	}
	return (char *)site;
}