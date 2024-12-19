/*
 * LED.c
 *
 *  Created on: Sep 25, 2023
 *      Author: 2023
 */
#include "LED.h"

//LED_Init
STD_TYPE HAL_LED_u8LedInit(u8 LOC_u8LEDPortID, u8 LOC_u8LEDPinID)
{
	u8 LOC_u8Return_Value = E_NOT_OK;
	if( (LOC_u8LEDPortID <= PortD) && (LOC_u8LEDPinID <= Pin7) )
	{
		LOC_u8Return_Value = MCAL_DIO_u8SetPinDirection(LOC_u8LEDPortID,LOC_u8LEDPinID,Pin_Output);
	}
	else
	{
		//Do Nothing.
	}
	return LOC_u8Return_Value;
}

STD_TYPE HAL_LED_u8AllLedsInit()
{
	HAL_LED_u8LedInit(LED1_Port,LED1_Pin);
	HAL_LED_u8LedInit(LED2_Port,LED2_Pin);
	HAL_LED_u8LedInit(LED3_Port,LED3_Pin);
	HAL_LED_u8LedInit(LED4_Port,LED4_Pin);
	HAL_LED_u8LedInit(LED5_Port,LED5_Pin);
}

//LED_Mode
STD_TYPE HAL_LED_u8LedMode(u8 LOC_u8LEDPortID, u8 LOC_u8LEDPinID, u8 LOC_u8LEDMode)
{
	u8 LOC_u8Return_Value = E_NOT_OK;
	if( (LOC_u8LEDPortID <= PortD) && (LOC_u8LEDPinID <= Pin7) && (LOC_u8LEDMode <= LED_TOG))
	{
		if (LOC_u8LEDMode == LED_ON)
		{
			LOC_u8Return_Value = MCAL_DIO_u8SetPinValue(LOC_u8LEDPortID, LOC_u8LEDPinID, LED_ON);
		}
		else if (LOC_u8LEDMode == LED_OFF)
		{
			LOC_u8Return_Value = MCAL_DIO_u8SetPinValue(LOC_u8LEDPortID, LOC_u8LEDPinID, LED_OFF);
		}
		else if (LOC_u8LEDMode == LED_TOG)
		{
			LOC_u8Return_Value = MCAL_DIO_u8TogglePinValue(LOC_u8LEDPortID, LOC_u8LEDPinID);
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
