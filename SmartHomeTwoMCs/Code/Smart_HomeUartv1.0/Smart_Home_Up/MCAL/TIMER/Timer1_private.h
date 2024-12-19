/*
 * Timer1_private.h
 *
 *  Created on: Oct 28, 2023
 *      Author: Abdulrahman Ayman
 */

#ifndef MCAL_TIMER_TIMER1_PRIVATE_H_
#define MCAL_TIMER_TIMER1_PRIVATE_H_


/*******************  TIMER1  *****************/

#define TCNT1  		(*(volatile u16*)0x4C)		//Timer/Counter1 – TCNT1H and TCNT1L
#define OCR1A		(*(volatile u16*)0x4A)		//Output Compare Register 1 A – OCR1AH and OCR1AL
#define OCR1B		(*(volatile u16*)0x48)		//Output Compare Register 1 B – OCR1BH and OCR1BL
#define ICR1		(*(volatile u16*)0x46)		//Input Capture Register 1 – ICR1H and ICR1L

#define TCCR1A		(*(volatile u8*)0x4F)
/* TCCR1A BITS */
#define TCCR1A_COM1A1 	7		// Compare Output Mode for Channel A.
#define TCCR1A_COM1A0 	6		// Compare Output Mode for Channel A.
#define TCCR1A_COM1B1 	5		// Compare Output Mode for Channel B.
#define TCCR1A_COM1B0 	4		// Compare Output Mode for Channel B.
#define TCCR1A_FOC1A 	3		// Force Output Compare for Channel A.
#define TCCR1A_FOC1B 	2		// Force Output Compare for Channel B.
#define TCCR1A_WGM11 	1		// Waveform Generation Mode.
#define TCCR1A_WGM10	0		// Waveform Generation Mode.

#define TCCR1B		(*(volatile u8*)0x4E)
/* TCCR1B BITS */
#define TCCR1B_ICNC1  	7		// Input Capture Noise Canceler.
#define TCCR1B_ICES1  	6		// Input Capture Edge Select.

#define TCCR1B_WGM13  	4		// Waveform Generation Mode.
#define TCCR1B_WGM12 	3		// Waveform Generation Mode.
#define TCCR1B_CS12 	2		// Clock Select.
#define TCCR1B_CS11  	1		// Clock Select.
#define TCCR1B_CS10	0		// Clock Select.

#define TIMSK 	(*(volatile u8*)0x59)		//Timer/Counter Interrupt Mask Register.
/*TIMSK BITS in TIMER1 */
#define TIMSK_TICIE1 	5		// Input Capture Interrupt Enable.
#define TIMSK_OCIE1A 	4		// Output Compare A Match Interrupt Enable.
#define TIMSK_OCIE1B 	3		// Output Compare A Match Interrupt Enable.
#define TIMSK_TOIE1 	2		// Overflow Interrupt Enable.

#define TIFR 	(*(volatile u8*)0x58)		//Timer/Counter Interrupt Flag Register.
/*TIFR BITS in TIMER1*/
#define TIFR_ICF1  	5		// Input Capture Flag.
#define TIFR_OCF1A 	4		// Output Compare A Match Flag.
#define TIFR_OCF1B 	3		// Output Compare B Match Flag.
#define TIFR_TOV1	2		// Overflow Flag.
/***************************************************************************************/

#define RISING_EDGE 	1
#define FALLING_EDGE 	0

#endif /* MCAL_TIMER_TIMER1_PRIVATE_H_ */
