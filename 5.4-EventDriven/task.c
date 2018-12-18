#include "task.h"

unsigned int Task_Create(Task * mytask, unsigned int Handler, unsigned int prio)
{
	if(mytask == 0)
		return 1;
	mytask->tSTATUS = READY;
	mytask->tPRIO = prio;
	for(unsigned int i = 1; i < 15; i++)
	{
		mytask->tSTACK[STACKSIZE - i] = 0;
	}

	mytask->tSTACK[STACKSIZE - 1] = Handler;
	mytask->tSP = &(mytask->tSTACK[STACKSIZE - 14]); //SET SP TO TOP OF STACK
	return 0;
}

