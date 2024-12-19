/*
 * State_program.c
 *
 *  Created on: Nov 27, 2024
 *      Author: DELL
 */

#include "State_interface.h"

u8 volatile G_u8_Receive;
void APP_STATE_void_AppStateInit(void)
{
	MCAL_Interrupt_GIE_Enable();
	MCAL_EXT_INT_voidEXTInt_Init(INT_0,RISING_EDGE);
	MCAL_EXT_INT_voidEXTInt_CallBack(INT_0,INT0_APP_CALLBACK);
	MCAL_DIO_u8SetPinDirection(PortB,PIN2,PIN_OUTPUT);
	MCAL_SPI_MASTER_SLAVE_u8_SetMasterSalve_Prescaler_SpiMasterSlaveInit(SPI_MASTER,SPI_PRESCALER_128);
}

void INT0_APP_CALLBACK(void)
{
	MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
	G_u8_Receive = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('x');
	MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
	_delay_ms(50);
	if(G_u8_Receive == '1')
	{
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_u8_Receive = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('x');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		if(G_u8_Receive == 'N')
		{
			HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_ON);
			G_DeviceOneFlag = 1;
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_OFF);
			G_DeviceOneFlag = 0;
		}
		else if(G_u8_Receive == 'T')
		{
			HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_TOG);
			TOGGLE_BIT(G_DeviceOneFlag,PIN0);
		}
		G_RunningDevicesIndicator = 1;
	}
	else if(G_u8_Receive == '2')
	{
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_u8_Receive = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('x');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		if(G_u8_Receive == 'N')
		{
			HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_ON);
			G_DeviceTwoFlag = 1;
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_OFF);
			G_DeviceTwoFlag = 0;
		}
		else if(G_u8_Receive == 'T')
		{
			HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_TOG);
			TOGGLE_BIT(G_DeviceTwoFlag,PIN0);
		}
		G_RunningDevicesIndicator = 1;
	}
	else if(G_u8_Receive == '3')
	{
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_u8_Receive = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('x');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		if(G_u8_Receive == 'N')
		{
			HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_ON);
			G_DeviceThreeFlag = 1;
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_OFF);
			G_DeviceThreeFlag = 0;
		}
		else if(G_u8_Receive == 'T')
		{
			HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_TOG);
			TOGGLE_BIT(G_DeviceThreeFlag,PIN0);
		}
		G_RunningDevicesIndicator = 1;
	}
	else if(G_u8_Receive == '4')
	{
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_u8_Receive = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('x');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		if(G_u8_Receive == 'N')
		{
			HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_ON);
			G_DeviceFourFlag = 1;
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_OFF);
			G_DeviceFourFlag = 0;
		}
		else if(G_u8_Receive == 'T')
		{
			HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_TOG);
			TOGGLE_BIT(G_DeviceFourFlag,PIN0);
		}
		G_RunningDevicesIndicator = 1;
	}
	else if(G_u8_Receive == '5')
	{
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_u8_Receive = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('x');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		if(G_u8_Receive == 'N')
		{
			HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_ON);
			G_DeviceFiveFlag = 1;
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_OFF);
			G_DeviceFiveFlag = 0;
		}
		else if(G_u8_Receive == 'T')
		{
			HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_TOG);
			TOGGLE_BIT(G_DeviceFiveFlag,PIN0);
		}
		G_RunningDevicesIndicator = 1;
	}
	else if(G_u8_Receive == 'B')
	{
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_u8_Receive = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('x');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		if(G_u8_Receive == 'N')
		{
			HAL_Buzzer_u8BuzzerMode(Buzzer_Port,Buzzer_Pin,Buzzer_ON);
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_Buzzer_u8BuzzerMode(Buzzer_Port,Buzzer_Pin,Buzzer_OFF);
		}
		else if(G_u8_Receive == 'T')
		{
			HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_TOG);
			TOGGLE_BIT(G_DeviceFiveFlag,PIN0);
		}
	}
	else if(G_u8_Receive == 'F')
	{
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_u8_Receive = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('x');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		if(G_u8_Receive == 'N')
		{
			HAL_DCMOTOR_void_DcMotorClockWise(motor_speed);
			G_FanFlag = 1;
			G_FanFlagOff = 1;
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_DCMOTOR_void_DcMotorStop();
			G_FanFlag = 0;
			G_FanFlagOn = 1;
		}
		else if(G_u8_Receive == 'T')
		{
			G_FanFlagOn = 0;
			G_FanFlagOff = 0;
			G_FanControlFlag =0;
		}
		else if(G_u8_Receive == 'M')
		{
			/*G_FanFlagOn = 0;
			G_FanFlagOff = 0;*/
		G_FanControlFlag =1;
		}
		G_RunningDevicesIndicator = 1;
	}

	/*while(GET_BIT(PINB,PIN4));
	G_u8_Receive = MCAL_SPI_SLAVE_u8_SpiSlave_Transceive('F');
	if(G_u8_Receive == '1')
	{
		while(GET_BIT(PINB,PIN4));
		G_u8_Receive = MCAL_SPI_SLAVE_u8_SpiSlave_Transceive('F');
		if(G_u8_Receive == 'N')
		{
			HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_ON);
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_OFF);
		}
		else if(G_u8_Receive == 'T')
		{
			HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_TOG);
		}
	}
	else if(G_u8_Receive == '2')
	{
		while(GET_BIT(PINB,PIN4));
		G_u8_Receive = MCAL_SPI_SLAVE_u8_SpiSlave_Transceive('F');
		if(G_u8_Receive == 'N')
		{
			HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_ON);
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_OFF);
		}
		else if(G_u8_Receive == 'T')
		{
			HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_TOG);
		}
	}
	else if(G_u8_Receive == '3')
	{
		while(GET_BIT(PINB,PIN4));
		G_u8_Receive = MCAL_SPI_SLAVE_u8_SpiSlave_Transceive('F');
		if(G_u8_Receive == 'N')
		{
			HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_ON);
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_OFF);
		}
		else if(G_u8_Receive == 'T')
		{
			HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_TOG);
		}
	}
	else if(G_u8_Receive == '4')
	{
		while(GET_BIT(PINB,PIN4));
		G_u8_Receive = MCAL_SPI_SLAVE_u8_SpiSlave_Transceive('F');
		if(G_u8_Receive == 'N')
		{
			HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_ON);
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_OFF);
		}
		else if(G_u8_Receive == 'T')
		{
			HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_TOG);
		}
	}
	else if(G_u8_Receive == '5')
	{
		while(GET_BIT(PINB,PIN4));
		G_u8_Receive = MCAL_SPI_SLAVE_u8_SpiSlave_Transceive('F');
		if(G_u8_Receive == 'N')
		{
			HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_ON);
		}
		else if(G_u8_Receive == 'F')
		{
			HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_OFF);
		}
		else if(G_u8_Receive == 'T')
		{
			HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_TOG);
		}
	}*/

}
