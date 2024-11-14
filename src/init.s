.global _start

_start:

	auipc sp, 0x0
	addi sp, sp, 1024
	j main
