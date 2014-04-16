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

#define WDCON		0x53000000

#define INTMASK		0x4a000008
#define INTSUBMASK	0x4a00001c

.globl _start
_start:
	b	reset
	
reset:
	/* change to supervisor mode */
	mrs	r0, cpsr
	bic	r0, r0, #MODEMASK
	orr 	r0, r0, #SVCMODE
	msr 	cpsr, r0

	/* disable watch dog */
	ldr 	r0, =0x53000000
	mov 	r1, #0x00000000
	str	r1, [r0]
	
	/* mask interrupt */
	ldr 	r0, =0x53000000
	mov	r1, #0x00000000
	str	r1, [r0]
	
	ldr 	r0, =INTSUBMASK
	ldr	r1, =0x7fff
	str	r1, [r0]
	
	/* mask interrupt */
	ldr 	r0, =INTMASK
	ldr	r1, =0xffffffff
	str	r1, [r0]
	ldr 	r0, =INTSUBMASK
	ldr	r1, =0x7fff
	str	r1, [r0]

