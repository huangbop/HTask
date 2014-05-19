

void print_banner(void)
{
	serial_putc('a');
}


void main_loop(void)
{
	board_init();

	interrupt_init();

	serial_init();

	print_banner();
}
