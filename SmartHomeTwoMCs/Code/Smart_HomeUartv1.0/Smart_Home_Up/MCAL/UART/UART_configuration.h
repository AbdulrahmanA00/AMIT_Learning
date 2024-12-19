/*
 * UART_configuration.h
 *
 *  Created on: Oct 27, 2023
 *      Author: Abdulrahman Ayman
 */

#ifndef MCAL_UART_UART_CONFIGURATION_H_
#define MCAL_UART_UART_CONFIGURATION_H_


/**
 * Options:
 *      CPU_FREQ_8MHZ
 *      CPU_FREQ_16MHZ
*/
#define     CPU_FREQ                    CPU_FREQ_16MHZ

/**
 * Options:
 *      BAUDRATE_2400
 *      BAUDRATE_4800
 *      BAUDRATE_9600
 *      BAUDRATE_19200
 *      BAUDRATE_115200
*/
#define     BAUDRATE                    BAUDRATE_9600
/**
 * Options:
 *      _5_BIT_DATA
 *      _6_BIT_DATA
 *      _7_BIT_DATA
 *      _8_BIT_DATA
 *      _9_BIT_DATA
*/
#define     DATA_SIZE                   _8_BIT_DATA

/**
 * Options:
 *      PARITY_NONE
 *      PARITY_EVEN
 *      PARITY_ODD
*/
#define     PARITY_MODE                 PARITY_NONE

/**
 * Options:
 *      _1_STOP_BIT
 *      _2_STOP_BIT
*/
#define     STOP_BIT_SIZE               _1_STOP_BIT

/**
 * Options:
 *      ASYNCHRONOUS
 *      SYNCHRONOUS
*/
#define     SYNCHRONIZATION             ASYNCHRONOUS

/**
 * Options:
 *      RX_DISABLE
 *      RX_ENABLE
*/
#define     RECEIVING_MODE              RX_ENABLE

/**
 * Options:
 *      TX_DISABLE
 *      TX_ENABLE
*/
#define     TRANSMITTING_MODE           TX_ENABLE


#endif /* MCAL_UART_UART_CONFIGURATION_H_ */
