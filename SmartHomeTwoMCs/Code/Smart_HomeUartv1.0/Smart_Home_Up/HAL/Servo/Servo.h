/*
 * Servo.h
 *
 *  Created on: Feb 9, 2024
 *      Author: Abdulrahman Ayman
 */

#ifndef HAL_SERVO_SERVO_H_
#define HAL_SERVO_SERVO_H_

#include"../../ServiceLayer/PWM/PWM.h"
#include"../../MCAL/DIO/DIO.h"

void HAL_Servo_voidServoInit(void);
void HAL_Servo_voidServoOpenDoor(void);
void HAL_Servo_voidServoCloseDoor(void);

#define SERVO_FREQUENC_50_HZ	50
#define STARTING_DUTYCYCLE_5_	5

#define SERVO_PORT	PortD
#define SERVO_PIN	Pin5
#define OUTPUT		1
#endif /* HAL_SERVO_SERVO_H_ */
