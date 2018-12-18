#include "clcd.h"

static inline void clcd_clearpx(unsigned int x, unsigned int y);
static inline void clcd_setpx(unsigned int x, unsigned int y);

unsigned int * const fb = (unsigned int * const)0x200000;; /*frame buffer pointer*/
char const cursor = 127;
unsigned int row = 0, col = 0, scrow_row = 4;
enum COLOR color;
extern char fonts[];
extern char _binary_font_start;
static char tab[] = "0123456789ABCDEF";

void clcd_init(void)
{
#if (WIDTH == 640)
	/*640*480 display*/
	SCR->OSC1 = 0x2C77;		//Enable clock;
	CLCD->Timing0 = 0x3F1F3F9C;
	CLCD->Timing1 = 0x090B61DF;
	CLCD->Timing2 = 0x067F1800;	
	CLCD->UPBASE = (unsigned int)fb;
	CLCD->IMSC = 0x82B;

	  for (unsigned int x=0; x<640*480; x++)
    		fb[x] = 0x0;    // clean screen; all pixels are BLACK

#elif (WIDTH == 800)
	SCR->OSC1 = 0x2CAC;		//Enable clock;
	CLCD->Timing0 = 0x1313A4C4;
	CLCD->Timing1 = 0x0505F6F7;
	CLCD->Timing2 = 0x071F1800;	
	CLCD->UPBASE = (unsigned int)fb;
	CLCD->IMSC = 0x82B;

	for(unsigned int x = 0; x < 800*600; x++)
		fb[x] = 0x0;	// clean screen; all pixels are BLACK
#endif

}

void clcd_test(void)
{
//create RGB Bands
	for (unsigned int x = 0; x < (212*480); ++x)
  		fb[x] = 0x00FF0000;  //00BBGGRR
  	for (unsigned int x = 212*480+1; x < (424*480); ++x)
  		fb[x] = 0x0000FF00;  //00BBGGRR
  	for (unsigned int x = 424*480+1; x < (640*480); ++x)
  		fb[x] = 0x000000FF;  //00BBGGRR
}

void clcd_showbmp(unsigned char *img, unsigned int startRow, unsigned int startCol)
{
	unsigned int h, w, * q, rowsize;
	unsigned char * byte = 0;

	q = (unsigned int *)(img + 14);
	w = *(q + 1);
	h = *(q + 2);
	img += 54;

	rowsize = 4 * ((3 * w + 3) / 4);
	img += (h - 1) * rowsize; //skip to the last RGB aka first pixel.

	for(unsigned int i = startRow; i < startRow + h; i++)
	{
		byte = img;
		for(unsigned int j = startCol; j < startCol + w; j++)
			{
				fb[i * WIDTH + j] = ((*byte) << 16) | ((*(byte + 1)) << 8) | *(byte + 2); //contruct BGR pixel
				byte += 3;
			}
		img -= rowsize;
	}


}

void clcd_setColor(enum COLOR x)
{
 	color = x;
}
static inline void clcd_clearpx(unsigned int x, unsigned int y)
{
	fb[y * WIDTH + x] = 0x0;
}

static inline void clcd_setpx(unsigned int x, unsigned int y)
{
	switch(color)
	{
		case RED:
			fb[y * WIDTH + x] = 0xFF;
			break;
		case BLUE:
			fb[y * WIDTH + x] = 0x00FF0000;
			break;
		case GREEN:
			fb[y * WIDTH + x] = 0x0000FF00;
			break;
		case WHITE:
			fb[y * WIDTH + x] = 0x00FFFFFF;
			break;
		case YELLOW:
			fb[y * WIDTH + x] = 0x0000FFFF;
			break;
		case CYAN:
			fb[y * WIDTH + x] = 0x00FFFF00;	
			break;
	}
}
void clcd_displayChar(unsigned char c, unsigned int x, unsigned int y)
{
	char * charloc = fonts + c * 16;
	unsigned char byte;
	for(unsigned int i = 0; i < 16; i++)
		{
			byte = *(charloc + i);
			for(unsigned int bit = 0; bit < 8; bit++)
			{
				clcd_clearpx(x + bit, y + i);
				if( byte & (1 << bit))
					clcd_setpx(x + bit , y + i);
			}
		}
}
void clcd_eraseChar(unsigned char c, unsigned int x, unsigned int y)
{
	char * charloc = fonts + c * 16;
	unsigned char byte;
	for(unsigned int i = 0; i < 16; i++)
		{
			byte = *(charloc + i);
			for(unsigned int bit = 0; bit < 8; bit++)
			{
				if( byte & (1 << bit))
					clcd_clearpx(x + bit , y + i);
			}
		}
}
void clcd_displayString(unsigned char *s, unsigned int x, unsigned int y)
{
	while(*s)
	{
		clcd_displayChar(*s, x , y);
		x += 8;
		s++;
	}
}


