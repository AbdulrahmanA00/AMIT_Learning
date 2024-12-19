/*
 * USART.c
 *
 *  Created on: Oct 23, 2023
 *      Author: Abdulrahman Ayman
 */
//#include "../../Common/MCU.h"
#include"UART.h"

void (*GLOB_CallBackToAPP_Transmit) (void) = 	NULL;
void (*GLOB_CallBackToAPP_Receive) (void) = 	NULL;


void MCAL_UART_voidInit(void)
{
	//Data Size -> 8-bit , Configure parity -> Disable , Stop bit -> 1-bit
	u16 LOC_u16BaudRate = 0;
	u8 LOC_u8UCSRC = 0;
	//Enabel TX
#if TRANSMITTING_MODE == TX_ENABLE
	SET_BIT(UCSRB, UCSRB_TXEN);
#elif TRANSMITTING_MODE == TX_DISABLE
	CLR_BIT(UCSRB, UCSRB_TXEN);
#else
#error TRANSMITTING_MODE Configs Error
#endif

	//Enabel RX
#if RECEIVING_MODE == RX_ENABLE
	SET_BIT(UCSRB, UCSRB_RXEN);

#elif RECEIVING_MODE == RX_DISABLE
	CLR_BIT(UCSRB, UCSRB_RXEN);
#else
#error RECEIVING_MODE Configs Error
#endif

//SYNCHRONIZATION
#if SYNCHRONIZATION == ASYNCHRONOUS
	CLR_BIT(LOC_u8UCSRC,UCSRC_UMSEL);

#elif SYNCHRONIZATION == SYNCHRONOUS
	SET_BIT(LOC_u8UCSRC,UCSRC_UMSEL);
#else
#error SYNCHRONIZATION Configs Error
#endif

//DATA_SIZE
#if DATA_SIZE == _5_BIT_DATA
	CLR_BIT(LOC_u8UCSRC, UCSRC_UCSZ0);
	CLR_BIT(LOC_u8UCSRC, UCSRC_UCSZ1);
#elif DATA_SIZE == _6_BIT_DATA
	SET_BIT(LOC_u8UCSRC, UCSRC_UCSZ0);
	CLR_BIT(LOC_u8UCSRC, UCSRC_UCSZ1);
#elif DATA_SIZE == _7_BIT_DATA
	CLR_BIT(LOC_u8UCSRC, UCSRC_UCSZ0);
	SET_BIT(LOC_u8UCSRC, UCSRC_UCSZ1);
#elif DATA_SIZE == _8_BIT_DATA
	SET_BIT(LOC_u8UCSRC, UCSRC_UCSZ0);
	SET_BIT(LOC_u8UCSRC, UCSRC_UCSZ1);
#elif DATA_SIZE == _9_BIT_DATA
	SET_BIT(LOC_u8UCSRC, UCSRC_UCSZ0);
	SET_BIT(LOC_u8UCSRC, UCSRC_UCSZ1);
	SET_BIT(UCSRB, UCSRB_UCSZ2);

#else
#error DATA_SIZE Configs Error
#endif

//Stop Bit Size
#if STOP_BIT_SIZE == _1_STOP_BIT
	CLR_BIT(LOC_u8UCSRC,UCSRC_USBS);

#elif STOP_BIT_SIZE == _2_STOP_BIT
	SET_BIT(LOC_u8UCSRC,UCSRC_USBS);
#else
#error STOP_BIT_SIZE Configs Error
#endif

//Parity Mode
#if PARITY_MODE == PARITY_NONE
	CLR_BIT(LOC_u8UCSRC,UCSRC_UPM0);
	CLR_BIT(LOC_u8UCSRC,UCSRC_UPM1);

/*
#elif PARITY_MODE == PARITY_RESERVED
	SET_BIT(LOC_u8UCSRC,UCSRC_UPM0);
	CLR_BIT(LOC_u8UCSRC,UCSRC_UPM1);
*/

#elif PARITY_MODE == PARITY_EVEN
	CLR_BIT(LOC_u8UCSRC,UCSRC_UPM0);
	SET_BIT(LOC_u8UCSRC,UCSRC_UPM1);

#elif PARITY_MODE == PARITY_ODD
	SET_BIT(LOC_u8UCSRC,UCSRC_UPM0);
	SET_BIT(LOC_u8UCSRC,UCSRC_UPM1);

#else
#error STOP_BIT_SIZE Configs Error
#endif
	SET_BIT(LOC_u8UCSRC, UCSRC_URSEL);

	//Set Baudrate
	LOC_u16BaudRate = (CPU_FREQ/(16 * BAUDRATE)) -1;
	UBRRH = (u8)(LOC_u16BaudRate>>8);
//	UBRRH = (u8)(103>>8);
	UBRRL = (u8) LOC_u16BaudRate;
//	UBRRL = (u8) 103;

	UCSRC = LOC_u8UCSRC;




/*
	UCSRA |= 0b00100000;
	UCSRB |= 0b00011000;
	UCSRC |= 0b10000110;

	UBRRL = 103;
 */

}

