
ENTRY(reset_handler)

SECTIONS
{
	. = 0x10000; /*loading address*/
	.text : { ts.o *(.text) }
	.data : { *(.data) }
	_bss_start = .;	/*BSS SECTION START*/
	.bss : { *(.bss) }
	_bss_end = .;	/*BSS SECTION END*/
	. = ALIGN(8);
	. = . + 0x1000;		/* 4KB of SVC Stack*/
	svc_stack_top = .;
	. = . + 0x1000; 		/* 4KB Of IRQ stack*/
	irq_stack_top = .;
}
