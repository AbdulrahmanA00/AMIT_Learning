/*
 * LcdUser_config.h
 *
 *  Created on: Nov 26, 2024
 *      Author: DELL
 */

#ifndef APP_LCDUSER_LCDUSER_CONFIG_H_
#define APP_LCDUSER_LCDUSER_CONFIG_H_

#include "..\..\Common\MCU.h"
#include "..\..\Common\Macros.h"
#include "..\..\Common\STD_Types.h"

#include "..\..\MCAL\DIO\DIO.h"

#include "..\..\HAL\LCD\LCD_interface.h"
#include "..\..\HAL\KEYPAD\KEYPAD_interface.h"
#include "..\..\HAL\LED\LED.h"
#include "..\..\HAL\Buzzer\Buzzer.h"
#include "..\PASSWORD\PASSWORD_interface.h"
#include "..\..\HAL/DC_MOTOR/DC_MOTOR_interface.h"
#include "..\..\HAL/LM35/LM35_Interface.h"
#include "..\SMART_HOMRE/LM_WITH_DC_MOTOR.h"

#define F_CPU 16000000UL
#define  OFF  0
#define  ON   1

#endif /* APP_LCDUSER_LCDUSER_CONFIG_H_ */
