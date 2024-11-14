#include <stdint.h>

void printk (const char* text) {
	uint32_t char_index;
	while (text[char_index])
		*(char*) 0x10000000 = text[char_index++];
}
