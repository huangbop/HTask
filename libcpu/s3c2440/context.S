;;;
;;; Copyright (C) 2014 Huang Bo
;;;

NOINT	equ	0xc0

	area 	|.text|, code, readonly, align=2
	arm
	preserve8

	;; rt_hw_interrupt_disable()
rt_hw_interrupt_disable	proc
	export	rt_hw_interrupt_disable
	mrs	r0, cpsr
	orr	r1, r0, #NOINT
	msr	cpsr_c, r1
	bx	lr
	endp

	;; rt_hw_interrupt_enable(level)
rt_hw_interrupt_enable	proc
	export 	rt_hw_interrupt_enable
	msr	cpsr_c, r0
	bx	lr
	endp



	;; rt_hw_context_switch(from, to)
rt_hw_context_switch	proc
	export	rt_hw_context_switch

	;; push |spsr, cpsr, r0-r12, lr, pc|
	stmfd	sp!, {lr}
	stmfd	sp!, {r0-r12, lr}
	mrs	r4, cpsr
	stmfd	sp!, {r4}
	mrs	r4, spsr
	stmfd	sp!, {r4}

	;; refresh & change sp
	str	sp, [r0]
	ldr	sp, [r1]
	
	;; pop & run
	ldmfd	sp!, {r4}
	msr	spsr_cxsf, r4
	ldmfd	sp!, {r4}
	msr	cpsr_cxsf, r4
	ldmfd	sp!, {r0-r12, lr, pc}^
	
	endp

	;; rt_hw_context_switch_to(to)
rt_hw_context_switch_to 	proc
	export	rt_hw_context_switch_to
	ldr	sp, [r0]

	;; pop & run
	ldmfd	sp!, {r4}
	msr	spsr_cxsf, r4
	ldmfd	sp!, {r4}
	msr	cpsr_cxsf, r4
	ldmfd	sp!, {r0-r12, lr, pc}
	
	endp

	;; 
	;; rt_hw_context_switch_interrupt(from, to)
	;; switch in irq handler
	;; set flag, from, to
	;;
rt_hw_context_switch_interrupt	proc
	export	rt_hw_context_switch_interrupt
	import	rt_interrupt_switch_flag
	import	rt_interrupt_from_thread
	import	rt_interrupt_to_thread

	ldr	r2, =rt_interrupt_switch_flag
	ldr	r3, [r2]
	cmp	r3, #1
	beq	_reswitch
	mov	r3, #1
	str	r3, [r2]
	ldr	r2, =rt_interrupt_from_thread
	str	r0, [r2]
_reswitch
	ldr	r2, =rt_interrupt_to_thread
	str	r1, [r2]
	bx	lr
	
	endp
	
	end
