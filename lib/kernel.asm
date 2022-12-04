[bits 32]
%define ERROR_CODE nop
%define ZERO push 0

extern idt_table

section .data
global intr_entry_table
intr_entry_table:

%macro INTR_VECTOR 2
section .text
intr_%1_entry:
	; 写入的操作
	%2

	; 保存上下文
	push ds
	push es
	push fs
	push gs
	pushad

	; 返回EOI
	mov al, 0x20
	out 0xa0, al
	out 0x20, al

	; 调用函数
	push %1
	call [idt_table + %1 * 4]
	add esp, 4
	
	; 恢复现场
	popad
	pop gs
	pop fs
	pop es
	pop ds

	; 跨过error code
	add esp, 4
	iretd

section .data
	dd intr_%1_entry

%endmacro

INTR_VECTOR 0x00, ZERO
INTR_VECTOR 0x01, ZERO
INTR_VECTOR 0x02, ZERO
INTR_VECTOR 0x03, ZERO
INTR_VECTOR 0x04, ZERO
INTR_VECTOR 0x05, ZERO
INTR_VECTOR 0x06, ZERO
INTR_VECTOR 0x07, ZERO
INTR_VECTOR 0x08, ZERO
INTR_VECTOR 0x09, ZERO
INTR_VECTOR 0x0a, ZERO
INTR_VECTOR 0x0b, ZERO
INTR_VECTOR 0x0c, ZERO
INTR_VECTOR 0x0d, ZERO
INTR_VECTOR 0x0e, ZERO
INTR_VECTOR 0x0f, ZERO
INTR_VECTOR 0x10, ZERO
INTR_VECTOR 0x11, ZERO
INTR_VECTOR 0x12, ZERO
INTR_VECTOR 0x13, ZERO
INTR_VECTOR 0x14, ZERO
INTR_VECTOR 0x15, ZERO
INTR_VECTOR 0x16, ZERO
INTR_VECTOR 0x17, ZERO
INTR_VECTOR 0x18, ZERO
INTR_VECTOR 0x19, ZERO
INTR_VECTOR 0x1a, ZERO
INTR_VECTOR 0x1b, ZERO
INTR_VECTOR 0x1c, ZERO
INTR_VECTOR 0x1d, ZERO
INTR_VECTOR 0x1e, ERROR_CODE
INTR_VECTOR 0x1f, ZERO
INTR_VECTOR 0x20, ZERO
