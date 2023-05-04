/*
 * Adxl345.h
 *
 * Created: 6/25/2022 11:43:32 AM
 *  Author: mahdy
 */ 


#ifndef ADXL345_H_
#define ADXL345_H_

/***************************_INCLUDES_***************************/
#include "Adxl345Cfg.h"
#include "Twi.h"
#include "StdTypes.h"
#define F_CPU 16000000UL
#include <util/delay.h>
/***************************_MACROS_***************************/

#define   ADXL345_ADDRESS     0x53
#define   POWER_CTL           0x2D
#define   READING_ENABLE      0x08

#define   XAXIS_LOWBYTE       0x32
#define   XAXIS_HIGHBYTE      0x33

#define   YAXIS_LOWBYTE       0x34
#define   YAXIS_HIGHBYTE      0x35

#define   ZAXIS_LOWBYTE       0x36
#define   ZAXIS_HIGHBYTE      0x37


/***************************_PROTOTYPES_***************************/
void H_Adxl345_Init(void);
f32  H_Adxl345_Read_Xaxis(void);
f32  H_Adxl345_Read_Yaxis(void);
f32  H_Adxl345_Read_Zaxis(void);

#endif /* ADXL345_H_ */