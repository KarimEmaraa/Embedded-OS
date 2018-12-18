#include "kernel.h"

TASK t1, *running;
unsigned int scheduler(void)
{
	running = &t1; //always schdule t1
	return 0 ;
}
