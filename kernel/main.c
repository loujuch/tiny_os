#include "print.h"
#include "init.h"

#include "bitmap.h"

void main() {
	set_cursor(0, 0);
	init_all();
	uint8_t map[8];
	struct bitmap bmap;
	bmap.map = map;
	bitmap_init(&bmap, 8);
	put_uint32(bmap.bitmap_size);
	put_char('\n');
	put_uint32(bmap.map[0]);
	put_char('\n');
	put_uint32(bmap.map[1]);
	put_char('\n');
	put_uint32(bmap.map[2]);
	put_char('\n');
	put_uint32(bmap.map[3]);
	put_char('\n');
	put_uint32(bmap.map[4]);
	put_char('\n');
	put_uint32(bmap.map[5]);
	put_char('\n');
	put_uint32(bmap.map[6]);
	put_char('\n');
	put_uint32(bmap.map[7]);
	put_char('\n');
	put_char('\n');
	bitmap_used(&bmap, 2);
	bitmap_used(&bmap, 36);
	bitmap_used(&bmap, 42);
	bitmap_used(&bmap, 45);
	bitmap_used(&bmap, 59);
	put_uint32(bmap.map[0]);
	put_char('\n');
	put_uint32(bmap.map[1]);
	put_char('\n');
	put_uint32(bmap.map[2]);
	put_char('\n');
	put_uint32(bmap.map[3]);
	put_char('\n');
	put_uint32(bmap.map[4]);
	put_char('\n');
	put_uint32(bmap.map[5]);
	put_char('\n');
	put_uint32(bmap.map[6]);
	put_char('\n');
	put_uint32(bmap.map[7]);
	put_char('\n');
	put_char('\n');
	uint32_t tmp = bitmap_scan_block(&bmap, 29);
	put_uint32(tmp);
	put_char('\n');
	put_uint32(bmap.map[0]);
	put_char('\n');
	put_uint32(bmap.map[1]);
	put_char('\n');
	put_uint32(bmap.map[2]);
	put_char('\n');
	put_uint32(bmap.map[3]);
	put_char('\n');
	put_uint32(bmap.map[4]);
	put_char('\n');
	put_uint32(bmap.map[5]);
	put_char('\n');
	put_uint32(bmap.map[6]);
	put_char('\n');
	put_uint32(bmap.map[7]);
	put_char('\n');
	put_char('\n');
	tmp = bitmap_scan_block(&bmap, 2);
	put_uint32(tmp);
	put_char('\n');
	put_uint32(bmap.map[0]);
	put_char('\n');
	put_uint32(bmap.map[1]);
	put_char('\n');
	put_uint32(bmap.map[2]);
	put_char('\n');
	put_uint32(bmap.map[3]);
	put_char('\n');
	put_uint32(bmap.map[4]);
	put_char('\n');
	put_uint32(bmap.map[5]);
	put_char('\n');
	put_uint32(bmap.map[6]);
	put_char('\n');
	put_uint32(bmap.map[7]);
	put_char('\n');
	put_char('\n');
	tmp = bitmap_scan_block(&bmap, 29);
	put_uint32(tmp);
	put_char('\n');
	put_uint32(bmap.map[0]);
	put_char('\n');
	put_uint32(bmap.map[1]);
	put_char('\n');
	put_uint32(bmap.map[2]);
	put_char('\n');
	put_uint32(bmap.map[3]);
	put_char('\n');
	put_uint32(bmap.map[4]);
	put_char('\n');
	put_uint32(bmap.map[5]);
	put_char('\n');
	put_uint32(bmap.map[6]);
	put_char('\n');
	put_uint32(bmap.map[7]);
	put_char('\n');
	put_char('\n');
	tmp = bitmap_scan_block(&bmap, 8);
	put_uint32(tmp);
	put_char('\n');
	put_uint32(bmap.map[0]);
	put_char('\n');
	put_uint32(bmap.map[1]);
	put_char('\n');
	put_uint32(bmap.map[2]);
	put_char('\n');
	put_uint32(bmap.map[3]);
	put_char('\n');
	put_uint32(bmap.map[4]);
	put_char('\n');
	put_uint32(bmap.map[5]);
	put_char('\n');
	put_uint32(bmap.map[6]);
	put_char('\n');
	put_uint32(bmap.map[7]);
	put_char('\n');
	put_char('\n');
	while(1);
}