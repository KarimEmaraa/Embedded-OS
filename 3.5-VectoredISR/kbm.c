#include "kbm.h"

static KEYBOARD keyb;

/* Scan codes to ASCII for unshifted keys; unused keys are left out 
static char unsh[N_SCAN] = {
 0,033,'1','2','3','4','5','6','7','8','9','0', '-','=','\b','\t',
 'q','w','e','r','t','y','u','i','o','p','[',']', '\r', 0,'a','s',
 'd','f','g','h','j','k','l',';',0,  0,  0,  0,  'z','x','c','v',
 'b','n','m',',','.','/', 0,'*',0, ' '
};*/

/* Scan codes to ASCII for shifted keys; unused keys are left out */
static char sh[N_SCAN] = {
 0,033,'!','@','#','$','%','^',        '&','*','(',')', '_', '+','\b','\t',
 'Q','W','E','R','T','Y','U','I',      'O','P','{','}', '\r', 0, 'A', 'S',
 'D','F','G','H','J','K','L',':',       0, '~', 0, '|', 'Z', 'X','C', 'V',
 'B','N','M','<','>','?',0,'*',         0, ' '
};

void kbm_init(void)
{
	KB->ICR = 0x14;
	KB->CLKDIV = 8;
	keyb.head = keyb.tail = keyb.datanum = 0;
	keyb.room = SIZE;
		
}

void kbm_ToASCII(void)
{
	//if key is pressed
	if(KB->DATA & 0x80)
	{
		return;
	}
	//if key is released
	char c = sh[KB->DATA];	//get data
	keyb.buffer[keyb.head++] = c; //add to the buffer
	keyb.head %= SIZE; //rewind on buffer overflow
	keyb.datanum++;
	keyb.room--;	
}
unsigned char kbm_getc(void)
{	
	char c;
	//enable interrupts
	unlock();
	while(keyb.datanum == 0);
	//disable interrupts
	lock();

	c = keyb.buffer[keyb.tail++];
	keyb.tail %= SIZE; //rewind on buffer overflow
	keyb.datanum--;
	keyb.room--;
	//re-enable interrupts
	unlock();
	return c;

}

void kbm_gets(char * s)
{
	char c;
	while( (c = kbm_getc() ) != '\r')
		*s++ = c;
	*s = '\0';
}


















