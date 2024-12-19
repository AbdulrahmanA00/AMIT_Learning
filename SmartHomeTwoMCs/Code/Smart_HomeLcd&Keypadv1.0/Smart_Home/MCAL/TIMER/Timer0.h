/*
 * Timer.h
 *
 *  Created on: Oct 14, 2023
 *      Author: 2023
 */

#ifndef MCAL_TIMER_TIMER0_H_
#define MCAL_TIMER_TIMER0_H_

#include "../GIE/GIE.h"

/***************Configuration******************/
#define NORMAL 				0
#define PWM_PHASECORRECT 	1
#define CTC 				2
#define FAST_PWM 			3

#define TIMER_MODE 			PWM_PHASECORRECT

#define CLK_OFF 		0
#define CLK_PRE1 		1
#define CLK_PRE8 		2
#define CLK_PRE64 		3
#define CLK_PRE256 		4
#define CLK_PRE1024 	5
#define EXTCLK_FALLING 	6
#define EXTCLK_RISING 	7

#define PRESCALER_MODE 		CLK_PRE256
//Modes for non-PWM mode
#define NORMAL_OC0		0
#define TOG_OC0			1
#define CLR_OC0			2
#define SET_OC0			3
//Modes for Fast PWM
//Modes for PWM Correct
#define NORMAL_OC0				0
#define NON_INVERTING_OC0		1
#define INVERTING_OC0			2
#define COMP_OUT_MODE			INVERTING_OC0
/*****************************************************/

#define OVF_Count  	256
#define CLK			16
//Declaration
void MCAL_TIMER_Timer0_Init(u8 LOC_u8Timer0Mode,u8 LOC_u8Prescaler,u8 LOC_u8OCR0Mode);
void MCAL_TIMER_Timer0_SetPreloadValue(u8 LOC_u8Value);
void MCAL_TIMER_Timer0_SetCompareValue(u8 LOC_u8Value);
void MCAL_TIMER_Timer0_InterruptCompare_Enable(void);
void MCAL_TIMER_Timer0_InterruptCompare_Disable(void);
void MCAL_TIMER_Timer0_InterruptOVF_Enable(void);
void MCAL_TIMER_Timer0_InterruptOVF_Disable(void);
void DelayUs(u32 LOC_u32Time);
void DelayMs(u32 LOC_u32Time);
void MCAL_TIMER_voidTimer0_SetCallBack(void(*Timer0Action)(void));
void MCAL_TIMER_voidTimer0_COMPSetCallBack(void(*Timer0Action)(void));
#endif /* MCAL_TIMER_TIMER0_H_ */
