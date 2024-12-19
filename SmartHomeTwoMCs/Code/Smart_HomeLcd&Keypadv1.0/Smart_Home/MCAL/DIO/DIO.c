/*
 * DIO.c
 *
 *  Created on: Sep 23, 2023
 *      Author: Abdulrahman Ayman
 */
#include "DIO.h"
//SetPortDirection
STD_TYPE MCAL_DIO_u8SetPortDirection (u8 LOC_u8PortID, u8 LOC_u8PortDirection)
{
	u8 LOC_u8Return_Value = E_NOT_OK;
	if((LOC_u8PortID <= PortD))
	{
		if (LOC_u8PortID ==PortA)
		{
			DDRA = LOC_u8PortDirection;
			LOC_u8Return_Value = E_OK;
		}
		else if(LOC_u8PortID ==PortB)
		{
			DDRB = LOC_u8PortDirection;
			LOC_u8Return_Value = E_OK;
		}
		else if(LOC_u8PortID ==PortC)
		{
			DDRC = LOC_u8PortDirection;
			LOC_u8Return_Value = E_OK;
		}
		else if(LOC_u8PortID ==PortD)
		{
			DDRD = LOC_u8PortDirection;
			LOC_u8Return_Value = E_OK;
		}
		else
		{
			//Do Nothing
		}
	}
	else
	{
		//Do Nothing
	}
	return LOC_u8Return_Value;
}

//SetPortValue
STD_TYPE MCAL_DIO_u8SetPortValue (u8 LOC_u8PortID, u8 LOC_u8PortValue)
{
	u8 LOC_u8Return_Value = E_NOT_OK;
	if( (LOC_u8PortID <= PortD) && (LOC_u8PortValue <= Port_HIGH) )
	{
		//		if(LOC_u8PortValue == Port_HIGH)
		//		{
		if(LOC_u8PortID ==PortA)
		{
			PORTA = LOC_u8PortValue;
			LOC_u8Return_Value = E_OK;
		}
		else if(LOC_u8PortID ==PortB)
		{
			PORTB = LOC_u8PortValue;
			LOC_u8Return_Value = E_OK;
		}
		else if(LOC_u8PortID ==PortC)
		{
			PORTC = LOC_u8PortValue;
			LOC_u8Return_Value = E_OK;
		}
		else if(LOC_u8PortID ==PortD)
		{
			PORTD = LOC_u8PortValue;
			LOC_u8Return_Value = E_OK;
		}
		else
		{
			//Do Nothing
		}
		//		}
		//		else if (LOC_u8PortValue == Port_LOW)
		//		{
		//			if(LOC_u8PortID ==PortA)
		//			{
		//				PORTA = Port_LOW;
		//				LOC_u8Return_Value = E_OK;
		//			}
		//			else if(LOC_u8PortID ==PortB)
		//			{
		//				PORTB = Port_LOW;
		//				LOC_u8Return_Value = E_OK;
		//			}
		//			else if(LOC_u8PortID ==PortC)
		//			{
		//				PORTC = Port_LOW;
		//				LOC_u8Return_Value = E_OK;
		//			}
		//			else if(LOC_u8PortID ==PortD)
		//			{
		//				PORTD = Port_LOW;
		//				LOC_u8Return_Value = E_OK;
		//			}
		//			else
		//			{
		//				//Do Nothing
		//			}
		//		}
		//		else
		//		{
		//			//Do Nothing
		//		}
	}
	else
	{
		//Do Nothing
	}
	return LOC_u8Return_Value;
}

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
STD_TYPE MCAL_DIO_u8GetPinValue (u8 LOC_u8PortID, u8 LOC_u8PinID, u8* LOC_Pu8PinValue)
{
	u8 LOC_u8Return_Value = E_NOT_OK;
	if( (LOC_u8PortID <= PortD) && (LOC_u8PinID <= Pin7) )
	{

		if(LOC_u8PortID == PortA)
		{
			*LOC_Pu8PinValue = GET_BIT(PINA,LOC_u8PinID);
			LOC_u8Return_Value = E_OK;
		}
		else if(LOC_u8PortID ==PortB)
		{
			*LOC_Pu8PinValue = GET_BIT(PINB,LOC_u8PinID);
			LOC_u8Return_Value = E_OK;
		}
		else if(LOC_u8PortID ==PortC)
		{
			*LOC_Pu8PinValue = GET_BIT(PINC,LOC_u8PinID);
			LOC_u8Return_Value = E_OK;
		}
		else if(LOC_u8PortID ==PortD)
		{
			*LOC_Pu8PinValue = GET_BIT(PIND,LOC_u8PinID);
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

//TogglePortValue
STD_TYPE MCAL_DIO_u8TogglePortValue (u8 LOC_u8PortID)
{
	u8 LOC_u8Return_Value = E_NOT_OK;
	if(LOC_u8PortID <= PortD)
	{
		if (LOC_u8PortID ==PortA)
		{
			PORTA = ~PORTA;
			LOC_u8Return_Value = E_OK;
		}
		else if (LOC_u8PortID ==PortB)
		{
			PORTB = ~PORTB;
			LOC_u8Return_Value = E_OK;
		}
		else if (LOC_u8PortID ==PortC)
		{
			PORTC = ~PORTC;
			LOC_u8Return_Value = E_OK;
		}
		else if (LOC_u8PortID == PortD)
		{
			PORTD = ~PORTD;
			LOC_u8Return_Value = E_OK;
		}
		else
		{
			//Do Nothing.
		}
	}
	else
	{
		//Do Nothing
	}
	return LOC_u8Return_Value;
}

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
STD_TYPE MCAL_DIO_u8GetPortValue (u8 LOC_u8PortID, u8* LOC_Pu8PortValue)
{
	u8 LOC_u8Return_Value = E_NOT_OK;
	if (LOC_u8PortID <= PortD)
	{

		if(LOC_u8PortID == PortA)
		{
			*LOC_Pu8PortValue = PINA;
			LOC_u8Return_Value = E_OK;
		}
		else if(LOC_u8PortID ==PortB)
		{
			*LOC_Pu8PortValue = PINB;
			LOC_u8Return_Value = E_OK;
		}
		else if(LOC_u8PortID ==PortC)
		{
			*LOC_Pu8PortValue = PINC;
			LOC_u8Return_Value = E_OK;
		}
		else if(LOC_u8PortID ==PortD)
		{
			*LOC_Pu8PortValue = PIND;
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
