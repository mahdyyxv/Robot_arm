/*
 * LcdCfg.h
 *
 * Created: 5/21/2022 7:22:14 PM
 *  Author: mahdy
 */ 


#ifndef LCDCFG_H_
#define LCDCFG_H_
/***************************_SELECT_LCD_MODE_***************************/

// Option 1 -> [ _8_BIT_MODE ]
// Option 2 -> [ _4_BIT_MODE ]

#define LCD_MODE          _4_BIT_MODE

// Option 1 -> [ _12_BIT_MODE ]
// Option 2 -> [ _24_BIT_MODE ]
#define TIME_MODE         _24_HOUR_MODE


/***************************_SELECT_LCD_PIN_***************************/

#define LCD_DATA_PORT   _PORTA

#define LCD_DATA0_PIN   _PA0
#define LCD_DATA1_PIN	_PA1
#define LCD_DATA2_PIN	_PA2
#define LCD_DATA3_PIN	_PA3
#define LCD_DATA4_PIN	_PA4
#define LCD_DATA5_PIN	_PA5
#define LCD_DATA6_PIN	_PA6
#define LCD_DATA7_PIN	_PA7
/*for kit*/
#define LCD_RS_PIN      _PB1
//#define LCD_RW_PIN      _PB2
#define LCD_EN_PIN      _PB0
/*for simu*/
// #define LCD_RS_PIN      _PB1
// #define LCD_RW_PIN      PB2
// #define LCD_EN_PIN      _PB3
#endif /* LCDCFG_H_ */