void MCAL_UART_voidTransmitData(u8 LOC_u8Data)
{
	//Wait Until Transmit Complete.
	while( GET_BIT(UCSRA,UCSRA_UDRE) == 0);
	UDR = LOC_u8Data;

	while( GET_BIT(UCSRA,UCSRA_TXC) == 0);
	//Reset Flag.
	SET_BIT(UCSRA,UCSRA_TXC);
}

void MCAL_UART_voidReceiveData(u8 *LOC_Pu8ReceivedData)
{
	//Wait Until Receive Complete.
	while (GET_BIT(UCSRA,UCSRA_RXC) == 0);

			*LOC_Pu8ReceivedData = UDR;
}


void MCAL_UART_voidSendString(u8 *LOC_Pu8String)
{
	u8 LOC_u8Counter;
	for(LOC_u8Counter = 0 ;LOC_Pu8String[LOC_u8Counter] != 0 ;LOC_u8Counter++)
	{
		MCAL_UART_voidTransmitData(LOC_Pu8String[LOC_u8Counter]);
	}

}
void MCAL_UART_voidReceiveString(u8 *LOC_Pu8String)
{
	u8 LOC_u8CharacterReceived;
    u32 LOC_u32Counter = 0;

	    while (1) {
	        MCAL_UART_voidReceiveData(&LOC_u8CharacterReceived);
	        if (LOC_u8CharacterReceived == '\r' ) {  // Enter key pressed
	            LOC_Pu8String[LOC_u32Counter] = '\0';          // Null-terminate the string
	            break;
	        }
	        if (LOC_u32Counter < MAX_BUFFER_SIZE - 1) {
	        	LOC_Pu8String[LOC_u32Counter++] = LOC_u8CharacterReceived;           // Store the received character
	        }

}
}




void MCAL_UART_voidTransmitCompleteInterruptEnable(void)
{
	SET_BIT(UCSRB,UCSRB_TXCIE);
}


void MCAL_UART_voidTransmitCompleteInterruptDisable(void)
{
	CLR_BIT(UCSRB,UCSRB_TXCIE);
}


void MCAL_UART_voidReceiveCompleteInterruptEnable(void)
{
	SET_BIT(UCSRB,UCSRB_RXCIE);
}


void MCAL_UART_voidReceiveCompleteInterruptDisable(void)
{
	CLR_BIT(UCSRB,UCSRB_RXCIE);
}





void MCAL_UART_voidTransmitCompleteSetCallBack(void (*LOC_pvNotifiFunction)(void))
{
	if (*LOC_pvNotifiFunction != NULL)
	{
		GLOB_CallBackToAPP_Transmit = LOC_pvNotifiFunction;
	}
}
void MCAL_UART_voidReceiveCompleteSetCallBack(void (*LOC_pvNotifiFunction)(void))
{
	if (*LOC_pvNotifiFunction != NULL)
	{
		GLOB_CallBackToAPP_Receive = LOC_pvNotifiFunction;
	}

}

ISR(USART_TXC_vect)
{
	if (*GLOB_CallBackToAPP_Transmit != NULL)
	{
		GLOB_CallBackToAPP_Transmit();
	}
}
ISR(USART_RXC_vect)
{
	if (*GLOB_CallBackToAPP_Receive != NULL)
	{
		GLOB_CallBackToAPP_Receive();
	}

}
