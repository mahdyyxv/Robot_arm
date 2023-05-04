/*
 * Lcd.h
 *
 * Created: 5/21/2022 7:21:32 PM
 *  Author: mahdy
 */ 


#ifndef LCD_H_
#define LCD_H_


/***************************_INCLUDES_***************************/
#include "LcdCfg.h"
#include "Dio.h"
#include "StdTypes.h"
#include <stdio.h>
#include <stdbool.h>
#define F_CPU 16000000UL
#include <util/delay.h>

/***************************_MACROS_***************************/
#define _8_BIT_MODE                    1
#define _4_BIT_MODE                    2

#define _24_HOUR_MODE                  1
#define _12_HOUR_MODE                  2

#define LCD_8_BIT_MODE                 0x38
#define LCD_4_BIT_MODE_1               0x33
#define LCD_4_BIT_MODE_2               0x32
#define LCD_4_BIT_MODE_3               0x28

#define DISPLAYON_CURSOROFF            0x0C
#define LCD_CLEAR                      0x01
#define LCD_RETURN_HOME                0x02

#define LCD_SHIFT_RIGHT 			   0x05
#define LCD_SHIFT_LEFT   			   0x07

#define _NULL                          '\0'
/***************************_PROTOTYPES_***************************/

void H_Lcd_Init(void);
void H_Lcd_WriteCharacter(u8);
void H_Lcd_WriteCommand(u8); 
void H_Lcd_WriteString(u8*); 
void H_Lcd_WriteNumber(f32);
void H_Lcd_Clr(void);
void H_Lcd_GoTo(u8, u8);
void H_Lcd_ShiftRight(void);
void H_Lcd_ShiftLeft(void);
void H_Lcd_ClockDisplay(u8,u8,u8);
bool IsInteger(f32);
#endif /* LCD_H_ */