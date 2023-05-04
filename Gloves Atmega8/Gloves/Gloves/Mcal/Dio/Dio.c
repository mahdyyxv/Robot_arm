/*
 * Dio.c
 *
 * Created: 6/27/2022 11:16:32 AM
 *  Author: mahdy
 */ 
#include "Dio.h"

void M_Dio_PinMode(u8 Local_u8_Pin, u8 Local_u8_Mode)
{
	u8 Local_u8_Port = Local_u8_Pin / 10;
	u8 Local_u8_Bit  = Local_u8_Pin % 10;
	
	switch(Local_u8_Mode)
	{
		case INPUT:
		switch(Local_u8_Port)
		{
			case 1: ClrBit(_DDRB, Local_u8_Bit); break;
			case 2: ClrBit(_DDRC, Local_u8_Bit); break;
			case 3: ClrBit(_DDRD, Local_u8_Bit); break;
			default:                             break;
		}
												 break;
		case OUTPUT:
		switch(Local_u8_Port)
		{
			case 1: SetBit(_DDRB, Local_u8_Bit); break;
			case 2: SetBit(_DDRC, Local_u8_Bit); break;
			case 3: SetBit(_DDRD, Local_u8_Bit); break;
			default:                             break;
		}
												 break;
		case INPUT_PULLUP:
		switch(Local_u8_Port)
		{
			case 1:
				ClrBit(_DDRB, Local_u8_Bit);
				SetBit(_PORTB, Local_u8_Bit); 
				break;
			
			case 2:
				ClrBit(_DDRC, Local_u8_Bit);
				SetBit(_PORTC, Local_u8_Bit); 
				break;
				
			case 3: 
				ClrBit(_DDRD, Local_u8_Bit);
				SetBit(_PORTD, Local_u8_Bit);
				break;
				
			default:                             break;
		}
												 break;
		
		default:                                 break;		
	}	
}

void M_Dio_PinWrite(u8 Local_u8_Pin, u8 Local_u8_Mode)
{
	u8 Local_u8_Port = Local_u8_Pin / 10;
	u8 Local_u8_Bit  = Local_u8_Pin % 10;
	
	switch(Local_u8_Mode)
	{
		case LOW:
		switch(Local_u8_Port)
		{
			case 1: ClrBit(_PORTB, Local_u8_Bit); break;
			case 2: ClrBit(_PORTC, Local_u8_Bit); break;
			case 3: ClrBit(_PORTD, Local_u8_Bit); break;
			default:                              break;
		}
		break;
		case HIGH:
		switch(Local_u8_Port)
		{
			case 1: SetBit(_PORTB, Local_u8_Bit); break;
			case 2: SetBit(_PORTC, Local_u8_Bit); break;
			case 3: SetBit(_PORTD, Local_u8_Bit); break;
			default:                              break;
		}
		break;
		
		default:                                  break;
	}
}


u8   M_Dio_PinRead(u8 Local_u8_Pin)
{
	u8 Local_u8_Port = Local_u8_Pin / 10;
	u8 Local_u8_Bit  = Local_u8_Pin % 10;
	u8 Local_u8_PinRead = 0;
	switch(Local_u8_Port)
	{
		case 1: Local_u8_PinRead = GetBit(_PINB, Local_u8_Bit); break;
		case 2: Local_u8_PinRead = GetBit(_PINC, Local_u8_Bit); break;
		case 3: Local_u8_PinRead = GetBit(_PIND, Local_u8_Bit); break;
		default:                                                break;
	}
	
	return Local_u8_PinRead;
}
void M_Dio_PinToggle(u8 Local_u8_Pin)
{
	u8 Local_u8_Port = Local_u8_Pin / 10;
	u8 Local_u8_Bit  = Local_u8_Pin % 10;
	
	switch(Local_u8_Port)
	{
		case 1: TogBit(_PORTB, Local_u8_Bit); break;
		case 2: TogBit(_PORTC, Local_u8_Bit); break;
		case 3: TogBit(_PORTD, Local_u8_Bit); break;
		default:                                                break;
	}
}
void M_Dio_PortMode(u8 Local_u8_Port, u8 Local_u8_Value)
{
	switch (Local_u8_Port)
	{
		case B: _DDRB = Local_u8_Value; break;
		case C: _DDRC = Local_u8_Value; break;
		case D: _DDRD = Local_u8_Value; break;
		default:                         break;
	}
}
void M_Dio_PortWrite(u8 Local_u8_Port, u8 Local_u8_Value)
{
	switch (Local_u8_Port)
	{
		case B: _PORTB = Local_u8_Value; break;
		case C: _PORTC = Local_u8_Value; break;
		case D: _PORTD = Local_u8_Value; break;
		default:                         break;
	}
}
