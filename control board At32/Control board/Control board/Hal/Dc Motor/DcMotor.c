/*
 * DcMotor.c
 *
 * Created: 6/10/2022 10:16:27 PM
 *  Author: mahdy
 */ 

#include "DcMotor.h"


void H_Motor_Init()
{
	M_Dio_PinMode(MOTOR1_LEFT, OUTPUT);
	M_Dio_PinMode(MOTOR1_RIGHT, OUTPUT);
	
	M_Dio_PinMode(MOTOR2_LEFT, OUTPUT);
	M_Dio_PinMode(MOTOR2_RIGHT, OUTPUT);
	
	M_Dio_PinWrite(MOTOR1_LEFT, LOW);
	M_Dio_PinWrite(MOTOR2_LEFT, LOW);
	
	M_Dio_PinWrite(MOTOR1_RIGHT, LOW);
	M_Dio_PinWrite(MOTOR2_RIGHT, LOW);
	
}
void H_Motor_Forward()
{
	M_Dio_PinWrite(MOTOR1_LEFT, HIGH);
	M_Dio_PinWrite(MOTOR2_LEFT, HIGH);
	
	M_Dio_PinWrite(MOTOR1_RIGHT, LOW);
	M_Dio_PinWrite(MOTOR2_RIGHT, LOW);
}
void H_Motor_Backward()
{
	M_Dio_PinWrite(MOTOR1_LEFT, LOW);
	M_Dio_PinWrite(MOTOR2_LEFT, LOW);
	
	M_Dio_PinWrite(MOTOR1_RIGHT, HIGH);
	M_Dio_PinWrite(MOTOR2_RIGHT, HIGH);	
}

void H_Motor_Left()
{
	M_Dio_PinWrite(MOTOR2_LEFT, HIGH);
	M_Dio_PinWrite(MOTOR1_LEFT, LOW);
	
	M_Dio_PinWrite(MOTOR1_RIGHT, LOW);
	M_Dio_PinWrite(MOTOR2_RIGHT, LOW);
	
}
void H_Motor_Right()
{
	M_Dio_PinWrite(MOTOR2_LEFT, LOW);
	M_Dio_PinWrite(MOTOR1_LEFT, HIGH);
	
	M_Dio_PinWrite(MOTOR1_RIGHT, LOW);
	M_Dio_PinWrite(MOTOR2_RIGHT, LOW);
}

void H_Motor_Stop()
{
	M_Dio_PinWrite(MOTOR2_LEFT, LOW);
	M_Dio_PinWrite(MOTOR1_LEFT, LOW);
	
	M_Dio_PinWrite(MOTOR1_RIGHT, LOW);
	M_Dio_PinWrite(MOTOR2_RIGHT, LOW);
}