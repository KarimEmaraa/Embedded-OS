#ifndef _UART_H
#define _UART_H

#ifdef V
	#include "versatile-pb.h"
#endif

#ifdef R
	#include "realview-pbx-a9.h"
#endif

#define TXFE 0x80
#define RXFF 0x40
#define TXFF 0x20
#define RXFE 0x10
#define BUSY 0x08

unsigned char uart_getc(UART_Type *device);
void uart_putc(UART_Type *device, char c);
void uart_gets(UART_Type *device, char *s);
void uart_puts(UART_Type *device, char *s);
void uart_prints(UART_Type *device, char *s);
void uart_rpx(UART_Type *device, int x);
void uart_printx(UART_Type *device, int x);
void uart_rpu(UART_Type *device, int x);
void uart_printu(UART_Type *device, int x);
void uart_printi(UART_Type *device, int x);
void uart_fprintf(UART_Type *device, char *fmt,...);
void uart_printf(char *fmt, ...);
//none blocking functions

unsigned char uart_Ngetc(UART_Type *device);			//return 0 if buffer is empty
unsigned char uart_Nputc(UART_Type *device, char c);		//return 0 if buffer is full
unsigned char uart_Nputs(UART_Type *device, char *s);		//return 0 on fail
unsigned char uart_Ngets(UART_Type *device, char *s);		//return 0 on fail
#endif
