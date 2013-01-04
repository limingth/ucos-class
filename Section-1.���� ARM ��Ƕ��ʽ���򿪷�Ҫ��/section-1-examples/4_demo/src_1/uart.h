/*
 *	uart.h    -     header file for uart driver
 *	
 *	Author: 	li ming <admin@lumit.org>
 *	Date:		2005-5-24
 *	Copyleft:	http://www.lumit.org
 */

/**************************************************************
 * ROUTINES
 **************************************************************/
#ifndef SYSCFG
#define SYSCFG      0x03FF0000
#endif

#define UART0_BASE	(SYSCFG + 0xD000)
#define UART1_BASE 	(SYSCFG + 0xE000)

 /* default baud rate value */ 
#define BAUD_9600	(162 << 4)

void uart_init( unsigned int UART_BASE, unsigned int baud );

int uart_putchar( unsigned int UART_BASE, char ch );

int uart_getchar( unsigned int UART_BASE, char * ch );

int uart_test( void );
