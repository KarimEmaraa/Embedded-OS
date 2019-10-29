#include "semaphore.h"
#include "task.h"
#include "queue.h"

extern Task * running;  
extern TaskPtr readyQueue,  tailReadyQueue;

extern void tswitch(void);
extern void unlock(unsigned int temp);
extern unsigned int lock(void);


void sema_Take(Semaphore * sem)
{
	if(sem == 0) return;
	unsigned int temp;
	unsigned int ints = lock();
	temp = sem->value;
	unlock(ints);
	if(temp == 0)
	{
		running->tSTATUS = BLOCK;
    	qTask_Enqueue(&sem->queueHead, &sem->queueTail, running);
		unlock(ints);
    	tswitch();
	}

	
}

void sema_Give(Semaphore * sem)
{
	if(sem == 0) return;
	Task * temp;
  	unsigned int SR = lock();

  	sem->value++;
	unlock(SR);
	if (sem->value <= 0){
		temp = qTask_Dequeue(&sem->queueHead, &sem->queueTail);
		temp->tSTATUS = READY;
		qTask_Enqueue(&readyQueue, &tailReadyQueue, temp);
	  }

  
}

unsigned int sema_CreateBinary( Semaphore * sem)
{
	if(sem == 0) return 1;
	sem->value = 1;
	sem->queueHead = 0;
	sem->queueTail = 0;
	return 0;
}

unsigned int sema_CreateCount(Semaphore * sem , unsigned int count)
{
	if(sem == 0) return 1;
		sem->value = (int)count;
	sem->queueHead = 0;
	sem->queueTail = 0;
	return 0;
}

