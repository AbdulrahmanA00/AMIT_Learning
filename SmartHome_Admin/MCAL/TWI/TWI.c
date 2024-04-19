/*
 * TWI.c
 *
 *  Created on: Nov 4, 2023
 *      Author: Abdulrahman Ayman
 */
#include"TWI.h"

void MCAL_TWI_voidMasterInit(void)
{
	//Enable TWI
	SET_BIT(TWCR,TWEN);
	//Enable Acknowledge
	SET_BIT(TWCR,TWEA);
	//SCL Clock Frequency
	CLR_BIT(TWCR,TWPS1);
	CLR_BIT(TWCR,TWPS0);
	TWBR = 152;	//50KHz
}




void MCAL_TWI_voidSlaveInit(u8 LOC_u8SlaveAddress)
{
	//Enable TWI
	SET_BIT(TWCR,TWEN);
	//Enable Acknowledge
	SET_BIT(TWCR,TWEA);
	//Set Slave Address
	TWAR = LOC_u8SlaveAddress <<1 ;
	//Configure General Call
#if GENERAL_CALL 	== 	ENABLE
	SET_BIT(TWAR,TWGCE);
#elif	GENERAL_CALL 	== 		DISABLE
	CLR_BIT(TWAR,TWGCE);
#endif
	//CLR Interrupt Flag (TWINT)
	SET_BIT(TWCR,TWINT);

}
void MCAL_TWI_voidStartCondition(void)
{
	//Set Start Condition Bit
	SET_BIT(TWCR,TWSTA);
	//CLR Interrupt Flag (TWINT)
	SET_BIT(TWCR,TWINT);
	//wait until TWINT is Set.
	while((GET_BIT(TWCR,TWINT))==0);

}

void MCAL_TWI_voidRepeatedStartCondition(void)
{
	//Set Start Condition Bit
	SET_BIT(TWCR,TWSTA);
	//CLR Interrupt Flag (TWINT)
	SET_BIT(TWCR,TWINT);
	//wait until TWINT is Set.
	while((GET_BIT(TWCR,TWINT))==0);

}

void MCAL_TWI_voidStopCondition(void)
{
	CLR_BIT(TWCR,TWSTA);
	//Set Stop Condition Bit
	SET_BIT(TWCR,TWSTO);
	//CLR Interrupt Flag (TWINT)
	SET_BIT(TWCR,TWINT);
	//wait until TWINT is Set.
//	while((GET_BIT(TWCR,TWINT))==0);

}
void MCAL_TWI_voidSendSlaveAddressWithWrite(u8 LOC_u8SlaveAddress)
{
	//Select Address
	TWDR = LOC_u8SlaveAddress << 1;
	//write
	CLR_BIT(TWDR,0);
	//Clear Start Condition Bit
	CLR_BIT(TWCR,TWSTA);
	//CLR Interrupt Flag (TWINT)
	SET_BIT(TWCR,TWINT);
	while((GET_BIT(TWCR,TWINT))==0);

}

void MCAL_TWI_voidSendSlaveAddressWithRead(u8 LOC_u8SlaveAddress)
{
	//Select Address
	TWDR = LOC_u8SlaveAddress << 1;
	//Read
	SET_BIT(TWDR,0);
	//Clear Start Condition Bit
	CLR_BIT(TWCR,TWSTA);
	//CLR Interrupt Flag (TWINT)
	SET_BIT(TWCR,TWINT);
	while((GET_BIT(TWCR,TWINT))==0);

}

void MCAL_TWI_voidMasterReceiveData(u8* LOC_Pu8Data)
{
	//Set Acknowledge.
	SET_BIT(TWCR,TWEA);
	//CLR Interrupt Flag (TWINT)
	SET_BIT(TWCR,TWINT);
	while((GET_BIT(TWCR,TWINT))==0);
	*LOC_Pu8Data = TWDR;
}
void MCAL_TWI_voidMasterSendData(u8 LOC_u8Data)
{
	TWDR = LOC_u8Data;
	//CLR Interrupt Flag (TWINT)
	SET_BIT(TWCR,TWINT);
	while((GET_BIT(TWCR,TWINT))==0);

}
void MCAL_TWI_voidSlaveListen(void)
{
	while((GET_BIT(TWCR,TWINT))==0);
}


void MCAL_TWI_voidMasterReceiveDataNACK(u8* LOC_Pu8Data)
{
	//Clear Acknowledge.
	CLR_BIT(TWCR,TWEA);
	//CLR Interrupt Flag (TWINT)
	SET_BIT(TWCR,TWINT);
	while((GET_BIT(TWCR,TWINT))==0);
	*LOC_Pu8Data = TWDR;
}
