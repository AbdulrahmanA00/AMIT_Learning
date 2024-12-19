/*
 * PASSWORD_interface.h
 *
 *  Created on: Nov 17, 2023
 *      Author: DELL
 */

#ifndef APP_PASSWORD_PASSWORD_INTERFACE_H_
#define APP_PASSWORD_PASSWORD_INTERFACE_H_

/*******************************Includes Section *****************************************/



#include "PASSWORD_config.h"

/*******************************Macros Section *****************************************/

/*******************************Prototyping Section *****************************************/

STD_TYPE APP_PASSWORD_u8_AppGetPasswordInit(void);
void APP_USERID_u8_AppUserID(void);
void APP_PASSWORD_u8_AppGetPassword(void);
//void APP_PASSWORD_u8_AppGetPassword(u16 Loc_32_CheckID);
//u16  APP_USERID_u8_AppUserID(void);

#endif /* APP_PASSWORD_PASSWORD_INTERFACE_H_ */
