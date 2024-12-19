/*
 * LED.h
 *
 *  Created on: Sep 25, 2023
 *      Author: 2023
 */

#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_
#include "../../MCAL/DIO/DIO.h"

#define LED1_Port 	PortA
#define LED1_Pin 	Pin3

#define LED2_Port 	PortA
#define LED2_Pin 	Pin4

#define LED3_Port 	PortA
#define LED3_Pin 	Pin5

#define LED4_Port 	PortA
#define LED4_Pin 	Pin6

#define LED5_Port 	PortA
#define LED5_Pin 	Pin7

#define LED_OFF 	0
#define LED_ON 		1
#define LED_TOG 	2

STD_TYPE HAL_LED_u8LedInit(u8 LOC_u8LEDPortID, u8 LOC_u8LEDPinID);
STD_TYPE HAL_LED_u8AllLedsInit();
STD_TYPE HAL_LED_u8LedMode(u8 LOC_u8LEDPortID, u8 LOC_u8LEDPinID, u8 LOC_u8LEDMode);

#endif /* HAL_LED_LED_H_ */
