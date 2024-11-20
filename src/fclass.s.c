#include <stdint.h>
#include "test_utils.h"
#include <math.h>

void main (int argc, char* argv[]) {
	// testing printk
	printk("Starting experiment ...\n");

	union freg NaN;
	int64_t class;
	NaN.f = 3e9;
	// NaN.bits = 0xffffffff;

	asm volatile (
		"fclass.s %0, %1"
		: "=r" (class)
		: "f" (NaN.f)
	);

	switch (class) {
		case 0x001: class = 0; break;
		case 0x002: class = 1; break;
		case 0x004: class = 2; break;
		case 0x008: class = 3; break;
		case 0x010: class = 4; break;
		case 0x020: class = 5; break;
		case 0x040: class = 6; break;
		case 0x080: class = 7; break;
		case 0x100: class = 8; break;
		case 0x200: class = 9; break;
		default: class = 0xffffffffffffffff;
	}

	// testing printf
	printf("Class of bit representation 0x%x : %d\n", (uint64_t) NaN.bits, class);

	// looping forever
	while(1)
		;
}
