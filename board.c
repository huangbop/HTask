
struct GPIO {
	volatile unsigned GPACON;
	volatile unsigned GPADAT;
	volatile unsigned res1[2];
	volatile unsigned GPBCON;
	volatile unsigned GPBDAT;
	volatile unsigned GPBUP;
	volatile unsigned res2;
	volatile unsigned GPCCON;
	volatile unsigned GPCDAT;
	volatile unsigned GPCUP;
	volatile unsigned res3;
	volatile unsigned GPDCON;
	volatile unsigned GPDDAT;
	volatile unsigned GPDUP;
	volatile unsigned res4;
	volatile unsigned GPECON;
	volatile unsigned GPEDAT;
	volatile unsigned GPEUP;
	volatile unsigned res5;
	volatile unsigned GPFCON;
	volatile unsigned GPFDAT;
	volatile unsigned GPFUP;
	volatile unsigned res6;
	volatile unsigned GPGCON;
	volatile unsigned GPGDAT;
	volatile unsigned GPGUP;
	volatile unsigned res7;
	volatile unsigned GPHCON;
	volatile unsigned GPHDAT;
	volatile unsigned GPHUP;
	volatile unsigned res8;

	volatile unsigned MISCCR;
	volatile unsigned DCLKCON;
	volatile unsigned EXTINT0;
	volatile unsigned EXTINT1;
	volatile unsigned EXTINT2;
	volatile unsigned EINTFLT0;
	volatile unsigned EINTFLT1;
	volatile unsigned EINTFLT2;
	volatile unsigned EINTFLT3;
	volatile unsigned EINTMASK;
	volatile unsigned EINTPEND;
	volatile unsigned GSTATUS0;
	volatile unsigned GSTATUS1;
	volatile unsigned GSTATUS2;
	volatile unsigned GSTATUS3;
	volatile unsigned GSTATUS4;

	volatile unsigned res9[4];
	volatile unsigned GPJCON;
	volatile unsigned GPJDAT;
	volatile unsigned GPJUP;
};



int board_init(void)
{
	

	return 0;
}
