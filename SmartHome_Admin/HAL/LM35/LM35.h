/*
 * LM35.h
 *
 *  Created on: Feb 10, 2024
 *      Author: Abdulrahman Ayman
 */

#ifndef HAL_LM35_LM35_H_
#define HAL_LM35_LM35_H_

#include"../../MCAL/DIO/DIO.h"
#include"../../MCAL/ADC/ADC.h"
#include"../../MCAL/Timer/Timer0.h"

#define LM35_PORT 	PortA
#define LM35_PIN 	Pin0
#define PIN_INPUT	0

void LM35_Init(void);
u8 LM35_Read(void);


#endif /* HAL_LM35_LM35_H_ */
