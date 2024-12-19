/*********************************************
 * Author:          Mohamed.A.Ewis
 * Creation Data:   7 NOV, 2023
 * Version:         v1.0
 * Compiler:        GNU GCC
 ********************************************/
/*********************************************
 * Version      Date                  Author                  Description
 * v1.0         7 NOV, 2023       Mohamed.A.Ewis          Initial Creation
*********************************************/

/*******************************Includes Section *****************************************/

#include "..\..\MCAL\SPI\SPI_interface.h"
#include "..\..\HAL\KEYPAD\KEYPAD_interface.h"
#include "..\..\HAL\LCD\LCD_interface.h"
#include "..\..\HAL\Buzzer\Buzzer.h"

#include "PASSWORD_interface.h"
#include "PASSWORD_config.h"
#include "PASSWORD_private.h"

/*****************************************************************************************/

extern u8 volatile G_RecieveValue;

/************************************ Implementation Section ******************************/

/************************************************************************
 * description : PASSWORD Initializaton
 * INPUT Arg   : No Args
 * RETURN      : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/
STD_TYPE APP_PASSWORD_u8_AppGetPasswordInit(void)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	Loc_u8_Retval = HAL_KEYPAD_u8_KaypadInit();
	Loc_u8_Retval = HAL_LCD_u8_LcdInit();
	return Loc_u8_Retval;
}

/************************************************************************
 * description : PASSWORD Implentaion
 * INPUT Arg   : No Args
 * RETURN      : No
 * **********************************************************************
 **/

/*u16 APP_USERID_u16_AppUserID()
{
	u8 Loc_u8_Pass[4] = {0};
	u8 index = 0;
	u32 Loc_32_CheckPass = 0;
	u8 Loc_u8_Flag = 0;
	HAL_LCD_u8_ClearFullScreen();
	while(1)
	{
		HAL_LCD_u8_ClearFullScreen();
		HAL_LCD_u8_WriteString("Enter User ID :");
		HAL_LCD_u8_GoTo(1,0);
		for(index = 0; index <= 3; index++)
		{
			HAL_KEYPAD_u8_KaypadButton1(&Loc_u8_Pass[index]);
			if(Loc_u8_Pass[index] == 'N')
			{
				index--;
				HAL_LCD_u8_ClearCharacter(1,index);
				HAL_LCD_u8_GoTo(1,index);
				index--;
			}
			else
			{
				HAL_LCD_u8_WriteNumber(Loc_u8_Pass[index]);
			}
		}
		Loc_32_CheckPass = Loc_u8_Pass[0]*10 + Loc_u8_Pass[1];
		Loc_32_CheckPass = Loc_32_CheckPass*10 + Loc_u8_Pass[2];
		Loc_32_CheckPass = Loc_32_CheckPass*10 + Loc_u8_Pass[3];
		if(Loc_32_CheckPass == USER_ID)
		{
			HAL_LCD_u8_ClearFullScreen();
			HAL_LCD_u8_GoTo(1,0);
			HAL_Buzzer_u8BuzzerMode(Buzzer_Port,Buzzer_Pin,Buzzer_OFF);
			break;
		}
		else
		{
			HAL_LCD_u8_ClearFullScreen();
			HAL_LCD_u8_GoTo(1,0);
			HAL_LCD_u8_WriteString("Wrong ID");
			Loc_u8_Flag++;
			if(Loc_u8_Flag == 3)
			{
				HAL_Buzzer_u8BuzzerMode(Buzzer_Port,Buzzer_Pin,Buzzer_ON);
			}
			_delay_ms(1000);
		}
	}
}
void APP_PASSWORD_u8_AppGetPassword(void)
{
	u8 Loc_u8_Pass[4] = {0};
	u8 index = 0;
	u32 Loc_32_CheckPass = 0;
	u8 Loc_u8_Flag = 0;
	HAL_LCD_u8_ClearFullScreen();
	while(1)
	{
		HAL_LCD_u8_ClearFullScreen();
		HAL_LCD_u8_WriteString("Enter Password :");
		HAL_LCD_u8_GoTo(1,0);
		for(index = 0; index <= 3; index++)
		{
			HAL_KEYPAD_u8_KaypadButton1(&Loc_u8_Pass[index]);
			if(Loc_u8_Pass[index] == 'N')
			{
				index--;
				HAL_LCD_u8_ClearCharacter(1,index);
				HAL_LCD_u8_GoTo(1,index);
				index--;
			}
			else
			{
				HAL_LCD_u8_WriteNumber(Loc_u8_Pass[index]);
			}
		}
		Loc_32_CheckPass = Loc_u8_Pass[0]*10 + Loc_u8_Pass[1];
		Loc_32_CheckPass = Loc_32_CheckPass*10 + Loc_u8_Pass[2];
		Loc_32_CheckPass = Loc_32_CheckPass*10 + Loc_u8_Pass[3];
		if(Loc_32_CheckPass == PASSWORD)
		{
			HAL_LCD_u8_ClearFullScreen();
			HAL_LCD_u8_GoTo(1,0);
			HAL_LCD_u8_WriteString("Welcome !!!");
			HAL_Buzzer_u8BuzzerMode(Buzzer_Port,Buzzer_Pin,Buzzer_OFF);
			break;
		}
		else
		{
			HAL_LCD_u8_ClearFullScreen();
			HAL_LCD_u8_GoTo(1,0);
			HAL_LCD_u8_WriteString("Wrong Password");
			Loc_u8_Flag++;
			if(Loc_u8_Flag == 3)
			{
				HAL_Buzzer_u8BuzzerMode(Buzzer_Port,Buzzer_Pin,Buzzer_ON);
			}
			_delay_ms(1000);
		}
	}
}*/

