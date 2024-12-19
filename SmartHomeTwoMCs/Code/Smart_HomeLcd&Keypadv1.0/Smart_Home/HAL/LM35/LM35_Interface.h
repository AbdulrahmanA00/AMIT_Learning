/*
 * LM35_Interface.h
 *
 *  Created on: Dec 10, 2023
 *      Author: a.elfaramawi
 */

#ifndef HAL_LM35_LM35_INTERFACE_H_
#define HAL_LM35_LM35_INTERFACE_H_

#include"../../MCAL/DIO/DIO.h"
#include"../../MCAL/ADC/ADC.h"
#include"../../MCAL/Timer/Timer0.h"

#define LM35_PORT 	PortA
#define LM35_PIN 	Pin0

void LM35_Init(void);
u16 LM35_Read(void);

#endif /* HAL_LM35_LM35_INTERFACE_H_ */
