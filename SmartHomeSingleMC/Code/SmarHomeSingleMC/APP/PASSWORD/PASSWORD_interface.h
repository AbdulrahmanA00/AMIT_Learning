/*
 * PASSWORD_interface.h
 *
 *  Created on: Nov 17, 2023
 *      Author: DELL
 */

#ifndef APP_PASSWORD_PASSWORD_INTERFACE_H_
#define APP_PASSWORD_PASSWORD_INTERFACE_H_

/*******************************Includes Section *****************************************/


#include "../../HAL/KEYPAD/KEYPAD_interface.h"
#include "../../HAL/LCD/LCD_interface.h"
#include "../../HAL/Buzzer/Buzzer.h"
#include "../../APP/Registeration/Registeration.h"

#include "PASSWORD_config.h"
/*******************************Macros Section *****************************************/

/*******************************Prototyping Section *****************************************/

STD_TYPE APP_PASSWORD_u8_AppGetPasswordInit(void);
u16 APP_USERID_u8_AppUserID(void);
void APP_PASSWORD_u8_AppGetPassword(u16 LOC_u16UserID);

#endif /* APP_PASSWORD_PASSWORD_INTERFACE_H_ */
