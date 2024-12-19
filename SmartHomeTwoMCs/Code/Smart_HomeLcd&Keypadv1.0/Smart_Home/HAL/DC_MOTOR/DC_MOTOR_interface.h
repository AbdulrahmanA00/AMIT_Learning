/*********************************************
 * Author:          Mohamed.A.Ewis
 * Creation Data:   7 NOV, 2023
 * Version:         v1.0
 * Compiler:        GNU GCC
 ********************************************/
/*********************************************
 * Version      Date                  Author                  Description
 * v1.0         7 NOV, 2023       Mohamed.A.Ewis          Initial Creation
*********************************************/


#ifndef HAL_DC_MOTOR_DC_MOTOR_INTERFACE_H_
#define HAL_DC_MOTOR_DC_MOTOR_INTERFACE_H_

/*******************************Includes Section *****************************************/
#include "..\..\Common\MCU.h"
#include "..\..\Common\Macros.h"
#include "..\..\Common\STD_Types.h"

#include "..\..\MCAL\DIO\DIO.h"

#include "DC_MOTOR_private.h"
#include "DC_MOTOR_config.h"

/*******************************Prototyping Section *****************************************/


void HAL_DCMOTOR_void_DcMotorInit(void);
void HAL_DCMOTOR_void_DcMotorClockWise(u8 Loc_u8_Speed);
void HAL_DCMOTOR_void_DcMotorAntiClockWise(u8 Loc_u8_Speed);
void HAL_DCMOTOR_void_DcMotorStop(void);


#endif /* HAL_DC_MOTOR_DC_MOTOR_INTERFACE_H_ */
