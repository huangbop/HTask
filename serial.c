#include "htask.h"
#include "serial.h"


int serial_init(void)
{
	struct gpio *gpio = get_base_gpio();
	struct uart *uart = get_base_uart();

	gpio->GPHCON |= 0xa0;

	/* Tx/Rx interrupt mode */
	uart->ucon = 0x5;
	/* baudrate & flow control setting */
	uart->ubrdiv = 26;
	uart->ulcon = 0x3;

	return 0;
}

void serial_putc(const char c)
{
	struct uart *uart = get_base_uart();

	while (!(uart->utrstat & 0x2));

	uart->utxh = c;

	if (c == '\n')
		serial_putc('\r');
}

void serial_puts(const char *s)
{
	while (*s)
		serial_putc(*s++);
}
