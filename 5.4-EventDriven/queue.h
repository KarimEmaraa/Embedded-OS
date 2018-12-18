#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "task.h"

//Adds myTask to the Queue
void qTask_Enqueue(TaskPtr * head, TaskPtr * tail, Task * myTask);
//Remove a task from Queue
Task * qTask_Dequeue(TaskPtr * head, TaskPtr * tail);
//Normal enqueue without using priorities
void qTask_EnqueueNoPrio( TaskPtr * head, TaskPtr * tail, Task * myTask);

//for debugging purpose.
void print_Queue(TaskPtr head);

#endif
