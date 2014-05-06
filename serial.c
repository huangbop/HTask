
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

void ht_init_uart(void)
{
	GPHCON |= 0xaa;		/* GPH3 - RxD, GPH2 - TxD */
	GPHUP |= 0xf;		/* disable pull up */

	
}


