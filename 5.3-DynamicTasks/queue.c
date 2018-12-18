#include "queue.h"
#include "clcd.h"

#define printf clcd_kprintf
extern void unlock(void);
extern void lock(void);

void qTask_Enqueue(TaskPtr * head, TaskPtr * tail, Task * myTask)
{
	Task * temp = *head;
	lock();
	Task * prev = 0;
	if(*head == 0 || (myTask->tPRIO > (*head)->tPRIO) )  //if the task to be enqueued has higher priority
	{
		*head = myTask;			//set it to head
		myTask->tNEXT = temp;
		if(*head == 0)
			*tail = myTask;
		return;
	}

	while(temp != 0 && myTask->tPRIO <= temp->tPRIO)
	{
		prev = temp;
		temp = temp->tNEXT;
	}
	if(temp == 0) //if we are at the end
	{
		*tail = prev;
	}
	else	//else insert between 2 nodes
	{
		prev->tNEXT = myTask;
		myTask = temp;
	}
	unlock();
	*tail = myTask;
}

Task * qTask_Dequeue(TaskPtr * head, TaskPtr * tail)
{
	lock();
	Task * temp = *head;
	*head = temp->tNEXT;
	if(*head == 0)
		*tail = 0;
	unlock();
	return temp;
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
