/*
 * Twi.c
 *
 * Created: 7/3/2022 11:33:56 AM
 *  Author: mahdy
 */ 
#include "Twi.h"

void M_Twi_Init(void)
{
	TWBR = 3;	

	SetBit(TWCR, 2);
}

void M_Twi_StartCondition(void)
{ 
	SetBit(TWCR, 5);
	ClrBit(TWCR, 4);
	ClrBit(TWCR, 6);
	SetBit(TWCR, 7); // To clear Interrupt flag
	while(!( GetBit(TWCR, 7) ));
	while( ( ( TWSR & 0xF8 ) != 0x08 ) );
}

void M_Twi_SendSlaveAddressWrite(u8 Local_u8_Address)
{
	TWDR = (Local_u8_Address << 1);
	ClrBit(TWCR, 5);
	SetBit(TWCR, 7); // To clear Interrupt flag
	while(!( GetBit(TWCR, 7) ));
	while( ( ( TWSR & 0xF8 ) != 0x18 ) );
}
void M_Twi_SendSlaveAddressRead(u8 Local_u8_Address)
{
	TWDR = (Local_u8_Address << 1) | 1;
	ClrBit(TWCR, 5);
	SetBit(TWCR, 7); // To clear Interrupt flag
	while(!( GetBit(TWCR, 7) ));
	while( ( ( TWSR & 0xF8 ) != 0x40 ) );
}

void M_Twi_SendByte(u8 Local_u8_Data)
{
	TWDR = Local_u8_Data;
	ClrBit(TWCR, 5);
	//ClrBit(TWCR, 4);
	SetBit(TWCR, 7); // To clear Interrupt flag
	while(!( GetBit(TWCR, 7) ));
	while( ( ( TWSR & 0xF8 ) != 0x28) );
}
u8   M_Twi_ReadByte(u8 Local_u8_AkcStatus)
{
	
	
	if (Local_u8_AkcStatus == ACK)
	{
		ClrBit(TWCR, 5);
		ClrBit(TWCR, 4);
		SetBit(TWCR, 6);
		SetBit(TWCR, 7); // To clear Interrupt flag
		while(!( GetBit(TWCR, 7) ));
		while( ( ( TWSR & 0xF8 ) != 0x50 ) );
	}
	else if (Local_u8_AkcStatus == NACK)
	{
		ClrBit(TWCR, 6);
		SetBit(TWCR, 7); // To clear Interrupt flag
		while(!( GetBit(TWCR, 7) ));
	}
		
	return TWDR;
}

void M_Twi_StopCondition(void)
{
	
	SetBit(TWCR, 4);
	SetBit(TWCR, 7); // To clear Interrupt flag
/*	while(!( GetBit(TWCR, 7) ));*/
}

void M_Twi_RepeatedStart(void)
{
	SetBit(TWCR, 5);
	SetBit(TWCR, 7); // To clear Interrupt flag
	while(!( GetBit(TWCR, 7) ));
	while( ( ( TWSR & 0xF8 ) != 0x10 ) );
}