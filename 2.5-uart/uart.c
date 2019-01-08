#include "uart.h"

static const char *tab = "0123456789ABCDEF";

unsigned char uart_getc(UART_Type *device)
{
	while ((device->FR & RXFE));	// loop if FR is REFE
	return (unsigned char)device->DR; 	// return a char in DR
}



void uart_putc(UART_Type *device, char c)
{
	while (device->FR & TXFF); // loop if FR is TXFF
	device->DR = (unsigned int)c;  // write char to data register
}


void uart_gets(UART_Type *device, char *s)
{
	while ((*s = uart_getc(device)) != '\r') 
	{
		uart_putc(device,*s);	//echo back
		s++;
 	}
	*s = 0;
}


void uart_puts(UART_Type *device, char *s)
{
	while (*s)
	{
		uart_putc(device, *s++);
		if(*s == '\n')
		{
			uart_putc(device, '\r');
		}
	}
}


void uart_prints(UART_Type *device, char *s)
{
	while(*s)
    		uart_putc(device, *s++);
}

void uart_rpx(UART_Type *device, int x)
{
	
	char c;
	if (x){
		c = tab[x % 16];
		uart_rpx(device, x / 16);
		uart_putc(device, c);
	}
	
}

void uart_printx(UART_Type *device, int x)
{
	
	uart_prints(device, "0x");
	if (x==0)
		uart_putc(device, '0');
	else
		uart_rpx(device, x);
	uart_putc(device, ' ');
}

void uart_rpu(UART_Type *device, int x)
{
	char c;
  	if (x){
     		c = tab[x % 10];
     		uart_rpu(device, x / 10);
		uart_putc(device, c);
  	}
  	
}

void uart_printu(UART_Type *device, unsigned int x)
{
  	if (x==0)
    	uart_putc(device, '0');
 	else
    	uart_rpu(device, x);
  	uart_putc(device, ' ');
}

void uart_printi(UART_Type *device, int x)
{
	  if (x<0){
    	uart_putc(device, '-');
    	x = -x;
  		}
 	 uart_printu(device, x);
}

void uart_fprintf(UART_Type *device, char *fmt,...)
{
	int *ip;
  	char *cp;
  	cp = fmt;
  	ip = (int *)&fmt + 1;

  	while(*cp){
    	if (*cp != '%'){
      		uart_putc(device, *cp);
      	if (*cp=='\n')
		uart_putc(device, '\r');
      	cp++;
      	continue;
    	}
    	cp++;
    switch(*cp){
    	case 'c': uart_putc(device, (char)*ip);      break;
    	case 's': uart_prints(device, (char *)*ip);  break;
    	case 'd': uart_printi(device, *ip);           break;
    	case 'u': uart_printu(device, *ip);           break;
    	case 'x': uart_printx(device, *ip);  break;
    }
    cp++; ip++;
  }
}

void uart_printf(char *fmt, ...)
{
	int *ip;
  	char *cp;
  	cp = fmt;
  	ip = (int *)&fmt + 1;

  	while(*cp){
    	if (*cp != '%')
		{
      		uart_putc(UART0, *cp);
      		if (*cp=='\n')
				uart_putc(UART0, '\r');
      		cp++;
      		continue;
    	}
    	cp++;
    	switch(*cp){
			case 'c': uart_putc(UART0, (char)*ip);      break;
			case 's': uart_prints(UART0, (char *)*ip);  break;
			case 'd': uart_printi(UART0, *ip);           break;
			case 'u': uart_printu(UART0, *ip);           break;
			case 'x': uart_printx(UART0, *ip);  break;
    }
    cp++; ip++;
  }
}

