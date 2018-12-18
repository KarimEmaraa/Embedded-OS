#include "clcd.h"
#include "kbm.h"
#include "timer.h"
#define printf clcd_kprintf
#define VIC_BASE_ADDR 0x10140000
void __attribute__((interrupt)) undef_handler(void) { while(1); }
void __attribute__((interrupt)) swi_handler(void) { while(1); }
void __attribute__((interrupt)) prefetch_abort_handler(void) { while(1); }
void __attribute__((interrupt)) data_abort_handler(void) { while(1); }
void __attribute__((interrupt)) fiq_handler(void) { while(1); }

//void timer_handler(unsigned int x);

void IRQ_handler(void)
{

	void (*f)(void);
	// f as a function pointer
	f =(void *)*((unsigned int *)(VIC_BASE_ADDR+0x30));
	f();
	*((int *)(VIC_BASE_ADDR+0x30)) = 1; // write to vectorAddr as EOI*/

}



void DefaultHandler(void)
{
	printf("sd");
}

void KBM_handler(void)
{
	kbm_ToASCII();
}

void Timer01_handler(void)
{
	timer_DisableInt(TIMER01, 1);
	printf("In timer\n");
}

void Timer23_handler(void)
{
	while(1);
}

void UART0_handler(void)
{
	while(1);
}
void UART1_handler(void)
{
	while(1);
}

void WD_handler(void)
{
	while(1);
}














