.global _start

_start:

	auipc sp, 0x0
	li t0, 2048
	add sp, sp, t0
	j main
