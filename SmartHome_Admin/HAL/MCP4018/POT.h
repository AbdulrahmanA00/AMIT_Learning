/*
 * POT.h
 *
 *  Created on: Feb 14, 2024
 *      Author: Abdulrahman Ayman
 */

#ifndef HAL_MCP4018_POT_H_
#define HAL_MCP4018_POT_H_

#include"../../MCAL/TWI/TWI.h"
#include"util/delay.h"

void HAL_MCP4018_POT_voidDeviceInit(void);
void HAL_MCP4018_POT_voidWriteStep(u8 LOC_u8Step);

#define DEVICE_SLAVE_ADDRESS	0b0010101111
#define MAX_STEPS	127

#endif /* HAL_MCP4018_POT_H_ */
