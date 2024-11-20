#include <stdint.h>
#include <stdarg.h>

union freg {
	uint32_t bits;
	float f;
};

void printk (const char* text) {
	uint32_t char_index;
	while (text[char_index])
		*(char*) 0x10000000 = text[char_index++];
}

void printf (const char* text, ...) {
	va_list args;

	va_start(args, text);

	uint32_t char_index;
	while (text[char_index])
		switch (text[char_index]) {
			case '%': {
				switch (text[++char_index]) {
					case 'd': {
						uint64_t number = va_arg(args, int64_t);
						// when the number is negative
						if (number & 0x8000000000000000) {
							number = (~number) + 1;
							*(char*) 0x10000000 = '-';
						} 
						// Looking for the max possible divider
						uint64_t divider = 1;
						while (divider && (number / divider))
							divider = divider * 10;
						divider = divider > 1 ? divider/10 : divider;
						// printing the number as decimal
						while (divider) {
							*(char*) 0x10000000 = '0' + (number/divider);
							number = number%divider;
							divider= divider/10;
						}
						char_index++;
						break;
					}
					default: printk("illegal syntax\n"); va_end(args); return;

				}
			}
			default: *(char*) 0x10000000 = text[char_index++]; break;
		} 

	va_end(args);
}
