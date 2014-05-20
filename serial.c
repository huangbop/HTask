
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



int serial_init(void)
{
	int i;
	struct uart *uart = (struct uart *)0x50000000;

	/* FIFO enable */
	uart->ufcon = 0x7;
	uart->ulcon = 0x3;

	uart->ucon = 0x245;
	uart->ubrdiv = 27;

	for (i = 0; i < 100; i++);
	
	return 0;
}

void serial_putc(char c)
{
	struct uart *uart = (struct uart *)0x50000000;

	while (!(uart->utrstat & 0x2));

	uart->utxh = c;
}
