%include "boot.inc"

section loader vstart=LOADER_START_ADDR
	;设置GDT
	; GDT第0项一般弃置不用
GDT_BASE:
	dd 00000000
	dd 00000000

	; 代码段
GDT_CODE:
	dd 0x0000ffff
	dd DESC_CODE_HIGH4
	; 堆栈段
GDT_STACK:
	dd 0x0000ffff
	dd DESC_DATA_HIGH4
	; 显存段
GDT_VEDIO:
	dd 0x80000007
	dd DESC_VIDEO_HIGH4

	times 60 dq 0

	; GDT大小
	GDT_SIZE	equ	$-GDT_BASE
	GDT_LIMIT	equ	GDT_SIZE-1

	; GDT对应指针
gdt_ptr:
	dw GDT_LIMIT
	dd GDT_BASE

	; GDT选择符
	CODE_SELECTOR equ (0x1<<3)+TI_GDT+RPL0
	DATA_SELECTOR equ (0x2<<3)+TI_GDT+RPL0
	VEDIO_SELECTOR equ (0x3<<3)+TI_GDT+RPL0

	times LOADER_CODE_ADDR-LOADER_START_ADDR-($-$$) db 0x00

	; loader代码开始
start:
	; 打开A20地址线
	in al, 0x92
	or al, 0x2
	out 0x92, al

	; 设置GDT
	lgdt [gdt_ptr]

	; 设置CR0
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax

	; 以进入保护模式，使用jmp清空流水线
	jmp dword CODE_SELECTOR:protect_start

[bits 32]
protect_start:
	; 初始化寄存器
	mov ax, DATA_SELECTOR
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov esp, LOADER_STACK_TOP
	mov ax, VEDIO_SELECTOR
	mov gs, ax
	jmp $