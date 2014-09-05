/*
 * Copyright (C) 2014 Huang Bo
 */

#include "s3c2440.h"

extern void board_init(void);

int ht_startup(void)
{
	rt_hw_interrupt_init();

	board_init();
	
	rt_show_version();
	

	return 0;
}
