/*
 * EEPROM.h
 *
 *  Created on: Nov 5, 2023
 *      Author: Abdulrahman Ayman
 */

#ifndef HAL_EEPROM_EEPROM_H_
#define HAL_EEPROM_EEPROM_H_

#include "../../MCAL/TWI/TWI.h"
#include <util\delay.h>

void HAL_EEPROM_voidWriteData(u16 LOC_u16Location,u8 LOC_u8Data);
void HAL_EEPROM_voidReadData(u16 LOC_u16Location,u8* LOC_Pu8Data);


#endif /* HAL_EEPROM_EEPROM_H_ */
