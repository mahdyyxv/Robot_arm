/*
 * Gloves.c
 *
 * Created: 2/15/2023 3:06:18 PM
 * Author : mahdy
 */ 
////////////////////////////////////////////////////////////////////////////////
// includes
#define F_CPU 16000000UL
#include <util/delay.h>
#include "Led.h"
#include "Uart.h"
#include "Reg.h"
#include "MPU9250.h"
#include "PushButton.h"
#include "Adxl345.h"

#include <avr/interrupt.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define PI           3.1415926535897932384626433832795
#define RAD_TO_DEG   (180.0/PI)
////////////////////////////////////////////////////////////////////////////////
// Definition



////////////////////////////////////////////////////////////////////////////////
// Prototype functions - functions at end
f32 MAP(f32 au32_IN, f32 au32_INmin, f32 au32_INmax, f32 au32_OUTmin, f32 au32_OUTmax);

////////////////////////////////////////////////////////////////////////////////
// Variables

u8 flag = 0;
/*
bit 0  -> clapp start opening or stop  // if 0 stop else start   open
bit 1  -> clapp start closing or stop // if 0 stop else start closing

bit 2  -> Base Start to rotate clockwise       // if 0 stop else start Rotating
bit 3  -> Base Start to rotate anti clockwise // if 0 stop else start  Rotating
*/
u8 Mode = 0;
u8 accel_flag = 0;
u8 gyro_flag = 0;
char buffer[8];
unsigned char x,y,z;
u16 xangle,yangle,zangle ;
u8 AngleToSend = 0;
// variable for control Car
signed int Xaxs = 0;
signed int Yaxs = 0;
u8 string[10] = "Stop\r\n";
////////////////////////////////////////////////////////////////////////////////
// Main

