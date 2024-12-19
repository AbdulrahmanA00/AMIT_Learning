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


#ifndef MCAL_SPI_SPI_MASTER_SLAVE_SPI_INTERFACE_H_
#define MCAL_SPI_SPI_MASTER_SLAVE_SPI_INTERFACE_H_

/*******************************Includes Section *****************************************/

#include "SPI_private.h"

/*******************************Macros Section *****************************************/

/*******************************Prototyping Section *****************************************/

STD_TYPE MCAL_SPI_MASTER_SLAVE_u8_SetMasterSalve_Prescaler_SpiMasterSlaveInit(u8 Loc_u8_SelectMasterSlave,
																			  u8 Loc_u8_SelectPrescaler);
STD_TYPE MCAL_SPI_MASTER_SLAVE_u8_SpiSetMasterSlave(u8 Loc_u8_SelectMasterSlave);
void MCAL_SPI_MASTER_SLAVE_void_SpiEnableInterrupt(void);
void MCAL_SPI_MASTER_SLAVE_void_SpiEnable(void);
STD_TYPE MCAL_SPI_MASTER_SLAVE_u8_SpiSetMsbLsb(u8 Loc_u8_SelectMsbLsb);
STD_TYPE MCAL_SPI_MASTER_SLAVE_u8_SpiSetEdge(u8 Loc_u8_SelectEdge);
STD_TYPE MCAL_SPI_MASTER_SLAVE_u8_SpiSetLeadingEdge(u8 Loc_u8_SelectLeadingEdge);
STD_TYPE MCAL_SPI_MASTER_SLAVE_u8_SpiSetPrescaler(u8 Loc_u8_SelectPrescaler);
u8 MCAL_SPI_MASTER_u8_SpiMaster_Transceive(u8 Loc_u8_Data);
void MCAL_SPI_MASTER_void_SpiMaster_TransceiveString(u8 *Ploc_u8_Data);
u8 MCAL_SPI_SLAVE_u8_SpiSlave_Transceive(u8 Loc_u8_Data);
void MCAL_SPI_SLAVE_void_SpiSlave_TransceiveString(u8 *PLoc_u8_Data);

#endif /* MCAL_SPI_SPI_MASTER_SLAVE_SPI_INTERFACE_H_ */
