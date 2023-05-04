/*
 * Lcdc.c
 *
 * Created: 5/21/2022 7:22:01 PM
 *  Author: mahdy
 */ 
#include "Lcd.h"


void H_Lcd_Init(void)
{
	#if           LCD_MODE     ==    _8_BIT_MODE
	M_Dio_PinMode(LCD_DATA0_PIN, OUTPUT);
	M_Dio_PinMode(LCD_DATA1_PIN, OUTPUT);
	M_Dio_PinMode(LCD_DATA2_PIN, OUTPUT);
	M_Dio_PinMode(LCD_DATA3_PIN, OUTPUT);
	M_Dio_PinMode(LCD_DATA4_PIN, OUTPUT);
	M_Dio_PinMode(LCD_DATA5_PIN, OUTPUT);
	M_Dio_PinMode(LCD_DATA6_PIN, OUTPUT);
	M_Dio_PinMode(LCD_DATA7_PIN, OUTPUT);
	
	M_Dio_PinMode(LCD_RS_PIN, OUTPUT);
// 	M_Dio_PinMode(LCD_RW_PIN, OUTPUT);
	M_Dio_PinMode(LCD_EN_PIN, OUTPUT);
// 	M_Dio_PinWrite(LCD_RW_PIN, LOW);
	
	_delay_ms(1000);
	H_Lcd_WriteCommand(LCD_8_BIT_MODE);
	H_Lcd_WriteCommand(DISPLAYON_CURSOROFF);
	H_Lcd_WriteCommand(LCD_CLEAR);
	H_Lcd_WriteCommand(LCD_RETURN_HOME);
	
	#elif           LCD_MODE     ==    _4_BIT_MODE
	M_Dio_PinMode(LCD_DATA4_PIN, OUTPUT);
	M_Dio_PinMode(LCD_DATA5_PIN, OUTPUT);
	M_Dio_PinMode(LCD_DATA6_PIN, OUTPUT);
	M_Dio_PinMode(LCD_DATA7_PIN, OUTPUT);
	
 	M_Dio_PinMode(LCD_RS_PIN, OUTPUT);
// 	/*M_Dio_PinMode(LCD_RW_PIN, */OUTPUT);
	M_Dio_PinMode(LCD_EN_PIN, OUTPUT);
// 	M_Dio_PinWrite(LCD_RW_PIN, LOW);
	
	_delay_ms(1000);
	H_Lcd_WriteCommand(LCD_4_BIT_MODE_1);
	H_Lcd_WriteCommand(LCD_4_BIT_MODE_2);
	H_Lcd_WriteCommand(LCD_4_BIT_MODE_3);
	H_Lcd_WriteCommand(DISPLAYON_CURSOROFF);
	H_Lcd_WriteCommand(LCD_CLEAR);
	H_Lcd_WriteCommand(LCD_RETURN_HOME);
	
	#endif
}

void H_Lcd_WriteCharacter(u8 Local_u8_Character)
{
	#if           LCD_MODE     ==    _8_BIT_MODE
	
	M_Dio_PinWrite(LCD_RS_PIN, HIGH);
	LCD_DATA_PORT = Local_u8_Character;
	M_Dio_PinWrite(LCD_EN_PIN, HIGH);
	_delay_ms(1);
	M_Dio_PinWrite(LCD_EN_PIN, LOW);
	_delay_ms(5);
	
	#elif           LCD_MODE     ==    _4_BIT_MODE
	
	M_Dio_PinWrite(LCD_RS_PIN, HIGH);	
	LCD_DATA_PORT = (Local_u8_Character & 0xF0) | (LCD_DATA_PORT & 0x0F) ;
	
	M_Dio_PinWrite(LCD_EN_PIN, HIGH);
	_delay_ms(1);
	M_Dio_PinWrite(LCD_EN_PIN, LOW);
	_delay_ms(5);
	
	LCD_DATA_PORT = (Local_u8_Character << 4) | (LCD_DATA_PORT & 0x0F) ;
	M_Dio_PinWrite(LCD_EN_PIN, HIGH);
	_delay_ms(1);
	M_Dio_PinWrite(LCD_EN_PIN, LOW);
	
	_delay_ms(5);
	#endif
}

