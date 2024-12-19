/*********************************************
 * Author:          Mohamed.A.Ewis
 * Creation Data:   7 NOV, 2023
 * Version:         v1.0
 * Compiler:        GNU GCC
 ********************************************/
/*********************************************
 * Version      Date                  Author                  Description
 * v1.0         7 NOV, 2023       Mohamed.A.Ewis          Initial Creation
*********************************************/

#ifndef MCAL_SPI_SPI_MASTER_SLAVE_SPI_PRIVATE_H_
#define MCAL_SPI_SPI_MASTER_SLAVE_SPI_PRIVATE_H_

/*******************************Includes Section *****************************************/

#include "..\..\Common\Mcu.h"
#include "..\..\Common\Macros.h"
#include "..\..\Common\STD_Types.h"

#include "..\DIO\DIO.h"

/*******************************Macros Section *****************************************/

/* SPCR  */

#define      SPR0       0
#define      SPR1       1
#define      CPHA       2
#define      CPOL       3
#define      MSTR       4
#define      DORD       5
#define      SPE 		6
#define      SPIE       7

/* SPSR */

#define      SPI2X       0
#define      WCOL        6
#define      SPIF        7


#define      MOSI_PORT      PortB
#define      MISO_PORT      PortB
#define      SS_PORT        PortB
#define      SS2_PORT       PortD
#define      SCK_PORT       PortB


#define      SS_PIN         PIN4
#define      SS2_PIN        PIN5
#define      MOSI_PIN       PIN5
#define      MISO_PIN       PIN6
#define      SCK_PIN        PIN7

#define      SPI_SLAVE					  0
#define      SPI_MASTER					  1

#define      SPI_MSB					  2
#define      SPI_LSB					  3

#define   SPI_RISING_EDGE				  4
#define   SPI_FALLING_EDGE				  5

#define   SPI_SAMPLE_LEADING              6
#define   SPI_SETUP_LEADING               7

#define   SPI_PRESCALER_4                 0
#define   SPI_PRESCALER_16                1
#define   SPI_PRESCALER_64                2
#define   SPI_PRESCALER_128               3
#define   SPI_PRESCALER_SPI2X_2           4
#define   SPI_PRESCALER_SPI2X_8           5
#define   SPI_PRESCALER_SPI2X_32          6
#define   SPI_PRESCALER_SPI2X_64          7

/*******************************Prototyping Section *****************************************/




#endif /* MCAL_SPI_SPI_MASTER_SLAVE_SPI_PRIVATE_H_ */
