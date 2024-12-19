/*
 * Timer1.c
 *
 *  Created on: Oct 26, 2023
 *      Author: Abdulrahman Ayman
 */
#include"Timer1.h"

static void (*GLOB_PTimer1OVF_CallBack)(void) = NULL;
static void (*GLOB_PTimer1COMPA_CallBack)(void) = NULL;
static void (*GLOB_PTimer1COMPB_CallBack)(void) = NULL;
static void (*GLOB_PTimer1CAPT_CallBack)(void) = NULL;


void MCAL_Timer_Timer1_voidInit(u8 LOC_u8Mode,u8 LOC_u8Scaler,u8 LOC_u8OC1AMode,u8 LOC_u8OC1BMode)
{
	u8 LOC_u8TCCR1A_OCR1_Modes;
	if((LOC_u8Scaler>=TIMER1_SCALER_TIMER_STOP_MASK) && (LOC_u8Scaler<=TIMER1_SCALER_EXT_T1_RISING_EDGE_MASK))
	{
		TCCR1B &= TIMER1_SCALER_CLEAR_MASK;
		TCCR1B |= LOC_u8Scaler;
	}
	else {/*Do Nothing*/}

	if((LOC_u8Mode>=TIMER1_NORMAL_MODE) && (LOC_u8Mode<=TIMER1_PWM_FAST_MODE_TOP_OCR1A))
	{
		switch(LOC_u8Mode)
		{
		case TIMER1_NORMAL_MODE :
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1B,TCCR1B_WGM13);
			break;
		case TIMER1_PWM_PHASE_CORRECT_MODE_8_BIT :
			SET_BIT(TCCR1A,TCCR1A_WGM10);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1B,TCCR1B_WGM13);
			break;
		case TIMER1_PWM_PHASE_CORRECT_MODE_9_BIT :
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1B,TCCR1B_WGM13);
			break;
		case TIMER1_PWM_PHASE_CORRECT_MODE_10_BIT :
			SET_BIT(TCCR1A,TCCR1A_WGM10);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1B,TCCR1B_WGM13);
			break;
		case TIMER1_CTC_MODE_TOP_OCR1A :
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1B,TCCR1B_WGM13);
			break;

		case TIMER1_PWM_FAST_MODE_8_BIT :
			SET_BIT(TCCR1A,TCCR1A_WGM10);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1B,TCCR1B_WGM13);
			break;
		case TIMER1_PWM_FAST_MODE_9_BIT :
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1B,TCCR1B_WGM13);
			break;
		case TIMER1_PWM_FAST_MODE_10_BIT :
			SET_BIT(TCCR1A,TCCR1A_WGM10);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1B,TCCR1B_WGM13);
			break;
		case TIMER1_PWM_PHASE_FREQUENCY_CORRECT_MODE_TOP_ICR1 :
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1B,TCCR1B_WGM13);
			break;
		case TIMER1_PWM_PHASE_FREQUENCY_CORRECT_MODE_TOP_OCR1A :
			SET_BIT(TCCR1A,TCCR1A_WGM10);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1B,TCCR1B_WGM13);
			break;
		case TIMER1_PWM_PHASE_CORRECT_MODE_TOP_ICR1 :
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1B,TCCR1B_WGM13);
			break;
		case TIMER1_PWM_PHASE_CORRECT_MODE_TOP_OCR1A :
			SET_BIT(TCCR1A,TCCR1A_WGM10);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1B,TCCR1B_WGM13);
			break;
		case TIMER1_CTC_MODE_TOP_ICR1 :
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1B,TCCR1B_WGM13);
			break;
		case TIMER1_PWM_FAST_MODE_TOP_ICR1 :
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1B,TCCR1B_WGM13);
			break;
		case TIMER1_PWM_FAST_MODE_TOP_OCR1A :
			SET_BIT(TCCR1A,TCCR1A_WGM10);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1B,TCCR1B_WGM13);
			break;

		default:
			break;
		}
	}
	else {/*Do Nothing*/}

	//OCR1A/OCR1B Mode Select.
	if((LOC_u8OC1AMode >=TIMER1_OCR1_DISCONNECTED && LOC_u8OC1AMode<=TIMER1_OCR1_SET) && (LOC_u8OC1AMode >=TIMER1_OCR1_DISCONNECTED && LOC_u8OC1AMode<=TIMER1_OCR1_SET))
	LOC_u8TCCR1A_OCR1_Modes = (LOC_u8OC1AMode<<6) | (LOC_u8OC1BMode<<4);
	TCCR1A &= TIMER1_OCR1_CLEAR_MASK;
	TCCR1A |= LOC_u8TCCR1A_OCR1_Modes;

}


