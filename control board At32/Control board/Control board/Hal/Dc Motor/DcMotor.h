/*
 * DcMotor.h
 *
 * Created: 6/10/2022 10:16:37 PM
 *  Author: mahdy
 */ 


#ifndef DCMOTOR_H_
#define DCMOTOR_H_


/***************************_INCLUDES_***************************/
#include "Dio.h"
#include "DcMotorCfg.h"
#include "BitMath.h"
#include "Reg.h"
/***************************_MACROS_***************************/


/***************************_PROTOTYPES_***************************/

void H_Motor_Init();
void H_Motor_Forward();
void H_Motor_Backward();
void H_Motor_Left();
void H_Motor_Right();
void H_Motor_Stop();


#endif /* DCMOTOR_H_ */