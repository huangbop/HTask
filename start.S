/*
 * Copyright (C) 2014 Huang Bo
 */


	
.globl _start
_start:
	b	reset
	ldr	pc, _undefined_instruction
	ldr 	pc, _software_interrupt
	ldr	pc, _prefetch_abort
	ldr 	pc, _data_abort
	ldr	pc, _not_used
	ldr	pc, _irq
	ldr 	pc, _fiq

_undefined_instruction: 	.word undefined_instruction 
_software_interrupt:		.word software_interrupt 
_prefetch_abort:		.word prefetch_abort 
_data_abort:			.word data_abort 
_not_used:			.word not_used 
_irq:				.word irq 
_fiq:				.word fiq 

	.balignl 16, 0xdeadbeef

	/*
	 *
	 */
_TEXT_BASE:
	.word	_start

_bss_start:
	.word 	__bss_start

_bss_end:	
	.word 	__bss_end
	
reset:
	/*
	 * set the cpu to SVC32 mode
	 */
	mrs	r0, cpsr
	bic	r0, r0, #0x1f
	orr 	r0, r0, #0xd3
	msr 	cpsr, r0

	/*
	 * turn off the watchdog
	 */
	ldr 	r0, =0x53000000
	mov 	r1, #0x0
	str	r1, [r0]

	/*
	 * mask all IRQs
	 */
	mov 	r1, #0xffffffff
	ldr 	r0, =0x4a000008
	str 	r1, [r0]
	ldr 	r1, =0x7fff
	ldr 	r0, =0x4a00001c
	str 	r1, [r0]

	/*
	 * set up the stack
	 */
	ldr	r0, _TEXT_BASE
	sub 	sp, r0, #1024 * 1024

	/*
	 * set up clock
	 */
	bl 	clock_init

	/*
	 * clear bss
	 */
	ldr 	r0, _bss_start
	ldr	r1, _bss_end
	mov	r2, #0x00000000
clear_loop:
	str 	r2, [r0]
	add 	r0, r0, #4
	cmp 	r0, r1
	ble	clear_loop

	/*
	 * startup
	 */
	ldr 	pc, _ht_startup

_ht_startup:
	.word 	ht_startup

/*
 * except handlers
 */
	.align 5
undefined_instruction:
	b undefined_instruction

	.align 5
software_interrupt:
	b software_interrupt

	.align 5
prefetch_abort:
	b prefetch_abort
	
	.align 5
data_abort:
	b data_abort

	.align 5
not_used:
	b not_used

	.align 5
irq:
	b irq

	.align 5
fiq:
	b fiq
