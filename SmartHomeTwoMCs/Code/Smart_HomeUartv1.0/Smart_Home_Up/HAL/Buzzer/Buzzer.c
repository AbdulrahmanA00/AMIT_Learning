/*
 * Buzzer.c
 *
 *  Created on: Sep 25, 2023
 *      Author: 2023
 */
#include "Buzzer.h"

//BuzzerInit
STD_TYPE HAL_Buzzer_u8BuzzerInit(u8 LOC_u8BuzzerPortID, u8 LOC_u8BuzzerPinID)
{
	u8 LOC_u8Return_Value = E_NOT_OK;
	if( (LOC_u8BuzzerPortID <= PortD) && (LOC_u8BuzzerPinID <= Pin7) )
	{
		LOC_u8Return_Value = MCAL_DIO_u8SetPinDirection(LOC_u8BuzzerPortID,LOC_u8BuzzerPinID,Pin_Output);
	}
	else
	{
		//Do Nothing.
	}
	return LOC_u8Return_Value;
}

//BuzzerMode
STD_TYPE HAL_Buzzer_u8BuzzerMode(u8 LOC_u8BuzzerPortID, u8 LOC_u8BuzzerPinID, u8 LOC_u8BuzzerMode)
{
	u8 LOC_u8Return_Value = E_NOT_OK;
	if( (LOC_u8BuzzerPortID <= PortD) && (LOC_u8BuzzerPinID <= Pin7) && (LOC_u8BuzzerMode <= Buzzer_TOG))
	{
		if (LOC_u8BuzzerMode == Buzzer_ON)
		{
			LOC_u8Return_Value = MCAL_DIO_u8SetPinValue(LOC_u8BuzzerPortID, LOC_u8BuzzerPinID, Buzzer_ON);
		}
		else if (LOC_u8BuzzerMode == Buzzer_OFF)
		{
			LOC_u8Return_Value = MCAL_DIO_u8SetPinValue(LOC_u8BuzzerPortID, LOC_u8BuzzerPinID, Buzzer_OFF);
		}
		else if (LOC_u8BuzzerMode == Buzzer_TOG)
		{
			LOC_u8Return_Value = MCAL_DIO_u8TogglePinValue(LOC_u8BuzzerPortID, LOC_u8BuzzerPinID);
		}
		else
		{
			//Do Nothing.
		}
	}
	else
	{
		//Do Nothing.
	}
	return LOC_u8Return_Value;
}
