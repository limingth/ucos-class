/*
 *	main.c    -     demo of printf helloworld 
 *	
 *	Author: 	li ming <admin@lumit.org>
 *	Date:		2005-5-27
 *	Copyleft:	http://www.lumit.org
 */
 
#include "uart.h"

/* delay for some time */
void delay( int time )	
{
	int i, j;

	for( i=0; i<time; i++ )
		for ( j=0; j<65536; j++ )
			;
}

/* retarget code of printf low-level function */
/* *************************************************************** */
#include <stdio.h>

struct __FILE { int handle;   /* Add whatever you need here */};
FILE __stdout;

int fputc(int ch, FILE *f)
{
	if( ch == '\n' )
	{
		uart_putchar( UART0_BASE, '\r' );
		uart_putchar( UART0_BASE, '\n' );
	}
	else
		uart_putchar( UART0_BASE, ch );
	return ch;
}

int ferror(FILE *f)
{
	return EOF;
}
/* *************************************************************** */

int test_rw = 0x2468;
const int test_ro = 0x1357;
int test_bss;

/* demo of printf helloworld */
int main( void )
{
	// uart must be initialized before printf using it to output
	uart_init( UART0_BASE, BAUD_9600 );

	// here we just test uart_putchar function for printf
	uart_putchar( UART0_BASE, 'D' );
	uart_putchar( UART0_BASE, 'e' );
	uart_putchar( UART0_BASE, 'm' );
	uart_putchar( UART0_BASE, 'o' );
	uart_putchar( UART0_BASE, ' ' );
	uart_putchar( UART0_BASE, 'p' );
	uart_putchar( UART0_BASE, 'r' );
	uart_putchar( UART0_BASE, 'i' );
	uart_putchar( UART0_BASE, 'n' );
	uart_putchar( UART0_BASE, 't' );
	uart_putchar( UART0_BASE, 'f' );
	uart_putchar( UART0_BASE, '\r' );
	uart_putchar( UART0_BASE, '\n' );
	
	// demo of printf 
	printf( "hello, lumiter! \n" );	
	
	printf( "test_rw = 0x%x, test_ro = 0x%x, test_bss = 0x%x \n", test_rw, test_ro, test_bss );
	return 0;
}
