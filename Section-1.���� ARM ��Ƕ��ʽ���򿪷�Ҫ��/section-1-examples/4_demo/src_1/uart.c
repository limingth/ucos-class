/*
 *	uart.c    -     driver of uart 
 *	
 *	Author: 	li ming <admin@lumit.org>
 *	Date:		2005-5-24
 *	Copyleft:	http://www.lumit.org
 */

#include "uart.h"

/*
 * Serial settings.......................
 */
	
#define	ULCON	0x00
#define	UCON	0x04
#define	USTAT	0x08
#define	UTXBUF	0x0C
#define	URXBUF	0x10
#define	UBRDIV	0x14

/*
 * Line control register bits............
 */
 
#define	ULCR8bits	(3)
#define	ULCRS1StopBit	(0)
#define	ULCRNoParity	(0)

/*
 * UART Control Register bits............
 */
 
#define 	UCRRxM	(1)
#define 	UCRRxSI	(1 << 2)
#define 	UCRTxM	(1 << 3)
#define 	UCRLPB	(1 << 7)

/*
 * UART Status Register bits
 */
 
#define USROverrun     	(1 << 0)
#define	USRParity      	(1 << 1)
#define	USRFraming     	(1 << 2)
#define	USRBreak       	(1 << 3)
#define	USRDTR		(1 << 4)
#define	USRRxData      	(1 << 5) 
#define	USRTxHoldEmpty 	(1 << 6)
#define	USRTxEmpty     	(1 << 7)

#define COM1_DEBUG	(1)
#define COM0_USER	(0)

// UART registers are on word aligned, D8

/* UART primitives */
#define GET_STATUS(p)	(*(volatile unsigned  *)((p) + USTAT))
#define RX_DATA(s)     	((s) & USRRxData)
#define GET_CHAR(p)	(*(volatile unsigned  *)((p) + URXBUF))
#define TX_READY(s)    	((s) & USRTxHoldEmpty)
#define PUT_CHAR(p,c)  	(*(unsigned  *)((p) + UTXBUF) = (unsigned )(c))

void uart_init( unsigned int UART_BASE, unsigned int baud )
{
   /* Disable interrupts  */
   *(volatile unsigned *) (UART_BASE + UCON) = 0;

   /* Set port for 8 bit, one stop, no parity  */
   *(volatile unsigned *) (UART_BASE + ULCON) = (ULCR8bits);

   /* Enable interrupt operation on UART */
   *(volatile unsigned *) (UART_BASE + UCON) = UCRRxM | UCRTxM;

   /* Set baud rate  */
   *(volatile unsigned *) (UART_BASE + UBRDIV) = baud;

}

int uart_putchar( unsigned int UART_BASE, char ch )
{
	/* read tx ready flag, when =1 break */
	while ( TX_READY(GET_STATUS(UART_BASE))==0)
		;
	
	PUT_CHAR(UART_BASE, ch);

	return ch;
}

int uart_getchar( unsigned int UART_BASE, char * ch )
{
	/* read rx ready flag, when =1 break */
	while ( (RX_DATA(GET_STATUS(UART_BASE)))==0 ) 
		;		

	*ch = GET_CHAR(UART_BASE);

	return *ch;
}

/* a very simple uart driver test for echo function */
int uart_test( void )
{
	char ch ;
	
	uart_init( UART0_BASE, BAUD_9600 );
	
	while( 1 )
	{
		uart_getchar( UART0_BASE, &ch );
		uart_putchar( UART0_BASE, ch );
	}
	
	return 0;
}

#if 0
int uart0_putchar( char ch )
{
	uart_putchar( UART0_BASE, ch );
	return ch;
}

int uart1_putchar( char ch )
{
	uart_putchar( UART1_BASE, ch );
	return ch;
}
#endif