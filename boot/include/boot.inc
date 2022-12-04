;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; mbr
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
MBR_START_ADDR equ 0x7c00

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; kernel
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
KERNEL_SECTIOR_LENGTH equ 32
KERNEL_START_SECTIOR equ 5
KERNEL_LOAD_ADDR equ 0x9f00
KERNEL_RUN_ADDR equ 0x7E00

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; loader
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LOADER_START_SECTIOR equ 1
LOADER_SECTIOR_LENGTH equ 4
LOADER_START_ADDR equ 0x500
LOADER_CODE_ADDR equ 0x900
LOADER_STACK_TOP equ LOADER_START_ADDR

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; GDT
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
DESC_G_4K	equ 00000000_1_0_0_0_0000_0_00_0_0000_00000000b
DESC_G_1B	equ 00000000_0_0_0_0_0000_0_00_0_0000_00000000b

DESC_D_32	equ 00000000_0_1_0_0_0000_0_00_0_0000_00000000b
DESC_D_16	equ 00000000_0_0_0_0_0000_0_00_0_0000_00000000b

DESC_L_64	equ 00000000_0_0_1_0_0000_0_00_0_0000_00000000b
DESC_L_32	equ 00000000_0_0_0_0_0000_0_00_0_0000_00000000b

DESC_AVL	equ 00000000_0_0_0_0_0000_0_00_0_0000_00000000b

DESC_LIMIT_CODE2	equ 00000000_0_0_0_0_1111_0_00_0_0000_00000000b
DESC_LIMIT_DATA2	equ DESC_LIMIT_CODE2
DESC_LIMIT_VIDEO2	equ 00000000_0_0_0_0_0000_0_00_0_0000_00000000b

DESC_P_EXIST	equ 00000000_0_0_0_0_0000_1_00_0_0000_00000000b
DESC_P_NO_EXIST	equ 00000000_0_0_0_0_0000_0_00_0_0000_00000000b

DESC_DPL_0	equ 00000000_0_0_0_0_0000_0_00_0_0000_00000000b
DESC_DPL_1	equ 00000000_0_0_0_0_0000_0_01_0_0000_00000000b
DESC_DPL_2	equ 00000000_0_0_0_0_0000_0_10_0_0000_00000000b
DESC_DPL_3	equ 00000000_0_0_0_0_0000_0_11_0_0000_00000000b

DESC_S_CODE	equ 00000000_0_0_0_0_0000_0_00_1_0000_00000000b
DESC_S_DATA	equ DESC_S_CODE
DESC_S_SYS	equ 00000000_0_0_0_0_0000_0_00_0_0000_00000000b

;只可执行、读
DESC_TYPE_CODE	equ 00000000_0_0_0_0_0000_0_00_0_1000_00000000b
;只可读写
DESC_TYPE_DATA	equ 00000000_0_0_0_0_0000_0_00_0_0010_00000000b

DESC_CODE_HIGH4	equ (0x00<<24)+DESC_G_4K+DESC_D_32+DESC_L_32+DESC_AVL+ \
DESC_LIMIT_CODE2+DESC_P_EXIST+DESC_DPL_0+DESC_S_CODE+DESC_TYPE_CODE+0x00

DESC_DATA_HIGH4	equ (0x00<<24)+DESC_G_4K+DESC_D_32+DESC_L_32+DESC_AVL+ \
DESC_LIMIT_DATA2+DESC_P_EXIST+DESC_DPL_0+DESC_S_DATA+DESC_TYPE_DATA+0x00

DESC_VIDEO_HIGH4	equ (0x00<<24)+DESC_G_4K+DESC_D_32+DESC_L_32+DESC_AVL+ \
DESC_LIMIT_VIDEO2+DESC_P_EXIST+DESC_DPL_0+DESC_S_DATA+DESC_TYPE_DATA+0x0b

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; GDT SELECTOR
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
RPL0	equ 00b
RPL1	equ 01b
RPL2	equ 10b
RPL3	equ 11b

TI_GDT	equ 000b
TI_LDT	equ 100b

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; page table
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PAGE_DIR_TABLE_POS	equ 0x100000

PG_P_EXIST	equ 1b
PG_P_NO_EXIST	equ 0b

PG_RW_R	equ 00b
PG_RW_W	equ 10b

PG_US_S	equ 000b
PG_US_U	equ 100b