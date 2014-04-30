/*
 * Copyright (C) 2014 Huang Bo
 */

#define MODEMASK	0x1f
#define USRMODE		0x10
#define FIQMODE		0x11
#define IRQMODE		0x12
#define SVCMODE		0x13
#define ABTMODE		0x17
#define UNDMODE		0x1b
#define SYSMODE		0x1f
#define NOINT		0xc0	

#define WTDCON		0x53000000

#define INTMASK		0x4a000008
#define INTSUBMASK	0x4a00001c

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

/* stack start */
IRQ_STACK_START:
	.word 	_irq_stack + 1024

FIQ_STACK_START:
	.word 	_fiq_stack + 1024
	
UND_STACK_START:
	.word 	_und_stack + 1024

ABT_STACK_START:
	.word 	_abt_stack + 1024

SVC_STACK_START:
	.word 	_svc_stack + 1024	

	

	
reset:
	/* change to supervisor mode */
	mrs	r0, cpsr
	bic	r0, r0, #MODEMASK
	orr 	r0, r0, #SVCMODE
	msr 	cpsr, r0

	/* disable watch dog */
	ldr 	r0, =WTDCON
	mov 	r1, #0x0
	str	r1, [r0]
	
	/* mask interrupt */
	ldr 	r0, =INTMASK
	ldr	r1, =0xffffffff
	str	r1, [r0]
	ldr 	r0, =INTSUBMASK
	ldr	r1, =0x7fff
	str	r1, [r0]

	/* setup stack */
	bl	setup_stack


/*
 * setup stack
 */
setup_stack:
	mrs	r0, cpsr
	bic	r0, r0, #MODEMASK

	/* undefined mode */
	orr	r1, r0, #UNDMODE|NOINT
	msr	cpsr, r1
	ldr	sp, UND_STACK_START

	/* abort mode */
	orr	r1, r0, #ABTMODE|NOINT
	msr	cpsr, r1
	ldr	sp, ABT_STACK_START

	/* fiq mode */
	orr	r1, r0, #FIQMODE|NOINT
	msr	cpsr, r1
	ldr	sp, FIQ_STACK_START

	/* irq mode */
	orr	r1, r0, #IRQMODE|NOINT
	msr	cpsr, r1 
	ldr 	sp, IRQ_STACK_START

	/* svc mode */
	orr	r1, r0, #SVCMODE|NOINT
	msr	cpsr, r1
	ldr	sp, SVC_STACK_START

	mov	pc, lr


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
