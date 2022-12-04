#ifndef __INCLUDE_IO_H_
#define __INCLUDE_IO_H_

#include "stdint.h"

// 向port写入一个字节
static inline void outb(uint16_t port, uint8_t data) {
	asm volatile("outb %b0, %w1"::"a"(data), "Nd"(port));
}

// 向port写入addr开始的word_cnt个字
static inline void outsw(uint16_t port, const void *addr, uint32_t word_cnt) {
	asm volatile("cld; \
				rep outsw":"+S"(addr), "+c"(word_cnt) : "d"(port));
}

// 从port读入1个字节
static inline uint8_t inb(uint16_t port) {
	uint8_t data;
	asm volatile("inb %w1, %b0":"=a"(data) : "Nd"(port));
	return data;
}

// 从port读入word_cnt个字到addr
static inline void insw(uint16_t port, const void *addr, uint32_t word_cnt) {
	asm volatile("cld; \
				rep insw":"+D"(addr), "+c"(word_cnt) : "d"(port) : "memory");
}

#endif