/*
 * EXT_INT.c
 *
 *  Created on: Oct 7, 2023
 *      Author: 2023
 */
#include "EXT_INT.h"


void (*GLOB_CallBackToAPP[3]) (void) = {NULL,NULL,NULL};

void MCAL_EXT_INT_voidEXTInt_Init(u8 LOC_u8IntNum,u8 LOC_u8SenseControl)
{
	if (LOC_u8IntNum == INT_0)
	{
		SET_BIT(GICR,INT0_BIT);
		switch(LOC_u8SenseControl)
		{
		case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC00_BIT);
			CLR_BIT(MCUCR,ISC01_BIT);
			break;
		case LOGICAL_CHANGE:
			SET_BIT(MCUCR,ISC00_BIT);
			CLR_BIT(MCUCR,ISC01_BIT);
			break;
		case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC00_BIT);
			SET_BIT(MCUCR,ISC01_BIT);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR,ISC00_BIT);
			SET_BIT(MCUCR,ISC01_BIT);
			break;
		default:
			break;
		}
	}
	else if (LOC_u8IntNum == INT_1)
	{
		SET_BIT(GICR,INT1_BIT);
		switch(LOC_u8SenseControl)
		{
		case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC10_BIT);
			CLR_BIT(MCUCR,ISC11_BIT);
			break;
		case LOGICAL_CHANGE:
			SET_BIT(MCUCR,ISC10_BIT);
			CLR_BIT(MCUCR,ISC11_BIT);
			break;
		case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC10_BIT);
			SET_BIT(MCUCR,ISC11_BIT);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR,ISC10_BIT);
			SET_BIT(MCUCR,ISC11_BIT);
			break;
		default:
			break;
		}

	}
	else if (LOC_u8IntNum == INT_2)
	{
		SET_BIT(GICR,INT2_BIT);
		switch(LOC_u8SenseControl)
		{
		case FALLING_EDGE:
			CLR_BIT(MCUCSR,ISC2_BIT);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCSR,ISC2_BIT);
			break;
		default:
			break;
		}
	}
	else
	{
		//Do Nothing.
	}
}

void MCAL_EXT_INT_voidEXTInt_CallBack(u8 LOC_u8IntNum, void(*InterruptAction)(void))
{
	if (InterruptAction != NULL)
	{
		GLOB_CallBackToAPP[LOC_u8IntNum] = InterruptAction;
	}
}



ISR(EXTINT0_vect)
{
	if (GLOB_CallBackToAPP[INT_0] != NULL)
	{
		GLOB_CallBackToAPP[INT_0]();
	}
}
ISR(EXTINT1_vect)
{
	if (GLOB_CallBackToAPP[INT_1] != NULL)
	{
		GLOB_CallBackToAPP[INT_1]();
	}
}
ISR(EXTINT2_vect)
{
	if (GLOB_CallBackToAPP[INT_2] != NULL)
	{
		GLOB_CallBackToAPP[INT_2]();
	}
}