void H_Lcd_WriteCommand(u8 Local_u8_Command)
{
	#if           LCD_MODE     ==    _8_BIT_MODE
	M_Dio_PinWrite(LCD_RS_PIN, LOW);
	LCD_DATA_PORT = Local_u8_Command ;
	M_Dio_PinWrite(LCD_EN_PIN, HIGH);
	_delay_ms(1);
	M_Dio_PinWrite(LCD_EN_PIN, LOW);
	_delay_ms(5);
	#elif           LCD_MODE     ==    _4_BIT_MODE
	M_Dio_PinWrite(LCD_RS_PIN, LOW);
	
	LCD_DATA_PORT = (Local_u8_Command & 0xF0) | (LCD_DATA_PORT & 0x0F);
	M_Dio_PinWrite(LCD_EN_PIN, HIGH);
	_delay_ms(1);
	M_Dio_PinWrite(LCD_EN_PIN, LOW);
	_delay_ms(5);
	
	LCD_DATA_PORT = (Local_u8_Command << 4) | (LCD_DATA_PORT & 0x0F);
	M_Dio_PinWrite(LCD_EN_PIN, HIGH);
	_delay_ms(1);
	M_Dio_PinWrite(LCD_EN_PIN, LOW);
	
	_delay_ms(5);
	#endif	
}

void H_Lcd_WriteString(u8* Local_u8_Ptr)
{
	u8 Local_u8_Cnt = 0;
	while(Local_u8_Ptr[Local_u8_Cnt] != _NULL)
	{
		H_Lcd_WriteCharacter(Local_u8_Ptr[Local_u8_Cnt]);
		Local_u8_Cnt ++;
	}
	
}

void H_Lcd_WriteNumber(f32 Local_f32_Number) // ->124
{
	u8 Local_u8_Arr[10] = {0};
	s8 Local_s8_Cnt = 0;
	u8 Local_u8_Digit = 0;
	u8 Local_u8_NumArr[10];
	
	if(Local_f32_Number == 0) H_Lcd_WriteCharacter('0');
	
	else
	{
		if(!IsInteger(Local_f32_Number))
		{
			sprintf(Local_u8_NumArr, "%.2f", Local_f32_Number);
			H_Lcd_WriteString(Local_u8_NumArr);
			return;
		}
		else if(Local_f32_Number < 0)
		{
			H_Lcd_WriteCharacter('-');
			Local_f32_Number = Local_f32_Number * -1;
		}
		while (Local_f32_Number != 0)
		{
			Local_u8_Digit             = (u32)Local_f32_Number % 10;
			Local_u8_Arr[Local_s8_Cnt] = Local_u8_Digit;
			Local_s8_Cnt ++;
			Local_f32_Number = (u32)(Local_f32_Number / 10);
		}
		Local_s8_Cnt --;
		while(Local_s8_Cnt >= 0)
		{
			H_Lcd_WriteCharacter(Local_u8_Arr[Local_s8_Cnt] + 48);
			Local_s8_Cnt --;
		}
	}
}

void H_Lcd_Clr(void)
{
	H_Lcd_WriteCommand(LCD_CLEAR);
}

void H_Lcd_GoTo(u8 Local_u8_Row, u8 Local_u8_Col)
{
	
	u8 Local_u8_Arr[2] = {0x80, 0xC0};
	H_Lcd_WriteCommand(Local_u8_Arr[Local_u8_Row] + Local_u8_Col);
}

void H_Lcd_ShiftRight(void)
{
	H_Lcd_WriteCommand(LCD_SHIFT_RIGHT);
}

void H_Lcd_ShiftLeft(void)
{
	H_Lcd_WriteCommand(LCD_SHIFT_LEFT);
}

void H_Lcd_ClockDisplay(u8 Local_u8_Hour, u8 Local_u8_Minutes, u8 Local_u8_Secondes)
{
	
	H_Lcd_Clr();
	if( (Local_u8_Hour > 23) || (Local_u8_Minutes > 59) || (Local_u8_Secondes > 59) ) H_Lcd_WriteString("Error Format");
	else
	{
		if((Local_u8_Hour < 10)) H_Lcd_WriteCharacter('0');
		H_Lcd_WriteNumber(Local_u8_Hour);
		H_Lcd_WriteCharacter(':');
		if((Local_u8_Minutes < 10)) H_Lcd_WriteCharacter('0');
		H_Lcd_WriteNumber(Local_u8_Minutes);
		H_Lcd_WriteCharacter(':');
		if((Local_u8_Secondes < 10)) H_Lcd_WriteCharacter('0');
		H_Lcd_WriteNumber(Local_u8_Secondes);
	}
}


bool IsInteger(f32 Local_f32_Num)
{
	u32 Local_u32_Temp = (u32) Local_f32_Num;
	
	return Local_u32_Temp == Local_f32_Num;
}