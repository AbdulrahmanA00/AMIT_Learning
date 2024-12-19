/*
 * Interrupt.h
 *
 *  Created on: Oct 8, 2023
 *      Author: 2023
 */

#ifndef MCAL_GIE_GIE_H_
#define MCAL_GIE_GIE_H_

#include "../../Common/Macros.h"
#include "../../Common/MCU.h"

#define ISR(vectNum)	void vectNum(void)__attribute__((signal));\
					  	void vectNum(void)

/*******	External Interrupt	********/
#define EXTINT0_vect	__vector_1
#define EXTINT1_vect 	__vector_2
#define EXTINT2_vect 	__vector_3

/*******	ADC		*******/
#define ADC_vect 		__vector_16

/*******	TIMER	*******/
#define TIMER0_COMP_vect	 __vector_10
#define TIMER0_OVF_vect		 __vector_11
#define TIMER1_OVF_vect		 __vector_9
#define TIMER1_COMPB_vect	 __vector_8
#define TIMER1_COMPA_vect	 __vector_7
#define TIMER1_CAPT_vect	 __vector_6

/*******	USART	*******/
#define USART_RXC	 __vector_13
#define USART_UDRE	 __vector_14
#define USART_TXC	 __vector_15


void MCAL_Interrupt_GIE_Enable(void);
void MCAL_Interrupt_GIE_Disable(void);

#endif /* MCAL_GIE_GIE_H_ */
