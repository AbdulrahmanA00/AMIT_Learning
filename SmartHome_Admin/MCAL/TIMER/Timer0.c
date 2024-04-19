/*
 * Timer.c
 *
 *  Created on: Oct 14, 2023
 *      Author: Abdulrahman Ayman
 */
#include "Timer0.h"

static void (*GLOB_PTimer0OVF_CallBack)(void) = NULL;
static void (*GLOB_PTimer0COMP_CallBack)(void) = NULL;

void MCAL_TIMER_Timer0_Init(u8 LOC_u8Timer0Mode,u8 LOC_u8Prescaler,u8 LOC_u8OCR0Mode)
{
	//Timer Mode
	if (LOC_u8Timer0Mode == NORMAL)
	{
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		if (LOC_u8OCR0Mode == NORMAL_OC0)
		{
			CLR_BIT(TCCR0,COM01);
			CLR_BIT(TCCR0,COM00);
		}
		else if (LOC_u8OCR0Mode == TOG_OC0)
		{
			CLR_BIT(TCCR0,COM01);
			SET_BIT(TCCR0,COM00);
		}
		else if (LOC_u8OCR0Mode == CLR_OC0)
		{
			SET_BIT(TCCR0,COM01);
			CLR_BIT(TCCR0,COM00);
		}
		else if (LOC_u8OCR0Mode == SET_OC0)
		{
			SET_BIT(TCCR0,COM01);
			SET_BIT(TCCR0,COM00);
		}
		else{/*Do Nothing*/}

	}
	else if (LOC_u8Timer0Mode == PWM_PHASECORRECT)
	{

		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		if (LOC_u8OCR0Mode == NORMAL_OC0)
		{
			CLR_BIT(TCCR0,COM01);
			CLR_BIT(TCCR0,COM00);
		}
		else if (LOC_u8OCR0Mode == NON_INVERTING_OC0)
		{
			SET_BIT(TCCR0,COM01);
			CLR_BIT(TCCR0,COM00);
		}
		else if (LOC_u8OCR0Mode == INVERTING_OC0)
		{
			SET_BIT(TCCR0,COM01);
			SET_BIT(TCCR0,COM00);
		}
		else{/*Do Nothing*/}
	}

	else if (LOC_u8Timer0Mode == CTC)
	{
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		if (LOC_u8OCR0Mode == NORMAL_OC0)
		{
			CLR_BIT(TCCR0,COM01);
			CLR_BIT(TCCR0,COM00);
		}
		else if (LOC_u8OCR0Mode == TOG_OC0)
		{
			CLR_BIT(TCCR0,COM01);
			SET_BIT(TCCR0,COM00);
		}
		else if (LOC_u8OCR0Mode == CLR_OC0)
		{
			SET_BIT(TCCR0,COM01);
			CLR_BIT(TCCR0,COM00);
		}
		else if (LOC_u8OCR0Mode == SET_OC0)
		{
			SET_BIT(TCCR0,COM01);
			SET_BIT(TCCR0,COM00);
		}
		else {/*Do Nothiing*/}

	}
	else if (LOC_u8Timer0Mode == FAST_PWM)
	{
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		if (LOC_u8OCR0Mode == NORMAL_OC0)
		{
			CLR_BIT(TCCR0,COM01);
			CLR_BIT(TCCR0,COM00);
		}
		else if (LOC_u8OCR0Mode == NON_INVERTING_OC0)
		{
			SET_BIT(TCCR0,COM01);
			CLR_BIT(TCCR0,COM00);
		}
		else if (LOC_u8OCR0Mode == INVERTING_OC0)
		{
			SET_BIT(TCCR0,COM01);
			SET_BIT(TCCR0,COM00);
		}
		else {/*Do Nothing*/}

	}

	//Select Clock & Perscaler
	if (LOC_u8Prescaler == CLK_OFF)
	{
		CLR_BIT(TCCR0,CS02);
		CLR_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS00);
	}
	else if (LOC_u8Prescaler == CLK_PRE1)
	{
		CLR_BIT(TCCR0,CS02);
		CLR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS00);
	}
	else if (LOC_u8Prescaler == CLK_PRE8)
	{
		CLR_BIT(TCCR0,CS02);
		SET_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS00);
	}
	else if (LOC_u8Prescaler == CLK_PRE64)
	{
		CLR_BIT(TCCR0,CS02);
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS00);
	}
	else if (LOC_u8Prescaler == CLK_PRE256)
	{
		SET_BIT(TCCR0,CS02);
		CLR_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS00);
	}
	else if (LOC_u8Prescaler == CLK_PRE1024)
	{
		SET_BIT(TCCR0,CS02);
		CLR_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS00);
	}
	else if (LOC_u8Prescaler == EXTCLK_FALLING)
	{
		SET_BIT(TCCR0,CS02);
		SET_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS00);
	}
	else if (LOC_u8Prescaler == EXTCLK_RISING)
	{
		SET_BIT(TCCR0,CS02);
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS00);
	}
	else{/*Do Nothing*/}




}

