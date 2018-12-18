#include "uart.h"
//#include "string.h"

int main()
{

	//int i;
	char s[32];
uart_printf("Enter a char from serial terminal \n\r");
while(1)
{
	uart_gets(UART0, s);
	 uart_printf("    ");
	 uart_printf("%s\n", s);
}
}
