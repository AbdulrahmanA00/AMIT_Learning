/*
 * LcdUser_interface.h
 *
 *  Created on: Nov 26, 2024
 *      Author: DELL
 */

#ifndef APP_LCDUSER_LCDUSER_INTERFACE_H_
#define APP_LCDUSER_LCDUSER_INTERFACE_H_

#include "LcdUser_config.h"

//extern u8 volatile G_flag;
//extern u8 volatile G_flag1;
//extern u8 volatile G_flag2;
//extern u8 volatile G_flag3;
//extern u8 volatile G_flag4;
//extern u8 volatile G_flag5;
//extern u8 volatile G_FanFlag;
//extern u8 volatile G_FanFlagOn;
//extern u8 volatile G_FanFlagOff;
//extern u8 volatile G_FanControlFlag;
//extern u8 volatile G_Mainflag;
//extern u8 volatile G_LM35;
//extern u8 volatile G_Keypad_Value;
//extern u8 m;



void APP_DEVICES_void_AppGetAnyDeviceOn(void);// to know which devices are working
void APP_void_AppAfterFirstChoice(void);// The home page displays the devices and temperature options
void APP_void_AppGetDeviceID(void);// Take from the user the device number he wants to set
void APP_DEVICE1_u8_AppSetDevice1(void);// Set the device 1 as the user wants
void APP_DEVICE2_u8_AppSetDevice2(void);// Set the device 2 as the user wants
void APP_DEVICE3_u8_AppSetDevice3(void);// Set the device 3 as the user wants
void APP_DEVICE4_u8_AppSetDevice4(void);// Set the device 4 as the user wants
void APP_DEVICE5_u8_AppSetDevice5(void);// Set the device 5 as the user wants
void APP_FAN_void_AppFanSet(void);// Set the Fan as the user wants
void APP_TEMP_void_AppDisplayTemperature();// Display Temperature as degrees Celsius.
void APP_FAN_void_AppFanControlOptions(void);// Displays control options to the user.
void APP_FAN_void_AppFanAutomaticAndManualControl(void);// Makes control automatic and manual
void APP_FAN_void_AppFanManualOnlyControl(void);// Makes control manual only
void APP_FAN_void_AppFanReadWithoutWrite(void);// It reads the temperature and based on that it turns the fan on or off.

#endif /* APP_LCDUSER_LCDUSER_INTERFACE_H_ */
