TI_GDT equ 0
RPL0 equ 0
SELECTOR_VEDIO equ (0x3<<3)+TI_GDT+RPL0

[bits 32]
section .text
global put_char
global cls
global get_cursor
global set_cursor
global put_str
put_char:
	pushad
	; 初始化gs
	mov ax, SELECTOR_VEDIO
	mov gs, ax

	; 得到光标位置
	call get_cursor_value
	shl eax, 1

	; 获取要打印字符
	mov ecx, [esp+36]

	; 根据字符种类选择打印方式
	; 是回车'\r'或换行'\n'，这里将其一样的处理，均是换行+光标置于行首
	cmp cl, 0xd
	jz is_carriage_reture
	cmp cl, 0xa
	jz is_line_feed
	; 是删除符'Backspace'
	cmp cl, 0x8
	jz is_backspace

	; 是普通字符
	; 如果是屏幕上的最后一个字符，则需要上卷一行，并设置光标在新行行首
	cmp eax, 2*80*25-2
	jne show_char
	call scroll_line
	mov eax, 2*80*24

show_char:
	; 进行打印
	mov [gs:eax], cl
	inc eax
	mov byte [gs:eax], 0x7

	; 设置下一光标位置
	shr eax, 1
	inc eax
	call set_cursor_value

	jmp put_char_done

is_backspace:
	; 如果是屏幕上的第一个字符，则无需删除
	test eax, eax
	je put_char_done
	dec eax
	mov byte [gs:eax], 0x7
	dec eax
	mov byte [gs:eax], 0x0
	call set_cursor_value
	jmp put_char_done
	
is_carriage_reture:
is_line_feed:
	shr eax, 1
	add eax, 80
	mov edx, 0
	mov ebx, 80
	div ebx
	cmp eax, 25
	jne set_new_cursor
	call scroll_line
	mov eax, 24
set_new_cursor:
	mul ebx
	call set_cursor_value

put_char_done:
	popad
	ret

	; 将屏幕上卷一行，光标的绝对位置不变
scroll_line:
	push ecx
	push esi
	push edi
	; 向上搬运一行
	cld
	mov ecx, 960
	mov esi, 0xc00b80a0
	mov edi, 0xc00b8000
	rep movsd

	; 将尾行赋0
	mov ecx, 80
	mov esi, 3840
scroll_line_loop:
	mov word [gs:esi], 0x700
	add esi, 2
	loop scroll_line_loop
	pop edi
	pop esi
	pop ecx
	ret

; 清空屏幕，光标绝对位置不变
cls:
	push ecx

	; 置屏幕为空
	mov ecx, 80*25
	mov eax, 0
cls_loop:
	mov byte [gs:eax], 0x0
	inc eax
	mov byte [gs:eax], 0x7
	inc eax
	loop cls_loop

	pop ecx
	ret

	; 光标位置的索引设置光标位置
	;   光标位置的索引在eax中
set_cursor_value:
	push dx

	shl eax, 8
	; 设置低8位
	mov dx, 0x3d4
	mov al, 0xf
	out dx, al
	mov dx, 0x3d5
	shr eax, 8
	out dx, al

	; 设置高8位
	mov dx, 0x3d4
	mov al, 0xe
	out dx, al
	mov dx, 0x3d5
	mov al, ah
	out dx, al

	pop dx
	ret

	; 返回光标位置的索引
get_cursor_value:
	push dx
	xor eax, eax
	; 获取高8位
	mov dx, 0x3d4
	mov al, 0xe
	out dx, al
	mov dx, 0x3d5
	in al, dx
	mov ah, al

	; 获取低8位
	mov dx, 0x3d4
	mov al, 0xf
	out dx, al
	mov dx, 0x3d5
	in al, dx
	pop dx
	ret

get_cursor:
	pushad
	; 获取光标位置索引
	call get_cursor_value
	; 转化为h（eax），w（edx）的形式
	mov ebx, 80
	mov edx, 0
	div ebx
	; 获取输入h（edi），w（esi）
	mov esi, [esp+36]
	mov edi, [esp+40]
	; 输出结果
	mov [esi], dl
	mov [edi], al
	popad
	ret

set_cursor:
	pushad
	; 获取输入h（eax），w（ecx）
	mov ecx, [esp+36]
	mov eax, [esp+40]
	; 判断是否合法
	cmp cl, 79
	ja set_cursor_done
	cmp al, 24
	ja set_cursor_done
	; 转换为索引形式
	mov ebx, 80
	mul ebx
	add eax, ecx
	call set_cursor_value
set_cursor_done:
	popad
	ret

put_str:
	push esi
	push ebx
	xor eax, eax
	mov esi, [esp+12]
put_str_loop:
	mov bl, [esi]
	inc esi
	test bl, bl
	je put_str_done
	push ebx
	call put_char
	add esp, 4
	inc eax
	jmp put_str_loop
put_str_done:
	pop ebx
	pop esi
	ret