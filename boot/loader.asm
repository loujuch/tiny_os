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
	mov esp, 0x7c00
	mov ax, VEDIO_SELECTOR
	mov gs, ax

	; 创建页表与页目录表(页表在0x10000)
	call setup_page_table

	; 更新GDT
	; 更新显存段数据
	sgdt [gdt_ptr]
	mov ebx, [gdt_ptr+2]
	or dword [ebx +0x18 +4], 0xc0000000
	; 更新GDT_BASE
	add dword [gdt_ptr+2], 0xc0000000
	; 更新esp
	add esp, 0xc0000000
	; 设置CR3，写入段目录表基址
	mov eax, PAGE_DIR_TABLE_POS
	mov cr3, eax
	; 设置CR0，开启分页模式
	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax
	;设置GDTR
	lgdt [gdt_ptr]
	jmp $

	;创建页目录（PAGE_DIR_TABLE_POS）以及第一个系统页表（PAGE_DIR_TABLE_POS+0x1000）
setup_page_table:
	; 创建页目录表
	; 页目录表清0
	mov ecx, 4096
	mov ebx, 0
clear_page_dir_table:
	mov byte [PAGE_DIR_TABLE_POS+ebx], 0
	inc ebx
	loop clear_page_dir_table
	; 设置页目录表项
	mov eax, PAGE_DIR_TABLE_POS+0x1000
	or eax, PG_US_U | PG_RW_W | PG_P_EXIST
	; 第一个页表
	mov [PAGE_DIR_TABLE_POS], eax
	; 第一个页表放到3GB开始的地方
	mov [PAGE_DIR_TABLE_POS+0xc00], eax
	; 最后一个页表指向自身
	mov dword [PAGE_DIR_TABLE_POS+4092], PAGE_DIR_TABLE_POS | PG_US_U | PG_RW_W | PG_P_EXIST

	; 创建第一个页表，将其映射到低1MB
	mov ebx, 0x0
	mov ecx, 256
	mov edx, PG_US_U | PG_RW_W | PG_P_EXIST
create_page_table:
	mov [PAGE_DIR_TABLE_POS+0x1000+ebx*4], edx
	add edx, 4096
	inc ebx
	loop create_page_table

	; 设置其他页目录项
	mov edx, PAGE_DIR_TABLE_POS+0x2000
	or edx, PG_US_U | PG_RW_W | PG_P_EXIST
	mov ebx, 769
	mov ecx, 254
create_page_dir_table:
	mov [PAGE_DIR_TABLE_POS+ebx*4], edx
	add edx, 0x1000
	inc ebx
	loop create_page_dir_table
	ret