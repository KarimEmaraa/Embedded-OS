#include "kbm.h"
#include "clcd.h"
#define printf clcd_kprintf
int main(void)
{
	char x;
	//char line[128];
	clcd_init();
	kbm_init();
	clcd_setColor(GREEN);
	VIC->INTENABLE |= 1 << 31;
	//kbm is on interrupt line 3 in SIC
	SIC->ENSET |= 1 << 3;
	SIC->PICENSET |= 1 << 3;

	while(1)
	{
		printf("Enter a line: \n");
		x = kbm_getc();
		printf("%c\n",x);
			
	}
	return 0;	
}
