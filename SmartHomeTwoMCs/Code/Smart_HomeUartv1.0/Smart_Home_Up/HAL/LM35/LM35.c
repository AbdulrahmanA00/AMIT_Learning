/*
 * LM35_Program.c
 *
 *  Created on: Dec 10, 2023
 *      Author: Abdulrahman Ayman
 */
#include "LM35.h"


void LM35_Init(void)
{
	//ADC Initialization.
	//
	MCAL_ADC_ADC_Init();
	//Set LM35 Pin Direction as Input.
	MCAL_DIO_u8SetPinDirection(PortA,Pin0,PIN_INPUT);

}



u8 LM35_Read(void)
{

	u16 LOC_u16AnalogValue,LOC_u16DigitalValue;
	u8 LOC_u8Temp;
	MCAL_ADC_ADC_StartConversion();

	LOC_u16DigitalValue = ADC_DATA;
	LOC_u16AnalogValue = ((u32) LOC_u16DigitalValue*5000)/1024;

	LOC_u8Temp = LOC_u16AnalogValue/10;


	return LOC_u8Temp;
}


