/*
 * Copyright (C) 2014 Huang Bo
 */

#include "s3c2440.h"

void clock_init(void)
{
	clock_power.locktime = 0xffffffff;
	clock_power.clkdivn = 0x5;			   /* 1:4:8 */
	clock_power.mpllcon = (0x5c<<12) | (1<<4) | 1; /* 12MHz -> 400MHz */
	/* clock_power.clkcon |= (1<<10);			   /\* enable uart0 *\/ */

	__asm  ( "mrc p15, 0, r0, c1, c0, 0\n \
		orr r0, r0, #0xc0000000\n \
		mcr p15, 0, r0, c1, c0, 0");



}
