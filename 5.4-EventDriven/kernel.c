#include "kernel.h"
#include "clcd.h"
#define NUMTASK 9
#define printf clcd_kprintf
Task taskArray[NUMTASK], *running; //let it public for now	
TaskPtr freeList, readyQueue, tailReadyQueue;
TaskPtr	sleepQueue, tailSleepQueue;
unsigned int taskSize = sizeof(Task);

extern void tswitch(void);
extern void body(void);
extern void unlock(unsigned int temp);
extern unsigned int lock(void);

static void idle_task(void)
{
	printf("in idle\n");
	while(1);
}

void kernel_init(void)
{
	Task *temp;
	for(unsigned int i = 0; i < NUMTASK;i++)
	{
		temp = &taskArray[i];
		temp->tID = i;
		temp->tSTATUS = FREE;
		temp->tEVENT = 0;
		temp->tNEXT = temp + 1;		//point to next task
	}

	taskArray[NUMTASK - 1].tNEXT = 0;
	freeList = &taskArray[0];	//start task0
	readyQueue = 0;
	sleepQueue = 0;
	//Hard code task0
	//temp = kernel_getTask();
	kernel_fork((unsigned int)idle_task, 0);
	
	
}

unsigned int kernel_scheduler(void)
{
	if(running->tSTATUS == READY)
		qTask_Enqueue(&readyQueue, &tailReadyQueue, running);
	running = qTask_Dequeue(&readyQueue, &tailReadyQueue);
	//if(running == 0)
		
	return 0;
}

void kernel_fork(unsigned int handler, unsigned int prio)
{

	Task * mytask = kernel_getTask();//get a task
		
	if(mytask == 0)
		return;
	Task_Create(mytask, handler, prio);	//create it

	qTask_Enqueue(&readyQueue, &tailReadyQueue, mytask);//add it to ready queue
	if(handler == ((unsigned int)idle_task) )	//run the first task (idle task)
		running = mytask;
	
}

Task * kernel_getTask(void)
{
	if(freeList == 0)
		return 0;
	Task * mytask = freeList;		//get a task from free task list
	freeList = freeList->tNEXT;		//update free list to point to the next.
	return mytask;
}

void kernel_addTask(Task * mytask)		//add a task to free list
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


void kernel_sleep(unsigned int event)
{
	unsigned int temp = lock(); //get CPSR 
	running->tEVENT = event;
	running->tSTATUS = SLEEP;
	qTask_Enqueue(&sleepQueue, &tailSleepQueue, running); //add to sleep queue
	print_Queue(sleepQueue);
	
	tswitch();
	
	unlock(temp); //enable interrupts	
	
}

void kernel_wakeup(unsigned int event)
{
	Task * tempTask,  *tempSleep = 0, *tailsleep = 0;
	unsigned int temp = lock();
	printf("in Wake up\n");
	while((tempTask = qTask_Dequeue(&sleepQueue,&tailSleepQueue)) != 0)
	{
		if(tempTask->tEVENT == event)
		{
			tempTask->tSTATUS = READY;
			qTask_Enqueue(&readyQueue, &tailReadyQueue, tempTask); //ADD TO READY QUEUE
			break;
		}
		else
			qTask_EnqueueNoPrio(&tempSleep, &tailsleep, tempTask);
	}
	sleepQueue = tempSleep;
	tailSleepQueue = tailsleep;
	///while(1);
	unlock(temp);
}



















