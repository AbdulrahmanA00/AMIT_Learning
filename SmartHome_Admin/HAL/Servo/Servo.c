/*
 * Servo.c
 *
 *  Created on: Feb 9, 2024
 *      Author: Abdulrahman Ayman
 */
#include"Servo.h"

void HAL_Servo_voidServoInit(void)
{
	ServiceLayer_PWM_voidGenerateHZ(SERVO_FREQUENC_50_HZ,STARTING_DUTYCYCLE_5_);
	MCAL_DIO_u8SetPinDirection(SERVO_PORT,SERVO_PIN,OUTPUT);
}

void HAL_Servo_voidServoOpenDoor(void)
{
	MCAL_Timer_Timer1_voidSetOCR1AValue(1500);
}

void HAL_Servo_voidServoCloseDoor(void)
{
	MCAL_Timer_Timer1_voidSetOCR1AValue(750);
}
