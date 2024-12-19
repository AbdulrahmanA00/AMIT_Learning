/*
 * DIO.h
 *
 *  Created on: Sep 23, 2023
 *      Author: 2023
 */
#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_

#include <util\delay.h>
#include <stdio.h>
#include "../../Common/Macros.h"
#include "../../Common/MCU.h"
#define E_OK 		0
#define E_NOT_OK 	1
#define PortA 	0
#define PortB 	1
#define PortC 	2
#define PortD 	3
#define Port_Output		0xff
#define Port_Input 		0x00
#define Port_LOW 		0x00
#define Port_HIGH 		0xff
#define	Pin_Input 		0
#define	Pin_Output 		1
#define Pin_LOW 		0
#define Pin_HIGH 		1

#define PortA  0
#define PortB  1
#define PortC  2
#define PortD  3

#define PIN0   0
#define PIN1   1
#define PIN2   2
#define PIN3   3
#define PIN4   4
#define PIN5   5
#define PIN6   6
#define PIN7   7

#define  PORT_OUTPUT  0xFF
#define  PORT_INPUT   0x00
#define  PIN_OUTPUT   1
#define  PIN_INPUT	  0

#define  PORT_HIGH    0xFF
#define  PORT_LOW     0x00
#define  PIN_HIGH     1
#define  PIN_LOW	  0

enum {Pin0,Pin1,Pin2,Pin3,Pin4,Pin5,Pin6,Pin7} Pin_Number;
STD_TYPE MCAL_DIO_u8SetPortDirection (u8 LOC_u8PortID, u8 LOC_u8PortDirection);
STD_TYPE MCAL_DIO_u8SetPortValue (u8 LOC_u8PortID, u8 LOC_u8PortValue);
STD_TYPE MCAL_DIO_u8GetPortValue (u8 LOC_u8PortID, u8* LOC_Pu8PortValue);
STD_TYPE MCAL_DIO_u8TogglePortValue (u8 LOC_u8PortID);
STD_TYPE MCAL_DIO_u8SetPinDirection (u8 LOC_u8PortID, u8 LOC_u8PinID, u8 LOC_u8PinDirection);
STD_TYPE MCAL_DIO_u8SetPinValue (u8 LOC_u8PortID, u8 LOC_u8PinID, u8 LOC_u8PinValue);
STD_TYPE MCAL_DIO_u8GetPinValue (u8 LOC_u8PortID, u8 LOC_u8PinID, u8* LOC_Pu8PinValue);
STD_TYPE MCAL_DIO_u8TogglePinValue (u8 LOC_u8PortID, u8 LOC_u8PinID);

#endif /* MCAL_DIO_DIO_H_ */
