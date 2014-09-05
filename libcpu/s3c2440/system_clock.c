/*
 * Copyright (C) 2014 Huang Bo
 */

#include "s3c2440.h"

void clock_init(void)
{
	clock_power.locktime = 0xffffffff;
	clock_power.clkdivn = 0x5;			   /* 1:4:8 */
	clock_power.mpllcon = (0x5c<<12) | (1<<4) | 1; /* 12MHz -> 400MHz */

}
