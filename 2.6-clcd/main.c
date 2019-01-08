#include "clcd.h"

extern unsigned char _binary_panda_bmp_start;
extern unsigned char _binary_porkcar_bmp_start;


int main(void)
{

	clcd_init();
	//clcd_showbmp(&_binary_panda_bmp_start,0,80);
	//clcd_test();
	clcd_setColor(RED);
	//unsigned char he[6] = "Karim";
	/*clcd_putc('a');
	clcd_putc('d');
	clcd_putc('\n');
	clcd_putc('d');*/


	clcd_kprintf("%d %x", -14, 14);
	while(1);
	return 0;
}
