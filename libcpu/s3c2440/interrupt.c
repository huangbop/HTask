/*
 * Copyright (C) 2014 Huang Bo
 */

#include "rtthread.h"
#include "rthw.h"
#include "s3c2440.h"

unsigned rt_interrupt_from_thread, rt_interrupt_to_thread;
unsigned rt_interrupt_switch_flag;


#define MAX_HANDLER_SIZE    32
static struct rt_irq_desc isr_table[MAX_HANDLER_SIZE];

static void default_handler(int vector, void *param)
{
	rt_kprintf("Vector:%d do nothing.\n", vector);
}

void rt_hw_interrupt_init(void)
{
	int i;

	INTMSK = 0xffffffff;
	rt_memset(isr_table, 0, sizeof(isr_table));
	for (i = 0; i < MAX_HANDLER_SIZE; i++) {
		isr_table[i].handler = default_handler;
	}

}

rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler, 
			     void *param, char *name)
{
	if (vector < MAX_HANDLER_SIZE) {
		isr_table[vector].handler = handler;
		isr_table[vector].param = param;
	}
	
	return RT_NULL;
}

void rt_hw_interrupt_mask(int vector)
{
	INTMSK |= 1 << vector;
}

void rt_hw_interrupt_umask(int vector)
{
	INTMSK &= ~(1 << vector);
}

void rt_hw_do_irq(void)
{
	rt_isr_handler_t handler;
	int offset = INTOFFSET;

	handler = isr_table[offset].handler;
	handler(offset, RT_NULL);

	SRCPND = 1 << offset;
	INTPND = 1 << offset;

}
