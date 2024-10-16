/*
*  ports328.c
*
*  Copyright (c) 2023 by Avans Hogeschool Breda
*
*  Date:     08-jun-2023
*  Author:   Raoul Smeets
*
*  IO ports for Arduino Uno board. Uses:
*      8-bit output on port D (bits 7..0)
*      4-bit input  on port B (bits 3..0)
*/


///////////////////////////////////////////////////////////////////////////////
// system includes

#include <inttypes.h>
#include <avr/io.h>
#include <stdbool.h>


///////////////////////////////////////////////////////////////////////////////
// application specific includes

#include "ports328.h"


///////////////////////////////////////////////////////////////////////////////
// void InitPorts(void)

void InitPorts(void)
{
	//output: PORTD 7..0
	//input:  PINB  3..0

	DDRD = 0xFF;	// D: all outputs
	DDRB = 0x00;	// B: all inputs
}
