#include "htask.h"
#include "serial.h"
#include "lib.h"


void main_loop(void)
{
	char c;
	
	c = serial_getc();
	ht_printf("you input %c - %d\n" , c, 10);
}
