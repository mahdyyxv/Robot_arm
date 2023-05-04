/*
 * Uart.c
 *
 * Created: 6/29/2022 9:33:17 AM
 *  Author: mahdy
 */ 

#include "Uart.h"
#define F_CPU 16000000UL
#include <util/delay.h>

void (*Callback)(void) = _NULL ;

void M_Uart_Init(u32 Local_u32_BaudRate)
{
	//u16 Local_u16_UBRR= ( F_OSC / ((u32) 16 * Local_u32_BaudRate )) - 1;
	
	u16 Local_u16_UBRR= ( 16000000UL / ((u32) 16 * 9600 )) - 1;

	UBRRH = 0x00 | (unsigned char)(Local_u16_UBRR>>8);
	UBRRL = (unsigned char) Local_u16_UBRR;
	//M_Uart_Receive();
	
	u8 UBRRC = 0;
	ClrBit(UBRRC, 7);
	ClrBit(UBRRC, 6);
	
	ClrBit(UBRRC, 5);
	ClrBit(UBRRC, 4);
	
	ClrBit(UBRRC, 3);
	
	SetBit(UBRRC, 2);
	SetBit(UBRRC, 1);
	ClrBit(UBRRC, 0);
	
	M_Dio_PinMode(_PD0, INPUT);
	M_Dio_PinMode(_PD1, OUTPUT);
	/*Set baud rate */
	//UBRR0 = Local_u16_UBRR;
	//UBR = 0x00 | (Local_u16_UBRR >> 8);
	//Enable receiver and transmitter */
	UCSR0B = (1<<4)|(1<<3);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = UBRRC;
}
void M_Uart_Send(u8  Local_u8_Data)
{
	UDR0 = Local_u8_Data;
	while(  GetBit(UCSR0A, 5) == 0 );
}

void M_Uart_SendString(u8 *Local_u8_DataString)
{
	u8 Local_u8_StrSize = strlen(Local_u8_DataString);
	u8 Local_u8_Cnt = 0;
	for(Local_u8_Cnt = 0; Local_u8_Cnt < Local_u8_StrSize; Local_u8_Cnt++)
	{
		M_Uart_Send(Local_u8_DataString[Local_u8_Cnt]);
		_delay_ms(1);
	}
// 	M_Uart_Send('\r');
// 	M_Uart_Send('\n');
}

u8   M_Uart_Receive()
{
	while(  GetBit(UCSR0A, 7) == 0 );
	return UDR0;
}

void M_Uart_SetCallBack(void (*ptr)(void))
{
	Callback = ptr;
}

