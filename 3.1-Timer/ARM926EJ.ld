
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
	. = . + 0x800;		/* 2KB of SVC Stack*/
	svc_stack_top = .;
	. = . + 0x800; 		/* 2KB Of IRQ stack*/
	irq_stack_top = .;
	. = . + 0x800;		/* 2K Of FIQ stack*/
	fiq_stack_top = .;
	. = . + 0x800;		/* 2K Of FIQ stack*/
	und_stack_top = .;
	. = . + 0x800;		/* 2K Of FIQ stack*/
	pre_stack_top = .;
	. = . + 0x800;		/* 2K Of FIQ stack*/
	abt_stack_top = .;
	. = . + 0x1000;		/* 4K Of FIQ stack*/
	usr_stack_top = .;

}
