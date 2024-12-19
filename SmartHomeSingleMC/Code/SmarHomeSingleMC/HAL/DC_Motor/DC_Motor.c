/*
 * DC_Motor.c
 *
 *  Created on: Feb 10, 2024
 *      Author: Abdulrahman Ayman
 */

#include "DC_Motor.h"
#include "../../MCAL/TIMER/Timer1_interfacing.h"

void HAL_DCMOTOR_void_DcMotorInit(void)
{
	MCAL_DIO_u8SetPinDirection(PortC,Pin3,Pin_Output);
	MCAL_DIO_u8SetPinDirection(PortC,Pin4,Pin_Output);
}
void HAL_DCMOTOR_void_DcMotorClockWise(u8 Loc_u8_Speed)
{
	MCAL_Timer_Timer1_voidSetOCR1BValue(Loc_u8_Speed);
	MCAL_DIO_u8SetPinValue(PortC,Pin3,Pin_HIGH);
	MCAL_DIO_u8SetPinValue(PortC,Pin4,Pin_LOW);
}
void HAL_DCMOTOR_void_DcMotorAntiClockWise(u8 Loc_u8_Speed)
{
	MCAL_Timer_Timer1_voidSetOCR1BValue(Loc_u8_Speed);
	MCAL_DIO_u8SetPinValue(PortC,Pin3,Pin_LOW);
	MCAL_DIO_u8SetPinValue(PortC,Pin4,Pin_HIGH);
}
void HAL_DCMOTOR_void_DcMotorStop(void)
{
	MCAL_DIO_u8SetPinValue(PortC,Pin3,Pin_LOW);
	MCAL_DIO_u8SetPinValue(PortC,Pin4,Pin_LOW);
}


