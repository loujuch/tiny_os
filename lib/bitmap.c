#include "bitmap.h"

#include "debug.h"
#include "print.h"

// 初始化bitmap
void bitmap_init(struct bitmap *bmap, uint32_t size) {
	ASSERT(bmap != NULL && size != 0);
	bmap->bitmap_size = size;
	memset(bmap->map, 0, bmap->bitmap_size);
}

// 分配连续的size个位并完成设置；若成功，返回首地址；若失败，返回-1
int32_t bitmap_scan_block(struct bitmap *bmap, uint32_t size) {
	ASSERT(bmap != NULL && size != 0);
	uint32_t tsize = bmap->bitmap_size - (size >> 3);
	uint32_t i = 0, bnum = 0;
	int32_t site = -1;
	uint8_t *p = bmap->map;

	for(i = 0;i < tsize;++i) {
		// 若该字节均已分配，则跳过
		if(p[i] == 0xff) {
			continue;
		}
		bnum = 0;
		// 可以在当前块内分配
		uint32_t index = 0;
		// 块内空闲足够或到达最顶端
		while(bnum < size && index < 8) {
			if((p[i] >> index) & 0x1) {
				bnum = 0;
				site = -1;
			} else {
				site = site == -1 ? index : site;
				++bnum;
			}
			++index;
		}

		// 块内空闲不够且无顶端空闲
		if(bnum == 0) {
			continue;
		}
		// 块内空闲足够
		if(bnum == size) {
			// 设置为已使用
			uint8_t tmp = 0xff;
			tmp = (~(tmp << size)) << site;
			p[i] |= tmp;
			return site | (i << 3);
		}
		// 是否需要其他块
		uint32_t mbyte = (size - bnum) >> 3;
		uint32_t mbit = (size - bnum) & 0x7;

		uint32_t j = 0;
		// 整块确认
		for(j = i + 1;j <= i + mbyte;++j) {
			if(p[j] != 0x00) {
				break;
			}
		}

		if(j != i + mbyte + 1) {
			site = -1;
			i = j - 1;
			continue;
		}

		// 结束块确认
		uint8_t tmp = 0xff;
		tmp = ~(tmp << mbit);
		if((tmp & p[j]) != 0) {
			i = j - 1;
			site = -1;
			continue;
		}

		// 开始设置已使用标识
		p[j] |= tmp;
		for(j = i + 1;j <= i + mbyte;++j) {
			p[j] = 0xff;
		}
		tmp = 0xff;
		tmp = tmp << site;
		p[i] |= tmp;
		return site | (i << 3);
	}
	return -1;
}

// 测试bitmap的第index位是否已使用
enum bit_status bitmap_test(struct bitmap *bmap, uint32_t index) {
	ASSERT(bmap != NULL && index < (bmap->bitmap_size << 3));
	uint32_t idx = index >> 3;
	uint32_t offset = index & 0x7;
	return ((bmap->map[idx] >> offset) & 0x1) ? bit_used : bit_free;
}

// 设置bitmap的第index位为以使用
void bitmap_used(struct bitmap *bmap, uint32_t index) {
	ASSERT(bmap != NULL && index < (bmap->bitmap_size << 3));
	uint32_t idx = index >> 3;
	uint32_t offset = index & 0x7;
	bmap->map[idx] |= 1 << offset;
}

// 设置bitmap的第index位为未使用
void bitmap_free(struct bitmap *bmap, uint32_t index) {
	ASSERT(bmap != NULL && index < (bmap->bitmap_size << 3));
	uint32_t idx = index >> 3;
	uint32_t offset = index & 0x7;
	bmap->map[idx] &= ~(1 << offset);
}

// 设置bitmap的第index位为给定值
void bitmap_set(struct bitmap *bmap, uint32_t index, enum bit_status status) {
	ASSERT(bmap != NULL && index < (bmap->bitmap_size << 3));
	return status == bit_used ? bitmap_used(bmap, index) : bitmap_free(bmap, index);
}