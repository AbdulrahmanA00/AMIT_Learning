/*
 * Timer1_interfacing.h
 *
 *  Created on: Oct 28, 2023
 *      Author: Abdulrahman Ayman
 */

#ifndef MCAL_TIMER_TIMER1_INTERFACING_H_
#define MCAL_TIMER_TIMER1_INTERFACING_H_


void MCAL_Timer_Timer1_voidInit(u8 LOC_u8Mode,u8 LOC_u8Scaler,u8 LOC_u8OC1AMode,u8 LOC_u8OC1BMode);
void MCAL_Timer_Timer1_voidSetPreloadValue(u16 LOC_u16PreValue);
u16	 MCAL_Timer_Timer1_u16GetCounterValue(void);
void MCAL_Timer_Timer1_voidSetOCR1AValue(u16 LOC_u16OCR1AValue);
void MCAL_Timer_Timer1_voidSetOCR1BValue(u16 LOC_u16OCR1BValue);
void MCAL_Timer_Timer1_voidSetICR1Value(u16 LOC_u16ICR1Value);

void MCAL_Timer_Timer1_voidOverflowSetCallBack(void (*NotifiFunction)(void));
void MCAL_Timer_Timer1_voidCompareMatch1ASetCallBack(void (*NotifiFunction)(void));
void MCAL_Timer_Timer1_voidCompareMatch1BSetCallBack(void (*NotifiFunction)(void));
void MCAL_Timer_Timer1_voidOverflowInterruptEnable(void);
void MCAL_Timer_Timer1_voidOverflowInterruptDisable(void);
void MCAL_Timer_Timer1_voidCompareMatch1AInterruptEnable(void);
void MCAL_Timer_Timer1_voidCompareMatch1AInterruptDisable(void);
void MCAL_Timer_Timer1_voidCompareMatch1BInterruptEnable(void);
void MCAL_Timer_Timer1_voidCompareMatch1BInterruptDisable(void);

u16	 MCAL_Timer_Timer1_voidICUGetICR1Value(void);
void MCAL_Timer_Timer1_voidICUSetTriggerEdge(u8 LOC_u8TriggerEdge);
void MCAL_Timer_Timer1_voidICUInterruptEnable(void);
void MCAL_Timer_Timer1_voidICUInterruptDisable(void);


//Timer1 Mode Options:
#define TIMER1_NORMAL_MODE									0
#define TIMER1_PWM_PHASE_CORRECT_MODE_8_BIT					1
#define TIMER1_PWM_PHASE_CORRECT_MODE_9_BIT					2
#define TIMER1_PWM_PHASE_CORRECT_MODE_10_BIT				3
#define TIMER1_CTC_MODE_TOP_OCR1A							4
#define TIMER1_PWM_FAST_MODE_8_BIT							5
#define TIMER1_PWM_FAST_MODE_9_BIT							6
#define TIMER1_PWM_FAST_MODE_10_BIT							7
#define TIMER1_PWM_PHASE_FREQUENCY_CORRECT_MODE_TOP_ICR1	8
#define TIMER1_PWM_PHASE_FREQUENCY_CORRECT_MODE_TOP_OCR1A	9
#define TIMER1_PWM_PHASE_CORRECT_MODE_TOP_ICR1				10
#define TIMER1_PWM_PHASE_CORRECT_MODE_TOP_OCR1A				11
#define TIMER1_CTC_MODE_TOP_ICR1							12
#define TIMER1_PWM_FAST_MODE_TOP_ICR1						13
#define TIMER1_PWM_FAST_MODE_TOP_OCR1A						14


//Timer1 Prescaler Options:
#define TIMER1_SCALER_TIMER_STOP_MASK 					0x00
#define TIMER1_SCALER_1_MASK    						0x01
#define TIMER1_SCALER_8_MASK   							0x02
#define TIMER1_SCALER_64_MASK    						0x03
#define TIMER1_SCALER_256_MASK 		 					0x04
#define TIMER1_SCALER_1024_MASK    						0x05
#define TIMER1_SCALER_EXT_T1_FALLING_EDGE_MASK    		0x06
#define TIMER1_SCALER_EXT_T1_RISING_EDGE_MASK    		0x07
#define TIMER1_SCALER_CLEAR_MASK						0xF8  //0b11111000


//OCR1A/OCR1B Option:
#define TIMER1_OCR1_CLEAR_MASK							0x0F  //0b00001111
//For NON-PWM Modes (Normal, CTC)
#define TIMER1_OCR1_DISCONNECTED						0X00
#define TIMER1_OCR1_TOGGLE								0X01
#define TIMER1_OCR1_CLEAR								0X02
#define TIMER1_OCR1_SET									0X03
//For Fast PWM Modes
#define TIMER1_OCR1_DISCONNECTED						0X00
#define TIMER1_OCR1_TOGGLE_OC1A_DISCONNECTED_OCR1B		0X01
#define TIMER1_OCR1_NON_INVERTING						0X02
#define TIMER1_OCR1_INVERTING							0X03
//For Phase Correct and Phase and Frequency Correct Modes
#define TIMER1_OCR1_DISCONNECTED						0X00
#define TIMER1_OCR1_TOGGLE_OC1A_DISCONNECTED_OCR1B		0X01
#define TIMER1_OCR1_NON_INVERTING						0X02
#define TIMER1_OCR1_INVERTING							0X03



#endif /* MCAL_TIMER_TIMER1_INTERFACING_H_ */
