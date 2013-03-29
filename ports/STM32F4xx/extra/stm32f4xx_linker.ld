
MEMORY
{
	ROM (rx)	: ORIGIN = 0x00000000, LENGTH = 1024K
	SRAM (rwx)	: ORIGIN = 0x20000000, LENGTH = 192K
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
	} > ROM

	.data : AT(ADDR(.text) + SIZEOF(.text))
	{
		_data = .;
		*(vtable)
		*(.data*)
		_edata = .;
	} > SRAM

	.bss :
	{
		_bss = .;
		*(.bss*)
		*(COMMON)
		_ebss = .;
	} > SRAM
}

