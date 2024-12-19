/*
 * State_program.c
 *
 *  Created on: Nov 27, 2024
 *      Author: DELL
 */

#include "State_interface.h"
#include "..\..\HAL\Buzzer\Buzzer.h"

extern u8 volatile GLOB_u8Flag_LED1;
extern u8 volatile GLOB_u8Flag_LED2;
extern u8 volatile GLOB_u8Flag_LED3;
extern u8 volatile GLOB_u8Flag_LED4;
extern u8 volatile GLOB_u8Flag_LED5;
extern u8 volatile GLOB_u8Flag_AC;

u8 G_u8_Receive;
void APP_STATE_void_AppStateInit(void)
{
	MCAL_Interrupt_GIE_Enable();
	MCAL_EXT_INT_voidEXTInt_Init(INT_0,RISING_EDGE);
	MCAL_EXT_INT_voidEXTInt_CallBack(INT_0,INT0_APP_CALLBACK);
	MCAL_DIO_u8SetPinDirection(PortB,PIN2,PIN_OUTPUT);
	MCAL_SPI_MASTER_SLAVE_u8_SetMasterSalve_Prescaler_SpiMasterSlaveInit(SPI_SLAVE,SPI_PRESCALER_128);
}

void INT0_APP_CALLBACK(void)
{
	while(GET_BIT(PINB,PIN4));
	G_u8_Receive = MCAL_SPI_SLAVE_u8_SpiSlave_Transceive('F');
	if(G_u8_Receive == '1')
	{
		while(GET_BIT(PINB,PIN4));
		G_u8_Receive = MCAL_SPI_SLAVE_u8_SpiSlave_Transceive('F');
		if(G_u8_Receive == 'N')
		{
			HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_ON);
			GLOB_u8Flag_LED1 = 1;
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_OFF);
			GLOB_u8Flag_LED1 = 0;
		}
		else if(G_u8_Receive == 'T')
		{
			HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_TOG);
			TOGGLE_BIT(GLOB_u8Flag_LED1,PIN0);
		}
	}
	else if(G_u8_Receive == '2')
	{
		while(GET_BIT(PINB,PIN4));
		G_u8_Receive = MCAL_SPI_SLAVE_u8_SpiSlave_Transceive('F');
		if(G_u8_Receive == 'N')
		{
			HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_ON);
			GLOB_u8Flag_LED2 = 1;
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_OFF);
			GLOB_u8Flag_LED2 = 0;
		}
		else if(G_u8_Receive == 'T')
		{
			HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_TOG);
			TOGGLE_BIT(GLOB_u8Flag_LED2,PIN0);
		}
	}
	else if(G_u8_Receive == '3')
	{
		while(GET_BIT(PINB,PIN4));
		G_u8_Receive = MCAL_SPI_SLAVE_u8_SpiSlave_Transceive('F');
		if(G_u8_Receive == 'N')
		{
			HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_ON);
			GLOB_u8Flag_LED3 = 1;
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_OFF);
			GLOB_u8Flag_LED3 = 0;
		}
		else if(G_u8_Receive == 'T')
		{
			HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_TOG);
			TOGGLE_BIT(GLOB_u8Flag_LED3,PIN0);
		}
	}
	else if(G_u8_Receive == '4')
	{
		while(GET_BIT(PINB,PIN4));
		G_u8_Receive = MCAL_SPI_SLAVE_u8_SpiSlave_Transceive('F');
		if(G_u8_Receive == 'N')
		{
			HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_ON);
			GLOB_u8Flag_LED4 = 1;
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_OFF);
			GLOB_u8Flag_LED4 = 0;
		}
		else if(G_u8_Receive == 'T')
		{
			HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_TOG);
			TOGGLE_BIT(GLOB_u8Flag_LED4,PIN0);
		}
	}
	else if(G_u8_Receive == '5')
	{
		while(GET_BIT(PINB,PIN4));
		G_u8_Receive = MCAL_SPI_SLAVE_u8_SpiSlave_Transceive('F');
		if(G_u8_Receive == 'N')
		{
			HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_ON);
			GLOB_u8Flag_LED5 = 1;
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_OFF);
			GLOB_u8Flag_LED5 = 0;
		}
		else if(G_u8_Receive == 'T')
		{
			HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_TOG);
			TOGGLE_BIT(GLOB_u8Flag_LED5,PIN0);
		}
	}
	else if(G_u8_Receive == 'B')
	{
		while(GET_BIT(PINB,PIN4));
		G_u8_Receive = MCAL_SPI_SLAVE_u8_SpiSlave_Transceive('F');
		if(G_u8_Receive == 'N')
		{
			HAL_Buzzer_u8BuzzerMode(Buzzer_Port,Buzzer_Pin,Buzzer_ON);
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_Buzzer_u8BuzzerMode(Buzzer_Port,Buzzer_Pin,Buzzer_OFF);
		}
	}
	else if(G_u8_Receive == 'F')
	{
		while(GET_BIT(PINB,PIN4));
		G_u8_Receive = MCAL_SPI_SLAVE_u8_SpiSlave_Transceive('F');
		if(G_u8_Receive == 'N')
		{
			HAL_DCMOTOR_void_DcMotorClockWise(7);
			GLOB_u8Flag_AC = 1;
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_DCMOTOR_void_DcMotorStop();
			GLOB_u8Flag_AC = 0;
		}
		else if(G_u8_Receive == 'T')
		{
			TOGGLE_BIT(GLOB_u8Flag_AC,PIN0);
			if(GLOB_u8Flag_AC == 1)
			{
				HAL_DCMOTOR_void_DcMotorClockWise(7);
			}
			else if(GLOB_u8Flag_AC == 0)
			{
				HAL_DCMOTOR_void_DcMotorStop();
			}
		}
	}
}
