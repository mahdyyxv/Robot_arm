/*
 * PushButton.h
 *
 * Created: 5/20/2022 9:59:16 PM
 *  Author: mahdy
 */ 


#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

/***************************_INCLUDES_***************************/
#define F_CPU 16000000UL
#include "PushButtonCfg.h"
#include "Dio.h"
#include "StdTypes.h"
#include <util/delay.h>

/***************************_MACROS_***************************/

#define  CLAPP_OPEN_BUTTON		_PD2
#define  CLAPP_CLOSE_BUTTON		_PD3
#define  MODE_BUTTON			_PD4
#define  RESET_BUTTON           _PD5



/***************************_PROTOTYPES_***************************/

void H_PushButton_Init();
u8 H_PushButton_Read(u8);




#endif /* PUSHBUTTON_H_ */