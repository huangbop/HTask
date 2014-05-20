#include "htask.h"
#include "serial.h"


int serial_init(void)
{
	struct gpio *gpio = get_base_gpio();
	struct uart *uart = get_base_uart();

	gpio->GPHCON |= 0xa0;

	uart->ubrdiv = 27;
	uart->ulcon = 0x3;

	uart->ufcon = 0x7;
	uart->ucon = 0x245;

	return 0;
}

void serial_putc(const char c)
{
	struct uart *uart = get_base_uart();

	while (!(uart->utrstat & 0x2));

	uart->utxh = c;
}

void serial_puts(const char *s)
{
	while (*s)
		serial_putc(*s++);
}
