#include "LcdUser_interface.h"
#include "LcdUser_config.h"
#include "LcdUser_private.h"



/*****************************************************************************************/
//u8 volatile G_flag;//to know if any device is on or not to write on lcd ("is"->if one device is in, "are" if two or more are on)
//u8 volatile G_flag1;//to know state of device1
//u8 volatile G_flag2;//to know state of device2
//u8 volatile G_flag3;//to know state of device3
//u8 volatile G_flag4;//to know state of device4
//u8 volatile G_flag5;//to know state of device5
//u8 volatile G_FanFlag;//to know state of fan
//u8 volatile G_FanFlagOn;//to know that fan is on
//u8 volatile G_FanFlagOff;//to know that fan is off
//u8 volatile G_FanControlFlag;//to know the control option that user select it from lcd
u8 volatile G_Mainflag;// to know if any device is on or not
u8 volatile G_LM35;
u8 volatile G_Keypad_Value;// to know the value of keypad that user select it
//u8 volatile G_u8_Value1;

extern union {
	u8 volatile GLOB_u8AllFlags;
	struct GLOB_u8Flags{
		u8 volatile GLOB_u8Flag_LED1 	:1;
		u8 volatile GLOB_u8Flag_LED2 	:1;
		u8 volatile GLOB_u8Flag_LED3 	:1;
		u8 volatile GLOB_u8Flag_LED4 	:1;
		u8 volatile GLOB_u8Flag_LED5	:1;
		u8 volatile GLOB_u8Flag_Dimmer 	:1;
		u8 volatile GLOB_u8Flag_AC 	 	:1;
		u8 volatile GLOB_u8Flag_Door 	:1;

	}Flags;
}State;

/************************************ Implementation Section ******************************/

