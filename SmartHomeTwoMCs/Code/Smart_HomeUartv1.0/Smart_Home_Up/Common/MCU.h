/*
 * MCU.h
 *
 *  Created on: Sep 24, 2023
 *      Author: 2023
 */
#ifndef MCU_H_
#define MCU_H_
#include "STD_Types.h"

/******************* GIE ***************/
#define SREG 	(*(volatile u8*)0x5F)
// SREG/GIE BIT
#define I_BIT 	7

/******************* DIO *****************/
#define PORTA 	(*(volatile u8* const)0x3B)
#define DDRA 	(*(volatile u8* const)0x3A)
#define PINA 	(*(volatile u8* const)0x39)

#define PORTB	(*(volatile u8* const)0x38)
#define DDRB 	(*(volatile u8* const)0x37)
#define PINB 	(*(volatile u8* const)0x36)

#define PORTC 	(*(volatile u8* const)0x35)
#define DDRC 	(*(volatile u8* const)0x34)
#define PINC 	(*(volatile u8* const)0x33)

#define PORTD 	(*(volatile u8* const)0x32)
#define DDRD 	(*(volatile u8* const)0x31)
#define PIND 	(*(volatile u8* const)0x30)

/***************INTERRUPT***************/

/*#define   SREG     (*(volatile u8*)0x5F)
#define   GICR     (*(volatile u8*)0x5B)
#define   GIFR     (*(volatile u8*)0x5A)
#define   MCUCR    (*(volatile u8*)0x55)
#define   MCUCSR   (*(volatile u8*)0x54)*/

/**************SPI************************/

#define  SPCR        (*(volatile u8*)0x2D)
#define  SPSR        (*(volatile u8*)0x2E)
#define  SPDR        (*(volatile u8*)0x2F)



/****************** EXT_INT ****************/

#define MCUCR 	  (*((volatile u8* const)0x55))
#define MCUCSR    (*((volatile u8* const)0x54))
#define GICR  	  (*((volatile u8* const)0x5B))
#define GIFR  	  (*((volatile u8* const)0x5A))

 //MCUCR BITS
#define ISC00_BIT 0
#define ISC01_BIT 1
#define ISC10_BIT 2
#define ISC11_BIT 3

 //MCUCSR BITS
#define ISC2_BIT  6

 /*GICR BITS*/
#define INT1_BIT  7
#define INT0_BIT  6
#define INT2_BIT  5

/* GIFR BITS*/
#define INTF1		7
#define INTF0		6
#define INTF2		5


/***************** ADC ***************/

#define ADMUX  		(*((volatile u8* const)0x27))	//ADC Multiplexer Selection Register.
#define ADCSRA   	(*((volatile u8* const)0x26))	//ADC Control and Status Register A.
#define SFIOR   	(*((volatile u8* const)0x50))	//Special FunctionIO Register.
#define ADC_DATA	(*((volatile u16* const)0x24))
//#define ADCH   		(*((volatile u8* const)0x25))	//ADC Data Register (HIGH).
//#define ADCL   		(*((volatile u8* const)0x24))	//ADC Data Register (LOW).

/* ADMUX BITS */
#define REFS1	7
#define REFS0	6
#define ADLAR	5
#define MUX4	4
#define MUX3	3
#define MUX2	2
#define MUX1	1
#define MUX0	0

/* ADCSRA BITS */
#define ADEN	7
#define ADSC	6
#define ADATE	5
#define ADIF	4
#define ADIE	3
#define ADPS2	2
#define ADPS1	1
#define ADPS0	0

/* SFIOR BITS */
#define ADTS2	7
#define ADTS1	6
#define ADTS0	5

/******************************************** TIMERS *****************************************/
#define TIMSK 	(*(volatile u8*)0x59)		//Timer/Counter Interrupt Mask Register.
#define TIFR 	(*(volatile u8*)0x58)		//Timer/Counter Interrupt Flag Register.

/***************** TIMER0 ***************/

#define TCNT0 	(*(volatile u8*)0x52)		//Timer/Counter Register.
#define TCCR0 	(*(volatile u8*)0x53)		//Timer/Counter Control Register.
#define OCR0	(*(volatile u8*)0x5C)		//Output Compare Register.

/* TCCR0 BITS */
#define FOC0 	7
#define WGM00 	6		// Mode Bit
#define COM01 	5		//Compare Output Mode
#define COM00 	4		//Compare Output Mode
#define WGM01 	3		// Mode Bit
#define CS02 	2		// Clock Select Bit
#define CS01 	1		// Clock Select Bit
#define CS00	0		// Clock Select Bit

