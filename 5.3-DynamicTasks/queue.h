#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "task.h"

//Adds myTask to the ready Queue
void qTask_Enqueue(TaskPtr * head, TaskPtr * tail, Task * myTask);
//Remove a task from ready Queue
Task * qTask_Dequeue(TaskPtr * head, TaskPtr * tail);

//for debugging purpose.
void print_Queue(TaskPtr head);

#endif
