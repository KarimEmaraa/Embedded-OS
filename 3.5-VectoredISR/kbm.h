#ifndef _KBM_H_
#define _KBM_H_

#include "versatile-pb.h"

#define N_SCAN 64
#define SIZE 128

typedef volatile struct keyboard{
	char buffer[SIZE];
	unsigned int head, tail, datanum, room;
}KEYBOARD;

extern void unlock(void);
extern void lock(void);

void kbm_init(void);
unsigned char kbm_getc(void);
void kbm_gets(char *s);
void kbm_ToASCII(void);

#endif
