/*
 * Twi.h
 *
 * Created: 7/3/2022 11:34:07 AM
 *  Author: mahdy
 */ 


#ifndef TWI_H_
#define TWI_H_

/*********************************_INCLUDES_*********************************/

#include "TwiCfg.h"
#include "Reg.h"
#include "StdTypes.h"
#include "BitMath.h"

/*********************************_MACROS_*********************************/

#define MASTER      1
#define SLAVE       2

#define ACK         1
#define NACK        2

/*********************************_PROTOTYPE_*********************************/
void M_Twi_Init(void);
void M_Twi_StartCondition(void);
void M_Twi_SendSlaveAddressWrite(u8);
void M_Twi_SendSlaveAddressRead(u8);

void M_Twi_SendByte(u8);
u8   M_Twi_ReadByte(u8);

void M_Twi_StopCondition(void);
void M_Twi_RepeatedStart(void);

#endif /* TWI_H_ */