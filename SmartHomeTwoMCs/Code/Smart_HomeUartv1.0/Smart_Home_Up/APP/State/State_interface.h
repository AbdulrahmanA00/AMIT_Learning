/*
 * State_interface.h
 *
 *  Created on: Nov 27, 2024
 *      Author: DELL
 */

#ifndef APP_STATE_STATE_INTERFACE_H_
#define APP_STATE_STATE_INTERFACE_H_

void INT0_APP_CALLBACK(void);
void APP_STATE_void_AppStateInit(void);
#include "..\..\MCAL\INTERRUPT\EXTI\EXT_INT.h"
#include "..\..\MCAL\GIE\GIE.h"
#include "..\..\MCAL\GIE\GIE.h"
#include "..\..\MCAL\SPI\SPI_interface.h"
#include "..\..\HAL\LED\LED.h"

extern u8 G_u8_Receive;

#endif /* APP_STATE_STATE_INTERFACE_H_ */
