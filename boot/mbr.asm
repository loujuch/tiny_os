%include "boot.inc"

section mbr vstart=MBR_START_ADDR
	; 设置当前的段寄存器
	mov ax, cs
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov fs, ax

	; 设置段指针
	mov sp, MBR_START_ADDR -1

	; 设置显示段基址
	mov ax, 0xb800
	mov gs, ax

	; 清屏
	mov ax, 0x600
	mov bx, 0x700
	mov cx, 0
	mov dx, 0x184f
	int 0x10

	; 加载loader
	mov al, LOADER_SECTIOR_LENGTH
	mov bx, LOADER_START_ADDR
	mov ecx, LOADER_START_SECTIOR
	call read_disk

	; 加载kernel
	mov al, KERNEL_SECTIOR_LENGTH
	mov bx, KERNEL_RUN_ADDR
	mov ecx, KERNEL_START_SECTIOR
	call read_disk

	jmp LOADER_CODE_ADDR

; 从磁盘读取数据的函数
;    al:读入扇区数
;    bx:读入内存位置
;    ecx:LBA28值
read_disk:
	; 写入读入扇区数
	mov dx, 0x1f2
	out dx, al
	mov ah, al

	; 写入LBA28值
	; 低8位
	mov al, cl
	mov dx, 0x1f3
	out dx, al

	; 中间8位
	shr ecx, 8
	mov al, cl
	mov dx, 0x1f4
	out dx, al

	; 高8位
	shr ecx, 8
	mov al, cl
	mov dx, 0x1f5
	out dx, al

	; 最高4位，设置读取主盘，LBA模式
	shr ecx, 8
	and cl, 0xf
	or cl, 0xe0
	mov al, cl
	mov dx, 0x1f6
	out dx, al

	; 设置“读”命令
	mov al, 0x20
	mov dx, 0x1f7
	out dx, al

no_ready:
	nop
	in al, dx
	and al, 0x89
	cmp al, 0x8
	jne no_ready

	mov al, 0
	mov cx, ax
	mov dx, 0x1f0
read_a_block:
	in ax, dx
	mov [bx], ax
	add bx, 2
	loop read_a_block
	ret

	; 设置mbr尾部使mbr有效
	times 510 - ($ - $$) db 0x0
	db 0x55, 0xaa