/*
 * ADC.h
 *
 *  Created on: Oct 9, 2023
 *      Author: 2023
 */

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_

#include "../GIE/GIE.h"
/*
#include "../../Common/Macros.h"
#include "../../Common/MCU.h"
*/

#define AREF			0
#define AVCC			1
#define V_256			2
#define ADC_V_REF 		AVCC

#define RIGHT 	0
#define LEFT  	1
#define ADJUST 	LEFT

#define ADC0	0
#define ADC1	1
#define ADC2	2
#define ADC3	3
#define ADC4	4
#define ADC5	5
#define ADC6	6
#define ADC7	7
#define ADC_CHANNEL ADC0
#define KEEP_ADMUX 0b01000001


#define  ADC_REG    *((volatile u16*)0x24)

void MCAL_ADC_ADC_Init(void);
void MCAL_ADC_ADC_StartConversion(void);
void MCAL_ADC_ADC_InterruptEnable(void);
void MCAL_ADC_ADC_InterruptDisable(void);
void MCAL_ADC_voidADC_CallBack(void(*ADCAction)(void));

#endif /* MCAL_ADC_ADC_H_ */
