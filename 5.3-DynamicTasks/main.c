#include "clcd.h"
#include "kbm.h"
#include "task.h"
#include "kernel.h"
#define printf clcd_kprintf
void body(void);

extern Task * running, *readyQueue, *freeList;
extern void tswitch(void);

int main(void)
{
	//char line[128];
	clcd_init();
	kbm_init();
	clcd_setColor(GREEN);
	VIC->INTENABLE |= 1 << 31;
	//kbm is on interrupt line 3 in SIC
	SIC->ENSET |= 1 << 3;
	SIC->PICENSET |= 1 << 3;
	kernel_init();
	kernel_fork((unsigned int)body, 1);
	printf("Welcome to TESTOS\n");
	print_Queue(readyQueue);
	print_Queue(freeList);
	while(1)
	{
		printf("in WHile 1\n");
		while(readyQueue== ((TaskPtr)0));
		tswitch();
	}
	return 0;	
}

void body(void)
{
  char c; 
  printf("proc %d resume to body()\n", running->tID);
  while(1){

    printf("proc %d in body() input a char [s|f|x] : ", running->tID);
    c = kbm_getc(); 
    printf("%c\n", c);

    switch(c){
      case 'J': tswitch();           break;
      case 'X': kernel_fork((int)body, 1); break;
      case 'Z': kernel_Giveup();             break;
    }
  }
}
