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


#ifndef HAL_KEYPAD_KEYPAD_INTERFACE_H_
#define HAL_KEYPAD_KEYPAD_INTERFACE_H_

/*******************************Includes Section *****************************************/

#include "../../Common/MCU.h"
#include "../../Common/Macros.h"
#include "../../Common/STD_Types.h"
#include "../../APP/LcdUser/LcdUser_interface.h"
#include "../../MCAL/DIO/DIO.h"

#include "KEYPAD_private.h"
#include "KEYPAD_config.h"

/*******************************Macros Section *****************************************/

/*******************************Prototyping Section *****************************************/

STD_TYPE HAL_KEYPAD_u8_KaypadInit(void);
STD_TYPE HAL_KEYPAD_u8_KaypadButton(u8 *Ploc_u8_ButtuonValue);
STD_TYPE HAL_KEYPAD_u8_HomeKaypadButton(u8 *Ploc_u8_ButtuonValue);
STD_TYPE HAL_KEYPAD_u8_KaypadButton1(u8 *Ploc_u8_ButtuonValue);

#endif /* HAL_KEYPAD_KEYPAD_INTERFACE_H_ */
