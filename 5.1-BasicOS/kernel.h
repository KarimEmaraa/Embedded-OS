#ifndef _KERNEL_H_
#define _KERNEL_H_

#define STACKSIZE 1024  			//Stack size in bytes

typedef struct task{
	struct task *tnext;			//pointer to next task
	unsigned int * tSP;			//task stack pointer
	int tstack[STACKSIZE];			//task stack

}TASK;

unsigned int scheduler(void);
#endif
