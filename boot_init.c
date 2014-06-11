/*
 * Copyright (C) 2014 Huang Bo
 */
#include "htask.h"

void clock_init(void)
{
	struct clock_power *const clk_pow = get_base_clock_power();

	clk_pow->locktime = 0xffffffff;
	
	/* FCLK:HCLK:PCLK = 1:4:8 */
	clk_pow->clkdivn = 0x5;
	
	/* 12.0000MHz to 400.00MHz */
	clk_pow->mpllcon = (0x5c << 12) | (1 << 4) | 1;
	
	__asm__ __volatile__ (
		"mrc p15, 0, r0, c1, c0, 0\n"
		"orr r0, r0, #0xc0000000\n"
		"mcr p15, 0, r0, c1, c0, 0");
}

void nand_select_chip(void)
{
	int i;
	struct nand *nand = get_base_nand();

	nand->NFCONT &= ~(1<<1);
	for (i = 0; i < 10; i++);
}

void nand_write_cmd(unsigned char cmd)
{
	struct nand *nand = get_base_nand();

	volatile unsigned char *p = (volatile unsigned char *)&nand->NFCMD;
	*p = cmd;
}

void nand_wait_idle(void)
{
	int i;
	struct nand *nand = get_base_nand();

	volatile unsigned char *p = (volatile unsigned char *)&nand->NFSTAT;

	while (!(*p & 1))
		for (i = 0; i < 10; i++);
}

void nand_deselect_chip(void)
{
	struct nand *nand = get_base_nand();

	nand->NFCONT |= (1<<1);
}

void nand_reset(void)
{
	nand_select_chip();
	nand_write_cmd(0xff);
	nand_wait_idle();
	nand_deselect_chip();
}

void nand_init(void)
{
	struct nand *nand = get_base_nand();

#define TACLS   0
#define TWRPH0  3
#define TWRPH1  0

	nand->NFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4);
	nand->NFCONT = (1<<4)|(1<<1)|(1<<0);
	
	nand_reset();
}

void nand_write_addr(unsigned addr)
{
	int i;
	int col, row;
	struct nand *nand = get_base_nand();
	volatile unsigned char *p = (volatile unsigned char *)&nand->NFADDR;

	col = addr % 2048;
	row = addr / 2048;

	*p = col & 0xff;
	for(i=0; i<10; i++);
	
	*p = (col >> 8) & 0x0f;
	for(i=0; i<10; i++);
	
	*p = row & 0xff;
	for(i=0; i<10; i++);

	*p = (row >> 8) & 0xff;
	for(i=0; i<10; i++);

	*p = (row >> 16) & 0x03;
	for(i=0; i<10; i++);

}

unsigned char nand_read_data(void)
{
	struct nand *nand = get_base_nand();
	volatile unsigned char *p = (volatile unsigned char *)&nand->NFDATA;

	return *p;
}

/* start & size must align to 2048 */
void nand_read(unsigned char *buf, unsigned long start, int size)
{
	int i, j;

	nand_select_chip();
	
	for (i = start; i < (start + size);) {
		nand_write_cmd(0);

		nand_write_addr(i);
		nand_write_cmd(0x30);
		nand_wait_idle();

		for (j = 0; j < 2048; j++, i++) {
			*buf = nand_read_data();
			buf++;
		}
	}

	nand_deselect_chip();
}

void copy2ram(unsigned long start, unsigned char *buf, int size)
{
	nand_init();

	nand_read(buf, start, (size + 2047) & ~(2047));
}

