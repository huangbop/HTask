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
	.word	TEXT_BASE

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
	 * init ram
	 */
	adr	r0, _start
	ldr 	r1, _TEXT_BASE
	cmp 	r0, r1
	blne	ram_init

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
	 * copy2ram
	 */
	bl 	copy2ram

	ldr	pc, =clear_bss

	/*
	 * clear bss
	 */
clear_bss:	
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


ram_init:
	/* mem_setup: */	
	mov	r1, #0x48000000
	adrl	r2, mem_cfg_val
	add	r3, r1, #52
1:
	ldr	r4, [r2], #4
	str	r4, [r1], #4
	cmp	r1, r3
	bne	1b

	mov	pc, lr


copy2ram:	
	/* code2ram: */
	adr	r1, _start
	ldr	r2, _TEXT_BASE
	add	r3, r1, #4*1024
1:	
	ldr 	r4, [r1], #4
	str	r4, [r2], #4
	cmp	r1, r3
	bne	1b

	mov 	pc, lr

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

	.align 5
mem_cfg_val:
    .long   0x22011110      @ BWSCON
    .long   0x00000700      @ BANKCON0
    .long   0x00000700      @ BANKCON1
    .long   0x00000700      @ BANKCON2
    .long   0x00000700      @ BANKCON3  
    .long   0x00000700      @ BANKCON4
    .long   0x00000700      @ BANKCON5
    .long   0x00018005      @ BANKCON6
    .long   0x00018005      @ BANKCON7
    .long   0x008C07A3      @ REFRESH
    .long   0x000000B1      @ BANKSIZE
    .long   0x00000030      @ MRSRB6
    .long   0x00000030      @ MRSRB7
