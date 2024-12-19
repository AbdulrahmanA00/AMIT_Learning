/*********************************************
 * Author:          Mohamed.A.Ewis
 * Creation Data:   7 NOV, 2023
 * Version:         v1.0
 * Compiler:        GNU GCC
 ********************************************/
/*********************************************
 * Version      Date                  Author                  Description
 * v1.0         7 NOV, 2023       Mohamed.A.Ewis           Initial Creation
*********************************************/

/*******************************Includes Section *****************************************/

#include "..\DIO\DIO.h"

#include "SPI_private.h"
#include "SPI_config.h"
#include "SPI_interface.h"

#include "..\GIE\GIE.h"

/*****************************************************************************************/

/************************** Global Variable Definitions Section **************************/

/************************************ Implementation Section ******************************/

/************************************************************************
 * description : Set Prescaler Value
 * INPUT Arg1  : Value of Prescaler
 * RETURN      : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/

STD_TYPE MCAL_SPI_MASTER_SLAVE_u8_SetMasterSalve_Prescaler_SpiMasterSlaveInit(u8 Loc_u8_SelectMasterSlave,
																			  u8 Loc_u8_SelectPrescaler)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	if((Loc_u8_SelectMasterSlave <= SPI_MASTER) && (Loc_u8_SelectPrescaler <= SPI_PRESCALER_SPI2X_64))
	{
		if  (Loc_u8_SelectMasterSlave == SPI_MASTER)
		{
			Loc_u8_Retval = MCAL_DIO_u8SetPinDirection(MOSI_PORT,MOSI_PIN,PIN_OUTPUT);
			Loc_u8_Retval = MCAL_DIO_u8SetPinDirection(SS_PORT,SS_PIN,PIN_OUTPUT);
			Loc_u8_Retval = MCAL_DIO_u8SetPinDirection(SCK_PORT,SCK_PIN,PIN_OUTPUT);
			Loc_u8_Retval = MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
			Loc_u8_Retval = MCAL_SPI_MASTER_SLAVE_u8_SpiSetLeadingEdge(SPI_SETUP_LEADING);
			Loc_u8_Retval = MCAL_SPI_MASTER_SLAVE_u8_SpiSetEdge(SPI_FALLING_EDGE);
			Loc_u8_Retval = MCAL_SPI_MASTER_SLAVE_u8_SpiSetMsbLsb(SPI_LSB);
			Loc_u8_Retval = MCAL_SPI_MASTER_SLAVE_u8_SpiSetPrescaler(Loc_u8_SelectPrescaler);
			Loc_u8_Retval = MCAL_SPI_MASTER_SLAVE_u8_SpiSetMasterSlave(Loc_u8_SelectMasterSlave);
			MCAL_SPI_MASTER_SLAVE_void_SpiEnable();
		}
		else if (Loc_u8_SelectMasterSlave == SPI_SLAVE)
		{
			Loc_u8_Retval = MCAL_DIO_u8SetPinDirection(MISO_PORT,MISO_PIN,PIN_OUTPUT);
			Loc_u8_Retval = MCAL_SPI_MASTER_SLAVE_u8_SpiSetLeadingEdge(SPI_SETUP_LEADING);
			Loc_u8_Retval = MCAL_SPI_MASTER_SLAVE_u8_SpiSetEdge(SPI_FALLING_EDGE);
			Loc_u8_Retval = MCAL_SPI_MASTER_SLAVE_u8_SpiSetMsbLsb(SPI_LSB);
			Loc_u8_Retval = MCAL_SPI_MASTER_SLAVE_u8_SpiSetPrescaler(Loc_u8_SelectPrescaler);
			Loc_u8_Retval = MCAL_SPI_MASTER_SLAVE_u8_SpiSetMasterSlave(Loc_u8_SelectMasterSlave);
			MCAL_SPI_MASTER_SLAVE_void_SpiEnable();
		}
		else
		{
			//Do Nothing
		}
	}
	else
	{
		//Do Nothing
	}
	return Loc_u8_Retval;
}


STD_TYPE MCAL_SPI_MASTER_SLAVE_u8_SpiSetMasterSlave(u8 Loc_u8_SelectMasterSlave)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	if(Loc_u8_SelectMasterSlave == SPI_SLAVE)
	{
		CLR_BIT(SPCR,MSTR);
		Loc_u8_Retval = EOK;
	}
	else if(Loc_u8_SelectMasterSlave == SPI_MASTER)
	{
		SET_BIT(SPCR,MSTR);
		Loc_u8_Retval = EOK;
	}
	else
	{
		//Do Nothing
	}
	return Loc_u8_Retval;
}

void MCAL_SPI_MASTER_SLAVE_void_SpiEnableInterrupt(void)
{
	SET_BIT(SPCR,SPIE);
}

void MCAL_SPI_MASTER_SLAVE_void_SpiEnable(void)
{
	SET_BIT(SPCR,SPE);
}

STD_TYPE MCAL_SPI_MASTER_SLAVE_u8_SpiSetMsbLsb(u8 Loc_u8_SelectMsbLsb)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	if(Loc_u8_SelectMsbLsb == SPI_MSB)
	{
		CLR_BIT(SPCR,DORD);
		Loc_u8_Retval = EOK;
	}
	else if(Loc_u8_SelectMsbLsb == SPI_LSB)
	{
		SET_BIT(SPCR,DORD);
		Loc_u8_Retval = EOK;
	}
	else
	{
		//Do Nothing
	}
	return Loc_u8_Retval;
}

STD_TYPE MCAL_SPI_MASTER_SLAVE_u8_SpiSetEdge(u8 Loc_u8_SelectEdge)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	if(Loc_u8_SelectEdge == SPI_RISING_EDGE)
	{
		CLR_BIT(SPCR,CPOL);
		Loc_u8_Retval = EOK;
	}
	else if(Loc_u8_SelectEdge == SPI_FALLING_EDGE)
	{
		SET_BIT(SPCR,CPOL);
		Loc_u8_Retval = EOK;
	}
	else
	{
		//Do Nothing
	}
	return Loc_u8_Retval;
}

STD_TYPE MCAL_SPI_MASTER_SLAVE_u8_SpiSetLeadingEdge(u8 Loc_u8_SelectLeadingEdge)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	if(Loc_u8_SelectLeadingEdge == SPI_SAMPLE_LEADING)
	{
		CLR_BIT(SPCR,CPHA);
		Loc_u8_Retval = EOK;
	}
	else if(Loc_u8_SelectLeadingEdge == SPI_SETUP_LEADING)
	{
		SET_BIT(SPCR,CPHA);
		Loc_u8_Retval = EOK;
	}
	else
	{
		//Do Nothing
	}
	return Loc_u8_Retval;
}

STD_TYPE MCAL_SPI_MASTER_SLAVE_u8_SpiSetPrescaler(u8 Loc_u8_SelectPrescaler)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	if(Loc_u8_SelectPrescaler == SPI_PRESCALER_4)
	{
		CLR_BIT(SPCR,SPR0);
		CLR_BIT(SPCR,SPR1);
		CLR_BIT(SPSR,SPI2X);
		Loc_u8_Retval = EOK;
	}
	else if(Loc_u8_SelectPrescaler == SPI_PRESCALER_16)
	{
		SET_BIT(SPCR,SPR0);
		CLR_BIT(SPCR,SPR1);
		CLR_BIT(SPSR,SPI2X);
		Loc_u8_Retval = EOK;
	}
	else if(Loc_u8_SelectPrescaler == SPI_PRESCALER_64)
	{
		CLR_BIT(SPCR,SPR0);
		SET_BIT(SPCR,SPR1);
		CLR_BIT(SPSR,SPI2X);
		Loc_u8_Retval = EOK;
	}
	else if(Loc_u8_SelectPrescaler == SPI_PRESCALER_128)
	{
		SET_BIT(SPCR,SPR0);
		SET_BIT(SPCR,SPR1);
		CLR_BIT(SPSR,SPI2X);
		Loc_u8_Retval = EOK;
	}
	else if(Loc_u8_SelectPrescaler == SPI_PRESCALER_SPI2X_2)
	{
		CLR_BIT(SPCR,SPR0);
		CLR_BIT(SPCR,SPR1);
		SET_BIT(SPSR,SPI2X);
		Loc_u8_Retval = EOK;
	}
	else if(Loc_u8_SelectPrescaler == SPI_PRESCALER_SPI2X_8)
	{
		SET_BIT(SPCR,SPR0);
		CLR_BIT(SPCR,SPR1);
		SET_BIT(SPSR,SPI2X);
		Loc_u8_Retval = EOK;
	}
	else if(Loc_u8_SelectPrescaler == SPI_PRESCALER_SPI2X_32)
	{
		CLR_BIT(SPCR,SPR0);
		SET_BIT(SPCR,SPR1);
		SET_BIT(SPSR,SPI2X);
		Loc_u8_Retval = EOK;
	}
	else if(Loc_u8_SelectPrescaler == SPI_PRESCALER_SPI2X_64)
	{
		SET_BIT(SPCR,SPR0);
		SET_BIT(SPCR,SPR1);
		SET_BIT(SPSR,SPI2X);
		Loc_u8_Retval = EOK;
	}
	else
	{
		//Do Nothing
	}
	return Loc_u8_Retval;
}

u8 MCAL_SPI_MASTER_u8_SpiMaster_Transceive(u8 Loc_u8_Data)
{

	SPDR = Loc_u8_Data;
	while(!GET_BIT(SPSR,SPIF));
	return SPDR;
}


/*void MCAL_SPI_MASTER_void_SpiMaster_TransceiveString(u8 *Ploc_u8_Data)
{
	u8 index = 0;
	u8 Ploc_u8_Retval[30] = {0};
	while(Ploc_u8_Data[index] != '\0')
	{
	MCAL_DIO_u8_SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
	Ploc_u8_Retval[index] =  MCAL_SPI_MASTER_u8_SpiMaster_Transceive(Ploc_u8_Data[index]);
    MCAL_DIO_u8_SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
    HAL_LCD_u8_WriteCharacter(Ploc_u8_Retval[index]);
	index++;
	}
}*/

u8 MCAL_SPI_SLAVE_u8_SpiSlave_Transceive(u8 Loc_u8_Data)
{
	SPDR = Loc_u8_Data;
	while(!GET_BIT(SPSR,SPIF));
	return SPDR;
}

/*void MCAL_SPI_SLAVE_void_SpiSlave_TransceiveString(u8 *PLoc_u8_Data)
{
	u8 index = 0;
	u8 Ploc_u8_Retval[30] = {0};
	while(Ploc_u8_Retval[index-1] != 'K')
	{
		Ploc_u8_Retval[index] = MCAL_SPI_SLAVE_u8_SpiSlave_Transceive(PLoc_u8_Data[index]);
	    HAL_LCD_u8_WriteCharacter(Ploc_u8_Retval[index]);
		index++;
	}
}*/
