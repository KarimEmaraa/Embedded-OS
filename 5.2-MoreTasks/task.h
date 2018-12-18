#ifndef _TASK_H_
#define _TASK_H_

#define STACKSIZE 1024  			//Stack size in bytes

typedef enum {
	RUNNING,
	READY
}Task_Status;

typedef struct task{
	struct task *tNEXT;			//pointer to next task
	unsigned int * tSP;			//task stack pointer
	unsigned int tID;			//unique task number
	Task_Status tSTATUS;			//current task status
	unsigned int tSTACK[STACKSIZE];			//task stack

}TASK;

#endif
