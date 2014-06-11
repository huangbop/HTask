#include "htask.h"
#include "serial.h"
#include "lib.h"

static char line_buffer[128];

void read_line()
{
	char c;
	char *p;

	p = line_buffer;
	ht_printf("HTask> ");
	for (;;) {
		c = serial_getc();
		if (c <= 'z' && c >= 'a') {
			serial_putc(c);
			*p++ = c;
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
	
	for (;;) {
		main_loop();
	}
}
