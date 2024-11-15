#include <stdint.h>
#include "test_utils.h"

void main (int argc, char* argv[]) {
	// testing printk
	printk("Hello world!\n");

	// testing printf
	printf("Hello numbers! 1:%d 2:%d 3:%d\n", 0, -255, 255);

	// looping forever
	while(1)
		;
}
