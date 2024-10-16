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
	//uint8_t syncBit = ~PINB | (1 << 8);
	uint8_t syncBit = ~PINB & 8;
	
	if (syncBit == 0)
	{
		return false;
	}
	else
	{
		return true;
		PORTD = 0xFF;
		delayms(1000);
	}
}
bool IsSyncDetected() //af //Wachten op opgaande flank (rising edge)
{
	//uint8_t sync = PINB & 8;
	uint8_t syncBit = (PINB & 0x08) >> 3; //Masker voor bit 3 (1000) en verschuif naar bit 0
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
	while (isSyncPresent == false)
	{
		isSyncPresent = IsSyncBitSet();
	}
	return isSyncPresent;
}
void ControlLamps(uint8_t functionCode) //getest
{
	if (functionCode == 0)
	{
		// Actie voor functiecode 000 (0)
	}
	else if (functionCode == 1)
	{
		// Actie voor functiecode 001 (1)
	}
	else if (functionCode == 2)
	{
		// Actie voor functiecode 010 (2)
	}
	else if (functionCode == 3)
	{
		// Actie voor functiecode 011 (3)
	}
	else if (functionCode == 4)
	{
		// Actie voor functiecode 100 (4)
	}
	else if (functionCode == 5)
	{
		// Actie voor functiecode 101 (5)
	}
	else if (functionCode == 6)
	{
		// Actie voor functiecode 110 (6)
	}
	else if (functionCode == 7)
	{
		// Actie voor functiecode 111 (7)
	}
	else
	{
		// Doe niets als de functiecode niet tussen 0 en 7 ligt
	}
}
uint8_t GetPLCData(void) //getest
{
	uint8_t data = PINB & 0x0F; //Masker voor bits 0, 1, 2 en 3 (1111)
	return data;
}
uint8_t GetFunctionCode(uint8_t inputData) //getest
{
	uint8_t functionCode = inputData & 0x07; //Masker voor bits 0, 1 en 2 (0111)
	return functionCode;
}
void SetAcknowledge() // Zet bit 7 (ACK-bit) op "1", zonder de andere bits in PORTD te wijzigen
{
	//PORTD |= (1 << 7);
}
void ClearAcknowledge() // Zet bit 7 (ACK-bit) op "0", zonder de andere bits in PORTD te wijzigen
{
	//PORTD |= (0 << 7);
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
		
		uint8_t plcData = GetPLCData();
		uint8_t functionCode = GetFunctionCode(plcData);
		ControlLamps(functionCode);
		
		
		//while (WaitUntilSyncReleased() == true)
		//{
			//SetSyncLed(true);
			//delayms(100);
			//SetSyncLed(false);
			//delayms(100);
		//}
	}
}
