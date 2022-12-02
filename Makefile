CASM = nasm
CC = gcc-4.4 -m32 -c 
LINK = ld -m elf_i386 -Ttext 0x7E00 -e main
OBJCOPY = objcopy -O binary

#镜像信息
IMAGE_NAME = test
IMAGE_SIZE = 60

#各部分长度
MBR_COUNT = 1
LOADER_COUNT = 4
KERNEL_COUNT = 16

#偏移量
SEEK = 0

#写入块大小
BLOCK_SIZE = 512

image: $(IMAGE_NAME).img mbr.bin loader.bin kernel.bin
	dd if=mbr.bin of=test.img bs=$(BLOCK_SIZE) count=$(MBR_COUNT) seek=$(SEEK) conv=notrunc
	$(eval SEEK=$(shell echo $$(($(SEEK)+$(MBR_COUNT)))))
	dd if=loader.bin of=test.img bs=$(BLOCK_SIZE) count=$(LOADER_COUNT) seek=$(SEEK) conv=notrunc
	$(eval SEEK=$(shell echo $$(($(SEEK)+$(LOADER_COUNT)))))
	dd if=kernel.bin of=test.img bs=$(BLOCK_SIZE) count=$(KERNEL_COUNT) seek=$(SEEK) conv=notrunc
	@echo "当前共使用磁盘空间：$(SEEK)块"
	@echo "\n使用以下命令运行bochs查看镜像运行结果: \n  bochs -f bochsrc -q"

kernel.bin: kernel/main.c print.o
	$(CC) -I include kernel/main.c -o main.o
	$(LINK) main.o print.o -o kernel.elf
	$(OBJCOPY) kernel.elf kernel.bin

#编译lib
print.o: lib/print.asm include/print.h
	$(CASM) -f elf32 -o print.o lib/print.asm

#生成镜像
$(IMAGE_NAME).img:
	cp etc/bochsrc bochsrc
	bximage -hd -mode="flat" -size=$(IMAGE_SIZE) -q $(IMAGE_NAME).img | tail -n 1 | sed -e 's/^[ ]*//g' >> bochsrc

#引导部分
mbr.bin: boot/mbr.asm
	$(CASM) -I boot/include -o mbr.bin boot/mbr.asm

loader.bin: boot/loader.asm
	$(CASM) -I boot/include -o loader.bin boot/loader.asm

#伪指令
.PHONY: clean run

run: image
	bochs -f bochsrc -q

clean:
	-rm -rf *.bin *.img bochsrc bochs.log *.o *.elf