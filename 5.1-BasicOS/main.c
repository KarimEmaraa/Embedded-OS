#include "kernel.h"
#include "clcd.h"

#define printf clcd_kprintf
unsigned int taskSize = sizeof(TASK);
extern TASK * running, t1;
extern void tswitch(void);

int main(void)
{
	clcd_init();
	running = &t1;
	printf("Calling tswitch\n");
	tswitch();
	printf("back to main\n");
	return 0;
}
