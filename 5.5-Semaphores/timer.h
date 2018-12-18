#ifndef TIMER_H
#define TIMER_H

#include "versatile-pb.h"


void timer_init(TIMER_Type * timer, unsigned int num); //num = timer number 0 or 1 ONLY 
void timer_start(TIMER_Type * timer, unsigned int num);
void timer_DisableInt(TIMER_Type * timer, unsigned int num);


#endif
