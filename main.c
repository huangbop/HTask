#include "htask.h"
#include "serial.h"


void main_loop(void)
{
	char c;
	
	c = serial_getc();
	serial_putc(c);
}
