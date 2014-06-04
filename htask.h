/*
 * Copyright (C) 2014 Huang Bo
 */
#ifndef _HTASK_H_
#define _HTASK_H_

struct clock_power {
	volatile unsigned locktime;
	volatile unsigned mpllcon;
	volatile unsigned upllcon;
	volatile unsigned clkcon;
	volatile unsigned clkslow;
	volatile unsigned clkdivn;
	volatile unsigned camdivn;
};

struct gpio {
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

struct uart {
	volatile unsigned ulcon;
	volatile unsigned ucon;
	volatile unsigned ufcon;
	volatile unsigned umcon;
	volatile unsigned utrstat;
	volatile unsigned uerstat;
	volatile unsigned ufstat;
	volatile unsigned umstat;
	/* little endian */
	volatile unsigned char utxh;
	volatile unsigned char res0[3];
	volatile unsigned char urxh;
	volatile unsigned char res1[3];
	
	volatile unsigned ubrdiv;
};

struct nand {
	volatile unsigned NFCONF;
	volatile unsigned NFCONT;
	volatile unsigned NFCMD;
	volatile unsigned NFADDR;
	volatile unsigned NFDATA;
	volatile unsigned NFMECCD0;
	volatile unsigned NFMECCD1;
	volatile unsigned NFSECCD;
	volatile unsigned NFSTAT;
	volatile unsigned NFESTAT0;
	volatile unsigned NFESTAT1;
	volatile unsigned NFMECC0;
	volatile unsigned NFMECC1;
	volatile unsigned NFSECC;
	volatile unsigned NFSBLK;
	volatile unsigned NFEBLK;
};


static inline struct clock_power *get_base_clock_power(void)
{
	return (struct clock_power *)0x4c000000;
}

static inline struct gpio *get_base_gpio(void)
{
	return (struct gpio *)0x56000000;
}

static inline struct uart *get_base_uart(void)
{
	return (struct uart *)0x50000000;
}

static inline struct nand *get_base_nand(void)
{
	return (struct nand *)0x4e000000;
}

#endif /* _HTASK_H_ */
