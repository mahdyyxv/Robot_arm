/*
 * Servo.c
 *
 * Created: 3/11/2023 12:57:07 PM
 *  Author: mahdy
 */ 


#include "Servo.h"

void H_Sero_Init(void)
{
	M_Twi_Init();
	PCA9685_init();
}
void H_Servo_SetAngle(char Servo_number, unsigned char angle)
{
	u16 x = 0;
	
	if(Servo_number == ARM_BASE) x = (((angle / 360.0) * (max - min)) + min);
	else x = (((angle / 180.0) * (max - min)) + min);
	//uart1_write((x+48));
	PCA9685_send(x,Servo_number);
	//_delay_ms(1);
	//PCA9685_soft_reset();
	
}

void H_Servo_360(u8 Local_u8_Mode)
{
	switch(Local_u8_Mode)
	{
		case CLOCKWISE : PCA9685_send(min,ARM_BASE);break;
		case ANTICLOCKWISE : PCA9685_send(max,ARM_BASE);break;
		case STOP : PCA9685_send(((max-min)/2),ARM_BASE);break;
		default : break;
	}
}
////////////////////////////////////////////////////////////////////////////////
// Functions


// Init the chip with pwm frequency and MODE2 settings

void PCA9685_init(){
	M_Twi_StartCondition();             // Start
	H_Lcd_WriteNumber(1);
	M_Twi_SlaveAddressWrite(Write_address);   // Slave Write_address
	H_Lcd_WriteNumber(2);
	M_Twi_SendByte(MODE1);           // Mode 1 ADDRESS
	H_Lcd_WriteNumber(3);
	M_Twi_SendByte(0b00110001);      // Sleep and change default PWM frequency
	H_Lcd_WriteNumber(4);
	M_Twi_StopCondition();              // Stop
	_delay_ms(1);              // Required 50 us delay
	M_Twi_StartCondition();             // Start
	M_Twi_SlaveAddressWrite(Write_address);   // Slave Write_address
	M_Twi_SendByte(0xFE);            // PWM frequency PRE_SCALE ADDRESS to set pwm at 100Hz
	M_Twi_SendByte(0x7A);            // Osc_clk/(4096*update_rate)=25000000/(4096*60)=0x65
	M_Twi_StopCondition();              // Stop
	_delay_ms(1);              // delay at least 500 us
	M_Twi_StartCondition();             // Start
	M_Twi_SlaveAddressWrite(Write_address);   // Slave Write_address
	M_Twi_SendByte(MODE1);           // Mode 1 register ADDRESS
	M_Twi_SendByte(0b10100001);      // Set MODE1
	M_Twi_StopCondition();              // Stop
	_delay_ms(1);              // delay at least 500 us
	M_Twi_StartCondition();             // Start
	M_Twi_SlaveAddressWrite(Write_address);   // Slave Address
	M_Twi_SendByte(MODE2);           // Mode2 register ADDRESS
	M_Twi_SendByte(0b00000100);      // Set MODE2
	M_Twi_StopCondition();              //
}
// Send pulse length[0-4095] to selected LED/SERVO[0-15]
void PCA9685_send(unsigned int value, unsigned char led){
	unsigned char pulse_length;// temp variable for PWM
	M_Twi_StartCondition();              // Start
	M_Twi_SlaveAddressWrite(Write_address);    // address of selected pca9685
	M_Twi_SendByte(LED0 + 4 * led);   // select slected LED ADDRESS
	M_Twi_SendByte(0x00);             // LED_ON_L
	M_Twi_SendByte(0x00);             // LED_ON_H
	pulse_length = value;      // PWM value lo byte
	M_Twi_SendByte(pulse_length);     // LED_OFF_L
	pulse_length = value>>8;   // pwm 16 bit long, now shift upper 8 to lower 8
	M_Twi_SendByte(pulse_length);     // LED_OFF_H
	M_Twi_StopCondition();               // stop
}

void PCA9685AllLedOff(){
	M_Twi_StartCondition();              // atart
	M_Twi_SlaveAddressWrite(Write_address);    // select pca9685
	M_Twi_SendByte(ALL_CH_OFF_L_reg); // All LEDs Off regiter
	M_Twi_SendByte(0b00000000);       // low byte
	M_Twi_SendByte(0b00010000);       // high byte, bit4 set so full_off see page 21
	M_Twi_StopCondition();               // Stop
}
// Read a byte and return it's value
unsigned char PCA9685_read_byte(unsigned char chip_register){
	unsigned char temp = 0x00;
	M_Twi_StartCondition();
	M_Twi_SlaveAddressWrite(Write_address);
	M_Twi_SendByte(chip_register);
	M_Twi_ReapeatedStart();
	M_Twi_SlaveAddressRead(Write_address);
	temp = M_Twi_ReadByte(NACK);
	M_Twi_StopCondition();
	return temp;
}

void PCA9685_write_byte(unsigned char chip_register, unsigned char value){
	M_Twi_StartCondition();
	M_Twi_SlaveAddressWrite(Write_address);
	M_Twi_SlaveAddressWrite(chip_register);
	M_Twi_SendByte(value);
	M_Twi_StopCondition();
}
// Write 16bits to chip_register, increments automatically from lo to hi byte
void PCA9685_write_word(unsigned char chip_register, unsigned int word_value){
	unsigned char hb = 0x00;
	unsigned char lb = 0x00;
	lb = (word_value & 0x00FF);
	hb = ((word_value & 0xFF00) >> 0x08);
	PCA9685_write_byte(chip_register,lb);
	PCA9685_write_byte((chip_register+1),hb);
}



void PCA9685_soft_reset()
{
		M_Twi_StartCondition();
		M_Twi_SlaveAddressWrite(0x00);
		M_Twi_SlaveAddressWrite(PCA9685_software_reset);
		M_Twi_StopCondition();
}