ARCH    = /home/kaveesha/Documents/github/linux_compile/buildroot/output/host/bin/riscv64-buildroot-linux-uclibc
CC      = $(ARCH)-gcc
FLAGS   = -nostartfiles -g -mcmodel=medany
LD      = $(ARCH)-ld
OBJCOPY = $(ARCH)-objcopy


all: clean sample.img

sample.img: sample.elf
	$(OBJCOPY) sample.elf -I binary sample.img

sample.elf: init.o sample.o link.ld Makefile
	$(LD) -T link.ld -o sample.elf init.o sample.o

init.o: src/init.s
	$(CC) $(FLAGS) -c $< -o $@

sample.o: sample.s
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f *.o sample.elf sample.img

sample.s: src/sample.c $(wildcard src/*.h)
	$(CC) -mcmodel=medany -S -o sample.s src/sample.c

run: sample.img
	qemu-system-riscv64 -M virt -bios none -serial stdio -display none -kernel sample.img