void MCAL_Timer_Timer1_voidSetPreloadValue(u16 LOC_u16PreValue)
{
	TCNT1 = LOC_u16PreValue;
}


u16	 MCAL_Timer_Timer1_u16GetCounterValue(void)
{
	return TCNT1;
}


void MCAL_Timer_Timer1_voidSetOCR1AValue(u16 LOC_u16OCR1AValue)
{
	OCR1A = LOC_u16OCR1AValue;
}


void MCAL_Timer_Timer1_voidSetOCR1BValue(u16 LOC_u16OCR1BValue)
{
	OCR1B = LOC_u16OCR1BValue;
}


void MCAL_Timer_Timer1_voidSetICR1Value(u16 LOC_u16ICR1Value)
{
	ICR1 = LOC_u16ICR1Value;
}


void MCAL_Timer_Timer1_voidOverflowSetCallBack(void (*NotifiFunction)(void))
{
	if (NotifiFunction != NULL)
	{
		GLOB_PTimer1OVF_CallBack = NotifiFunction;
	}

}

void MCAL_Timer_Timer1_voidCompareMatch1ASetCallBack(void (*NotifiFunction)(void))
{
	if (NotifiFunction != NULL)
	{
		GLOB_PTimer1COMPA_CallBack = NotifiFunction;
	}

}

void MCAL_Timer_Timer1_voidCompareMatch1BSetCallBack(void (*NotifiFunction)(void))
{
	if (NotifiFunction != NULL)
	{
		GLOB_PTimer1COMPB_CallBack = NotifiFunction;
	}

}

void MCAL_Timer_Timer1_voidOverflowInterruptEnable(void)
{
	SET_BIT(TIMSK,TIMSK_TOIE1);
}

void MCAL_Timer_Timer1_voidOverflowInterruptDisable(void)
{
	CLR_BIT(TIMSK,TIMSK_TOIE1);
}

void MCAL_Timer_Timer1_voidCompareMatch1AInterruptEnable(void)
{
	SET_BIT(TIMSK,TIMSK_OCIE1A);

}

void MCAL_Timer_Timer1_voidCompareMatch1AInterruptDisable(void)
{
	CLR_BIT(TIMSK,TIMSK_OCIE1A);
}

void MCAL_Timer_Timer1_voidCompareMatch1BInterruptEnable(void)
{
	SET_BIT(TIMSK,TIMSK_OCIE1B);
}

void MCAL_Timer_Timer1_voidCompareMatch1BInterruptDisable(void)
{
	CLR_BIT(TIMSK,TIMSK_OCIE1B);
}

u16	 MCAL_Timer_Timer1_voidICUGetICR1Value(void)
{
	return ICR1;
}
void MCAL_Timer_Timer1_voidICUSetTriggerEdge(u8 LOC_u8TriggerEdge)
{
//ICES1
	if(LOC_u8TriggerEdge == RISING_EDGE)
	{
		SET_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else if(LOC_u8TriggerEdge == FALLING_EDGE)
	{
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else {/*Do Nothing.*/}
}
void MCAL_Timer_Timer1_voidICUInterruptEnable(void)
{
		SET_BIT(TIMSK,TIMSK_TICIE1);
}
void MCAL_Timer_Timer1_voidICUInterruptDisable(void)
{
		CLR_BIT(TIMSK,TIMSK_TICIE1);
}





ISR(TIMER1_OVF_vect)
{
	if (GLOB_PTimer1OVF_CallBack != NULL)
	{
		GLOB_PTimer1OVF_CallBack();
	}

}

ISR(TIMER1_COMPA_vect)
{
	if (GLOB_PTimer1COMPA_CallBack != NULL)
	{
		GLOB_PTimer1COMPA_CallBack();
	}

}

ISR(TIMER1_COMPB_vect)
{
	if (GLOB_PTimer1COMPB_CallBack != NULL)
	{
		GLOB_PTimer1COMPB_CallBack();
	}

}

ISR(TIMER1_CAPT_vect)
{
	if (GLOB_PTimer1CAPT_CallBack != NULL)
	{
		GLOB_PTimer1CAPT_CallBack();
	}

}
