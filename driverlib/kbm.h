#ifndef _KBM_H_
#define _KBM_H_

#include "versatile-pb.h"

#define N_SCAN 64
#define SIZE 128

typedef volatile struct keyboard{
	char buffer[SIZE];
	unsigned int head, tail, datanum, room;
}KEYBOARD;


void kbm_init(void);
unsigned char kbm_getc(void);
void kbm_gets(char *s);
void kbm_ToASCII(void);
//Non blocking function
unsigned char kbm_Ngetc(void);		//return 0 if buffer is empty
unsigned char kbm_Ngets(char *s);	//return 0 on fail

#endif
