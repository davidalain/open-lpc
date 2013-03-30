/*
 * Linker file para STM32F4xx para ser utilizado com GCC Compiler for ARM
 * Autor: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

MEMORY
{
	ROM1 (rx)	: ORIGIN = 0x08000000, LENGTH = 1024K
	SRAM1 (rwx)	: ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
	.text :
	{
		_text = .;
		KEEP(*(.isr_vector))
		*(.text)
		*(.rodata)
		_etext = .;
	} > ROM1

	.data : AT(ADDR(.text) + SIZEOF(.text))
	{
		_data = .;
		*(vtable)
		*(.data*)
		_edata = .;
	} > SRAM1

	.bss :
	{
		_bss = .;
		*(.bss*)
		*(COMMON)
		_ebss = .;
	} > SRAM1
}

