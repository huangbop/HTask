/*
 * Copyright (C) 2014 Huang Bo
 */
#include "htask.h"
#include "nand.h"

void nand_select_chip(void)
{
	int i;
	struct nand *nand = get_base_nand();

	nand->NFCONT &= ~(1<<1);
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
	struct nand *nand = get_base_nand();
	volatile unsigned char *p = (volatile unsigned char *)&nand->NFADDR;

	*p = addr & 0xff;
	for(i=0; i<10; i++);
	
	*p = (addr >> 9) & 0xff;
	for(i=0; i<10; i++);
	
	*p = (addr >> 17) & 0xff;
	for(i=0; i<10; i++);
	
	*p = (addr >> 25) & 0xff;
	for(i=0; i<10; i++);
	
}

unsigned char nand_read_data(void)
{
	struct nand *nand = get_base_nand();
	volatile unsigned char *p = (volatile unsigned char *)&nand->NFDATA;

	return *p;
}

void nand_read(unsigned char *buf, unsigned long start, int size)
{
	int i, j;

	nand_select_chip();
	
	for (i = start; i < (start + size);) {
		nand_write_cmd(0);

		nand_write_addr(i);
		nand_wait_idle();

		for (j = 0; j < 512; j++, i++) {
			*buf = nand_read_data();
			buf++;
		}
	}

	nand_deselect_chip();
}
