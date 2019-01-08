#include "timer.h"

void timer_init(TIMER_Type * timer, unsigned int num)
{
	if(num == 1)
	{
		timer->LOAD = 0x100;
		timer->CONTROL = 0x62; //enable interrupt and use 32 bit mode
		timer->BGLOAD = 0xF0000;
	}
	else if(num == 2)
	{
		timer->T2LOAD = 0x100;
		timer->T2CONTROL = 0x62; //enable interrupt and use 32 bit mode
		timer->T2BGLOAD = 0xF0000 / 2;
	}
}

void timer_start(TIMER_Type * timer, unsigned int num)
{
	if(num == 1)
	{
		timer->CONTROL |= 0x80;
	}
	else if(num == 2)
	{
		timer->T2CONTROL |= 0x80;
	}
}

void timer_DisableInt(TIMER_Type * timer, unsigned int num)
{
	if(num == 1)
	{
		timer->INTCLR |= 0x20;
	}
	else if(num == 2)
	{
		timer->T2INTCLR |= 0x20;
	}
}

void timer_stop(TIMER_Type * timer, unsigned int num)
{
	if(num == 1)
		timer->CONTROL &= ~80;
	else if(num == 1)
		timer->T2CONTROL &= ~80;
}

