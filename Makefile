CASM = nasm

IMAGE_NAME = test
IMAGE_SIZE = 60

MBR_COUNT = 1
LOADER_COUNT = 1

SEEK = 0

BLOCK_SIZE = 512

image: $(IMAGE_NAME).img mbr.bin loader.bin
	dd if=mbr.bin of=test.img bs=$(BLOCK_SIZE) count=$(MBR_COUNT) seek=$(SEEK) conv=notrunc
	$(eval SEEK=$(shell echo $$(($(SEEK)+$(MBR_COUNT)))))
	dd if=loader.bin of=test.img bs=$(BLOCK_SIZE) count=$(LOADER_COUNT) seek=$(SEEK) conv=notrunc
	@echo "\n使用以下命令运行bochs查看镜像运行结果: \n  bochs -f bochsrc -q"

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