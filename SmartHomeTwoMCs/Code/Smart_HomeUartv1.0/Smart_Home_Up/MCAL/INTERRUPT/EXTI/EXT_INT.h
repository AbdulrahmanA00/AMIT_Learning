/*
 * EXT_INT.h
 *
 *  Created on: Oct 7, 2023
 *      Author: 2023
 */

#ifndef MCAL_EXT_INT_EXT_INT_H_
#define MCAL_EXT_INT_EXT_INT_H_

#include "../../../Common/Macros.h"
#include "../../../Common/MCU.h"
#include "../../GIE/GIE.h"

#define INT_0 0
#define INT_1 1
#define INT_2 2

#define LOW_LEVEL        0
#define LOGICAL_CHANGE   1
#define FALLING_EDGE	 2
#define RISING_EDGE		 3


void MCAL_EXT_INT_voidEXTInt_Init(u8 LOC_u8IntNum,u8 LOC_u8SenseControl);
void MCAL_EXT_INT_voidEXTInt_CallBack(u8 LOC_u8IntNum, void(*InterruptAction)(void));
#endif /* MCAL_EXT_INT_EXT_INT_H_ */
