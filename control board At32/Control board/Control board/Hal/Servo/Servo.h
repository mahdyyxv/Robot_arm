/*
 * Servo.h
 *
 * Created: 3/11/2023 12:57:27 PM
 *  Author: mahdy
 */ 


#ifndef SERVO_H_
#define SERVO_H_

#include "Twi.h"
#include "BitMath.h"
#include "StdTypes.h"
#define F_CPU 16000000UL
#include <util/delay.h>
#include <math.h>


#define ARM_BICEPC     0
#define ARM_RST        7
#define ARM_HAND       2
#define ARM_BASE       3
#define ARM_CLAPP      4

#define CLOCKWISE      0
#define ANTICLOCKWISE  1
#define STOP           2


#define Write_address 0x80>>1  // I2C address for PCA9865 with no solder bridges
#define Read_address Write_address+1
#define PCA9685_software_reset 0x06
#define Reset   0x01        // Reset the device
#define MODE1   0x00        // 0x00 location for Mode1 register address
#define MODE2   0x01        // 0x01 location for Mode2 reigster address
#define LED0    0x06        // location for start of LED0 registers
#define ALL_CH_ON_L_reg   0xFA
#define ALL_CH_ON_H_reg   0xFB
#define ALL_CH_OFF_L_reg  0xFC
#define ALL_CH_OFF_H_reg  0xFD
#define max  550
#define min  204

void H_Sero_Init();
void PCA9685_init();
void PCA9685_send(unsigned int value, unsigned char led);
void PCA9685AllLedOff();
unsigned char PCA9685_read_byte(unsigned char chip_register);
void PCA9685_write_byte(unsigned char chip_register, unsigned char value);
void PCA9685_write_word(unsigned char chip_register, unsigned int word_value);
void PCA9685_soft_reset();
void H_Servo_SetAngle(char Servo_number, unsigned char angle);
void H_Servo_360(u8);

#endif /* SERVO_H_ */