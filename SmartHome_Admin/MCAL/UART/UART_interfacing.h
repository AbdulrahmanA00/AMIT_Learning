/*
 * UART_interfacing.h
 *
 *  Created on: Oct 27, 2023
 *      Author: Abdulrahman Ayman
 */

#ifndef MCAL_UART_UART_INTERFACING_H_
#define MCAL_UART_UART_INTERFACING_H_

#include"../../Common/STD_Types.h"

void MCAL_UART_voidInit(void);
void MCAL_UART_voidTransmitData(u8 LOC_u8Data);
void MCAL_UART_voidReceiveData(u8 *LOC_Pu8ReceivedData);

void MCAL_UART_voidSendString(u8 *LOC_Pu8String);
void MCAL_UART_voidReceiveString(u8 *LOC_Pu8String);

void MCAL_UART_voidTransmitCompleteInterruptEnable(void);
void MCAL_UART_voidTransmitCompleteInterruptDisable(void);
void MCAL_UART_voidReceiveCompleteInterruptEnable(void);
void MCAL_UART_voidReceiveCompleteInterruptDisable(void);

void MCAL_UART_voidTransmitCompleteSetCallBack(void (*LOC_pvNotifiFunction)(void));
void MCAL_UART_voidReceiveCompleteSetCallBack(void (*LOC_pvNotifiFunction)(void));


#endif /* MCAL_UART_UART_INTERFACING_H_ */
