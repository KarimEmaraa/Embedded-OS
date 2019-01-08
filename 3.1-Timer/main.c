#include "versatile-pb.h"
#include "timer.h"
#include "clcd.h"
#include "string.c"


#define printf clcd_kprintf



int main(void)
{

	clcd_setColor(GREEN);
	clcd_init();
    	VIC->INTENABLE |= (1<<4);  // timer0,1 at bit4 
  	//VIC->INTENABLE |= (1<<5);  // timer2,3 at bit5 
	timer_init(TIMER01,1);
	timer_start(TIMER01, 1);
	timer_init(TIMER01,2);
	timer_start(TIMER01, 2);

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
		printf("Hello from timer 2\n");
	}
	return;

}


