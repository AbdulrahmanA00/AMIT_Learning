/*
 * EEPROM.c
 *
 *  Created on: Nov 5, 2023
 *      Author: Abdulrahman Ayman
 */
#include"EEPROM.h"

void HAL_EEPROM_voidWriteData(u16 LOC_u16Location,u8 LOC_u8Data)
{
	u8 LOC_u8FixedAddress = 0b01010000,LOC_u8Location;
	if (LOC_u16Location <=255 )
	{
		LOC_u8FixedAddress = 0b01010000;
		LOC_u8Location =  (u8) LOC_u16Location;
	}
	else if ((LOC_u16Location >= 256) && (LOC_u16Location <= 511))
	{
		LOC_u8FixedAddress = 0b01010001;
		LOC_u8Location =  (u8) (LOC_u16Location - 256);
	}
	else if ((LOC_u16Location >= 512) && (LOC_u16Location <= 767))
	{
		LOC_u8FixedAddress = 0b01010010;
		LOC_u8Location =  (u8) (LOC_u16Location - 512);
	}
	else if ((LOC_u16Location >= 768) && (LOC_u16Location <= 1023))
	{
		LOC_u8FixedAddress = 0b01010100;
		LOC_u8Location =  (u8) (LOC_u16Location - 768);
	}
	else {/*Do Nothing*/}

	MCAL_TWI_voidStartCondition();
	MCAL_TWI_voidSendSlaveAddressWithWrite(LOC_u8FixedAddress);
	MCAL_TWI_voidMasterSendData(LOC_u8Location);
	MCAL_TWI_voidMasterSendData(LOC_u8Data);
	MCAL_TWI_voidStopCondition();
	_delay_ms(10);
}


void HAL_EEPROM_voidReadData(u16 LOC_u16Location,u8* LOC_Pu8Data)
{
	u8 LOC_u8FixedAddress = 0b01010000,LOC_u8Location;
	if (LOC_u16Location <=255 )
	{
		LOC_u8FixedAddress = 0b01010000;
		LOC_u8Location =  (u8) LOC_u16Location;
	}
	else if ((LOC_u16Location >= 256) && (LOC_u16Location <= 511))
	{
		LOC_u8FixedAddress = 0b01010001;
		LOC_u8Location =  (u8) (LOC_u16Location - 256);
	}
	else if ((LOC_u16Location >= 512) && (LOC_u16Location <= 767))
	{
		LOC_u8FixedAddress = 0b01010010;
		LOC_u8Location =  (u8) (LOC_u16Location - 512);
	}
	else if ((LOC_u16Location >= 768) && (LOC_u16Location <= 1023))
	{
		LOC_u8FixedAddress = 0b01010100;
		LOC_u8Location =  (u8) (LOC_u16Location - 768);
	}
	else {/*Do Nothing*/}

	MCAL_TWI_voidStartCondition();
	MCAL_TWI_voidSendSlaveAddressWithWrite(LOC_u8FixedAddress);
	MCAL_TWI_voidMasterSendData(LOC_u8Location);
	MCAL_TWI_voidRepeatedStartCondition();
	MCAL_TWI_voidSendSlaveAddressWithRead(LOC_u8FixedAddress);
	MCAL_TWI_voidMasterReceiveDataNACK(LOC_Pu8Data);
	MCAL_TWI_voidStopCondition();

}