void scroll(void)
{
	for(unsigned int i = scrow_row * 16 * WIDTH; i < WIDTH * LENGTH; i++)
	{
		fb[i] = fb[i + WIDTH * 16];
	}
}
void clcd_KdisplayChar(unsigned char c, int ro, int co)
{
	clcd_displayChar(c, co * 8 , ro * 16);
}
void clcd_KeraseChar(unsigned char c, int ro, int co)
{
	clcd_eraseChar(c, co * 8 , ro * 16);	
}

void clcd_clearCursor(void)
{
	clcd_KeraseChar(cursor, row, col);
}
void clcd_putCursor(void)
{
	clcd_KdisplayChar(cursor, row, col);
}
void clcd_putc(unsigned char c)
{
	clcd_clearCursor();
	if(c == '\r')
	{
		col = 0;
		clcd_putCursor();
		return;
	}
	else if( c == '\n')
	{
		row++;
		if(row >= 30)
		{
			row = 29;
			scroll();
		}
		clcd_putCursor();
		return;
	}
	else if( c == '\b')
	{
		if(col > 0)
		{
			col--;
			clcd_putCursor();
		}
		return;
	}
	else
	{
		clcd_KdisplayChar(c, row , col);
		col++;
		if(col >= 80)
		{
			col = 0; 
			row++;
			if(row >= 30)
			{
				row = 29;
				scroll();
			}
		}
		clcd_putCursor();
	}
}
void clcd_puts( char * s)
{
	while(*s)
	{
		clcd_putc(*s);	
		s++;
	}
}
void clcd_krpx(unsigned int x)
{
	char c;
  	if (x){
     c = tab[x % 16];
     clcd_krpx(x / 16);
  	}
  	clcd_putc(c);
}
void clcd_kprintx(unsigned int x)
{
	clcd_putc('0'); clcd_putc('x');
  	if (x==0)
    	clcd_putc('0');
  	else
    	clcd_krpx(x);
}
void clcd_krpu(unsigned int x)
{
	char c;
  	if (x){
     	c = tab[x % 10];
     	clcd_krpu(x / 10);
  	}
  	clcd_putc(c);	
}
void clcd_kprintu(unsigned int x)
{
	if (x==0){
		clcd_putc('0');
	}
  	else
    	clcd_krpu(x);

}
void clcd_kprinti(unsigned int x)
{
	if (x<0){
    	clcd_putc('-');
    	x = -x;
  }
  clcd_kprintu(x);
}
void clcd_kprintf(char * fmt, ...)
{
	int *ip;
 	char *cp;
  	cp = fmt;
  	ip = (int *)&fmt + 1;

  	while(*cp){
    	if (*cp != '%'){
      		clcd_putc(*cp);
      		if (*cp=='\n')
				clcd_putc('\r');
      		cp++;
      		continue;
    	}
		cp++;
		switch(*cp){
			case 'c': clcd_putc((char)*ip);      break;
			case 's': clcd_puts((char *)*ip);  break;
			case 'd': clcd_kprinti(*ip);          break;
			case 'u': clcd_kprintu(*ip);          break;
			case 'x': clcd_kprintx(*ip);          break;
    }
    	cp++; ip++;
  }
}













