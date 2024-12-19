/*
 * DC_Motor.h
 *
 *  Created on: Feb 10, 2024
 *      Author: Abdulrahman Ayman
 */

#ifndef HAL_DC_MOTOR_DC_MOTOR_H_
#define HAL_DC_MOTOR_DC_MOTOR_H_

//#include "..\..\Common\MCU.h"
#include "..\..\Common\Macros.h"
#include "..\..\Common\STD_Types.h"

#include "..\..\MCAL\DIO\DIO.h"

/*******************************Prototyping Section *****************************************/


void HAL_DCMOTOR_void_DcMotorInit(void);
void HAL_DCMOTOR_void_DcMotorClockWise(u8 Loc_u8_Speed);
void HAL_DCMOTOR_void_DcMotorAntiClockWise(u8 Loc_u8_Speed);
void HAL_DCMOTOR_void_DcMotorStop(void);


#endif /* HAL_DC_MOTOR_DC_MOTOR_H_ */