/************************************************************************
 * description : to know which devices are working
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/

//Can be replaced by the union flags state.
void APP_DEVICES_void_AppGetAnyDeviceOn(void)
{
	HAL_LCD_u8_ClearFullScreen();
	HAL_LCD_u8_GoTo(0,0);
	if(State.GLOB_u8AllFlags != OFF )
	{
		HAL_LCD_u8_WriteString("Running: ");
		HAL_LCD_u8_GoTo(1,0);
		HAL_LCD_u8_WriteString("Lights: ");
		HAL_LCD_u8_GoTo(1,8);
//		if(State.GLOB_u8AllFlags <= 31 )
//		{
			if(State.Flags.GLOB_u8Flag_LED1 == ON)
			{
				HAL_LCD_u8_WriteCharacter('1');
				if(State.Flags.GLOB_u8Flag_LED2 == ON)
					HAL_LCD_u8_WriteString("&2");
				if(State.Flags.GLOB_u8Flag_LED3 == ON)
					HAL_LCD_u8_WriteString("&3");
				if(State.Flags.GLOB_u8Flag_LED4 == ON)
					HAL_LCD_u8_WriteString("&4");
				if(State.Flags.GLOB_u8Flag_LED5 == ON)
					HAL_LCD_u8_WriteString("&5");
			}
			else if (State.Flags.GLOB_u8Flag_LED2 == ON)
			{
				HAL_LCD_u8_WriteCharacter('2');
				if(State.Flags.GLOB_u8Flag_LED3 == ON)
					HAL_LCD_u8_WriteString("&3");
				if(State.Flags.GLOB_u8Flag_LED4 == ON)
					HAL_LCD_u8_WriteString("&4");
				if(State.Flags.GLOB_u8Flag_LED5 == ON)
					HAL_LCD_u8_WriteString("&5");
			}
			else if (State.Flags.GLOB_u8Flag_LED3 == ON)
			{
				HAL_LCD_u8_WriteCharacter('3');
				if(State.Flags.GLOB_u8Flag_LED4 == ON)
					HAL_LCD_u8_WriteString("&4");
				if(State.Flags.GLOB_u8Flag_LED5 == ON)
					HAL_LCD_u8_WriteString("&5");
			}
			else if (State.Flags.GLOB_u8Flag_LED4 == ON)
			{
				HAL_LCD_u8_WriteCharacter('4');
				if(State.Flags.GLOB_u8Flag_LED5 == ON)
					HAL_LCD_u8_WriteString("&5");
			}
			else if (State.Flags.GLOB_u8Flag_LED5 == ON)
			{
				HAL_LCD_u8_WriteCharacter('5');
			}


//		}
//		else
//		{
			if(State.Flags.GLOB_u8Flag_AC == ON)
			{

				HAL_LCD_u8_GoTo(2,0);
				if(State.GLOB_u8AllFlags <= 127 && State.GLOB_u8AllFlags != 64)
				{
					HAL_LCD_u8_WriteString("&Fan");
				}
				else
				{
					HAL_LCD_u8_WriteString("Fan");
				}
			}

//		}

	}
	else
	{
		HAL_LCD_u8_GoTo(0,0);
		HAL_LCD_u8_WriteString("All Devices");
		HAL_LCD_u8_GoTo(1,0);
		HAL_LCD_u8_WriteString("are OFF");
	}
	HAL_LCD_u8_GoTo(3,0);
	HAL_LCD_u8_WriteString("0.Logout");

//	if(State.Flags.GLOB_u8Flag_LED3 == ON)
//	{
//		if(State.GLOB_u8AllFlags == OFF)
//		{
//			HAL_LCD_u8_WriteCharacter("3");
//		}
//		else if(State.GLOB_u8AllFlags <= 7)
//		{
//			HAL_LCD_u8_WriteString("&3");
//		}
//	}
//	if(State.Flags.GLOB_u8Flag_LED4 == ON)
//	{
//		if(State.GLOB_u8AllFlags == OFF)
//		{
//			HAL_LCD_u8_WriteCharacter("4");
//		}
//		else if(State.GLOB_u8AllFlags <= 15)
//		{
//			HAL_LCD_u8_WriteString("&4");
//		}
//	}
//	if(State.Flags.GLOB_u8Flag_LED5 == ON)
//	{
//		if(State.GLOB_u8AllFlags == OFF)
//		{
//			HAL_LCD_u8_WriteCharacter("5");
//		}
//		else if(State.GLOB_u8AllFlags <= 31)
//		{
//			HAL_LCD_u8_WriteString("&5");
//		}
//	}

	//	else if(State.GLOB_u8AllFlags == 1 ||\
	//			State.GLOB_u8AllFlags == 2 ||\
	//			State.GLOB_u8AllFlags == 8 ||\
	//			State.GLOB_u8AllFlags == 16 ||\
	//			State.GLOB_u8AllFlags == 32 ||\
	//			State.GLOB_u8AllFlags == 64 ||\
	//			State.GLOB_u8AllFlags == 128 )
	//	{
	//		//Look for a logic here to fix that.
	//		HAL_LCD_u8_GoTo(1,0);
	//		HAL_LCD_u8_WriteString("is ON");
	////		G_flag = OFF;
	//	}
	//	else if(State.GLOB_u8AllFlags <= 255)
	//	{
	//		HAL_LCD_u8_GoTo(1,0);
	//		HAL_LCD_u8_WriteString("are ON");
	//
	////		G_flag = OFF;
	//	}
}

/************************************************************************
 * description : Set the device 1 as the user wants
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/

void APP_Device_Messeges(void)
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

}
void APP_DEVICE1_u8_AppSetDevice1(void)
{
	APP_Device_Messeges();
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 1)
	{
		HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_ON);
		State.Flags.GLOB_u8Flag_LED1 = 1;
	}
	else if(G_Keypad_Value == 2)
	{
		HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_OFF);
		State.Flags.GLOB_u8Flag_LED1 = 0;
	}
	else if(G_Keypad_Value == 3)
	{
		HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_TOG);
		State.Flags.GLOB_u8Flag_LED1 = !State.Flags.GLOB_u8Flag_LED1;
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppAfterFirstChoice();
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
		APP_DEVICE1_u8_AppSetDevice1();
	}
}

/************************************************************************
 * description : Set the device 2 as the user wants
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_DEVICE2_u8_AppSetDevice2(void)
{
	APP_Device_Messeges();
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 1)
	{
		HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_ON);
		State.Flags.GLOB_u8Flag_LED2 = 1;
	}
	else if(G_Keypad_Value == 2)
	{
		HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_OFF);
		State.Flags.GLOB_u8Flag_LED2 = 0;
	}
	else if(G_Keypad_Value == 3)
	{
		HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_TOG);
		State.Flags.GLOB_u8Flag_LED2 = !State.Flags.GLOB_u8Flag_LED2;
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppAfterFirstChoice();
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
		APP_DEVICE2_u8_AppSetDevice2();
	}
}

/************************************************************************
 * description : Set the device 3 as the user wants
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_DEVICE3_u8_AppSetDevice3(void)
{
	APP_Device_Messeges();
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 1)
	{
		HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_ON);
		State.Flags.GLOB_u8Flag_LED3 = 1;
	}
	else if(G_Keypad_Value == 2)
	{
		HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_OFF);
		State.Flags.GLOB_u8Flag_LED3 = 0;
	}
	else if(G_Keypad_Value == 3)
	{
		HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_TOG);
		State.Flags.GLOB_u8Flag_LED3 = !State.Flags.GLOB_u8Flag_LED3;
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppAfterFirstChoice();
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
		APP_DEVICE3_u8_AppSetDevice3();
	}
}

/************************************************************************
 * description : Set the device 4 as the user wants
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_DEVICE4_u8_AppSetDevice4(void)
{
	APP_Device_Messeges();
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 1)
	{
		HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_ON);
		State.Flags.GLOB_u8Flag_LED4 = 1;
	}
	else if(G_Keypad_Value == 2)
	{
		HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_OFF);
		State.Flags.GLOB_u8Flag_LED4 = 0;
	}
	else if(G_Keypad_Value == 3)
	{
		HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_TOG);
		State.Flags.GLOB_u8Flag_LED4 = !State.Flags.GLOB_u8Flag_LED4;
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppAfterFirstChoice();
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
		APP_DEVICE4_u8_AppSetDevice4();
	}
}

/************************************************************************
 * description : Set the device 5 as the user wants
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_DEVICE5_u8_AppSetDevice5(void)
{
	APP_Device_Messeges();
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 1)
	{
		HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_ON);
		State.Flags.GLOB_u8Flag_LED5 = 1;
	}
	else if(G_Keypad_Value == 2)
	{
		HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_OFF);
		State.Flags.GLOB_u8Flag_LED5 = 0;
	}
	else if(G_Keypad_Value == 3)
	{
		HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_TOG);
		State.Flags.GLOB_u8Flag_LED5 = !State.Flags.GLOB_u8Flag_LED5;
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppAfterFirstChoice();
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
		APP_DEVICE5_u8_AppSetDevice5();
	}
}

/************************************************************************
 * description : Display Temperature as degrees Celsius.
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_TEMP_void_AppDisplayTemperature()
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
			APP_void_AppAfterFirstChoice();
		}
		else if (G_Keypad_Value == 7)
		{
			APP_TEMP_void_AppDisplayTemperature();
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
			APP_FAN_void_AppFanSet();
		}
	}
	else if(G_Keypad_Value == 2)
	{
		APP_FAN_void_AppFanSet();
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppAfterFirstChoice();
	}
	else if (G_Keypad_Value == 7)
	{
		APP_void_AppAfterFirstChoice();
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
		APP_FAN_void_AppFanSet();
	}
}

/************************************************************************
 * description : User can control FAN manually.
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_FAN_void_AppFanManually(void)
{
	MCAL_TIMER_Timer0_InterruptOVF_Disable(); //To stop it from automatically controlling the fan.

	APP_Device_Messeges();
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);

	if(G_Keypad_Value == 1)
	{

		HAL_DCMOTOR_void_DcMotorClockWise(motor_speed);
		State.Flags.GLOB_u8Flag_AC = 1;
	}
	else if(G_Keypad_Value == 2)
	{
		HAL_DCMOTOR_void_DcMotorStop();
		State.Flags.GLOB_u8Flag_AC = 0;
	}
	else if(G_Keypad_Value == 3)
	{
		if(State.Flags.GLOB_u8Flag_AC)
		{
			HAL_DCMOTOR_void_DcMotorStop();
		}
		else if(State.Flags.GLOB_u8Flag_AC == 0)
		{
			HAL_DCMOTOR_void_DcMotorClockWise(motor_speed);
		}
		State.Flags.GLOB_u8Flag_AC = !State.Flags.GLOB_u8Flag_AC;
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppAfterFirstChoice();
	}

	else if (G_Keypad_Value == 7)
	{
		APP_TEMP_void_AppDisplayTemperature();
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
		APP_FAN_void_AppFanSet();
	}

}
/************************************************************************
 * description : Set the Fan as the user wants
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_FAN_void_AppFanSet(void)
{
	HAL_LCD_u8_ClearFullScreen();
	HAL_LCD_u8_GoTo(0,0);
	HAL_LCD_u8_WriteString("1.MANUAL");
	HAL_LCD_u8_GoTo(1,0);
	HAL_LCD_u8_WriteString("2.AUTO");
	HAL_LCD_u8_GoTo(2,0);
	HAL_LCD_u8_WriteString("0.Logout");
	HAL_LCD_u8_GoTo(2,10);
	HAL_LCD_u8_WriteString("7.BACK");
	HAL_LCD_u8_GoTo(3,0);
	HAL_LCD_u8_WriteString("8.HOME");
	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value == 1)
	{
		APP_FAN_void_AppFanManually();
	}
	else if(G_Keypad_Value == 2)
	{
		//Enabling This interrupt causes the fan to be controlled automatically and its implemented in "SmartHome_interface.c" file.
		MCAL_TIMER_Timer0_InterruptOVF_Enable();
	}
	else if(G_Keypad_Value == 8)
	{
		APP_void_AppAfterFirstChoice();
	}

	else if (G_Keypad_Value == 7)
	{
		APP_TEMP_void_AppDisplayTemperature();
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
		//remove this recursion.
		APP_FAN_void_AppFanSet();
	}
}

/************************************************************************
 * description : The home page displays the devices and temperature options
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
void APP_void_AppAfterFirstChoice(void)
{
	while(1)
	{
		//		if((G_Keypad_Value == 0) && (G_Mainflag == 0))
		//		{
		//			G_Mainflag = 1;
		//			HAL_LCD_u8_ClearFullScreen();
		//			HAL_LCD_u8_GoTo(0,0);
		//			HAL_LCD_u8_WriteString("Logging Out");
		//			HAL_LCD_u8_WriteCharacter('.');
		//			_delay_ms(5);
		//			HAL_LCD_u8_WriteCharacter('.');
		//			_delay_ms(5);
		//			HAL_LCD_u8_WriteCharacter('.');
		//			_delay_ms(5);
		//			//m = 1;
		//			break;
		//		}
		//		else if (G_Keypad_Value == 0)
		//		{
		//			break;
		//		}
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
			APP_TEMP_void_AppDisplayTemperature();
		}
		else if(G_Keypad_Value == 0)
		{
			G_Mainflag = 1;
			HAL_LCD_u8_ClearFullScreen();
			HAL_LCD_u8_GoTo(0,0);
			HAL_LCD_u8_WriteString("Logging Out");
			HAL_LCD_u8_WriteCharacter('.');
			_delay_ms(5);
			HAL_LCD_u8_WriteCharacter('.');
			_delay_ms(5);
			HAL_LCD_u8_WriteCharacter('.');
			_delay_ms(5);
			//m = 1;
			break;
		}
		else
		{
			HAL_LCD_u8_ClearFullScreen();
			HAL_LCD_u8_GoTo(0,0);
			HAL_LCD_u8_WriteString("Wrong Choice");
			_delay_ms(1000);
			APP_void_AppAfterFirstChoice();
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
		APP_DEVICE1_u8_AppSetDevice1();
	}
	else if(G_Keypad_Value == 2)
	{
		APP_DEVICE2_u8_AppSetDevice2();
	}
	else if(G_Keypad_Value == 3)
	{
		APP_DEVICE3_u8_AppSetDevice3();
	}
	else if(G_Keypad_Value == 4)
	{
		APP_DEVICE4_u8_AppSetDevice4();
	}
	else if(G_Keypad_Value == 5)
	{
		APP_DEVICE5_u8_AppSetDevice5();
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
 * description : Displays control options to the user.
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
//void APP_FAN_void_AppFanControlOptions(void)
//{
//	HAL_LCD_u8_ClearFullScreen();
//	HAL_LCD_u8_GoTo(0,0);
//	HAL_LCD_u8_WriteString("1.Automatic & Manual");
//	HAL_LCD_u8_GoTo(1,0);
//	HAL_LCD_u8_WriteString("2.Manual Only");
//	HAL_LCD_u8_GoTo(2,0);
//	HAL_LCD_u8_WriteString("0.Logout");
//	HAL_LCD_u8_GoTo(2,10);
//	HAL_LCD_u8_WriteString("7.BACK");
//	HAL_LCD_u8_GoTo(3,0);
//	HAL_LCD_u8_WriteString("8.HOME");
//	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
//	if(G_Keypad_Value == 1)
//	{
//		APP_FAN_void_AppFanAutomaticAndManualControl();
//	}
//	else if(G_Keypad_Value == 2)
//	{
//		APP_FAN_void_AppFanManualOnlyControl();
//	}
//	else if(G_Keypad_Value == 0)
//	{
//		return;
//	}
//	else if(G_Keypad_Value == 7)
//	{
//		APP_FAN_void_AppFanSet();
//	}
//	else if(G_Keypad_Value == 8)
//	{
//		APP_void_AppAfterFirstChoice();
//	}
//	else
//	{
//		HAL_LCD_u8_ClearFullScreen();
//		HAL_LCD_u8_GoTo(0,0);
//		HAL_LCD_u8_WriteString("Wrong Choice");
//		_delay_ms(1000);
//		APP_FAN_void_AppFanControlOptions();
//	}
//}
//
///************************************************************************
// * description : Makes control automatic and manual
// * INPUT Arg   : No Args
// * RETURN      : No Return
// * **********************************************************************
// **/
//void APP_FAN_void_AppFanAutomaticAndManualControl(void)
//{
//	G_FanControlFlag = 0;
//	G_FanFlagOn = 0;
//	G_FanFlagOff = 0;
//	HAL_LCD_u8_ClearFullScreen();
//	HAL_LCD_u8_GoTo(0,0);
//	HAL_LCD_u8_WriteString("Fan is Controlled ");
//	HAL_LCD_u8_GoTo(1,0);
//	HAL_LCD_u8_WriteString("Automatic And Manual");
//	HAL_LCD_u8_GoTo(2,0);
//	HAL_LCD_u8_WriteString("0.Logout");
//	HAL_LCD_u8_GoTo(2,10);
//	HAL_LCD_u8_WriteString("7.BACK");
//	HAL_LCD_u8_GoTo(3,0);
//	HAL_LCD_u8_WriteString("8.HOME");
//	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
//	if(G_Keypad_Value == 0)
//	{
//		return;
//	}
//	else if(G_Keypad_Value == 7)
//	{
//		APP_FAN_void_AppFanControlOptions();
//	}
//	else if(G_Keypad_Value == 8)
//	{
//		APP_void_AppAfterFirstChoice();
//	}
//	else
//	{
//		HAL_LCD_u8_ClearFullScreen();
//		HAL_LCD_u8_GoTo(0,0);
//		HAL_LCD_u8_WriteString("Wrong Choice");
//		_delay_ms(1000);
//		APP_FAN_void_AppFanAutomaticAndManualControl();
//	}
//}
//
///************************************************************************
// * description : Makes control manual only
// * INPUT Arg   : No Args
// * RETURN      : No Return
// * **********************************************************************
// **/
//void APP_FAN_void_AppFanManualOnlyControl(void)
//{
//	G_FanControlFlag = 1;
//	HAL_LCD_u8_ClearFullScreen();
//	HAL_LCD_u8_GoTo(0,0);
//	HAL_LCD_u8_WriteString("Fan is Controlled ");
//	HAL_LCD_u8_GoTo(1,0);
//	HAL_LCD_u8_WriteString("Manual Only");
//	HAL_LCD_u8_GoTo(2,0);
//	HAL_LCD_u8_WriteString("0.Logout");
//	HAL_LCD_u8_GoTo(2,10);
//	HAL_LCD_u8_WriteString("7.BACK");
//	HAL_LCD_u8_GoTo(3,0);
//	HAL_LCD_u8_WriteString("8.HOME");
//	HAL_KEYPAD_u8_KaypadButton(&G_Keypad_Value);
//	if(G_Keypad_Value == 0)
//	{
//		return;
//	}
//	else if(G_Keypad_Value == 7)
//	{
//		APP_FAN_void_AppFanControlOptions();
//	}
//	else if(G_Keypad_Value == 8)
//	{
//		APP_void_AppAfterFirstChoice();
//	}
//	else
//	{
//		HAL_LCD_u8_ClearFullScreen();
//		HAL_LCD_u8_GoTo(0,0);
//		HAL_LCD_u8_WriteString("Wrong Choice");
//		_delay_ms(1000);
//		APP_FAN_void_AppFanManualOnlyControl();
//	}
//}

/************************************************************************
 * description : It reads the temperature and based on that it turns the fan on or off.
 * INPUT Arg   : No Args
 * RETURN      : No Return
 * **********************************************************************
 **/
