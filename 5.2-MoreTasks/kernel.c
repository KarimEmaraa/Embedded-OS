#include "kernel.h"
#define NUMTASK 5

TASK taskArray[NUMTASK], *running; //let it public for now	
unsigned int taskSize = sizeof(TASK);


extern void body(void);

void kernel_init(void)
{
	TASK *temp;
	for(unsigned int i = 0; i < NUMTASK;i++)
	{
		temp = &taskArray[i];
		temp->tID = i;
		temp->tSTATUS = READY;
		if(i){
			for(unsigned int j = 1; j < 15; j++)
				temp->tSTACK[STACKSIZE - j] = 0; //all cpu regs = 0
			temp->tSTACK[STACKSIZE - 1] = (unsigned int)body;  //hardcoded resume point
			temp->tSP = &(temp->tSTACK[STACKSIZE - 14]);	//init task sp
		}
		temp->tNEXT = temp + 1;		//point to next task
	}

	taskArray[NUMTASK - 1].tNEXT = &taskArray[0];
	running = &taskArray[0];	//start task0
	
}

unsigned int kernel_scheduler(void)
{
	running = running->tNEXT;
	return 0;
}

