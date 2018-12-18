#include "clcd.h"
#include "kbm.h"
#include "task.h"
#include "kernel.h"
#include "uart.h"
#include "versatile-pb.h"
#include "timer.h"

#include <stddef.h>

#define printf clcd_kprintf

extern Task * running, *readyQueue, *freeList;
extern void tswitch(void);
extern void int_on(void);

unsigned int tick, tick2;
char data;


void timer_task(void)
{
  int i;
  int hh, mm, ss;
  char clock[16];

  //kprintf("timertask %d start\n", running->pid);
  hh = mm = ss = 0;
 
  while(1){
    //kprintf("timertask %d running\n", running->pid);
	printf("timer task\n");
    kernel_sleep((unsigned int)&tick);

    clcd_clearCursor();
 
    clcd_putCursor();

    ss++;
    ss %= 60;
    if (ss==0){
       mm++;
       mm %= 60;
  
       if (mm==0){
           hh++;
           hh %= 24;
       }
    }
    clock[7]='0'+(ss%10); clock[6]='0'+(ss/10);
    clock[4]='0'+(mm%10); clock[3]='0'+(mm/10);
    clock[1]='0'+(hh%10); clock[0]='0'+(hh/10);
 
    for (i=0; i<8; i++){
       	clcd_KdisplayChar(clock[i], 0, 70+i);
		}
	}
}

void timer2_task(void)
{
	while(1)
	{
		printf("Hello its me timer2 task\n");
		kernel_sleep((unsigned int)&tick2);
		printf("Tick now is %d\n",tick2);
	}
}

void kbm_task(void)
{
	while(1)
	{
		printf("Enter a key bro: \n");
		if(kbm_Ngetc() == 0)
		{
			printf("before kbm task sleep\n");
			kernel_sleep((unsigned int)&data);
		}
		data = kbm_Ngetc();
		printf("Entered char is %c\n", data);
	}
}



int main(void)
{
	int_on();
	clcd_init();
	timer_init(TIMER01, 1);
	//timer_init(TIMER23, 1);
	kbm_init();
	clcd_setColor(GREEN);
	VIC->INTENABLE |=   (1 << 4) | (1 << 5) | (1 << 31);	//enable interrupts  add (1 << 31) for kbm
	//kbm is on interrupt line 3 in SIC
	SIC->ENSET |= 1 << 3;
	SIC->PICENSET |= 1 << 3;
	kernel_init();
	kernel_fork((unsigned int)timer_task,3);
	kernel_fork((unsigned int)kbm_task,4);
	//kernel_fork((unsigned int)timer2_task, 3);
	printf("Welcome to TESTOS\n");
	print_Queue(readyQueue);
	print_Queue(freeList);
	timer_start(TIMER01,1);
	//timer_start(TIMER23,1);
	while(1)
	{
		printf("in While 1\n");
		while(readyQueue == ((TaskPtr)0));
		tswitch();
	}
	return 0;	
}

void Timer01_handler(void)
{
	printf("IN TIMER HNADLER\n");
	timer_DisableInt(TIMER01, 1);
	tick++;
	kernel_wakeup((unsigned int)&tick);
}

void Timer23_handler(void)
{
	printf("IN TIMER22 HNADLER\n");
	timer_DisableInt(TIMER23, 1);
	tick2++;
	kernel_wakeup((unsigned int)&tick2);
}

void KBM_handler(void)
{
	kbm_ToASCII();	
	kernel_wakeup((unsigned int)&data);
}


void memcpy(void *dest, void *src, size_t n)
{
   // Typecast src and dest addresses to (char *)
   char *csrc = (char *)src;
   char *cdest = (char *)dest;
 
   // Copy contents of src[] to dest[]
   for (int i=0; i<n; i++)
       cdest[i] = csrc[i];
}







