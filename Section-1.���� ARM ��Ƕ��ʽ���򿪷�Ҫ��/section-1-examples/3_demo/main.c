/*
 *	main.c    -     demo of how bootloader works
 *	
 *	Author: 	li ming <admin@lumit.org>
 *	Date:		2005-5-24
 *	Copyleft:	http://www.lumit.org
 */

/* delay for about one second */
void delay( void )	
{
	int i, j;

	for( i=0; i<100; i++ )
		for ( j=0; j<65536; j++ )
			;
}

/* led blink */
int main( void )
{
	volatile unsigned int * leds = (volatile unsigned int *)0x03ff5008;

	while(1)	
	{
		*leds = 0x00020070;		// light led = 1111
		delay();
		*leds = 0x00000000;		// dark led = 0000
		delay();
	}
	
	return 1;
}
