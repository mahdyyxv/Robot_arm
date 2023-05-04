/*
 * Led.h
 *
 * Created: 5/14/2022 10:27:04 PM
 *  Author: mahdy
 */ 


#ifndef LED_H_
#define LED_H_
/***************************_INCLUDES_***************************/
#include "StdTypes.h"
#include "Dio.h"
#include "LedCfg.h"
#define F_CPU 16000000UL
#include <util/delay.h>

/***************************_MACROS_***************************/

#define FORWARD       _PC0
#define BACKWARD      _PB1
#define LEFT          _PB2
#define RIGHT         _PB3

/***************************_PROTOTYPES_***************************/
void H_Led_Init();
void H_Led_On(u8);
void H_Led_Off(u8);

#endif /* LED_H_ */