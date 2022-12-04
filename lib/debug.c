#include "debug.h"

#include "interrupt.h"
#include "print.h"

void panic_spin(char *filename, int line, const char *func, const char *condition) {
	intr_disable();
	put_str("---------ERROR---------\n");
	put_str("file name: ");
	put_str(filename);
	put_char('\n');
	put_str("line: ");
	put_uint32(line);
	put_char('\n');
	put_str("function: ");
	put_str((char *)func);
	put_char('\n');
	put_str("condition: ");
	put_str((char *)condition);
	put_char('\n');
	while(1);
}