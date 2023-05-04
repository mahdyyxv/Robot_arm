/*
 * Led.c
 *
 * Created: 5/14/2022 10:27:40 PM
 *  Author: mahdy
 */ 

#include "Led.h"
#include "LedCfg.h"

void H_Led_Init()
{
	M_Dio_PinMode(FORWARD,  OUTPUT);
	M_Dio_PinMode(BACKWARD, OUTPUT);
	M_Dio_PinMode(LEFT,     OUTPUT);
	M_Dio_PinMode(RIGHT,    OUTPUT);
	
	M_Dio_PinWrite(FORWARD,  LOW);
	M_Dio_PinWrite(BACKWARD, LOW);
	M_Dio_PinWrite(LEFT,     LOW);
	M_Dio_PinWrite(RIGHT,    LOW);
}

void H_Led_On(u8 Local_u8_Led)
{
	M_Dio_PinWrite(Local_u8_Led, HIGH);
}

void H_Led_Off(u8 Local_u8_Led)
{
	M_Dio_PinWrite(Local_u8_Led, LOW);
}
