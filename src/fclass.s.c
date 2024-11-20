#include <stdint.h>
#include "test_utils.h"

void main (int argc, char* argv[]) {
	// testing printk
	printk("Starting experiment ...\n");

	union freg NaN;
	int64_t class;
	NaN.bits = 0x7f000002;

	asm volatile (
		"fclass.s %0, %1"
		: "=r" (class)
		: "f" (NaN.f)
	);

	// testing printf
	printf("Class of bit representation 0x7fc00000 :%d\n", class);

	// looping forever
	while(1)
		;
}
