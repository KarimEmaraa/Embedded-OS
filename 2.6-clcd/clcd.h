/*
The LCD screen may be regarded as a rectangular box consisting of 480x640 pixels. Each pixel has a (x,y) coordinate on the
screen. Correspondingly, the frame buffer, u32 fbuf[ ], is a memory area containing 480*640 or 800 * 600 u32 integers, in which the low
24 bits of each integer represents the BGR values of the pixel.

pixel index = x  +  y * 640 (or 800);
*/



#ifndef _CLCD_H_
#define _CLCD_H_
#include "versatile-pb.h"

#define WIDTH 640
#define LENGTH 480

enum COLOR
{
	RED, BLUE, GREEN, WHITE , CYAN, YELLOW
};


void clcd_init(void);
void clcd_test(void);
void clcd_showbmp(unsigned char *img, unsigned int startRow, unsigned int startCol);
void clcd_setColor(enum COLOR x);
void clcd_displayChar(unsigned char c, unsigned int x, unsigned int y); //display using x,y coordinates
void clcd_eraseChar(unsigned char c, unsigned int x, unsigned int y);	//erase using x,y coordinates
void clcd_displayString(unsigned char *s, unsigned int x, unsigned int y);
void scroll(void);
void clcd_KdisplayChar(unsigned char c, int ro, int co);//display using rows and columns.
void clcd_KeraseChar(unsigned char c, int ro, int co); //erase using rows and columns.
void clcd_eraseCurrChar(void); //erase char at current cursor position.
void clcd_clearCursor(void); 
void clcd_putCursor(void); //at current row col postions.
void clcd_putc(unsigned char c); //at current row col and move cursor to the next position.
void clcd_puts( char * s);
void clcd_krpx(unsigned int x); //print hex number at current position.
void clcd_kprintx(unsigned int x); //print hex number in 0x format.
void clcd_krpu(unsigned int x); //for unsigned number
void clcd_kprintu(unsigned int x);
void clcd_kprinti( int x); //signed number
void clcd_kprintf(char * fmt, ...);


 



#endif
