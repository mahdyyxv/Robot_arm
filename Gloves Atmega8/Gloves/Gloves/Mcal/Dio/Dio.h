/*
 * Dio.h
 *
 * Created: 6/27/2022 11:16:14 AM
 *  Author: mahdy
 */ 


#ifndef DIO_H_
#define DIO_H_

/*********************************_INCLUDES_*********************************/

#include "DioCfg.h"
#include "Reg.h"
#include "StdTypes.h"
#include "BitMath.h"

/*********************************_MACROS_*********************************/
#define    INPUT        1
#define    OUTPUT       2
#define    INPUT_PULLUP 3

#define    HIGH         1
#define    LOW          2

#define    ENABLE       1
#define    DISABLE      2

#define    B            1
#define    C            2
#define    D            3

#define    _PB0         10
#define    _PB1         11
#define    _PB2         12
#define    _PB3         13
#define    _PB4         14
#define    _PB5         15
		   
#define    _PC0         20
#define    _PC1         21
#define    _PC2         22
#define    _PC3         23
#define    _PC4         24
#define    _PC5         25
		   
#define    _PD0         30
#define    _PD1         31
#define    _PD2         32
#define    _PD3         33
#define    _PD4         34
#define    _PD5         35
#define    _PD6         36
#define    _PD7         37


/*********************************_PROTOTYPE_*********************************/
void M_Dio_PinMode(u8, u8);
void M_Dio_PinWrite(u8, u8);
u8   M_Dio_PinRead(u8);
void M_Dio_PinToggle(u8);
void M_Dio_PortMode(u8, u8 );/*Port Ex (B) , value in hex*/
void M_Dio_PortWrite(u8, u8);

#endif /* DIO_H_ */