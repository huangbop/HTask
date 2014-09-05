/*
 * Copyright (C) 2014 Huang Bo
 */
#ifndef S3C2440_H
#define S3C2440_H

#define USR_MODE        0x10
#define FIQ_MODE        0x11
#define IRQ_MODE        0x12
#define SVC_MODE        0x13
#define ABT_MODE        0x17
#define UND_MODE        0x1b
#define SYS_MODE        0x1f
#define MODE_MASK       0x1f
#define I_BIT           0x80
#define F_BIT           0x40
#define NOINT           0xc0	

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

/* PWM TIMER */
#define TCFG0  (*(volatile unsigned *)0x51000000) /* Timer 0 configuration */
#define TCFG1  (*(volatile unsigned *)0x51000004) /* Timer 1 configuration */
#define TCON   (*(volatile unsigned *)0x51000008) /* Timer control */
#define TCNTB0 (*(volatile unsigned *)0x5100000c) /* Timer count buffer 0 */
#define TCMPB0 (*(volatile unsigned *)0x51000010) /* Timer compare buffer 0 */
#define TCNTO0 (*(volatile unsigned *)0x51000014) /* Timer count observation 0 */
#define TCNTB1 (*(volatile unsigned *)0x51000018) /* Timer count buffer 1 */
#define TCMPB1 (*(volatile unsigned *)0x5100001c) /* Timer compare buffer 1 */
#define TCNTO1 (*(volatile unsigned *)0x51000020) /* Timer count observation 1 */
#define TCNTB2 (*(volatile unsigned *)0x51000024) /* Timer count buffer 2 */
#define TCMPB2 (*(volatile unsigned *)0x51000028) /* Timer compare buffer 2 */
#define TCNTO2 (*(volatile unsigned *)0x5100002c) /* Timer count observation 2 */
#define TCNTB3 (*(volatile unsigned *)0x51000030) /* Timer count buffer 3 */
#define TCMPB3 (*(volatile unsigned *)0x51000034) /* Timer compare buffer 3 */
#define TCNTO3 (*(volatile unsigned *)0x51000038) /* Timer count observation 3 */
#define TCNTB4 (*(volatile unsigned *)0x5100003c) /* Timer count buffer 4 */
#define TCNTO4 (*(volatile unsigned *)0x51000040) /* Timer count observation 4 */

// INTERRUPT
#define SRCPND     (*(volatile unsigned *)0x4a000000) //Interrupt request status
#define INTMOD     (*(volatile unsigned *)0x4a000004) //Interrupt mode control
#define INTMSK     (*(volatile unsigned *)0x4a000008) //Interrupt mask control
#define PRIORITY   (*(volatile unsigned *)0x4a00000c) //IRQ priority control
#define INTPND     (*(volatile unsigned *)0x4a000010) //Interrupt request status
#define INTOFFSET  (*(volatile unsigned *)0x4a000014) //Interruot request source offset
#define SUBSRCPND  (*(volatile unsigned *)0x4a000018) //Sub source pending
#define INTSUBMSK  (*(volatile unsigned *)0x4a00001c) //Interrupt sub mask

/* PENDING BIT */
#define INTEINT0      (0)
#define INTEINT1      (1)
#define INTEINT2      (2)
#define INTEINT3      (3)
#define INTEINT4_7    (4)
#define INTEINT8_23   (5)
#define INTNOTUSED6   (6)
#define INTBAT_FLT    (7)
#define INTTICK       (8)
#define INTWDT        (9)
#define INTTIMER0     (10)
#define INTTIMER1     (11)
#define INTTIMER2     (12)
#define INTTIMER3     (13)
#define INTTIMER4     (14)
#define INTUART2      (15)
#define INTLCD        (16)
#define INTDMA0       (17)
#define INTDMA1       (18)
#define INTDMA2       (19)
#define INTDMA3       (20)
#define INTSDI        (21)
#define INTSPI0       (22)
#define INTUART1      (23)
/* #define INTNOTUSED24  (24) */
#define INTNIC  (24)
#define INTUSBD       (25)
#define INTUSBH       (26)
#define INTIIC        (27)
#define INTUART0      (28)
#define INTSPI1       (29)
#define INTRTC        (30)
#define INTADC        (31)


#define clock_power        (*(struct clock_power *)0x4c000000)
#define gpio               (*(struct gpio *)0x56000000)
#define uart               (*(struct uart *)0x50000000)
#define nand               (*(struct nand *)0x4e000000)


#endif /* S3C2440_H */
