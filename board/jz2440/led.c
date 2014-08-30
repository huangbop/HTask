/*
 * Copyright (C) 2014 Huang Bo
 */

#include <s3c2440.h>

void led_init(void)
{
	gpio.GPFCON = 0x1500;	/* output with 4,5,6 */
}
