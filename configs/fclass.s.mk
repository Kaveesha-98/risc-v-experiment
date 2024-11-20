ARCH    = /opt/riscv/bin/riscv64-unknown-elf
CC      = $(ARCH)-gcc
FLAGS   = -nostartfiles -g -mcmodel=medany
LD      = $(ARCH)-ld
OBJCOPY = $(ARCH)-objcopy


all: clean fclass.s.img

fclass.s.img: fclass.s.elf
	$(OBJCOPY) fclass.s.elf -I binary fclass.s.img

fclass.s.elf: init.o fclass.s.o link.ld
	$(LD) -T link.ld -o fclass.s.elf init.o fclass.s.o

init.o: src/init.s
	$(CC) $(FLAGS) -c $< -o $@

fclass.s.o: fclass.s.s
	$(CC) $(FLAGS) -march=rv64g -c $< -o $@

clean:
	rm -f *.o *.elf *.img

fclass.s.s: src/fclass.s.c $(wildcard src/*.h)
	$(CC) -march=rv64g -mcmodel=medany -S -o fclass.s.s src/fclass.s.c

run: fclass.s.img
	qemu-system-riscv64 -M virt -bios none -serial stdio -display none -kernel fclass.s.img

