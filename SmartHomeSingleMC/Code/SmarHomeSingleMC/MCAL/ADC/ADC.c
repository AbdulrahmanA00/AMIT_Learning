/*
 * ADC.c
 *
 *  Created on: Oct 9, 2023
 *      Author: 2023
 */
#include "ADC.h"

static void (*GLOB_PADC_CallBack)(void) = NULL;

/*volatile u16 LOC_u16ADC_Value;*/
//(Volt_Ref,LEFT/RIGHT_ADJUST,INPUT_Channel) //Single Ended Input

void MCAL_ADC_ADC_Init(void)
{
#if   ADC_V_REF   ==   AVCC
	SET_BIT(ADMUX,REFS0);
	CLR_BIT(ADMUX,REFS1);
#elif ADC_V_REF   ==   AREF
	CLR_BIT(ADMUX,REFS0);
	CLR_BIT(ADMUX,REFS1);
#elif ADC_V_REF   ==   V_256
	SET_BIT(ADMUX,REFS0);
	SET_BIT(ADMUX,REFS1);
#endif
#if   	ADJUST   ==   LEFT
	SET_BIT(ADMUX,ADLAR);
#elif   ADJUST   ==   RIGHT
	CLR_BIT(ADMUX,ADLAR);
#endif

	/* To select an ADC channel */
	ADMUX = (ADMUX & KEEP_ADMUX) | ADC_CHANNEL ;
	/* To select the ADC frequency (Under Editing) */
	ADCSRA = 0b10000111;

	//MCAL_Interrupt_GIE_Enable();
	/* To enable ADC circuit */
	//SET_BIT(ADCSRA,ADEN_BIT);


}

void MCAL_ADC_ADC_InterruptEnable(void)
{
	/* To Enable ADC Interrupt */
	SET_BIT(ADCSRA,ADIE);
}
void MCAL_ADC_ADC_InterruptDisable(void)
{
	/* To Disable ADC Interrupt */
	CLR_BIT(ADCSRA,ADIE);
}


void MCAL_ADC_ADC_StartConversion(void)
{
	/* To start conversion */
	SET_BIT(ADCSRA,ADSC);
	//while(IS_BIT_CLEARED(ADCSRA,ADIF_BIT));
}

void MCAL_ADC_voidADC_CallBack(void(*ADCAction)(void))
{
	if (ADCAction != NULL)
	{
		GLOB_PADC_CallBack = ADCAction;
	}
}



ISR(ADC_vect)
{
	if (GLOB_PADC_CallBack != NULL)
	{
		GLOB_PADC_CallBack();
	}

}
