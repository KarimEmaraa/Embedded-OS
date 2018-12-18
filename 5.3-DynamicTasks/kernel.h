#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "task.h"
#include "queue.h"

unsigned int kernel_scheduler(void);
void kernel_init(void);
//create a task mytask with priority prio then enqueue it in running queue and set it to running task
void kernel_fork(unsigned int handler, unsigned int prio);
//gets a task for free task list
Task * kernel_getTask(void);
//adds a task to freeList
void kernel_addTask(Task * mytask);
//called by application tasks to give up cpu voluntarly and switch
void kernel_Giveup(void);

#endif
