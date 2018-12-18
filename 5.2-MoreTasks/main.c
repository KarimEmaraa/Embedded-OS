#include "clcd.h"
#include "kbm.h"
#include "task.h"
#include "kernel.h"
#define printf clcd_kprintf
void body(void);

extern TASK * running;
extern void tswitch(void);

int main(void)
{
	char c;
	//char line[128];
	clcd_init();
	kbm_init();
	clcd_setColor(GREEN);
	VIC->INTENABLE |= 1 << 31;
	//kbm is on interrupt line 3 in SIC
	SIC->ENSET |= 1 << 3;
	SIC->PICENSET |= 1 << 3;
	kernel_init();
	printf("Welcome to TESTOS\n");
	while(1)
	{
		printf("Task 0 running input a key : ");
		c = kbm_getc(); printf("%c\n", c);
		tswitch();
	}
	return 0;	
}

void body(void)
{
	char c;
	printf("Task %d resumes now in function body\n", running->tID);
	while(1)
	{
		printf("Task %d in while loop, input a char [s] : ", running->tID);
		c = kbm_getc();
		printf("%c\n", c);
		tswitch();
	}
}
