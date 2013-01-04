/*
 *	led.h    --     demo of LED application
 *	
 *	Author: 	lumit-admin <admin@lumit.org>
 *	Date:		2004-8-26
 *	Copyright:	http://www.lumit.org
 */

/**************************************************************************
 *
 * ARM - Strategic Support Group
 *
 ***************************************************************************/

/***************************************************************************
 *
 * Module		: led.h
 * Description 	: Set of Macro's to control the LED's on a Evaluator7T 
 *				  board.   
 * Platform		: Evaluator7T
 * Tool Chain	: ARM Developer Suite 1.0
 * History		:
 *
 *			980329 Andrew N. Sloss
 *			- Added header for AEB-1
 *
 *			990320 Andrew N. Sloss
 *			- Added header for Evaluator7T
 *
 **************************************************************************/

/**************************************************************************
 * IMPORTS
 **************************************************************************/

/* none... */

/**************************************************************************
 * MACROS
 **************************************************************************/

	
/* -- On Evaluator7T, the LEDs are connected through IO Port 
   LED1 is Green, LED2 is Red, LED3 is Yellow, LED4 is Green
 */


#define SYSCFG      0x03FF0000
#define IOPDATA		(SYSCFG + 0x5008)
#define LEDBANK		*((unsigned *)IOPDATA)					

#define LED_4_ON    (LEDBANK=LEDBANK|16)
#define LED_3_ON	(LEDBANK=LEDBANK|32)
#define LED_2_ON	(LEDBANK=LEDBANK|64)
#define LED_1_ON	(LEDBANK=LEDBANK|128)

#define LED_4_OFF	(LEDBANK=LEDBANK^16)
#define LED_3_OFF	(LEDBANK=LEDBANK^32)
#define LED_2_OFF	(LEDBANK=LEDBANK^64)
#define LED_1_OFF	(LEDBANK=LEDBANK^128)

/**************************************************************************
 * DATATYPES
 **************************************************************************/

/* none... */

/**************************************************************************
 * STATICS
 **************************************************************************/

/* none... */

/**************************************************************************
 * PROTOTYPES
 **************************************************************************/

/* none... */

/**************************************************************************
 * End of led.h
 **************************************************************************/
