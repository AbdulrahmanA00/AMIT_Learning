/*
 * POT.c
 *
 *  Created on: Feb 14, 2024
 *      Author: Abdulrahman Ayman
 */
#include"POT.h"

void HAL_MCP4018_POT_voidDeviceInit(void)
{
	MCAL_TWI_voidMasterInit();
}


void HAL_MCP4018_POT_voidWriteStep(u8 LOC_u8Step)
{
	if(LOC_u8Step <= MAX_STEPS)
	{
		MCAL_TWI_voidStartCondition();
		MCAL_TWI_voidSendSlaveAddressWithWrite(DEVICE_SLAVE_ADDRESS);
		MCAL_TWI_voidMasterSendData(LOC_u8Step);
		MCAL_TWI_voidStopCondition();
		_delay_ms(10);
	}
	else
	{
		//Do Nothing.
	}
}

