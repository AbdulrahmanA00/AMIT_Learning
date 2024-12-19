/*
 * TWI.h
 *
 *  Created on: Nov 4, 2023
 *      Author: Abdulrahman Ayman
 */

#ifndef MCAL_TWI_TWI_H_
#define MCAL_TWI_TWI_H_

#include "avr/io.h"
#include "../../Common/Macros.h"
#include "../../Common/STD_Types.h"

#define DISABLE		0
#define ENABLE		1
#define GENERAL_CALL	DISABLE


void MCAL_TWI_voidMasterInit(void);
void MCAL_TWI_voidSlaveInit(u8 LOC_u8SlaveAddress);
void MCAL_TWI_voidStartCondition(void);

void MCAL_TWI_voidRepeatedStartCondition(void);

void MCAL_TWI_voidStopCondition(void);
void MCAL_TWI_voidSendSlaveAddressWithWrite(u8 LOC_u8SlaveAddress);

void MCAL_TWI_voidSendSlaveAddressWithRead(u8 LOC_u8SlaveAddress);

void MCAL_TWI_voidMasterReceiveData(u8* LOC_Pu8Data);
void MCAL_TWI_voidMasterSendData(u8 LOC_u8Data);
void MCAL_TWI_voidSlaveListen(void);

void MCAL_TWI_voidMasterReceiveDataNACK(u8* LOC_Pu8Data);

#endif /* MCAL_TWI_TWI_H_ */
