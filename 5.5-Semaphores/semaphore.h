#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include "task.h"

typedef struct sema
{
	int value;
	Task * queueHead;
	Task * queueTail;
}Semaphore;

void sema_Take(Semaphore * sem);
void sema_Give(Semaphore * sem);
/*creates a binary semaphore, returns 0 on success*/
unsigned int sema_CreateBinary( Semaphore * sem);
/* creates a counting semaphore, returns 0 on success */
unsigned int sema_CreateCount(Semaphore * sem , unsigned int count);

#endif
