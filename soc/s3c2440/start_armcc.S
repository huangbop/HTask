;;
;; Copyright (C) 2014 Huang Bo
;; 

MODE_MASK	equ	0x1f
SVC_MODE	equ	0x13
USR_MODE	equ	0x10
IRQ_MODE	equ	0x12
FIQ_MODE	equ	0x11
ABT_MODE	equ	0x17
SYS_MODE	equ	0x1f
UND_MODE	equ	0x1b

	;; watch dog define
WTCON	equ	0x53000000
	
	
	area init, code, readonly

	entry
	export _start
_start
	;;  move to SVC mode
	mrs 	r0, cpsr
	bic	r0, r0, #MODE_MASK
	orr	r0, r0, #SVC_MODE
	msr	cpsr_c, r0

	;; disable watch dog
	ldr	r0, =WTCON
	ldr	r1, =0
	str	r1, [r0]
	
	;; clock init
	mov	sp, #4096
	import clock_init
	bl	clock_init
	
	import htask_startup
	bl	htask_startup
	
	end
