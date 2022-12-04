#include "init.h"

#include "interrupt.h"
#include "timer.h"
#include "print.h"

void init_all() {
	put_str("init all start\n");
	idt_init();
	timer_init();
	put_str("init all end\n");
}