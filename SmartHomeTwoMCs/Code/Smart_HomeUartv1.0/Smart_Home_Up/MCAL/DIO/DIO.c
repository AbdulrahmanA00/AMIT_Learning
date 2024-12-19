/*
 * DIO.c
 *
 *  Created on: Sep 23, 2023
 *      Author: Abdulrahman Ayman
 */
#include "DIO.h"
//SetPortDirection

//SetPortValue

//SetPinValue
STD_TYPE MCAL_DIO_u8SetPinValue (u8 LOC_u8PortID, u8 LOC_u8PinID, u8 LOC_u8PinValue)
{
	u8 LOC_u8Return_Value = E_NOT_OK;
	if( (LOC_u8PortID <= PortD) && (LOC_u8PinID <= Pin7) && (LOC_u8PinValue <= Pin_HIGH) )
	{
		if(LOC_u8PinValue == Pin_HIGH)
		{
			if(LOC_u8PortID == PortA)
			{
				SET_BIT(PORTA,LOC_u8PinID);
				LOC_u8Return_Value = E_OK;
			}
			else if(LOC_u8PortID ==PortB)
			{
				SET_BIT(PORTB,LOC_u8PinID);
				LOC_u8Return_Value = E_OK;
			}
			else if(LOC_u8PortID ==PortC)
			{
				SET_BIT(PORTC,LOC_u8PinID);
				LOC_u8Return_Value = E_OK;
			}
			else if(LOC_u8PortID ==PortD)
			{
				SET_BIT(PORTD,LOC_u8PinID);
				LOC_u8Return_Value = E_OK;
			}
			else
			{
				//Do Nothing
			}
		}
		else if(LOC_u8PinValue == Pin_LOW)
		{
			if(LOC_u8PortID == PortA)
			{
				CLR_BIT(PORTA,LOC_u8PinID);
				LOC_u8Return_Value = E_OK;
			}
			else if(LOC_u8PortID ==PortB)
			{
				CLR_BIT(PORTB,LOC_u8PinID);
				LOC_u8Return_Value = E_OK;
			}
			else if(LOC_u8PortID ==PortC)
			{
				CLR_BIT(PORTC,LOC_u8PinID);
				LOC_u8Return_Value = E_OK;
			}
			else if(LOC_u8PortID ==PortD)
			{
				CLR_BIT(PORTD,LOC_u8PinID);
				LOC_u8Return_Value = E_OK;
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
	}
	else
	{
		//Do Nothing.
	}
	return LOC_u8Return_Value;
}

//SetPinDirection
STD_TYPE MCAL_DIO_u8SetPinDirection (u8 LOC_u8PortID, u8 LOC_u8PinID, u8 LOC_u8PinDirection)
{
	u8 LOC_u8Return_Value = E_NOT_OK;
	if( (LOC_u8PortID <= PortD) && (LOC_u8PinID <= Pin7) && (LOC_u8PinDirection <= Pin_Output) )
	{
		if(LOC_u8PinDirection == Pin_Output)
		{
			if(LOC_u8PortID == PortA)
			{
				SET_BIT(DDRA,LOC_u8PinID);
				LOC_u8Return_Value = E_OK;
			}
			else if(LOC_u8PortID ==PortB)
			{
				SET_BIT(DDRB,LOC_u8PinID);
				LOC_u8Return_Value = E_OK;
			}
			else if(LOC_u8PortID ==PortC)
			{
				SET_BIT(DDRC,LOC_u8PinID);
				LOC_u8Return_Value = E_OK;
			}
			else if(LOC_u8PortID ==PortD)
			{
				SET_BIT(DDRD,LOC_u8PinID);
				LOC_u8Return_Value = E_OK;
			}
			else
			{
				//Do Nothing
			}
		}
		else if(LOC_u8PinDirection == Pin_Input)
		{
			if(LOC_u8PortID == PortA)
			{
				CLR_BIT(DDRA,LOC_u8PinID);
				LOC_u8Return_Value = E_OK;
			}
			else if(LOC_u8PortID ==PortB)
			{
				CLR_BIT(DDRB,LOC_u8PinID);
				LOC_u8Return_Value = E_OK;
			}
			else if(LOC_u8PortID ==PortC)
			{
				CLR_BIT(DDRC,LOC_u8PinID);
				LOC_u8Return_Value = E_OK;
			}
			else if(LOC_u8PortID ==PortD)
			{
				CLR_BIT(DDRD,LOC_u8PinID);
				LOC_u8Return_Value = E_OK;
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
	}
	else
	{
		//Do Nothing.
	}
	return LOC_u8Return_Value;
}

//GetPinValue

//TogglePortValue
//TogglePinValue
STD_TYPE MCAL_DIO_u8TogglePinValue (u8 LOC_u8PortID, u8 LOC_u8PinID)
{
	u8 LOC_u8Return_Value = E_NOT_OK;
	if( (LOC_u8PortID <= PortD) && (LOC_u8PinID <= Pin7) )
	{

		if(LOC_u8PortID == PortA)
		{
			TOGGLE_BIT(PORTA,LOC_u8PinID);
			LOC_u8Return_Value = E_OK;
		}
		else if(LOC_u8PortID ==PortB)
		{
			TOGGLE_BIT(PORTB,LOC_u8PinID);
			LOC_u8Return_Value = E_OK;
		}
		else if(LOC_u8PortID ==PortC)
		{
			TOGGLE_BIT(PORTC,LOC_u8PinID);
			LOC_u8Return_Value = E_OK;
		}
		else if(LOC_u8PortID ==PortD)
		{
			TOGGLE_BIT(PORTD,LOC_u8PinID);
			LOC_u8Return_Value = E_OK;
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

//GetPortValue
