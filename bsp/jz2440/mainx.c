/*
 * Copyright (C) 2014 Huang Bo
 */

struct led {
	volatile unsigned con;
	volatile unsigned dat;
};

#define led (*(struct led*)0x56000050)

void htask_startup(void)
{
	
	led.con = 0x00001500; 	/* 0001 0101 GPF4,5,6 */

	for (;;) {
		led.dat = 0xff;
		led.dat = 0xef;
		led.dat = 0xdf;
		led.dat = 0xbf;
	}
}
