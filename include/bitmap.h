#ifndef __INCLUDE_BITMAP_H_
#define __INCLUDE_BITMAP_H_

#include "stdint.h"
#include "string.h"

enum bit_status { bit_used, bit_free };

struct bitmap {
	uint32_t bitmap_size;
	uint8_t *map;
};

void bitmap_init(struct bitmap *bmap, uint32_t size);

int32_t bitmap_scan_block(struct bitmap *bmap, uint32_t size);

enum bit_status bitmap_test(struct bitmap *bmap, uint32_t index);

void bitmap_used(struct bitmap *bmap, uint32_t index);

void bitmap_free(struct bitmap *bmap, uint32_t index);

void bitmap_set(struct bitmap *bmap, uint32_t index, enum bit_status status);

#endif