/*TIMSK BITS in TIMER0 */
#define OCIE0  	1		// Output Compare Match Interrupt Enable Bit
#define TOIE0	0		// Overflow Interrupt Enable Bit

/*TIFR BITS in TIMER0*/
#define OCF0 	1		// Output compare flag 0.
#define TOV0	0		// Timer overflow flag 0.

/*******************  TIMER1  *****************/

/*
#define TCCR1A		(*(volatile u8*)0x4F)
#define TCCR1B		(*(volatile u8*)0x4E)
#define TCNT1  		(*(volatile u16*)0x4C)
#define OCR1A		(*(volatile u16*)0x4A)
#define OCR1B		(*(volatile u16*)0x48)
#define ICR1		(*(volatile u16*)0x46)

 TCCR1A BITS
#define COM1A1 	7		// Compare Output Mode for Channel A.
#define COM1A0 	6		// Compare Output Mode for Channel A.
#define COM1B1 	5		// Compare Output Mode for Channel B.
#define COM1B0 	4		// Compare Output Mode for Channel B.
#define FOC1A 	3		// Force Output Compare for Channel A.
#define FOC1B 	2		// Force Output Compare for Channel B.
#define WGM11 	1		// Waveform Generation Mode.
#define WGM10	0		// Waveform Generation Mode.

 TCCR1B BITS
#define ICNC1  	7		// Input Capture Noise Canceler.
#define ICES1  	6		// Input Capture Edge Select.

#define WGM13  	4		// Waveform Generation Mode.
#define WGM12 	3		// Waveform Generation Mode.
#define CS12 	2		// Clock Select.
#define CS11  	1		// Clock Select.
#define CS10	0		// Clock Select.


TIMSK BITS in TIMER1
#define TICIE1 	5		// Input Capture Interrupt Enable.
#define OCIE1A 	4		// Output Compare A Match Interrupt Enable.
#define OCIE1B 	3		// Output Compare A Match Interrupt Enable.
#define TOIE1 	2		// Overflow Interrupt Enable.

TIFR BITS in TIMER1
#define ICF1  	5		// Input Capture Flag.
#define OCF1A 	4		// Output Compare A Match Flag.
#define OCF1B 	3		// Output Compare B Match Flag.
#define TOV1	2		// Overflow Flag.
*/

/******************  WDTCR  ******************/
#define WDTCR		(*(volatile u8*)0x41)
#define WDTOE 	4
#define WDE 	3
#define WDP2  	2
#define WDP1  	1
#define WDP0 	0


/*
******************  USART  ****************

#define UDR		(*(volatile u8*)0x2C)
#define UCSRA	(*(volatile u8*)0x2B)
#define UCSRB	(*(volatile u8*)0x2A)
#define UCSRC	(*(volatile u8*)0x40)
#define UBRRH	(*(volatile u8*)0x40)
#define UBRRL	(*(volatile u8*)0x29)

****	UCSRA	****
#define RXC  	7		// USART Receive Complete.
#define TXC  	6		// USART Transmit Complete.
#define UDRE  	5		// USART Data Register Empty.
#define FE  	4		// Frame Error.
#define DOR  	3		// Data OverRun.
#define PE  	2		// Parity Error.
#define U2X  	1		// Double the USART Transmission Speed.
#define MPCM	0		// Multi-processor Communication Mode.

****	UCSRB	****
#define RXCIE  	7		// RX Complete Interrupt Enable.
#define TXCIE  	6		// TX Complete Interrupt Enable.
#define UDREIE  5		// USART Data Register Empty Interrupt Enable.
#define RXEN   	4		// Receiver Enable.
#define TXEN  	3		// Transmitter Enable.
#define UCSZ2  	2		// Character Size.
#define RXB8 	1		// Receive Data Bit 8.
#define TXB8	0		// Transmit Data Bit 8.

****	UCSRC	****
#define URSEL  	7		// Register Select.
#define UMSEL  	6		// USART Mode Select.
#define UPM1  	5		// Parity Mode.
#define UPM0   	4		// Parity Mode.
#define USBS  	3		// Stop Bit Select.
#define UCSZ1  	2		// Character Size.
#define UCSZ0 	1		// Character Size.
#define UCPOL	0		// Clock Polarity.
*/

#endif /* MCU_H_ */

