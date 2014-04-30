/*
 * Copyright (C) 2014 Huang Bo
 */

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
	. = 0x30000000;

	. = ALIGN(4);
	.text :
	{
		start.o (.text*)
		*(.text*)
	}

	. = ALIGN(4);
	.rodata : { *(.rodata*) }

	. = ALIGN(4);
	.data : { *(.data*) }

	. = ALIGN(4);
	.nobss : { *(.nobss*) }

	. = 0x30200000;
	. = ALIGN(4);
	_bss_start = .;
	.bss : { *(.bss) }
	_bss_end = .;
}
