#include "versatile-pb.h"
#include "clcd.h"
#include "kbm.h"
#define printf clcd_kprintf

void __attribute__((interrupt)) undef_handler(void) { while(1); }
void __attribute__((interrupt)) swi_handler(void) { while(1); }
void __attribute__((interrupt)) prefetch_abort_handler(void) { while(1); }
void __attribute__((interrupt)) data_abort_handler(void) { while(1); }
void __attribute__((interrupt)) fiq_handler(void) { while(1); }

void timer_handler(unsigned int x);

void IRQ_handler(void)
{

	/*//timer 0 or 1 interrupt bits
	if(VIC->IRQSTATUS & 0x0010)
	{	
		//check intrrupt source
		if(TIMER01->RIS)
		{
			TIMER01->INTCLR = 1;//write clears interrupts
			timer_handler(0UL);
		}	
		else if(TIMER01->T2MIS)
		{
			TIMER01->T2INTCLR = 1;
			timer_handler(1UL);			
		}
	}
	else if(VIC->IRQSTATUS & 0x0020)
	{
		if(TIMER23->MIS)
		{
			TIMER23->INTCLR = 1;//write clears interrupts
			timer_handler(2UL);
		}	
		else if(TIMER23->T2MIS)
		{
			TIMER23->T2INTCLR = 1;
			timer_handler(3UL);			
		}
	}*/

	if(VIC->IRQSTATUS & (1 << 31))
	{
		//KB->DATA = 0; //clear interrupt
		kbm_ToASCII();
	}
}


















