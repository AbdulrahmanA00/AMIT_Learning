/*
 * PWM.c
 *
 *  Created on: Oct 26, 2023
 *      Author: Abdulrahman Ayman
 */
#include "../../ServiceLayer/PWM/PWM.h"


//Generate PWM wave in (Hz)
void ServiceLayer_PWM_voidGenerateHZ(u16 LOC_u16Frequency,u8 LOC_u8Duty)
{
#if	TIMER_TYPE == TIMER1
	u16 LOC_u16TopValue;
	u16 LOC_u16OCR1AValue;
	if((LOC_u16Frequency<=62500) && (LOC_u16Frequency>=8))
	{
		LOC_u16TopValue = ((F_CPU)/(2*LOC_u16Frequency*SCALER_NUMBER));
		MCAL_Timer_Timer1_voidSetICR1Value(LOC_u16TopValue-1);

		if((LOC_u8Duty<=100) && (LOC_u8Duty>=0))
		{
			LOC_u16OCR1AValue = ((u32)LOC_u8Duty*LOC_u16TopValue/100)-1;
			MCAL_Timer_Timer1_voidSetOCR1AValue(LOC_u16OCR1AValue);
		}
		else {/*Do Nothing*/}
		MCAL_Timer_Timer1_voidInit(TIMER1_PWM_PHASE_FREQUENCY_CORRECT_MODE_TOP_ICR1,TIMER1_SCALER_8_MASK,TIMER1_OCR1_NON_INVERTING,TIMER1_OCR1_NON_INVERTING);
	}
	else {/*Do Nothing*/}


#endif


}



//Generate PWM wave in (KHz)
void ServiceLayer_PWM_voidGenerateKHZ(u16 LOC_u16Frequency,u8 LOC_u8Duty)
{
#if	TIMER_TYPE == TIMER1
	u32 LOC_u32FrequencyHz;
	u16 LOC_u16TopValue;
	u16 LOC_u16OCR1AValue;
	if((LOC_u16Frequency<=4000) && (LOC_u16Frequency>=1))
	{
		LOC_u32FrequencyHz = LOC_u16Frequency*1000;
		LOC_u16TopValue = ((F_CPU)/(2*LOC_u16Frequency*SCALER_NUMBER_KHZ));
		MCAL_Timer_Timer1_voidSetICR1Value(LOC_u16TopValue-1);

		if((LOC_u8Duty<=100) && (LOC_u8Duty>=0))
		{
			LOC_u16OCR1AValue = ((u32)LOC_u8Duty*LOC_u16TopValue/100)-1;
			MCAL_Timer_Timer1_voidSetOCR1AValue(LOC_u16OCR1AValue);
		}
		else {/*Do Nothing*/}
		MCAL_Timer_Timer1_voidInit(TIMER1_PWM_PHASE_FREQUENCY_CORRECT_MODE_TOP_ICR1,TIMER1_SCALER_1_MASK,TIMER1_OCR1_NON_INVERTING,TIMER1_OCR1_NON_INVERTING);
	}
	else {/*Do Nothing*/}


#endif


}
