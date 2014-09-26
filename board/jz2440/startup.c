/*
 * Copyright (C) 2014 Huang Bo
 */

#include "s3c2440.h"

extern void board_init(void);

#define GPFCON              (*(volatile unsigned long *)0x56000050)

void ht_startup(void)
{
	
	rt_hw_interrupt_init();

	board_init();
	
	rt_show_version();

	rt_system_timer_init();

	rt_system_scheduler_init();

	rt_application_init();

	rt_thread_idle_init();

	rt_system_scheduler_start();

	return; 
}