void MCAL_TIMER_Timer0_SetPreloadValue(u8 LOC_u8Value)
{
	TCNT0 = LOC_u8Value;
}
void MCAL_TIMER_Timer0_SetCompareValue(u8 LOC_u8Value)
{
	OCR0 = LOC_u8Value;
}


void MCAL_TIMER_Timer0_InterruptOVF_Enable(void)
{
	/* To Enable Timer0 OVF Interrupt */
	SET_BIT(TIMSK,TOIE0);
}
void MCAL_TIMER_Timer0_InterruptOVF_Disable(void)
{
	/* To Disable Timer0 OVF Interrupt */
	CLR_BIT(TIMSK,TOIE0);
}


void MCAL_TIMER_Timer0_InterruptCompare_Enable(void)
{
	/* To Enable Timer0 OVF Interrupt */
	SET_BIT(TIMSK,OCIE0);
}
void MCAL_TIMER_Timer0_InterruptCompare_Disable(void)
{
	/* To Disable Timer0 OVF Interrupt */
	CLR_BIT(TIMSK,OCIE0);
}


void MCAL_TIMER_voidTimer0_OVFSetCallBack(void(*Timer0Action)(void))
{
	if (Timer0Action != NULL)
	{
		GLOB_PTimer0OVF_CallBack = Timer0Action;
	}
}
void MCAL_TIMER_voidTimer0_COMPSetCallBack(void(*Timer0Action)(void))
{
	if (Timer0Action != NULL)
	{
		GLOB_PTimer0COMP_CallBack = Timer0Action;
	}
}

void DelayUs(u32 LOC_u32Time)
{
	u32 Tick,OVF_Time,Perscaler = 256,Preload;
	f32 OVF_Number;
	Tick = Perscaler/CLK;
	OVF_Time = Tick * OVF_Count;
	OVF_Number = LOC_u32Time/OVF_Time;
	Preload = OVF_Count - ( (((f32) LOC_u32Time/OVF_Count)-OVF_Number) * OVF_Count);
	if(Preload!=0)
	{
		MCAL_TIMER_Timer0_SetPreloadValue((u8)Preload);
		OVF_Number++;
	}
	else
	{
		//Do Nothing.
	}
	while(OVF_Number--)
	{
		while(GET_BIT(TIFR,TOV0)==0);
		SET_BIT(TIFR,TOV0);
	}

}
void DelayMs(u32 LOC_u32Time)
{
	u16 LOC_u16OVF_NO,OVF_Time,Perscaler = 256;
	u8 Tick,LOC_u8Preload;
	Tick = Perscaler/CLK;
	OVF_Time = Tick * OVF_Count;
	u16 Local_u16Remainder = (LOC_u32Time * 1000) % OVF_Time;
	if(Local_u16Remainder == 0)
	{
		LOC_u16OVF_NO = (LOC_u32Time * 1000) / OVF_Time;
		LOC_u8Preload = 0;
	}
	else
	{
		LOC_u16OVF_NO = ((LOC_u32Time * 1000) / OVF_Time ) + 1;
		LOC_u8Preload = OVF_Count - (Local_u16Remainder / Tick);
	}
	MCAL_TIMER_Timer0_SetPreloadValue(LOC_u8Preload);
	while(LOC_u16OVF_NO--)
	{
		while(GET_BIT(TIFR,TOV0)==0);
		SET_BIT(TIFR,TOV0);
	}

}


ISR(TIMER0_OVF_vect)
{
	if (GLOB_PTimer0OVF_CallBack != NULL)
	{
		GLOB_PTimer0OVF_CallBack();
	}

}

ISR(TIMER0_COMP_vect)
{
	if (GLOB_PTimer0COMP_CallBack != NULL)
	{
		GLOB_PTimer0COMP_CallBack();
	}

}

