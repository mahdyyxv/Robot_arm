 /*
 * Adxl345.c
 *
 * Created: 6/25/2022 11:43:52 AM
 *  Author: mahdy
 */ 
#include "Adxl345.h"

void H_Adxl345_Init(void)
{
	M_Twi_Init();	
	_delay_ms(1000);
	M_Twi_StartCondition();
	M_Twi_SendSlaveAddressWrite(ADXL345_ADDRESS);
	M_Twi_SendByte(POWER_CTL);
	M_Twi_SendByte(READING_ENABLE);
	M_Twi_StopCondition();
	
}

f32   H_Adxl345_Read_Xaxis(void)
{
	int Local_s16_Xaxis = 0;

	M_Twi_StartCondition();
	M_Twi_SendSlaveAddressWrite(ADXL345_ADDRESS);  // 0x53  0b0101 0011 <<1  1010 0110
	M_Twi_SendByte(XAXIS_LOWBYTE);
	
	M_Twi_RepeatedStart();
	M_Twi_SendSlaveAddressRead(ADXL345_ADDRESS);
	Local_s16_Xaxis = M_Twi_ReadByte(1);
	Local_s16_Xaxis |= ( ( M_Twi_ReadByte(2) << 8) );
	
	M_Twi_StopCondition();
	
	return Local_s16_Xaxis / 256.0;
}

f32   H_Adxl345_Read_Yaxis(void)
{
	s16 Local_s16_Yaxis = 0;

	M_Twi_StartCondition();
	M_Twi_SendSlaveAddressWrite(ADXL345_ADDRESS);  // 0x53  0b0101 0011 <<1  1010 0110
	M_Twi_SendByte(YAXIS_LOWBYTE);
	
	M_Twi_RepeatedStart();
	M_Twi_SendSlaveAddressRead(ADXL345_ADDRESS);
	Local_s16_Yaxis = M_Twi_ReadByte(1);
	Local_s16_Yaxis |= ( ( M_Twi_ReadByte(2) << 8) );
	
	M_Twi_StopCondition();
	
	return Local_s16_Yaxis / 256.0;
}

f32   H_Adxl345_Read_Zaxis(void)
{
	s16 Local_s16_Zaxis = 0;

	M_Twi_StartCondition();
	M_Twi_SendSlaveAddressWrite(ADXL345_ADDRESS);  // 0x53  0b0101 0011 <<1  1010 0110
	M_Twi_SendByte(ZAXIS_LOWBYTE);
	
	M_Twi_RepeatedStart();
	M_Twi_SendSlaveAddressRead(ADXL345_ADDRESS);
	Local_s16_Zaxis = M_Twi_ReadByte(1);
	Local_s16_Zaxis |= ( ( M_Twi_ReadByte(2) << 8) );
	
	M_Twi_StopCondition();
	
	return Local_s16_Zaxis / 256.0;
}