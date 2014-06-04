#include "htask.h"
#include "serial.h"
#include "nand.h"

/* #include "lib.h" */

/* static char line_buffer[128]; */

/* void read_line() */
/* { */
/* 	char c; */
/* 	char *p; */

/* 	p = line_buffer; */
/* 	ht_printf("HTask> "); */
/* 	for (;;) { */
/* 		c = serial_getc(); */
/* 		if (c <= 'z' && c >= 'a') { */
/* 			serial_putc(c); */
/* 			*p++ = c; */
/* 		} */
/* 		if (c == '\r' || c == '\n') { */
/* 			ht_printf("\n"); */
/* 			*p = 0; */
/* 			return; */
/* 		} */

/* 	} */
/* } */

void main_loop(void)
{
	char c;
	int i;
	char *p;
	char r;
	
	c = serial_getc();
	serial_putc(c);
	if (c == '\r') {
		serial_puts("\n\n");

		nand_init();

		nand_wait_idle();
		nand_write_cmd(0);
		nand_write_addr(200);
		nand_wait_idle();
		r = nand_read_data();
		serial_putc(r + 'A');
		

	}
	
	/* ht_printf("HTask\n"); */
	/* ht_printf("Copyright (C) 2014 Huang Bo\n\n"); */

	/* for (;;) { */
	/* 	read_line(); */
	/* 	ht_printf("Now, we will process this / %s /\n", line_buffer); */
		
	/* } */
}
