/*
 * UART_private.h
 *
 *  Created on: Oct 27, 2023
 *      Author: Abdulrahman Ayman
 */

#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_

/*UART Data I/O Register	*/
#define UDR		(*(volatile u8*)0x2C)
/* USART Baud Rate Register High */
#define     UBRRH_URSEL        7
#define UBRRH	(*(volatile u8*)0x40)
#define UBRRL	(*(volatile u8*)0x29)

/*****	UCSRA	*****/
#define UCSRA	(*(volatile u8*)0x2B)

#define UCSRA_RXC  	7		// USART Receive Complete.
#define UCSRA_TXC  	6		// USART Transmit Complete.
#define UCSRA_UDRE 	5		// USART Data Register Empty.
#define UCSRA_FE  	4		// Frame Error.
#define UCSRA_DOR  	3		// Data OverRun.
#define UCSRA_PE  	2		// Parity Error.
#define UCSRA_U2X  	1		// Double the USART Transmission Speed.
#define UCSRA_MPCM	0		// Multi-processor Communication Mode.

/*****	UCSRB	*****/
#define UCSRB	(*(volatile u8*)0x2A)

#define UCSRB_RXCIE  	7		// RX Complete Interrupt Enable.
#define UCSRB_TXCIE  	6		// TX Complete Interrupt Enable.
#define UCSRB_UDREIE 	5		// USART Data Register Empty Interrupt Enable.
#define UCSRB_RXEN   	4		// Receiver Enable.
#define UCSRB_TXEN  	3		// Transmitter Enable.
#define UCSRB_UCSZ2  	2		// Character Size.
#define UCSRB_RXB8 		1		// Receive Data Bit 8.
#define UCSRB_TXB8		0		// Transmit Data Bit 8.

/*****	UCSRC	*****/
#define UCSRC	(*(volatile u8*)0x40)

#define UCSRC_URSEL  	7		// Register Select.
#define UCSRC_UMSEL  	6		// USART Mode Select.
#define UCSRC_UPM1  	5		// Parity Mode.
#define UCSRC_UPM0   	4		// Parity Mode.
#define UCSRC_USBS  	3		// Stop Bit Select.
#define UCSRC_UCSZ1  	2		// Character Size.
#define UCSRC_UCSZ0 	1		// Character Size.
#define UCSRC_UCPOL		0		// Clock Polarity.



#define     CPU_FREQ_8MHZ       8000000UL
#define     CPU_FREQ_16MHZ      16000000UL

#define     BAUDRATE_2400       2400UL
#define     BAUDRATE_4800       4800UL
#define     BAUDRATE_9600       9600UL
#define     BAUDRATE_19200      19200UL
#define     BAUDRATE_115200     115200UL

#define     _5_BIT_DATA         0x00
#define     _6_BIT_DATA         0x02
#define     _7_BIT_DATA         0x04
#define     _8_BIT_DATA         0x06
#define     _9_BIT_DATA         0x86

#define     PARITY_NONE         0x00
#define     PARITY_EVEN         0x20
#define     PARITY_ODD          0x30

#define     _1_STOP_BIT         0
#define     _2_STOP_BIT         1

#define     ASYNCHRONOUS        0
#define     SYNCHRONOUS         1

#define     RX_DISABLE          0
#define     RX_ENABLE           1

#define     TX_DISABLE          0
#define     TX_ENABLE           1

#define 	MAX_BUFFER_SIZE		100

#define     USART_RXC_vect      __vector_13
#define     USART_UDRE_vect     __vector_14
#define     USART_TXC_vect      __vector_15

#define ISR(vectNum)	void vectNum(void)__attribute__((signal));\
					  	void vectNum(void)

#define     DATA_CLR_MASK       0xF9
#define     PARITY_CLR_MASK     0xCF


#endif /* MCAL_UART_UART_PRIVATE_H_ */
