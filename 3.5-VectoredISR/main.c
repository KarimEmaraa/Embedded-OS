#include "kbm.h"
#include "clcd.h"
#include "timer.h"
#define printf clcd_kprintf
int main(void)
{
	char x;
	//char line[128];
	clcd_init();
	kbm_init();
	timer_init(TIMER01, 1);
	
	clcd_setColor(GREEN);
	VIC->INTENABLE |= (1 << 31) | (1 << 4);
	//kbm is on interrupt line 3 in SIC
	SIC->ENSET |= 1 << 3;
	SIC->PICENSET |= 1 << 3;
timer_start(TIMER01,1);
	while(1)
	{
		printf("Enter a line: \n");
		x = kbm_getc();
		printf("%c\n",x);
			
	}
	return 0;	
}
