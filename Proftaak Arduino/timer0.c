/*
*  Timer0.c
*
*  Copyright (c) 2009 by Avans Hogeschool.
* 
*  Date:    13-apr-2009
*			29-apr-2009
*			15-apr-2010
*			21-dec-2012, Arduino Uno version, runs at 16 MHz
*  Author:  R. Smeets
*/


///////////////////////////////////////////////////////////////////////////////
// system includes

#include <inttypes.h>
#include <avr/io.h>

///////////////////////////////////////////////////////////////////////////////
// application specific includes

#include "timer0.h"

///////////////////////////////////////////////////////////////////////////////
// set timer compare value in OCR0

void timer0_SetCompareValue(uint8_t count)
{
    OCR0A = count; 
}

///////////////////////////////////////////////////////////////////////////////
// initialize timer 0. 

void timer0_Init(void)
{
    TIMSK0 = 0x00;
	TCNT0  = 0;
    TCCR0A = _BV(WGM01);  // select CTC mode, clock not started yet
}



///////////////////////////////////////////////////////////////////////////////
// start timer 0. 16 MHz clock / 8 -> T = 0.5 us

void timer0_Start(void)
{
	uint8_t clockSelect = _BV(CS01) ; // clock / 8

    TCCR0B |= clockSelect; 
}


///////////////////////////////////////////////////////////////////////////////
// delay 100 us
// delay is slightly larger because of instruction and function call overhead !!
// This is taken into account with OCR0_CALL_COMPENSATION, to be subtracted from
// the theoretical/computed required OCR0 value.
// NB.: this is an experimental value and has been determined with the simulator.

void timer0_Delay100us(void)
{
	// define free running counter to start at zero!!
	TCNT0 = 0;

	// wait for Output Compare Flag 0
	while ( (TIFR0 & _BV(OCF0A)) == 0)
	{
	}

	// clear Output Compare Flag 0
	TIFR0 |= _BV(OCF0A);  
}


///////////////////////////////////////////////////////////////////////////////
// delay N times 100 us

void timer0_DelayN100us(uint32_t number)
{
	uint32_t ix = 0;

	for (ix = 0; ix < number; ix++)
	{
		timer0_Delay100us();
	}
}


///////////////////////////////////////////////////////////////////////////////
// function for the user of the library: delays the specified number of
// milliseconds

void delayms(uint32_t milliSeconds)
{
	timer0_DelayN100us(10 * milliSeconds);
}


void InitTimer(void)
{
	timer0_Init();
	timer0_SetCompareValue(200 - OCR0_CALL_COMPENSATION);
	timer0_Start();	
}