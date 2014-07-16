#include "htask.h"
#include "serial.h"
#include "lib.h"

static char line_buffer[128];

struct led {
	volatile unsigned con;
	volatile unsigned dat;
};

#define led (*(struct led*)0x56000050)

void read_line()
{
	char c;
	char *p;
	int i;

	p = line_buffer;
	ht_printf("HTask> ");
	for (;;) {
		c = serial_getc();
		if (c <= 'z' && c >= 'a') {
			serial_putc(c);
			*p++ = c;
			
			i = c - 'a' + 4; /* a, b, c map to GPF4, 5, 6 */
			if (i <= 6) {
				led.dat |= 0xff;
				led.dat &= ~(1<<i);
			}
		}
		if (c == '\r' || c == '\n') {
			ht_printf("\n");
			*p = 0;
			return;
		}

	}
}

static char buf[8192] = {'a', 'b',};


void main_loop(void)
{
	read_line();
}

void ht_startup(void)
{
	serial_init();

	led.con = 0x00001500; 	/* 0001 0101 GPF4,5,6 */

	
	for (;;) {
		main_loop();
	}
}
