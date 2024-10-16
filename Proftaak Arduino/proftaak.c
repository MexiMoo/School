/*
*  proftaak.c
*
*  Copyright (c) 2024 maxro
* 
*  Date:    04-10-2024
*
*/


///////////////////////////////////////////////////////////////////////////////
// system includes

#include <inttypes.h>
#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>

///////////////////////////////////////////////////////////////////////////////
// application specific includes

#include "ports328.h"
#include "timer0.h"

///////////////////////////////////////////////////////////////////////////////
// program defenitions
void SetSyncLed(bool ledOn) //af
{
	if (ledOn == true)
	{
		PORTD = (1 << 6);
	}
	else
	{
		PORTD = (0 << 6);
	}
}
bool IsSyncBitSet() //af
{
	//uint8_t syncBit = ~PINB | (1 << 4);
	uint8_t test = PINB & 8;
	
	if (!test == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool IsSyncDetected() //af //Wachten op opgaande flank (rising edge)
{
	uint8_t sync = PINB & 8;
	while (sync == 1)
	{
		
	}
	while (sync == 0)
	{
		//Niks doen
		//Wachten op opgaande flank (rising edge)
	}
	return true;
}
bool WaitUntilSyncReleased()
{
	bool isSyncPresent = false;
	while (isSyncPresent = false)
	{
		isSyncPresent = IsSyncBitSet();
	}
	return true;
}
void ControlLamps (uint8_t functionCode)
{
	if (functionCode > 7)
	{
		// Buiten de 0-7, er gebeurt niks met de lampen
		return;
	}
	
	if (PINB & 8)
	{
		PORTD = 0x01;
	}
	else if (PINB & 9)
	{
		PORTD = 0x02;
	}
	else if(PINB & 10)
	{
		PORTD = 0x04;
	}
}
uint8_t GetPLCData() // Masker bits 2-0 & Masker bit 3 en verschuif naar bit 0 positie
{
	uint8_t bit210 = PINB & ;
	uint8_t bit3 = PINB & 8;
	return (bit210 | (bit3 << 3));
}
uint8_t GetFunctionCode(uint8_t inputData)
{
	return inputData & 0x07;
}
void SetAcknowledge() // Zet bit 7 (ACK-bit) op "1", zonder de andere bits in PORTD te wijzigen
{
	PORTD |= (1 << 7);
}
void ClearAcknowledge() // Zet bit 7 (ACK-bit) op "0", zonder de andere bits in PORTD te wijzigen
{
	PORTD |= (0 << 7);
}
///////////////////////////////////////////////////////////////////////////////
// program entry point

int main(void)
{
	InitPorts();
	InitTimer();
	
	PORTD = 0x00;	// all LED's off
	
	while (true)
	{
		//uint8_t button_status = PINB & 0x07;  // Lees de status van drukknoppen D2..D0 (bits 2..0 van poort B)
		//ControlLamps(button_status);
		
		while (IsSyncBitSet() == true)
		{
			SetSyncLed(true);
			delayms(100);
			SetSyncLed(false);
			delayms(100);
		}
	}
}
