#include "interrupt.h"

#include "global.h"
#include "stdint.h"
#include "io.h"
#include "print.h"

#define IDT_DESC_CNT 0x21

#define PIC_M_CTRL 0x20
#define PIC_M_DATA 0x21
#define PIC_S_CTRL 0xa0
#define PIC_S_DATA 0xa1

// 各中断名称
char *intr_name[IDT_DESC_CNT];

// 各中断处理函数入口地址
intr_handler idt_table[IDT_DESC_CNT];

// 引入的各中断处理函数
extern intr_handler intr_entry_table[IDT_DESC_CNT];

// 中断描述符结构
struct gate_desc {
	uint16_t func_offset_low_word;
	uint16_t selector;
	uint8_t dcount;
	uint8_t attribute;
	uint16_t func_offset_high_word;
};

// 最后的中断描述符表
static struct gate_desc idt[IDT_DESC_CNT];

// 通用的中断处理函数
static void general_intr_handler(uint8_t vec_nr) {
	if(vec_nr == 0x27 || vec_nr == 0x2f) {
		return;
	}
	put_str("intr vector: ");
	put_uint32(vec_nr);
	put_char('\n');
}

// 注册中断处理函数与异常名称
static void exception_init() {
	put_str("exception init start\n");
	int i;
	for(i = 0;i < IDT_DESC_CNT;++i) {
		idt_table[i] = general_intr_handler;
		intr_name[i] = "unknown";
	}
	intr_name[0] = "#DE Divide Error";
	intr_name[1] = "#DB Debug Exception";
	intr_name[2] = "NMI Interrupt";
	intr_name[3] = "#BP Breakpoint Exception";
	intr_name[4] = "#OF Overflow Exception";
	intr_name[5] = "#BR BOUND Range Exceeded Exception";
	intr_name[6] = "#UD Invalid Opcode Exception";
	intr_name[7] = "#NM Device Not Available Exception";
	intr_name[8] = "#DF Double Fault Exception";
	intr_name[9] = "Coprocessor Segment Overrun";
	intr_name[10] = "#TS nvalid TSS Exception";
	intr_name[11] = "#NP Segment Not Present";
	intr_name[12] = "#SS Stack Fault Exception";
	intr_name[13] = "#GP General Protection Exception";
	intr_name[14] = "#PF Page-Fault Exception";
	// intr_name[15］第 15 项是 intel 保留项，未使用
	intr_name[16] = "#MF x87 FPU Floating-Point Error";
	intr_name[17] = "#AC Alignment Check Exception";
	intr_name[18] = "#MC Machine-Check Exception";
	intr_name[19] = "#XF SIMD Floating-Point Exception ";
	put_str("exception init end\n");
}

// 设置一个中断描述符表项
static void make_a_gate_desc(struct gate_desc *p_desc, uint8_t attr, intr_handler func) {
	p_desc->attribute = attr;
	p_desc->dcount = 0;
	uint32_t handler = (uint32_t)func;
	p_desc->func_offset_low_word = handler & 0xffff;
	p_desc->func_offset_high_word = handler >> 16;
	p_desc->selector = SELECT_K_CODE;
}

// 初始化中断描述符表项
static void idt_desc_init() {
	put_str("idt desc init start\n");
	int i;
	for(i = 0;i < IDT_DESC_CNT;++i) {
		make_a_gate_desc(&idt[i], IDT_DESC_ATTR_DPL0, intr_entry_table[i]);
	}
	put_str("idt desc init end\n");
}

// 初始化PIC
static void pic_init() {
	put_str("pic init start\n");
	// 初始化主片
	outb(PIC_M_CTRL, 0x11);
	outb(PIC_M_DATA, 0x20);
	outb(PIC_M_DATA, 0x04);
	outb(PIC_M_DATA, 0x01);

	// 初始化从片
	outb(PIC_S_CTRL, 0x11);
	outb(PIC_S_DATA, 0x28);
	outb(PIC_S_DATA, 0x02);
	outb(PIC_S_DATA, 0x01);

	// 打开主片上的IRO
	outb(PIC_M_DATA, 0xfe);
	outb(PIC_S_DATA, 0xff);
	put_str("pic init end\n");
}

void idt_init() {
	put_str("idt init start\n");
	// 注册中断函数
	exception_init();
	// 初始化中断描述符表
	idt_desc_init();
	// 初始化PIC
	pic_init();

	// 加载IDT（使用内连汇编）
	uint64_t idt_ptr = (sizeof(idt) - 1) | (((uint64_t)((int32_t)idt)) << 16);
	asm volatile("lidt %0"::"m"(idt_ptr));
	put_str("idt init end\n");
}

// IF在eflags中的位置
#define EFLAGES_IF 0x200

// 获取当前中断状态
enum intr_status intr_get_status() {
	uint32_t status = 0;
	asm volatile("pushfl; \
				popl %0":"=g"(status));
	return (status & EFLAGES_IF) ? INTR_ON : INTR_OFF;
}

// 设置当前中断状态
enum intr_status intr_set_status(enum intr_status status) {
	return (status == INTR_ON) ? intr_enable() : intr_disable();
}

// 打开中断
enum intr_status intr_enable() {
	enum intr_status status = intr_get_status();
	if(status != INTR_ON) {
		asm volatile("sti");
	}
	return status;
}

// 关闭中断
enum intr_status intr_disable() {
	enum intr_status status = intr_get_status();
	if(status != INTR_OFF) {
		asm volatile("cli":::"memory");
	}
	return status;
}