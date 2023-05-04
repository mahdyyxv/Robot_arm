/*
 * PushButton.c
 *
 * Created: 5/20/2022 9:59:06 PM
 *  Author: mahdy
 */ 
#include "PushButton.h"
#include "Uart.h"
void H_PushButton_Init()
{
	M_Dio_PinMode(CLAPP_OPEN_BUTTON, INPUT_PULLUP) ;
	M_Dio_PinMode(CLAPP_CLOSE_BUTTON, INPUT_PULLUP);
	M_Dio_PinMode(MODE_BUTTON, INPUT_PULLUP);
	M_Dio_PinMode(RESET_BUTTON, INPUT_PULLUP);
}

u8 H_PushButton_Read(u8 Local_u8_PushButton)
{
    char state = 0;
	volatile int cnt = 0;
	if (M_Dio_PinRead(Local_u8_PushButton) == 0)
	{
		_delay_ms(20);
		if (M_Dio_PinRead(Local_u8_PushButton) == 0)
		{
			
			state = 1;
			while (M_Dio_PinRead(Local_u8_PushButton) == 0)
			{
				if( (Local_u8_PushButton == CLAPP_OPEN_BUTTON) || (Local_u8_PushButton == CLAPP_CLOSE_BUTTON) )
				{
					_delay_ms(1000);
					cnt++;
				}
			}
			if(cnt >= 2)
			{
				if(Local_u8_PushButton == CLAPP_OPEN_BUTTON)state = 'A';
				if(Local_u8_PushButton == CLAPP_CLOSE_BUTTON)state ='C';
			
				
			}
		}
	}
	return state;
}
