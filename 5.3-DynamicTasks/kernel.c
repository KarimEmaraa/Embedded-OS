#include "kernel.h"
#include "clcd.h"
#define NUMTASK 9
#define printf clcd_kprintf
Task taskArray[NUMTASK], *running; //let it public for now	
TaskPtr freeList, readyQueue, tailReadyQueue;
unsigned int taskSize = sizeof(Task);

extern void tswitch(void);
extern void body(void);

void kernel_init(void)
{
	Task *temp;
	for(unsigned int i = 0; i < NUMTASK;i++)
	{
		temp = &taskArray[i];
		temp->tID = i;
		temp->tSTATUS = FREE;
		temp->tNEXT = temp + 1;		//point to next task
	}

	taskArray[NUMTASK - 1].tNEXT = 0;
	freeList = &taskArray[0];	//start task0
	readyQueue = 0;
	//Hard code task0
	temp = kernel_getTask();
	temp->tPRIO = 0;		//lowest priority
	running = temp;
	
}

unsigned int kernel_scheduler(void)
{
	if(running->tSTATUS == READY)
		qTask_Enqueue(&readyQueue, &tailReadyQueue, running);
	running = qTask_Dequeue(&readyQueue, &tailReadyQueue);
	return 0;
}

void kernel_fork(unsigned int handler, unsigned int prio)
{

	Task * mytask = kernel_getTask();//get a task
		
	if(mytask == 0)
		return;
	Task_Create(mytask, handler, prio);	//create it

	qTask_Enqueue(&readyQueue, &tailReadyQueue, mytask);//add it to ready queue
	
}

Task * kernel_getTask(void)
{
	if(freeList == 0)
		return 0;
	Task * mytask = freeList;		//get a task from free task list
	freeList = freeList->tNEXT;		//update free list to point to the next.
	return mytask;
}

void kernel_addTask(Task * mytask)
{
	if(mytask == 0)
		return;
	mytask->tNEXT = freeList;
	freeList = mytask;
}

void kernel_Giveup(void)
{
	running->tSTATUS = FREE;		//set it to free task
	kernel_addTask(running);		//add it again to free list
	tswitch();						//switch context
}






















