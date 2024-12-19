#include "LcdUser_interface.h"
#include "LcdUser_config.h"
#include "LcdUser_private.h"


/*****************************************************************************************/
u8 volatile G_flag;//to know if any device is on or not to write on lcd ("is"->if one device is in, "are" if two or more are on)
u8 volatile G_DeviceOneFlag;//to know state of device1
u8 volatile G_DeviceTwoFlag;//to know state of device2
u8 volatile G_DeviceThreeFlag;//to know state of device3
u8 volatile G_DeviceFourFlag;//to know state of device4
u8 volatile G_DeviceFiveFlag;//to know state of device5
u8 volatile G_FanFlag;//to know state of fan
u8 volatile G_FanFlagOn;//to know that fan is on
u8 volatile G_FanFlagOff;//to know that fan is off
u8 volatile G_FanControlFlag;//to know the control option that user select it from lcd
u8 volatile G_LogoutFlag;// It is an indicator to log out of the system (if one -> logging out of system)
u8 volatile G_LM35;
u8 volatile G_Keypad_Value;// to know the value of keypad that user select it
u8 volatile G_RecieveValue;


/************************************ Implementation Section ******************************/

/************************************************************************
 * description : to know which devices are working
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_DEVICES_void_AppGetAnyDeviceOn(void)
{
	HAL_LCD_u8_ClearFullScreen();
	HAL_LCD_u8_GoTo(0,0);
	if(G_DeviceOneFlag == ON)
	{
		HAL_LCD_u8_WriteString("Device 1");
		G_flag++;
	}
	if(G_DeviceTwoFlag == ON)
	{
		if(G_flag == OFF)
		{
			HAL_LCD_u8_WriteString("Device 2");
			G_flag++;
		}
		else
		{
			HAL_LCD_u8_WriteString("&2");
			G_flag++;
		}
	}
	if(G_DeviceThreeFlag == ON)
	{
		if(G_flag == OFF)
		{
			HAL_LCD_u8_WriteString("Device 3");
			G_flag++;
		}
		else
		{
			HAL_LCD_u8_WriteString("&3");
			G_flag++;
		}
	}
	if(G_DeviceFourFlag == ON)
	{
		if(G_flag == OFF)
		{
			HAL_LCD_u8_WriteString("Device 4");
			G_flag++;
		}
		else
		{
			HAL_LCD_u8_WriteString("&4");
			G_flag++;
		}
	}
	if(G_DeviceFiveFlag == ON)
	{
		if(G_flag == OFF)
		{
			HAL_LCD_u8_WriteString("Device 5");
			G_flag++;
		}
		else
		{
			HAL_LCD_u8_WriteString("&5");
			G_flag++;
		}
	}
	if(G_FanFlag == ON)
	{
		if(G_flag == OFF)
		{
			HAL_LCD_u8_WriteString("Fan");
			G_flag++;
		}
		else
		{
			HAL_LCD_u8_WriteString("&Fan");
			G_flag++;
		}
	}
	if(G_flag == OFF)
	{
		HAL_LCD_u8_GoTo(0,0);
		HAL_LCD_u8_WriteString("All Devices");
		HAL_LCD_u8_GoTo(1,0);
		HAL_LCD_u8_WriteString("are OFF");
	}
	else if(G_flag == ON)
	{
		HAL_LCD_u8_GoTo(1,0);
		HAL_LCD_u8_WriteString("is ON");
		G_flag = OFF;
	}
	else if(G_flag <= SIX)
	{
		HAL_LCD_u8_GoTo(1,0);
		HAL_LCD_u8_WriteString("are ON");
		G_flag = OFF;
	}
	HAL_LCD_u8_GoTo(3,0);
	HAL_LCD_u8_WriteString("0.Logout");
}

/************************************************************************
 * description : The home page displays the devices and temperature options
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_void_AppHomePage(void)
{
	u8 Loc_u8_counter = 0;
	while(1)
	{
		if((G_Keypad_Value == 0) && (G_LogoutFlag == 0))
		{
			G_LogoutFlag = 1;
			HAL_LCD_u8_ClearFullScreen();
			HAL_LCD_u8_GoTo(0,0);
			HAL_LCD_u8_WriteString("Logging Out");
			for(Loc_u8_counter = 0; Loc_u8_counter <= 3; Loc_u8_counter++)
			{
				HAL_LCD_u8_WriteCharacter('.');
				_delay_ms(5);
			}
			G_RunningDevicesIndicator = 1;
			break;
		}
		else if (G_Keypad_Value == 0)
		{
			break;
		}
		HAL_LCD_u8_ClearFullScreen();
		HAL_LCD_u8_GoTo(0,0);
		HAL_LCD_u8_WriteString("1.Devices");
		HAL_LCD_u8_GoTo(1,0);
		HAL_LCD_u8_WriteString("2.Temperature");
		HAL_LCD_u8_GoTo(3,0);
		HAL_LCD_u8_WriteString("0.Logout");
		HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
		if(G_Keypad_Value == 1)
		{
			APP_void_AppGetDeviceID();
		}
		else if(G_Keypad_Value == 2)
		{
			APP_TEMP_void_ApptemperaturePage();
		}
		else if(G_Keypad_Value == 0)
		{
			G_LogoutFlag = 1;
			HAL_LCD_u8_ClearFullScreen();
			HAL_LCD_u8_GoTo(0,0);
			HAL_LCD_u8_WriteString("Logging Out");
			for(Loc_u8_counter = 0; Loc_u8_counter <= 3; Loc_u8_counter++)
			{
				HAL_LCD_u8_WriteCharacter('.');
				_delay_ms(5);
			}
			G_RunningDevicesIndicator = 1;
			break;
		}
		else
		{
			HAL_LCD_u8_ClearFullScreen();
			HAL_LCD_u8_GoTo(0,0);
			HAL_LCD_u8_WriteString("Wrong Choice");
			_delay_ms(1000);
			APP_void_AppHomePage();
		}
	}
}

/************************************************************************
 * description : Take from the user the device number he wants to set
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_void_AppGetDeviceID(void)
{
	HAL_LCD_u8_ClearFullScreen();
	HAL_LCD_u8_GoTo(0,0);
	HAL_LCD_u8_WriteString("Enter Device ID:");
	HAL_LCD_u8_GoTo(2,0);
	HAL_LCD_u8_WriteString("0.Logout");
	HAL_LCD_u8_GoTo(2,10);
	HAL_LCD_u8_WriteString("7.BACK");
	HAL_LCD_u8_GoTo(3,0);
	HAL_LCD_u8_WriteString("8.HOME");
	HAL_LCD_u8_GoTo(1,0);
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 1)
	{
		APP_DEVICE1_u8_AppSetDeviceOne();
	}
	else if(G_Keypad_Value == 2)
	{
		APP_DEVICE2_u8_AppSetDeviceTwo();
	}
	else if(G_Keypad_Value == 3)
	{
		APP_DEVICE3_u8_AppSetDeviceThree();
	}
	else if(G_Keypad_Value == 4)
	{
		APP_DEVICE4_u8_AppSetDeviceFour();
	}
	else if(G_Keypad_Value == 5)
	{
		APP_DEVICE5_u8_AppSetDeviceFive();
	}
	else if((G_Keypad_Value == 7) || (G_Keypad_Value == 8) || (G_Keypad_Value == 0))
	{
		return;
	}
	else
	{
		HAL_LCD_u8_ClearFullScreen();
		HAL_LCD_u8_GoTo(0,0);
		HAL_LCD_u8_WriteString("Wrong Choice");
		_delay_ms(1000);
		APP_void_AppGetDeviceID();
	}
}

/************************************************************************
 * description : Set the device 1 as the user wants
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_DEVICE1_u8_AppSetDeviceOne(void)
{
	HAL_LCD_u8_ClearFullScreen();
	HAL_LCD_u8_GoTo(0,0);
	HAL_LCD_u8_WriteString("1.ON");
	HAL_LCD_u8_GoTo(0,10);
	HAL_LCD_u8_WriteString("2.OFF");
	HAL_LCD_u8_GoTo(1,0);
	HAL_LCD_u8_WriteString("3.TOGGLE");
	HAL_LCD_u8_GoTo(2,0);
	HAL_LCD_u8_WriteString("0.Logout");
	HAL_LCD_u8_GoTo(2,10);
	HAL_LCD_u8_WriteString("7.BACK");
	HAL_LCD_u8_GoTo(3,0);
	HAL_LCD_u8_WriteString("8.HOME");
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 1)
	{
		HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_ON);
		G_DeviceOneFlag = 1;
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('1');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('N');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
	}
	else if(G_Keypad_Value == 2)
	{
		HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_OFF);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('1');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('F');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
		G_DeviceOneFlag = 0;
	}
	else if(G_Keypad_Value == 3)
	{
		HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_TOG);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('1');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('T');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
		TOGGLE_BIT(G_DeviceOneFlag,PIN0);
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppHomePage();
	}
	else if (G_Keypad_Value == 7)
	{
		APP_void_AppGetDeviceID();
	}
	else if (G_Keypad_Value == 0)
	{
		return;
	}
	else
	{
		HAL_LCD_u8_ClearFullScreen();
		HAL_LCD_u8_GoTo(0,0);
		HAL_LCD_u8_WriteString("Wrong Choice");
		_delay_ms(1000);
		APP_DEVICE1_u8_AppSetDeviceOne();
	}
}

/************************************************************************
 * description : Set the device 2 as the user wants
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_DEVICE2_u8_AppSetDeviceTwo(void)
{
	HAL_LCD_u8_ClearFullScreen();
	HAL_LCD_u8_GoTo(0,0);
	HAL_LCD_u8_WriteString("1.ON");
	HAL_LCD_u8_GoTo(0,10);
	HAL_LCD_u8_WriteString("2.OFF");
	HAL_LCD_u8_GoTo(1,0);
	HAL_LCD_u8_WriteString("3.TOGGLE");
	HAL_LCD_u8_GoTo(2,0);
	HAL_LCD_u8_WriteString("0.Logout");
	HAL_LCD_u8_GoTo(2,10);
	HAL_LCD_u8_WriteString("7.BACK");
	HAL_LCD_u8_GoTo(3,0);
	HAL_LCD_u8_WriteString("8.HOME");
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 1)
	{
		HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_ON);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('2');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('N');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
		G_DeviceTwoFlag = 1;
	}
	else if(G_Keypad_Value == 2)
	{
		HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_OFF);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('2');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('F');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
		G_DeviceTwoFlag = 0;
	}
	else if(G_Keypad_Value == 3)
	{
		HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_TOG);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('2');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('T');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
		TOGGLE_BIT(G_DeviceTwoFlag,PIN0);
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppHomePage();
	}

	else if (G_Keypad_Value == 7)
	{
		APP_void_AppGetDeviceID();
	}
	else if (G_Keypad_Value == 0)
	{
		return;
	}
	else
	{
		HAL_LCD_u8_ClearFullScreen();
		HAL_LCD_u8_GoTo(0,0);
		HAL_LCD_u8_WriteString("Wrong Choice");
		_delay_ms(1000);
		APP_DEVICE2_u8_AppSetDeviceTwo();
	}
}

/************************************************************************
 * description : Set the device 3 as the user wants
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_DEVICE3_u8_AppSetDeviceThree(void)
{
	HAL_LCD_u8_ClearFullScreen();
	HAL_LCD_u8_GoTo(0,0);
	HAL_LCD_u8_ClearFullScreen();
	HAL_LCD_u8_GoTo(0,0);
	HAL_LCD_u8_WriteString("1.ON");
	HAL_LCD_u8_GoTo(0,10);
	HAL_LCD_u8_WriteString("2.OFF");
	HAL_LCD_u8_GoTo(1,0);
	HAL_LCD_u8_WriteString("3.TOGGLE");
	HAL_LCD_u8_GoTo(2,0);
	HAL_LCD_u8_WriteString("0.Logout");
	HAL_LCD_u8_GoTo(2,10);
	HAL_LCD_u8_WriteString("7.BACK");
	HAL_LCD_u8_GoTo(3,0);
	HAL_LCD_u8_WriteString("8.HOME");
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 1)
	{
		HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_ON);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('3');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('N');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
		G_DeviceThreeFlag = 1;
	}
	else if(G_Keypad_Value == 2)
	{
		HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_OFF);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('3');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('F');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
		G_DeviceThreeFlag = 0;
	}
	else if(G_Keypad_Value == 3)
	{
		HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_TOG);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('3');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('T');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
		TOGGLE_BIT(G_DeviceThreeFlag,PIN0);
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppHomePage();
	}

	else if (G_Keypad_Value == 7)
	{
		APP_void_AppGetDeviceID();
	}
	else if (G_Keypad_Value == 0)
	{
		return;
	}
	else
	{
		HAL_LCD_u8_ClearFullScreen();
		HAL_LCD_u8_GoTo(0,0);
		HAL_LCD_u8_WriteString("Wrong Choice");
		_delay_ms(1000);
		APP_DEVICE3_u8_AppSetDeviceThree();
	}
}

/************************************************************************
 * description : Set the device 4 as the user wants
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_DEVICE4_u8_AppSetDeviceFour(void)
{
	HAL_LCD_u8_ClearFullScreen();
	HAL_LCD_u8_GoTo(0,0);
	HAL_LCD_u8_WriteString("1.ON");
	HAL_LCD_u8_GoTo(0,10);
	HAL_LCD_u8_WriteString("2.OFF");
	HAL_LCD_u8_GoTo(1,0);
	HAL_LCD_u8_WriteString("3.TOGGLE");
	HAL_LCD_u8_GoTo(2,0);
	HAL_LCD_u8_WriteString("0.Logout");
	HAL_LCD_u8_GoTo(2,10);
	HAL_LCD_u8_WriteString("7.BACK");
	HAL_LCD_u8_GoTo(3,0);
	HAL_LCD_u8_WriteString("8.HOME");
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 1)
	{
		HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_ON);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('4');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('N');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
		G_DeviceFourFlag = 1;
	}
	else if(G_Keypad_Value == 2)
	{
		HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_OFF);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('4');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('F');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
		G_DeviceFourFlag = 0;
	}
	else if(G_Keypad_Value == 3)
	{
		HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_TOG);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('4');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('T');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
		TOGGLE_BIT(G_DeviceFourFlag,PIN0);
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppHomePage();
	}

	else if (G_Keypad_Value == 7)
	{
		APP_void_AppGetDeviceID();
	}
	else if (G_Keypad_Value == 0)
	{
		return;
	}
	else
	{
		HAL_LCD_u8_ClearFullScreen();
		HAL_LCD_u8_GoTo(0,0);
		HAL_LCD_u8_WriteString("Wrong Choice");
		_delay_ms(1000);
		APP_DEVICE4_u8_AppSetDeviceFour();
	}
}

/************************************************************************
 * description : Set the device 5 as the user wants
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_DEVICE5_u8_AppSetDeviceFive(void)
{
	HAL_LCD_u8_ClearFullScreen();
	HAL_LCD_u8_GoTo(0,0);
	HAL_LCD_u8_WriteString("1.ON");
	HAL_LCD_u8_GoTo(0,10);
	HAL_LCD_u8_WriteString("2.OFF");
	HAL_LCD_u8_GoTo(1,0);
	HAL_LCD_u8_WriteString("3.TOGGLE");
	HAL_LCD_u8_GoTo(2,0);
	HAL_LCD_u8_WriteString("0.Logout");
	HAL_LCD_u8_GoTo(2,10);
	HAL_LCD_u8_WriteString("7.BACK");
	HAL_LCD_u8_GoTo(3,0);
	HAL_LCD_u8_WriteString("8.HOME");
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 1)
	{
		HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_ON);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('5');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('N');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
		G_DeviceFiveFlag = 1;
	}
	else if(G_Keypad_Value == 2)
	{
		HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_OFF);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('5');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('F');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
		G_DeviceFiveFlag = 0;
	}
	else if(G_Keypad_Value == 3)
	{
		HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_TOG);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('5');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('T');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
		TOGGLE_BIT(G_DeviceFiveFlag,PIN0);
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppHomePage();
	}

	else if (G_Keypad_Value == 7)
	{
		APP_void_AppGetDeviceID();
	}
	else if (G_Keypad_Value == 0)
	{
		return;
	}
	else
	{
		HAL_LCD_u8_ClearFullScreen();
		HAL_LCD_u8_GoTo(0,0);
		HAL_LCD_u8_WriteString("Wrong Choice");
		_delay_ms(1000);
		APP_DEVICE5_u8_AppSetDeviceFive();
	}
}

/************************************************************************
 * description : Display Temperature as degrees Celsius.
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_TEMP_void_ApptemperaturePage()
{
	HAL_LCD_u8_ClearFullScreen();
	HAL_LCD_u8_GoTo(0,0);
	HAL_LCD_u8_WriteString("1.Temperature");
	HAL_LCD_u8_GoTo(1,0);
	HAL_LCD_u8_WriteString("2.Fan");
	HAL_LCD_u8_GoTo(2,0);
	HAL_LCD_u8_WriteString("0.Logout");
	HAL_LCD_u8_GoTo(2,10);
	HAL_LCD_u8_WriteString("7.BACK");
	HAL_LCD_u8_GoTo(3,0);
	HAL_LCD_u8_WriteString("8.HOME");
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 1)
	{
		APP_TEMP_void_AppDisplayTemperature();
	}
	else if(G_Keypad_Value == 2)
	{
		APP_FAN_void_AppSetFan();
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppHomePage();
	}
	else if (G_Keypad_Value == 7)
	{
		APP_void_AppHomePage();
	}
	else if (G_Keypad_Value == 0)
	{
		return;
	}
	else
	{
		HAL_LCD_u8_ClearFullScreen();
		HAL_LCD_u8_GoTo(0,0);
		HAL_LCD_u8_WriteString("Wrong Choice");
		_delay_ms(1000);
		APP_TEMP_void_ApptemperaturePage();
	}
}

void APP_TEMP_void_AppDisplayTemperature()
{
	u8 Value = LM35_Read();
	HAL_LCD_u8_ClearFullScreen();
	HAL_LCD_u8_WriteString("Temperature is:");
	HAL_LCD_u8_WriteNumber(Value);
	HAL_LCD_u8_GoTo(2,0);
	HAL_LCD_u8_WriteString("0.Logout");
	HAL_LCD_u8_GoTo(2,10);
	HAL_LCD_u8_WriteString("7.BACK");
	HAL_LCD_u8_GoTo(3,0);
	HAL_LCD_u8_WriteString("8.HOME");
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 8)
	{
		APP_void_AppHomePage();
	}
	else if (G_Keypad_Value == 7)
	{
		APP_TEMP_void_ApptemperaturePage();
	}
	else if (G_Keypad_Value == 0)
	{
		return;
	}
	else
	{
		HAL_LCD_u8_ClearFullScreen();
		HAL_LCD_u8_GoTo(0,0);
		HAL_LCD_u8_WriteString("Wrong Choice");
		_delay_ms(1000);
		APP_TEMP_void_AppDisplayTemperature();
	}
}
/************************************************************************
 * description : Set the Fan as the user wants
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_FAN_void_AppSetFan(void)
{
	HAL_LCD_u8_ClearFullScreen();
	HAL_LCD_u8_GoTo(0,0);
	HAL_LCD_u8_WriteString("1.ON");
	HAL_LCD_u8_GoTo(0,6);
	HAL_LCD_u8_WriteString("2.OFF");
	HAL_LCD_u8_GoTo(0,12);
	HAL_LCD_u8_WriteString("3.TOGGLE");
	HAL_LCD_u8_GoTo(1,0);
	HAL_LCD_u8_WriteString("4.Control Options");
	HAL_LCD_u8_GoTo(2,0);
	HAL_LCD_u8_WriteString("0.Logout");
	HAL_LCD_u8_GoTo(2,10);
	HAL_LCD_u8_WriteString("7.BACK");
	HAL_LCD_u8_GoTo(3,0);
	HAL_LCD_u8_WriteString("8.HOME");
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 1)
	{
		HAL_DCMOTOR_void_DcMotorClockWise(motor_speed);
		G_FanFlag = 1;
		G_FanFlagOff = 1;
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('F');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('N');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
	}
	else if(G_Keypad_Value == 2)
	{
		HAL_DCMOTOR_void_DcMotorStop();
		G_FanFlag = 0;
		G_FanFlagOn = 1;
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('F');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('F');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
	}
	else if(G_Keypad_Value == 3)
	{
		if(G_FanFlag == 0)
		{
			HAL_DCMOTOR_void_DcMotorClockWise(motor_speed);
			G_FanFlag = 1;
		}
		else if(G_FanFlag == 1)
		{
			HAL_DCMOTOR_void_DcMotorStop();
			G_FanFlag = 0;
		}
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('F');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
		G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('T');
		MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
		MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
	}
	else if(G_Keypad_Value == 4)
	{
		APP_FAN_void_AppFanControlOptions();
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppHomePage();
	}

	else if (G_Keypad_Value == 7)
	{
		APP_TEMP_void_ApptemperaturePage();
	}
	else if (G_Keypad_Value == 0)
	{
		return;
	}
	else
	{
		HAL_LCD_u8_ClearFullScreen();
		HAL_LCD_u8_GoTo(0,0);
		HAL_LCD_u8_WriteString("Wrong Choice");
		_delay_ms(1000);
		APP_FAN_void_AppSetFan();
	}
}

/************************************************************************
 * description : Displays control options to the user.
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_FAN_void_AppFanControlOptions(void)
{
	HAL_LCD_u8_ClearFullScreen();
	HAL_LCD_u8_GoTo(0,0);
	HAL_LCD_u8_WriteString("1.Automatic & Manual");
	HAL_LCD_u8_GoTo(1,0);
	HAL_LCD_u8_WriteString("2.Manual Only");
	HAL_LCD_u8_GoTo(2,0);
	HAL_LCD_u8_WriteString("0.Logout");
	HAL_LCD_u8_GoTo(2,10);
	HAL_LCD_u8_WriteString("7.BACK");
	HAL_LCD_u8_GoTo(3,0);
	HAL_LCD_u8_WriteString("8.HOME");
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 1)
	{
		APP_FAN_void_AppFanAutomaticAndManualControl();
	}
	else if(G_Keypad_Value == 2)
	{
		APP_FAN_void_AppFanManualOnlyControl();
	}
	else if(G_Keypad_Value == 0)
	{
		return;
	}
	else if(G_Keypad_Value == 7)
	{
		APP_FAN_void_AppSetFan();
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppHomePage();
	}
	else
	{
		HAL_LCD_u8_ClearFullScreen();
		HAL_LCD_u8_GoTo(0,0);
		HAL_LCD_u8_WriteString("Wrong Choice");
		_delay_ms(1000);
		APP_FAN_void_AppFanControlOptions();
	}
}

/************************************************************************
 * description : Makes control automatic and manual
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_FAN_void_AppFanAutomaticAndManualControl(void)
{
	G_FanControlFlag = 0;
	G_FanFlagOn = 0;
	G_FanFlagOff = 0;
	HAL_LCD_u8_ClearFullScreen();
	HAL_LCD_u8_GoTo(0,0);
	HAL_LCD_u8_WriteString("Fan is Controlled ");
	HAL_LCD_u8_GoTo(1,0);
	HAL_LCD_u8_WriteString("Automatic And Manual");
	HAL_LCD_u8_GoTo(2,0);
	HAL_LCD_u8_WriteString("0.Logout");
	HAL_LCD_u8_GoTo(2,10);
	HAL_LCD_u8_WriteString("7.BACK");
	HAL_LCD_u8_GoTo(3,0);
	HAL_LCD_u8_WriteString("8.HOME");
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 0)
	{
		return;
	}
	else if(G_Keypad_Value == 7)
	{
		APP_FAN_void_AppFanControlOptions();
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppHomePage();
	}
	else
	{
		HAL_LCD_u8_ClearFullScreen();
		HAL_LCD_u8_GoTo(0,0);
		HAL_LCD_u8_WriteString("Wrong Choice");
		_delay_ms(1000);
		APP_FAN_void_AppFanAutomaticAndManualControl();
	}
}

/************************************************************************
 * description : Makes control manual only
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_FAN_void_AppFanManualOnlyControl(void)
{
	G_FanControlFlag = 1;
	HAL_LCD_u8_ClearFullScreen();
	HAL_LCD_u8_GoTo(0,0);
	HAL_LCD_u8_WriteString("Fan is Controlled ");
	HAL_LCD_u8_GoTo(1,0);
	HAL_LCD_u8_WriteString("Manual Only");
	HAL_LCD_u8_GoTo(2,0);
	HAL_LCD_u8_WriteString("0.Logout");
	HAL_LCD_u8_GoTo(2,10);
	HAL_LCD_u8_WriteString("7.BACK");
	HAL_LCD_u8_GoTo(3,0);
	HAL_LCD_u8_WriteString("8.HOME");
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 0)
	{
		return;
	}
	else if(G_Keypad_Value == 7)
	{
		APP_FAN_void_AppFanControlOptions();
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppHomePage();
	}
	else
	{
		HAL_LCD_u8_ClearFullScreen();
		HAL_LCD_u8_GoTo(0,0);
		HAL_LCD_u8_WriteString("Wrong Choice");
		_delay_ms(1000);
		APP_FAN_void_AppFanManualOnlyControl();
	}
}

/************************************************************************
 * description : It reads the temperature and based on that it turns the fan on or off.
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_FAN_void_AppFanReadWithoutWrite(void)
{
	G_LM35 = LM35_Read();
	if(G_FanControlFlag == 0)
	{
		if((G_LM35 > TURN_DC_ON_TEMP) && (G_FanFlagOn == 0))
		{
			G_FanFlagOn = 1;
			G_FanFlag = 1;
			G_FanFlagOff = 0;
			HAL_DCMOTOR_void_DcMotorClockWise(motor_speed);
			G_RunningDevicesIndicator = 1;
			MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
			MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
			G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('F');
			MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
			MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
			G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('N');
			MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
			MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
		}
		else if((G_LM35 < TURN_DC_OFF_TEMP) && (G_FanFlagOff == 0))
		{
			G_FanFlagOff = 1;
			G_FanFlag = 0;
			G_FanFlagOn = 0;
			HAL_DCMOTOR_void_DcMotorStop();
			G_RunningDevicesIndicator = 1;
			MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
			MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
			G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('F');
			MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
			MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
			G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('F');
			MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
			MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
		}
		else if((G_LM35 > TURN_DC_OFF_TEMP) && (G_LM35 < TURN_DC_ON_TEMP))
		{
			G_FanFlagOn = 0;
			G_FanFlagOff = 0;
		}
	}
}
