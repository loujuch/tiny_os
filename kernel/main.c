#include "print.h"
#include "init.h"

void main() {
	set_cursor(0, 0);
	init_all();
	asm volatile("sti");
	while(1);
}