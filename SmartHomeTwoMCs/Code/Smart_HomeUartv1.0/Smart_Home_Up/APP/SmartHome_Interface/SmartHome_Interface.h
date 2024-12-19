/*
 * Bluetooth.h
 *
 *  Created on: Feb 4, 2024
 *      Author: Abdulrahman Ayman
 */

#ifndef APP_SMARTHOME_INTERFACE_SMARTHOME_INTERFACE_H_
#define APP_SMARTHOME_INTERFACE_SMARTHOME_INTERFACE_H_

#include "../../MCAL/UART/UART_interfacing.h"
#include "../../MCAL/TIMER/Timer0.h"
#include "../Registeration/Registeration.h"
#include "../../HAL/Servo/Servo.h"
#include "../../HAL/AC/AC.h"
#include "../../HAL/LED/LED.h"
#include "../../HAL/Buzzer/Buzzer.h"
#include "../../HAL/MCP4018/POT.h"
#include "string.h"

void APP_Init(void);
void APP_Home_Page(void);
void APP_Login_Page(void);
void APP_Register_Page(void);
void APP_Options_Page(void);
void APP_RoomLights_Page(void);
void APP_AC_Contol_Page(void);
void APP_AC_Check(void);

void APP_UserManagement_Page(void);
void APP_RegisterNewUser_Page(void);
void APP_RemoveUser_Page(void);
void APP_DeleteAllUsers_Page(void);


void APP_DeviceControl_Page(void);
void APP_Devices_Status(void);
void APP_DoorControl_Page(void);


#define LIGHT1	(u8*)"1. Light 1\r\n"
#define LIGHT2	(u8*)"2. Light 2\r\n"
#define LIGHT3	(u8*)"3. Light 3\r\n"
#define LIGHT4	(u8*)"4. Light 4\r\n"
#define LIGHT5	(u8*)"5. Light 5\r\n"
#define DIMMER	(u8*)"6. Dimmer\r\n"
#define BACK	(u8*)"0 --> Back\r\n"

#endif /* APP_SMARTHOME_INTERFACE_SMARTHOME_INTERFACE_H_ */
