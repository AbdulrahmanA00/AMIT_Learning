/*
 * LcdUser_interface.h
 *
 *  Created on: Nov 26, 2024
 *      Author: DELL
 */

#ifndef APP_LCDUSER_LCDUSER_INTERFACE_H_
#define APP_LCDUSER_LCDUSER_INTERFACE_H_

#include "LcdUser_config.h"
#include "..\..\MCAL\SPI\SPI_interface.h"

extern u8 volatile G_flag;
extern u8 volatile G_DeviceOneFlag;
extern u8 volatile G_DeviceTwoFlag;
extern u8 volatile G_DeviceThreeFlag;
extern u8 volatile G_DeviceFourFlag;
extern u8 volatile G_DeviceFiveFlag;
extern u8 volatile G_FanFlag;
extern u8 volatile G_FanFlagOn;
extern u8 volatile G_FanFlagOff;
extern u8 volatile G_FanControlFlag;
extern u8 volatile G_LogoutFlag;
extern u8 volatile G_LM35;
extern u8 volatile G_Keypad_Value;
extern u8 G_RunningDevicesIndicator;

void APP_DEVICES_void_AppGetAnyDeviceOn(void);// to know which devices are working
void APP_void_AppHomePage(void);// The home page displays the devices and temperature options
void APP_void_AppGetDeviceID(void);// Take from the user the device number he wants to set
void APP_DEVICE1_u8_AppSetDeviceOne(void);// Set the device 1 as the user wants
void APP_DEVICE2_u8_AppSetDeviceTwo(void);// Set the device 2 as the user wants
void APP_DEVICE3_u8_AppSetDeviceThree(void);// Set the device 3 as the user wants
void APP_DEVICE4_u8_AppSetDeviceFour(void);// Set the device 4 as the user wants
void APP_DEVICE5_u8_AppSetDeviceFive(void);// Set the device 5 as the user wants
void APP_TEMP_void_ApptemperaturePage();
void APP_TEMP_void_AppDisplayTemperature();// Display Temperature as degrees Celsius.
void APP_FAN_void_AppSetFan(void);// Set the Fan as the user wants
void APP_FAN_void_AppFanControlOptions(void);// Displays control options to the user.
void APP_FAN_void_AppFanAutomaticAndManualControl(void);// Makes control automatic and manual
void APP_FAN_void_AppFanManualOnlyControl(void);// Makes control manual only
void APP_FAN_void_AppFanReadWithoutWrite(void);// It reads the temperature and based on that it turns the fan on or off.

#endif /* APP_LCDUSER_LCDUSER_INTERFACE_H_ */
