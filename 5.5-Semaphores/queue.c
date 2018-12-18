#include "queue.h"
#include "clcd.h"

#define printf clcd_kprintf
extern void unlock(unsigned int temp);
extern unsigned int lock(void);

void qTask_Enqueue(TaskPtr * head, TaskPtr * tail, Task * myTask)
{
	Task * temp = *head;
	unsigned int ints = lock();	//save cpsr and interrupts off
	Task * prev = 0;
	if(*head == 0 || (myTask->tPRIO > (*head)->tPRIO) )  //if the task to be enqueued has higher priority
	{
		*head = myTask;			//set it to head
		myTask->tNEXT = temp;
		if(*head == 0)
			*tail = myTask;
		unlock(ints);		//get saved cpsr and interrupts on
		return;
	}

	while(temp != 0 && myTask->tPRIO <= temp->tPRIO)
	{
		prev = temp;
		temp = temp->tNEXT;
	}
	if(temp == 0) //if we are at the end
	{
		prev->tNEXT = myTask;
		*tail = myTask;
		myTask->tNEXT = 0;
	}
	else	//else insert between 2 nodes
	{
		prev->tNEXT = myTask;
		myTask->tNEXT = temp;
	}
	unlock(ints);		//get saved cpsr and interrupts on
	*tail = myTask;
}

Task * qTask_Dequeue(TaskPtr * head, TaskPtr * tail)
{
	unsigned int ints = lock();
	if(*head == 0)
		return 0;
	Task * temp = *head;
	*head = temp->tNEXT;
	if(*head == 0)
		*tail = 0;
	unlock(ints);
	return temp;
}

void qTask_EnqueueNoPrio( TaskPtr * head, TaskPtr * tail, Task * myTask)
{
	unsigned int ints = lock();
	myTask->tNEXT = 0;
	if(*head == 0)
	{
		*head = myTask;
	}
	else
	{
		(*tail)->tNEXT = myTask;
	}
	*tail = myTask;
	unlock(ints);
}


void print_Queue(TaskPtr head)
{
	  //printf("readyQueue = ");
	  while(head){
	    printf("[%d %d]->",head->tID, head->tPRIO);
	    head = head->tNEXT;
	  }
	  printf("NULL\n");
}
