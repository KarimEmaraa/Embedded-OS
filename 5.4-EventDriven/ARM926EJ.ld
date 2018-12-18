
ENTRY(reset_handler)

MEMORY
{
	MOMO (RWX) : ORIGIN = 0x10000, LENGTH = 64K
}


SECTIONS
{

	.text : { ts.o *(.text) } > MOMO
	.data : { *(.data) } > MOMO
	_bss_start = .;	/*BSS SECTION START*/
	.bss : { *(.bss) } > MOMO
	_bss_end = .;	/*BSS SECTION END*/
	. = ALIGN(8);
	. = . + 0x1000;		/* 4KB of SVC Stack*/
	svc_stack_top = .;
	. = . + 0x1000; 		/* 4KB Of IRQ stack*/
	irq_stack_top = .;
}
