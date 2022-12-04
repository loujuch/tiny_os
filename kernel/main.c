#include "print.h"
#include "init.h"

#include "string.h"

void main() {
	set_cursor(0, 0);
	init_all();
	char test1[1024] = "this is a test1!";
	char test2[1024] = "this is a test2!";
	put_uint32(strlen(test1));
	put_char('\n');
	put_uint32(strcmp(test1, test2));
	put_char('\n');
	put_str(strcat(test1, test2));
	put_char('\n');
	put_str(strcpy(test1, test2));
	put_char('\n');
	put_uint32(strchrs(test1, 'i'));
	put_char('\n');
	put_str(strchr(test1, 'i'));
	put_char('\n');
	put_str(strrchr(test1, 'i'));
	put_char('\n');
	while(1);
}