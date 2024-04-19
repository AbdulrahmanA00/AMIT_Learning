/*
 * Interrupt.c
 *
 *  Created on: Oct 8, 2023
 *      Author: 2023
 */
#include "GIE.h"



void MCAL_Interrupt_GIE_Enable(void)
{
	/* To enable the global interrupt */
	SET_BIT(SREG,I_BIT);
}

void MCAL_Interrupt_GIE_Disable(void)
{
	/* To disable the global interrupt */
	CLR_BIT(SREG,I_BIT);
}

