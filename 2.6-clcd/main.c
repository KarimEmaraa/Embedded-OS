#include "clcd.h"

extern unsigned char _binary_panda_bmp_start;
extern unsigned char _binary_porkcar_bmp_start;


int main(void)
{

	clcd_init();
	//clcd_showbmp(&_binary_porkcar_bmp_start,0,80);
	//clcd_test();
	clcd_setColor(GREEN);
	clcd_kprintf("hello: 2s\nheelo %d\n",23);
	clcd_kprintf("%d,",2);
	while(1);
	return 0;
}
