#ifndef __INCLUDE_INTERRUPT_H_
#define __INCLUDE_INTERRUPT_H_

typedef void *intr_handler;

void idt_init();

enum intr_status {
	INTR_OFF = 0,
	INTR_ON = 1
};

enum intr_status intr_get_status();
enum intr_status intr_set_status(enum intr_status status);
enum intr_status intr_enable();
enum intr_status intr_disable();

#endif