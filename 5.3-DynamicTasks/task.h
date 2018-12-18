#ifndef _TASK_H_
#define _TASK_H_

#define STACKSIZE 1024  			//Stack size in bytes

typedef enum {
	RUNNING,
	READY,
	FREE
}Task_Status;

typedef struct task{
	struct task *tNEXT;			//pointer to next task
	unsigned int * tSP;			//task stack pointer
	unsigned int tID;			//unique task number
	unsigned int tPRIO;			//task priority
	Task_Status tSTATUS;			//current task status
	unsigned int tSTACK[STACKSIZE];			//task stack

}Task;

typedef Task * TaskPtr;

//create a task with (unsigned int)func and priority: prio. Returns 1 on failure. 0 on success
unsigned int Task_Create(Task * mytask, unsigned int Handler, unsigned int prio);

#endif
