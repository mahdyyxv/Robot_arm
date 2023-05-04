/*
 * Control board.c
 *
 * Created: 3/11/2023 12:52:39 PM
 * Author : mahdy
 */ 

////////////////////////////////////////////////////////////////////////////////
// includes

#include "Twi.h"
#include "Lcd.h"
#include "Servo.h"
#include "Uart.h"
#include "Timer0.h"
#include "DcMotor.h"
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>


////////////////////////////////////////////////////////////////////////////////
// Definition



////////////////////////////////////////////////////////////////////////////////
// Prototype functions - functions at end
void Uart_Interrupt();
void Timer0_Interrupt();
////////////////////////////////////////////////////////////////////////////////

// Variables
volatile u8 Local_u8_Cnt = 0;
volatile u8 rec[16] = ""; // edited volatile

u8  uart_rec[16];
u8  Buff[4];
u8  xangle = 90;
u8  yangle = 0;
u8  zangle = 45;
u8  X_Default = 90;
u8  Y_Default = 0;
u8  Z_Default = 45;
u8  clappCnt = 0;
u16 BaseCnt = 0;
u8  Mode = 0;
u8 flag;
////////////////////////////////////////////////////////////////////////////////
// Main

int main(void){
	
	
	//M_Dio_PinMode(_PB4, OUTPUT);
	M_Timer0_Init();
	M_Timer0_SetCallBack(Timer0_Interrupt);
	M_Uart_Init();
	M_Uart_SetCallBack(Uart_Interrupt);
	M_Dio_PinMode(_PD2, OUTPUT);
	M_Dio_PinWrite(_PD2, HIGH);
	sei();
	H_Sero_Init();
	_delay_ms(1000);
	H_Lcd_Init();
	H_Lcd_WriteString("Hi :)");
	_delay_ms(1000);
	H_Lcd_Clr();
	H_Motor_Init();
	H_Servo_SetAngle(ARM_BICEPC, X_Default);
	H_Servo_SetAngle(ARM_RST, Y_Default);
	H_Servo_SetAngle(ARM_HAND, Z_Default);
	//H_Servo_SetAngle(ARM_BASE, 0);
	for (int i = 20; i<70; i++)
	{
		H_Servo_SetAngle(ARM_CLAPP, i);
		_delay_ms(10);
	}
	H_Servo_SetAngle(ARM_CLAPP, 20);
	/*M_Uart_SendString("fsdfsd"); */
	//PCA9685_soft_reset();
	BaseCnt = 0;
	clappCnt = 10;
	
	while(1)
	{	
		//H_Lcd_WriteString("56456456");	
		while(Mode == 0) // Normal Mode (Arm Control)
		{
			//M_Uart_ReceiveString(uart_rec, 16);
// 			H_Lcd_GoTo(0,0);
// 			H_Lcd_WriteString(uart_rec);
			//H_Lcd_WriteString("BICEPS RST HAND");
			H_Servo_SetAngle(ARM_BICEPC, xangle);
			H_Servo_SetAngle(ARM_RST, yangle);
			H_Servo_SetAngle(ARM_HAND, zangle);
// 			M_Uart_Transmit(xangle);
// 			M_Uart_Transmit(yangle);
// 			M_Uart_Transmit(zangle);
			
			H_Lcd_GoTo(0,0);
			H_Lcd_WriteString("BICEPS RST HAND");
			H_Lcd_GoTo(1,0);
			H_Lcd_WriteNumber(xangle);
			H_Lcd_GoTo(1,7);
			H_Lcd_WriteNumber(yangle);
			H_Lcd_GoTo(1,11);
			H_Lcd_WriteNumber(zangle);
			_delay_ms(100);
			/*if(GetBit(flag, 0) == 0){*/
				if(uart_rec[0] == 'X')
				{
					strncpy(Buff, uart_rec+1, strlen(uart_rec)-1);
					xangle = atoi(Buff);
					H_Lcd_Clr();
					memset(Buff,0,4);
				}
			
				else if(uart_rec[0] == 'Y')
				{
					strncpy(Buff, uart_rec+1, strlen(uart_rec)-1);
					yangle = atoi(Buff);
					memset(Buff,0,4);H_Lcd_Clr();
				}
			
				else if(uart_rec[0] == 'Z')
				{
					strncpy(Buff, uart_rec+1, strlen(uart_rec));
					zangle = atoi(Buff);
					memset(Buff,0,4);H_Lcd_Clr();
				}
			//}
							
				if(strcmp(uart_rec, "Clapp+") == 0)
				{
					
					for (u8 i = clappCnt; i<=90; i++,++clappCnt)
					{
						
						if(clappCnt > 90 )
						{
							clappCnt = 90;
							break;
						}
						if(strcmp(uart_rec, "Stop") == 0)break;
						H_Servo_SetAngle(ARM_CLAPP, i);
						_delay_ms(10);
						
					}
					strcat(uart_rec, rec);
				}
				
				if(strcmp(uart_rec, "Clapp-") == 0)
				{
					
					for (u8 i = clappCnt; i>=0 ; --i,--clappCnt)
					{
						if(clappCnt == 0 )
						{
							//clappCnt = 0;
							H_Servo_SetAngle(ARM_CLAPP, 0);
							break;
						}
						if(strcmp(uart_rec, "Stop") == 0)break;
						H_Servo_SetAngle(ARM_CLAPP, i);
						_delay_ms(10);
						
					}
					strcat(uart_rec, rec);
					
				}
				
				if(strcmp(uart_rec, "Base+") == 0)
				{
					H_Servo_360(CLOCKWISE);
					_delay_ms(100);
					H_Servo_360(STOP);
					strcat(uart_rec, rec);
				}
				
				if(strcmp(uart_rec, "Base-") == 0)
				{
					H_Servo_360(ANTICLOCKWISE);
					_delay_ms(100);
					H_Servo_360(STOP);
					strcat(uart_rec, rec);
				}
				
				
				if(strcmp(uart_rec, "Reset") == 0)
				{
					H_Servo_SetAngle(ARM_BICEPC, X_Default);
					H_Servo_SetAngle(ARM_HAND, Z_Default);
					H_Servo_SetAngle(ARM_RST, Y_Default);
					H_Lcd_Clr();
					strcat(uart_rec, rec);
					
				}
				
				
			
		}
		
		H_Lcd_Clr();
		while(Mode == 1)
		{
			H_Lcd_GoTo(0,0);
			H_Lcd_WriteString("Motor Mode");
			if(strcmp(uart_rec, "Stop") == 0)  H_Motor_Stop();
			else if(strcmp(uart_rec, "Forward") == 0) 
			{
				H_Lcd_GoTo(1,0);
				H_Lcd_WriteString("FWD");
				H_Motor_Forward();
				_delay_ms(1000);
				H_Motor_Stop();_delay_ms(1000);
				
			}
			else if(strcmp(uart_rec, "Backward") == 0)
			{
				H_Lcd_GoTo(1,0);
				H_Lcd_WriteString("BWD");
				 H_Motor_Backward();
				_delay_ms(1000);
				H_Motor_Stop();_delay_ms(1000);
			}
			else if(strcmp(uart_rec, "Left") == 0)
			{
				H_Lcd_GoTo(1,0);
				H_Lcd_WriteString("LFT");
				 H_Motor_Left();
				_delay_ms(1000);
				H_Motor_Stop();_delay_ms(1000);
			}
			else if(strcmp(uart_rec, "Right") == 0)
			{
				H_Lcd_GoTo(1,0);
				H_Lcd_WriteString("RHT");
				 H_Motor_Right();
				_delay_ms(1000);
				H_Motor_Stop();_delay_ms(1000);
			}
		}
		
	}
}

/////////////////////////////////////////////////////////////////////
//Functions decleration

void Uart_Interrupt()
{
	

	memset(uart_rec, 0, 16);

	if(Local_u8_Cnt < 15 )
	{
		u8 c ;
		c = _UDR;
		if ( c == '\0' || c == '\n' ||c == '\r')
		{
			
			rec[Local_u8_Cnt] = '\0';
			Local_u8_Cnt = 0;
			
			strcat(uart_rec, rec);
			memset(rec, 0, 16);
			return;
			
		}
		rec[Local_u8_Cnt] = c;
		Local_u8_Cnt++;
	}
}

void Timer0_Interrupt()
{
	if(strcmp(uart_rec , "SwitchMode") == 0)
	{
		 TogBit(Mode, 0);
		 memset(uart_rec, 0, 16);
	}	
}
// 
// void get_angle_value(u8 string[], u8 *x, u8 *y,u8 *z )