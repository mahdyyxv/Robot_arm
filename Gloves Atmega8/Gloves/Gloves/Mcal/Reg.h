/*
 * Reg.h
 *
 * Created: 6/27/2022 11:11:20 AM
 *  Author: mahdy
 */ 


#ifndef REG_H_
#define REG_H_

/*********************************_INCLUDES_*********************************/

#include "StdTypes.h"

/*********************************_DIO_REGISTERS_*********************************/

#define     _PINB         *(volatile u8*)0x23
#define     _DDRB         *(volatile u8*)0x24
#define     _PORTB        *(volatile u8*)0x25

#define     _PINC         *(volatile u8*)0x26
#define     _DDRC         *(volatile u8*)0x27
#define     _PORTC        *(volatile u8*)0x28

#define     _PIND         *(volatile u8*)0x29
#define     _DDRD         *(volatile u8*)0x2A
#define     _PORTD        *(volatile u8*)0x2B

/*********************************_SPI_REGISTERS_*********************************/

#define     _SPCR         *(volatile u8*)0x4C
#define     _SPSR         *(volatile u8*)0x4D
#define     _SPDR         *(volatile u8*)0x4E

/*********************************_ADC_REGISTERS_*********************************/

#define     _ADCSRA       *(volatile u8*)0x7A
#define     _ADCSRB       *(volatile u8*)0x7B
#define     _ADMUX        *(volatile u8*)0x7C
#define     _DIDR0        *(volatile u8*)0x7E
#define     _ADCL         *(volatile u8*)0x78
#define     _ADCH         *(volatile u8*)0x79
#define     _ADC_READ     *(volatile u16*)0x78

/*********************************_UART_REGISTERS_*********************************/

#define     UCSR0A       *(volatile u8*)0xC0
#define     UCSR0B       *(volatile u8*)0xC1
#define     UCSR0C       *(volatile u8*)0xC2
#define     UBRR0        *(volatile u16*)0xC4
#define     UBRRL         *(volatile u8*)0xC4
#define     UBRRH         *(volatile u8*)0xC5
#define     UDR0         *(volatile u8*)0xC6


/*********************************_EXT_REGISTERS_*********************************/

#define     EICRA       *(volatile u8*)0x69
#define     EIMSK       *(volatile u8*)0x3D

/*********************************_WDT_REGISTERS_*********************************/

#define     WDTCSR      *(volatile u8*)0x60
#define     MCUSR       *(volatile u8*)0x54

/*********************************_TWI_REGISTERS_*********************************/

#define     TWBR        *(volatile u8*)0xB8
#define     TWSR        *(volatile u8*)0xB9
#define     TWAR        *(volatile u8*)0xBA
#define     TWDR        *(volatile u8*)0xBB
#define     TWCR        *(volatile u8*)0xBC
#define     TWAMR       *(volatile u8*)0xBD

#endif /* REG_H_ */
