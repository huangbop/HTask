/*
 * Copyright (C) 2014 Huang Bo
 */

#include "htask.h"





/* set stack */
unsigned char _irq_stack[1024];
unsigned char _fiq_stack[1024];
unsigned char _abt_stack[1024];
unsigned char _und_stack[1024];
unsigned char _svc_stack[1024];

int _htask_startup()
{
	/* enable cache */
	ht_cpu_enable_icache();
	ht_cpu_enable_dcache();

	/* init interrupt */
	ht_init_interrupt();

	return 0;
}
