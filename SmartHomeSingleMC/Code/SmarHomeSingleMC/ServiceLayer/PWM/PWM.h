/*
 * PWM.h
 *
 *  Created on: Oct 26, 2023
 *      Author: Abdulrahman Ayman
 */

#ifndef SERVICELAYER_PWM_PWM_H_
#define SERVICELAYER_PWM_PWM_H_
//#include"../../Common/MCU.h"
#include"../../Common/Macros.h"
#include"../../Common/STD_Types.h"
#include"../../MCAL/TIMER/Timer1_interfacing.h"

/*
#include"../../MCAL/TIMER/Timer0.h"
#define TIMER0		0
*/
#define TIMER1		1
#define TIMER_TYPE	TIMER1

#define SCALER_1_			1
#define SCALER_8_			8
#define SCALER_64_			64
#define SCALER_256_			256
#define SCALER_1024_		1024
#define SCALER_NUMBER		SCALER_8_
#define SCALER_NUMBER_KHZ	SCALER_1_

void ServiceLayer_PWM_voidGenerateHZ(u16 LOC_u16Frequency,u8 LOC_u8Duty);
void ServiceLayer_PWM_voidGenerateKHZ(u16 LOC_u16Frequency,u8 LOC_u8Duty);

#endif /* SERVICELAYER_PWM_PWM_H_ */
