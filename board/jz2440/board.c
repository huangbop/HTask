/*
 * Copyright (C) 2014 Huang Bo
 */

#include "rtthread.h"
#include "s3c2440.h"

extern void clock_init(void);
extern void uart_init(void);
extern void led_init(void);

extern unsigned pclk;

static void rt_timer_handler(int vector, void *param)
{
	rt_tick_increase();
}

/* init timer4 for system tick */
void timer_init(void)
{
	gpio.GPFDAT = 0xff; 		/* turn off leds */

	
	gpio.GPFCON &= ~0x33;	/* key int */
	gpio.GPFCON |= 0x22;

	
	TCFG0  = 99;
	TCFG1  = 0x03;		/* PCLK/100/16 */

	TCNTB0 = (int)(pclk/100/16/RT_TICK_PER_SECOND) - 1;		/* one second */
	TCON   |= (1<<1);   	/* update count buf */

	rt_hw_interrupt_install(10, rt_timer_handler, RT_NULL, "tick");
	rt_hw_interrupt_umask(10);

	TCON   = 0x09;      	/* set interval mode & run */
}

void board_init(void)
{
	clock_init();

	uart_init();	
	uart_register();
	rt_console_set_device("uart");

	led_init();

	timer_init();
	
	rt_hw_mmu_init();
}
