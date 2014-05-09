
#include "htask.h"

struct uart_rx {
	unsigned char buf[64];
} uart0_int_rx;

struct uart_port {
	volatile unsigned ulcon;
	volatile unsigned ucon;
	volatile unsigned ufcon;
	volatile unsigned umcon;
	volatile unsigned utrstat;
	volatile unsigned uerstat;
	volatile unsigned ufstat;
	volatile unsigned umstat;
	volatile unsigned utxh;
	volatile unsigned urxh;
	volatile unsigned ubrdiv;
};

struct serial_device {
	struct uart_port *uart;
	struct uart_rx *rx;
	struct uart_tx *tx;
} uart0 = { (struct uart_port *)&U0BASE, &uart0_int_rx, HT_NULL};

/* XXX:  */
#define PCLK       1
#define BPS        115200

void ht_uart0_handler(int vector, void *param)
{
	
}

void ht_init_uart(void)
{
	int i;
	
	GPHCON |= 0xaa;		/* GPH3 - RxD, GPH2 - TxD */
	GPHUP |= 0xf;		/* disable pull up */

	/* normal mode, no parity, 1 stop, 8-bits */
	uart0.uart->ulcon = 0x3;
	/*  */
	uart0.uart->ucon = 0x245;
	/* disable fifo */
	uart0.uart->ufcon = 0x0;
	/* disable flow control */
	uart0.uart->umcon = 0x0;
	/* baud rate */
	uart0.uart->ubrdiv = (int)(PCLK / (BPS * 16)) - 1;
	/* uart0/1 clock enable, pwmtimer enable */
	CLKCON |= 0xd00;

	for (i = 0; i < 100; i++)
		;		/* do nothing */

	/* install uart0 isr, rx interrupt */
	INTSUBMASK &= ~0x1;
	/* install uart0 interrupt */
	ht_install_interrupt(28, ht_uart0_handler, HT_NULL);
		
}