int main(void)
{
	M_Uart_Init(9600);
	M_Twi_Init();
	//M_Uart_SendString("X90\n");
	M_Dio_PinMode(_PB5, OUTPUT);
 	MPU9250_beginAccel(ACC_FULL_SCALE_2_G);
	H_PushButton_Init();
	
	while (1)
	{

		//if(H_PushButton_Read(MODE_BUTTON) == 1) TogBit(Mode, 0);
		while(Mode == 0)
		{
			if(H_PushButton_Read(MODE_BUTTON) == 1) TogBit(Mode, 0);
			//M_Dio_PinToggle(_PC0);
		    MPU9250_accelUpdate();
// 			M_Uart_Send(sdfg);
			//M_Uart_Send('\n');
			M_Dio_PinToggle(_PB5);
			_delay_ms(100);
			//M_Uart_SendString("Z0\n");
			if (1)
			{
				x = (u8)((((MPU9250_accelX()*10)+10) / 20.0 ) * 180.0 ) ;
				y = (u8)((((MPU9250_accelY()*10)+10) / 20.0 ) * 180.0 );
				z = (u8)((((MPU9250_accelZ()*10)+10) / 20.0 ) * 180.0 );
// 									sprintf(buffer, "X%d\r", x);
// 									M_Uart_SendString(buffer);
// 									memset(buffer, 0, 8);
// 									
// 									sprintf(buffer, "y%d\r", y);
// 									M_Uart_SendString(buffer);
// 									memset(buffer, 0, 8);
// 									
// 									sprintf(buffer, "z%d\r", z);
// 									M_Uart_SendString(buffer);
// 									memset(buffer, 0, 8);
// 									_delay_ms(1000);
// 				
// 				xangle= (u16)((RAD_TO_DEG * (atan2(-y, -z)+PI)));
// 				yangle= (u16)((RAD_TO_DEG * (atan2(-x, -z)+PI)));
// 				zangle= (u16)((RAD_TO_DEG * (atan2(-y, -x)+PI)));
//       		M_Uart_SendString("X180\r\n");
				
// 				if((x >=90  && x <= 150) && (y >= 90 && y <= 180) )
// 				{
// 					u8 mov1 = MAP(x,90,150,90,180);
// 					sprintf(buffer, "X%u\r", mov1);
// 					M_Uart_SendString(buffer);
// 					memset(buffer, 0, 8);
// 					_delay_ms(1000);
// 					if(y >= 150 && y <= 180)
// 					{
// 						u8 mov2 = MAP(y,150,180,0,30);
// 						sprintf(buffer, "Y%u\r", mov2);
// 						M_Uart_SendString(buffer);
// 						memset(buffer, 0, 8);
// 						_delay_ms(1000);
// 					}
// 					
// 				}
// 				else if((x >= 0 && x <= 85) && (y >= 0 && y <= 85) )
// 				{
// 					u8 mov2 = MAP(x,0,85,0,90);
// 					sprintf(buffer, "Y%u\r", mov2);
// 					M_Uart_SendString(buffer);
// 					memset(buffer, 0, 8);
// 					_delay_ms(1000);
// 					if(y >= 10 && y<=100 )
// 					{
// 						mov2 = MAP(x,10,100,90,180);
// 						sprintf(buffer, "Y%u\r", mov2);
// 						M_Uart_SendString(buffer);
// 						memset(buffer, 0, 8);
// 						_delay_ms(1000);
// 					}
// 				}
				if( (x >= 105 && x <= 180) && ( (y > 80 && y <100) || (y > 0 && y <20)  ))
				{
					xangle = MAP(x, 105, 180, 90, 180);
					sprintf(buffer, "X%u\r", xangle);
					M_Uart_SendString(buffer);
					memset(buffer, 0, 8);
					_delay_ms(1000);
					
				}
				else if(( x<=80 && x>=0) && ( (y > 80 && y <100) || (y > 0 && y <20)  ))
				{
					xangle = MAP(x, 0, 80, 180, 0);
					sprintf(buffer, "Y%u\r", xangle);
					M_Uart_SendString(buffer);
					memset(buffer, 0, 8);
					_delay_ms(1000);
				}
				
				else if(( y<=80 && y>=0) && ( (x > 80 && x <110) || (x > 0 && x <20)  ))
				{
					xangle = MAP(y, 0, 80, 70, 0);
					sprintf(buffer, "Z%u\r", xangle);
					M_Uart_SendString(buffer);
					memset(buffer, 0, 8);
					_delay_ms(1000);
				}
				
			}
			u8 Openclapread = H_PushButton_Read(CLAPP_OPEN_BUTTON);
			u8 Closeclapread = H_PushButton_Read(CLAPP_CLOSE_BUTTON);
			u8 ResetRead = H_PushButton_Read(RESET_BUTTON);
			if(Openclapread == 1)
			{
				
				TogBit(flag, 0);
				if(  GetBit(flag, 0) == 1 )
				{
					M_Uart_SendString(string);
					_delay_ms(100);
					M_Uart_SendString("Clapp+\n");
					_delay_ms(100);
				}
				else M_Uart_SendString(string);
				Openclapread = 0;
			}
			if(Closeclapread == 1)
			{
				TogBit(flag, 1);
				if(  GetBit(flag, 1) == 1 )
				{
					M_Uart_SendString(string);
					_delay_ms(1);
					M_Uart_SendString("Clapp-\n");
				}
				else M_Uart_SendString(string);
				Closeclapread = 0;
			}
			//M_Uart_Send(H_PushButton_Read(CLAPP_OPEN_BUTTON));
			if(Openclapread == 'A')
			{
				TogBit(flag, 2);
				//M_Uart_SendString('B');
				
				if(  GetBit(flag, 2) == 1 )
				{
					
					M_Uart_SendString(string);
					_delay_ms(1);
					M_Uart_SendString("Base+\n");
					
				}
				else M_Uart_SendString(string);
				Openclapread = 0;
			}
			if(Closeclapread == 'C')
			{
				TogBit(flag, 3);
				if(  GetBit(flag, 3) == 1 )
				{
					M_Uart_SendString(string);
					_delay_ms(1);
					M_Uart_SendString("Base-\n");
				}
				else M_Uart_SendString(string);
				Closeclapread = 0;
			}
			if(ResetRead == 1)
			{
				M_Uart_SendString("Reset\n");
				_delay_ms(10);
				
				ResetRead = 0;
			}
			//if( (GetBit(flag, 0) == 0) || (GetBit(flag, 1) == 0) || (GetBit(flag, 2) == 0) || (GetBit(flag, 3) == 0) )M_Uart_SendString(string);
			
// 			else{
// 				M_Uart_SendString(string);
// 			}
		}
		M_Uart_SendString("SwitchMode\r");
		while(Mode == 1)
		{
			if(H_PushButton_Read(MODE_BUTTON) == 1) TogBit(Mode, 0);
			MPU9250_accelUpdate();
			M_Dio_PinToggle(_PB5);
			//M_Uart_Send('\n');
			//M_Uart_SendString("SwitchMode\r");
			_delay_ms(400);
			if (1)
			{
				
				Yaxs = MPU9250_accelY()*10.0;
				Xaxs = MPU9250_accelX()*10.0;
				//M_Uart_SendString("Left\r");
				_delay_ms(10);
						
				
				if( Yaxs < -2 )
				{
					M_Uart_SendString("Backward\r");
					//_delay_ms(1);
					_delay_ms(100);
					
				}
				
				if( Yaxs > 2 )
				{
					M_Uart_SendString("Forward\r");
					_delay_ms(1);
				}
				
				/*else M_Uart_SendString(string);*/
				
				if( Xaxs < -2 )
				{
					M_Uart_SendString("Left\r");
					_delay_ms(1);
				}
				
				if( Xaxs > 2 ){
					M_Uart_SendString("Right\r");
					_delay_ms(1);
				}
				if((Xaxs < 2 && Xaxs > -2) && (Yaxs < 2 && Yaxs > -2) )
				{
					 M_Uart_SendString(string);
					
				}//else M_Uart_SendString(string);
			}
		}
		M_Uart_SendString("SwitchMode\r");
		//_delay_ms(100);
	}
}


/* YalahwaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaY ?????????? */

/////////////////////////////////////////////////////////////////////
//Functions decleration




f32 MAP(f32 au32_IN, f32 au32_INmin, f32 au32_INmax, f32 au32_OUTmin, f32 au32_OUTmax)
{
	return ((((au32_IN - au32_INmin)*(au32_OUTmax - au32_OUTmin))/(au32_INmax - au32_INmin)) + au32_OUTmin);
}