u16 APP_USERID_u8_AppUserID(void)
{
	u8 Loc_u8_Pass[4] = {0};
	u8 index = 0;
	u16 Loc_32_CheckPass = 0;
	u8 Loc_u8_Flag = 0;
	HAL_LCD_u8_ClearFullScreen();
	while(1)
	{
		HAL_LCD_u8_ClearFullScreen();
		HAL_LCD_u8_WriteString("Enter User ID :");
		HAL_LCD_u8_GoTo(1,0);
		for(index = 0; index <= 3; index++)
		{
			HAL_KEYPAD_u8_KaypadButton1(&Loc_u8_Pass[index]);
			if(Loc_u8_Pass[index] == 'N')
			{
				index--;
				HAL_LCD_u8_ClearCharacter(1,index);
				HAL_LCD_u8_GoTo(1,index);
				index--;
			}
			else
			{
				if(Loc_u8_Pass[index] > NINE)
				{
					index--;
				}
				else
				{
					HAL_LCD_u8_WriteNumber(Loc_u8_Pass[index]);
				}
			}
		}
		Loc_32_CheckPass = Loc_u8_Pass[0]*10 + Loc_u8_Pass[1];
		Loc_32_CheckPass = Loc_32_CheckPass*10 + Loc_u8_Pass[2];
		Loc_32_CheckPass = Loc_32_CheckPass*10 + Loc_u8_Pass[3];
		if(Check_UserID((u16)Loc_32_CheckPass) != USER_NOT_FOUND)
		{
			HAL_LCD_u8_ClearFullScreen();
			HAL_LCD_u8_GoTo(1,0);
			HAL_Buzzer_u8BuzzerMode(Buzzer_Port,Buzzer_Pin,Buzzer_OFF);
			MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
			MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
			G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('B');
			MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
			MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
			G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('F');
			MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
			MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
			return Loc_32_CheckPass;
		}
		else
		{
			HAL_LCD_u8_ClearFullScreen();
			HAL_LCD_u8_GoTo(1,0);
			HAL_LCD_u8_WriteString("Wrong ID");
			Loc_u8_Flag++;
			if(Loc_u8_Flag == 3)
			{
				HAL_Buzzer_u8BuzzerMode(Buzzer_Port,Buzzer_Pin,Buzzer_ON);
				MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
				MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
				G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('B');
				MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
				MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
				G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('N');
				MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
				MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
			}
			_delay_ms(1000);
		}
	}
}
void APP_PASSWORD_u8_AppGetPassword(u16 Loc_32_CheckID)
{
	u8 Loc_u8_Pass[4] = {0};
	u8 index = 0;
	u16 Loc_32_CheckPass = 0;
	u8 Loc_u8_Flag = 0;
	HAL_LCD_u8_ClearFullScreen();
	while(1)
	{
		HAL_LCD_u8_ClearFullScreen();
		HAL_LCD_u8_WriteString("Enter Password :");
		HAL_LCD_u8_GoTo(1,0);
		for(index = 0; index <= 3; index++)
		{
			HAL_KEYPAD_u8_KaypadButton1(&Loc_u8_Pass[index]);
			if(Loc_u8_Pass[index] == 'N')
			{
				index--;
				HAL_LCD_u8_ClearCharacter(1,index);
				HAL_LCD_u8_GoTo(1,index);
				index--;
			}
			else
			{
				if(Loc_u8_Pass[index] > NINE)
				{
					index--;
				}
				else
				{
					HAL_LCD_u8_WriteNumber(Loc_u8_Pass[index]);
				}
			}
		}
		Loc_32_CheckPass = Loc_u8_Pass[0]*10 + Loc_u8_Pass[1];
		Loc_32_CheckPass = Loc_32_CheckPass*10 + Loc_u8_Pass[2];
		Loc_32_CheckPass = Loc_32_CheckPass*10 + Loc_u8_Pass[3];
		if(Check_UserPassword(Loc_32_CheckID,(u16)Loc_32_CheckPass) == PASSWORD_MATCHED)
		{
			HAL_LCD_u8_ClearFullScreen();
			HAL_LCD_u8_GoTo(1,0);
			HAL_LCD_u8_WriteString("Welcome !!!");
			HAL_Buzzer_u8BuzzerMode(Buzzer_Port,Buzzer_Pin,Buzzer_OFF);
			MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
			MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
			G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('B');
			MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
			MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
			G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('F');
			MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
			MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
			break;
		}
		else
		{
			HAL_LCD_u8_ClearFullScreen();
			HAL_LCD_u8_GoTo(1,0);
			HAL_LCD_u8_WriteString("Wrong Password");
			Loc_u8_Flag++;
			if(Loc_u8_Flag == 3)
			{
				HAL_Buzzer_u8BuzzerMode(Buzzer_Port,Buzzer_Pin,Buzzer_ON);
				MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_HIGH);
				MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
				G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('B');
				MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
				MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_LOW);
				G_RecieveValue = MCAL_SPI_MASTER_u8_SpiMaster_Transceive('N');
				MCAL_DIO_u8SetPinValue(SS_PORT,SS_PIN,PIN_HIGH);
				MCAL_DIO_u8SetPinValue(PortB,PIN2,PIN_LOW);
			}
			_delay_ms(1000);
		}
	}
}
