#ifndef __INCLUDE_GLOBAL_H_
#define __INCLUDE_GLOBAL_H_

// 段选择子属性
#define RPL0 0
#define RPL1 1
#define RPL2 2
#define RPL3 3

#define TI_GDT 0
#define TI_LDT 1

#define SELECT_K_CODE ((1 << 3) + (TI_GDT << 2) + RPL0)
#define SELECT_K_DATA ((2 << 3) + (TI_GDT << 2) + RPL0)
#define SELECT_K_STACK SELECT_K_DATA
#define SELECT_K_VIDEO ((3 << 3) + (TI_GDT << 2) + RPL0)

// IDT属性
#define IDT_DESC_P 1

#define IDT_DESC_DPL0 0
#define IDT_DESC_DPL1 1
#define IDT_DESC_DPL2 2
#define IDT_DESC_DPL3 3

#define IDT_DESC_32_TYPE 0xE
#define IDT_DESC_16_TYPE 0x6

#define IDT_DESC_ATTR_DPL0 ((IDT_DESC_P << 7) + (IDT_DESC_DPL0 << 5) + IDT_DESC_32_TYPE)
#define IDT_DESC_ATTR_DPL3 ((IDT_DESC_P << 7) + (IDT_DESC_DPL3 << 5) + IDT_DESC_32_TYPE)

#endif