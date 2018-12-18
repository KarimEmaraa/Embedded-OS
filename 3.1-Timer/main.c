#include "versatile-pb.h"
#include "timer.h"
#include "clcd.h"
#include "string.c"


#define printf clcd_kprintf


#define VIC_BASE_ADDR 0x10140000
#define VIC_STATUS    (*((volatile unsigned int *)(VIC_BASE_ADDR + 0x000)))
#define VIC_INTENABLE (*((volatile unsigned int *)(VIC_BASE_ADDR + 0x010)))
#define VIC_VADDR     (*((volatile unsigned int *)(VIC_BASE_ADDR + 0x030)))

int main(void)
{

	clcd_setColor(BLUE);
	clcd_init();
    VIC->INTENABLE |= (1<<4);  // timer0,1 at bit4 
  // VIC_INTENABLE |= (1<<5);  // timer2,3 at bit5 

	timer_init(TIMER01,1);
	timer_start(TIMER01, 1);

	while(1);
	return 0;
}


void timer_handler(unsigned int x)
{
	if(x == 0)
	{
		printf("Hello from timer 0\n");
		
	}
	else if(x == 1)
	{
		while(1);
	}
	else if(x == 1)
	{
		while(1);
	}

	else if(x == 1)
	{
		while(1);
	}
	else
		return;

}


