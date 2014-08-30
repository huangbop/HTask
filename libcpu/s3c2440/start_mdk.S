;;;
;;; Copyright (C) 2014 Huang Bo
;;;

USR_MODE	equ	0x10
FIQ_MODE	equ	0x11
IRQ_MODE	equ	0x12
SVC_MODE	equ	0x13
ABT_MODE	equ	0x17
UND_MODE	equ	0x1b
SYS_MODE	equ	0x1f
MODE_MASK	equ 	0x1f
I_BIT		equ 	0x80
F_BIT		equ 	0x40
NOINT		equ 	0xc0	


	area	stack, readwrite, align=3
svc_stack	space	4096
stack_top
	

	
	area reset, code, readonly
	preserve8
	entry
	export _start
_start
	b	rst_handler
	ldr	pc, _und_handler
	ldr	pc, _swi_handler
	ldr	pc, _pabt_handler
	ldr	pc, _dabt_handler
	nop
	ldr	pc, _irq_handler
	ldr	pc, _fiq_handler

_und_handler	dcd 	und_handler
_swi_handler	dcd 	swi_handler
_pabt_handler	dcd 	pabt_handler
_dabt_handler	dcd 	dabt_handler
_irq_handler	dcd 	irq_handler
_fiq_handler	dcd 	fiq_handler

und_handler
swi_handler
pabt_handler
dabt_handler
irq_handler
fiq_handler 	b 	und_handler

rst_handler	
	;; disable watchdog
	ldr	r0, =0x53000000
	ldr	r1, =0x0
	str	r1, [r0]

	;; set svc stack
	msr	cpsr_c, #SVC_MODE :or: NOINT
	ldr	sp, =stack_top
	
	import 	htask_startup	
	b	htask_startup

	end
