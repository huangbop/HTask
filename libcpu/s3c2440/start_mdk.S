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

SVC_STACK_SIZE	equ	0x100
USR_STACK_SIZE	equ	0x0
IRQ_STACK_SIZE	equ	0x100

	area	stack, readwrite, align=3
isr_stack	space	(SVC_STACK_SIZE + USR_STACK_SIZE + IRQ_STACK_SIZE)
isr_stack_top
	
	
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
fiq_handler 	b 	und_handler

rst_handler	
	;; disable watchdog
	ldr	r0, =0x53000000
	ldr	r1, =0x0
	str	r1, [r0]

	;; set stack
	ldr	r0, =isr_stack_top

	;; msr	cpsr_c, #USR_MODE :or: NOINT
	;; mov	sp, r0
	;; sub	r0, r0, #USR_STACK_SIZE

	msr	cpsr_c, #IRQ_MODE :or: NOINT
	mov	sp, r0
	sub	r0, r0, #IRQ_STACK_SIZE

	msr	cpsr_c, #SVC_MODE
	mov	sp, r0
	sub	sl, sp, #SVC_STACK_SIZE

	import 	ht_startup	
	ldr	r0, =ht_startup
	bx	r0

irq_handler 	proc
	import	rt_interrupt_enter
	import	rt_interrupt_leave
	import	rt_hw_do_irq
	import	rt_interrupt_switch_flag
	import	rt_interrupt_from_thread 
	import	rt_interrupt_to_thread 

	stmfd	sp!, {r0-r12, lr}
	bl	rt_interrupt_enter
	bl	rt_hw_do_irq
	bl	rt_interrupt_leave

	;; ldr	r0, =rt_interrupt_switch_flag
	;; ldr	r1, [r0]
	;; cmp	r1, #1
	;; beq	rt_hw_context_switch_interrupt_do

	ldmfd	sp!, {r0-r12, lr}
	subs	pc, lr, #4

	endp

rt_hw_context_switch_interrupt_do	proc
	;; mov	r1, #0
	;; str	r1, [r0]

	;; ldmfd	sp!, {r0-r12, lr}
	;; stmfd	sp!, {r0-r3}
	;; mov	r1, sp
	;; add	sp, sp, #16
	;; sub	r2, lr, #4

	;; mrs	r3, spsr

	;; msr	cpsr_c, #SVC_MODE :or: NOINT
	;; stmfd   sp!, {r2}       ; push old task's pc
	;; stmfd   sp!, {r4-r12,lr}; push old task's lr,r12-r4
	;; mov     r4,  r1         ; Special optimised code below
	;; mov     r5,  r3
	;; ldmfd   r4!, {r0-r3}
	;; stmfd   sp!, {r0-r3}    ; push old task's r3-r0
	;; stmfd   sp!, {r5}       ; push old task's cpsr
	;; mrs     r4,  spsr
	;; stmfd   sp!, {r4}       ; push old task's spsr
	
	;; ldr     r4,  =rt_interrupt_from_thread
	;; ldr     r5,  [r4]
	;; str     sp,  [r5]       ; store sp in preempted tasks's TCB

	;; ldr     r6,  =rt_interrupt_to_thread
	;; ldr     r6,  [r6]
	;; ldr     sp,  [r6]       ; get new task's stack pointer
	
	;; ldmfd   sp!, {r4}       ; pop new task's spsr
	;; msr     spsr_cxsf, r4
	;; ldmfd   sp!, {r4}       ; pop new task's psr
	;; msr     cpsr_cxsf, r4
	
	;; ldmfd   sp!, {r0-r12,lr,pc} ; pop new task's r0-r12,lr & pc
	endp
 
	end
