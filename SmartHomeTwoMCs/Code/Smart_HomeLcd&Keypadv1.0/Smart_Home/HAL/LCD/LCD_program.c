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


#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"

/*****************************************************************************************/



/************************************ Implementation Section ******************************/

/************************************************************************
 * description : KEYPAD Initialize Its Pin As OUTPUT
 * INPUT Arg   : No Args
 * RETURN      : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/

STD_TYPE HAL_LCD_u8_LcdPinInit(u8 Loc_u8_LcdPortID, u8 Loc_u8_LcdPinID)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	if(Loc_u8_LcdPortID <= PortD && Loc_u8_LcdPinID <= PIN7)
	{
		Loc_u8_Retval = MCAL_DIO_u8SetPinDirection(Loc_u8_LcdPortID, Loc_u8_LcdPinID, PIN_OUTPUT);
	}
	else
	{
		//Do Nothing
	}
	return Loc_u8_Retval;
}

/************************************************************************
 * description : KEYPAD Initialization
 * INPUT Arg   : No Args
 * RETURN      : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/
STD_TYPE HAL_LCD_u8_LcdInit(void)
{
	u8 Loc_u8_Retval = E_NOT_OK;
#if ((LCD_CONTROL_PORT == NC) && (LCD_DATA_PORT == NC))
	Loc_u8_Retval  = HAL_LCD_u8_LcdPinInit(LCD_RS_PORT, LCD_RS_PIN);
	Loc_u8_Retval |= HAL_LCD_u8_LcdPinInit(LCD_RW_PORT, LCD_RW_PIN);
	Loc_u8_Retval |= HAL_LCD_u8_LcdPinInit(LCD_EN_PORT, LCD_EN_PIN);
	Loc_u8_Retval |= HAL_LCD_u8_LcdPinInit(LCD_D4_PORT, LCD_D4_PIN);
	Loc_u8_Retval |= HAL_LCD_u8_LcdPinInit(LCD_D5_PORT, LCD_D5_PIN);
	Loc_u8_Retval |= HAL_LCD_u8_LcdPinInit(LCD_D6_PORT, LCD_D6_PIN);
	Loc_u8_Retval |= HAL_LCD_u8_LcdPinInit(LCD_D7_PORT, LCD_D7_PIN);
	Loc_u8_Retval |= HAL_u8_LCD_4BitModeInit();
#elif ((LCD_CONTROL_PORT <= PortD) && (LCD_DATA_PORT <= PortD))
	Loc_u8_Retval  = HAL_LCD_u8_LcdPinInit(LCD_CONTROL_PORT, LCD_RS_PIN);
	Loc_u8_Retval |= HAL_LCD_u8_LcdPinInit(LCD_CONTROL_PORT, LCD_RW_PIN);
	Loc_u8_Retval |= HAL_LCD_u8_LcdPinInit(LCD_CONTROL_PORT, LCD_EN_PIN);
	Loc_u8_Retval |= HAL_LCD_u8_LcdPinInit(LCD_DATA_PORT, LCD_D4_PIN);
	Loc_u8_Retval |= HAL_LCD_u8_LcdPinInit(LCD_DATA_PORT, LCD_D5_PIN);
	Loc_u8_Retval |= HAL_LCD_u8_LcdPinInit(LCD_DATA_PORT, LCD_D6_PIN);
	Loc_u8_Retval |= HAL_LCD_u8_LcdPinInit(LCD_DATA_PORT, LCD_D7_PIN);
	Loc_u8_Retval |= HAL_u8_LCD_4BitModeInit();
#else
	#error ("Error Configurations")
#endif
	return Loc_u8_Retval;
}

/************************************************************************
 * description : Command Initialization
 * INPUT Arg   : No Args
 * RETURN      : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/
STD_TYPE HAL_LCD_u8_SendCommandInit(void)
{
	u8 Loc_u8_Retval = E_NOT_OK;
#if ((LCD_CONTROL_PORT == NC) && (LCD_DATA_PORT == NC))
	Loc_u8_Retval  = MCAL_DIO_u8SetPinValue(LCD_RS_PORT, LCD_RS_PIN, PIN_LOW);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_RW_PORT, LCD_RW_PIN, PIN_LOW);
#elif ((LCD_CONTROL_PORT <= PortD) && (LCD_DATA_PORT <= PortD))
	Loc_u8_Retval  = MCAL_DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, PIN_LOW);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, PIN_LOW);
#else
	#error ("Error Configurations")
#endif
	return Loc_u8_Retval;
}

/************************************************************************
 * description : Send Instructions to LCD
 * INPUT Arg   : Value of Instruction
 * RETURN      : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/
STD_TYPE HAL_LCD_u8_SendCommand(u8 Loc_u8_Command)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	Loc_u8_Retval = HAL_LCD_u8_SendCommandInit();
#if ((LCD_CONTROL_PORT == NC) && (LCD_DATA_PORT == NC))
	Loc_u8_Retval  = MCAL_DIO_u8SetPinValue(LCD_D4_PORT,LCD_D4_PIN,GET_BIT(Loc_u8_Command,4));
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_D5_PORT,LCD_D5_PIN,GET_BIT(Loc_u8_Command,5));
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_D6_PORT,LCD_D6_PIN,GET_BIT(Loc_u8_Command,6));
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_D7_PORT,LCD_D7_PIN,GET_BIT(Loc_u8_Command,7));
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_EN_PORT, LCD_EN_PIN, PIN_HIGH);
	_delay_ms(10);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_EN_PORT, LCD_EN_PIN, PIN_LOW);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_D4_PORT,LCD_D4_PIN,GET_BIT(Loc_u8_Command<<4,4));
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_D5_PORT,LCD_D5_PIN,GET_BIT(Loc_u8_Command<<4,5));
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_D6_PORT,LCD_D6_PIN,GET_BIT(Loc_u8_Command<<4,6));
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_D7_PORT,LCD_D7_PIN,GET_BIT(Loc_u8_Command<<4,7));
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_EN_PORT, LCD_EN_PIN, PIN_HIGH);
	_delay_ms(10);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_EN_PORT, LCD_EN_PIN, PIN_LOW);
	_delay_ms(10);
#elif ((LCD_CONTROL_PORT <= PortD) && (LCD_DATA_PORT <= PortD))
	Loc_u8_Retval = MCAL_DIO_u8SetPortValue(LCD_DATA_PORT,Loc_u8_Command);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_EN_PORT, LCD_EN_PIN, PIN_HIGH);
	_delay_ms(10);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, PIN_LOW);
	Loc_u8_Retval |= MCAL_DIO_u8SetPortValue(LCD_DATA_PORT,Loc_u8_Command<<4);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, PIN_HIGH);
	_delay_ms(10);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, PIN_LOW);
	_delay_ms(10);
#else
	#error ("Error Configurations")
#endif
	return Loc_u8_Retval;
}

/************************************************************************
 * description : Data Initialization
 * INPUT Arg   : No Args
 * RETURN      : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/
STD_TYPE HAL_LCD_u8_SendDataInit(void)
{
	u8 Loc_u8_Retval = E_NOT_OK;
#if ((LCD_CONTROL_PORT == NC) && (LCD_DATA_PORT == NC))
	Loc_u8_Retval  = MCAL_DIO_u8SetPinValue(LCD_RS_PORT, LCD_RS_PIN, PIN_HIGH);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_RW_PORT, LCD_RW_PIN, PIN_LOW);
#elif ((LCD_CONTROL_PORT <= PortD) && (LCD_DATA_PORT <= PortD))
	Loc_u8_Retval  = MCAL_DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, PIN_HIGH);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, PIN_LOW);
#else
	#error ("Error Configurations")
#endif
	return Loc_u8_Retval;
}

/************************************************************************
 * description : Send Data To LCD
 * INPUT Arg   : Value Of Data in ASCII Table or Character
 * RETURN      : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/
STD_TYPE HAL_LCD_u8_SendData(u8 Loc_u8_Data)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	Loc_u8_Retval = HAL_LCD_u8_SendDataInit();
#if ((LCD_CONTROL_PORT == NC) && (LCD_DATA_PORT == NC))
	Loc_u8_Retval  = MCAL_DIO_u8SetPinValue(LCD_D4_PORT,LCD_D4_PIN,GET_BIT(Loc_u8_Data,4));
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_D5_PORT,LCD_D5_PIN,GET_BIT(Loc_u8_Data,5));
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_D6_PORT,LCD_D6_PIN,GET_BIT(Loc_u8_Data,6));
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_D7_PORT,LCD_D7_PIN,GET_BIT(Loc_u8_Data,7));
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_EN_PORT, LCD_EN_PIN, PIN_HIGH);
	_delay_ms(3);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_EN_PORT, LCD_EN_PIN, PIN_LOW);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_D4_PORT,LCD_D4_PIN,GET_BIT(Loc_u8_Data<<4,4));
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_D5_PORT,LCD_D5_PIN,GET_BIT(Loc_u8_Data<<4,5));
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_D6_PORT,LCD_D6_PIN,GET_BIT(Loc_u8_Data<<4,6));
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_D7_PORT,LCD_D7_PIN,GET_BIT(Loc_u8_Data<<4,7));
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_EN_PORT, LCD_EN_PIN, PIN_HIGH);
	_delay_ms(3);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_EN_PORT, LCD_EN_PIN, PIN_LOW);
	_delay_ms(3);
#elif ((LCD_CONTROL_PORT <= PortD) && (LCD_DATA_PORT <= PortD))
	Loc_u8_Retval  = MCAL_DIO_u8SetPortValue(LCD_DATA_PORT,Loc_u8_Data);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_EN_PORT, LCD_EN_PIN, PIN_HIGH);
	_delay_ms(10);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, PIN_LOW);
	Loc_u8_Retval |= MCAL_DIO_u8SetPortValue(LCD_DATA_PORT,Loc_u8_Data<<4);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, PIN_HIGH);
	_delay_ms(10);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, PIN_LOW);
	_delay_ms(10);
#else
	#error ("Error Configurations")
#endif
	return Loc_u8_Retval;
}

/************************************************************************
 * description : 4 BIT Mode Initialization
 * INPUT Arg   : No Args
 * RETURN      : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/
STD_TYPE HAL_u8_LCD_4BitModeInit(void)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	Loc_u8_Retval  = HAL_LCD_u8_SendCommand(0x02);
	Loc_u8_Retval |= HAL_LCD_u8_SendCommand(0x28);
	Loc_u8_Retval |= HAL_LCD_u8_SendCommand(0x0F);
	Loc_u8_Retval |= HAL_LCD_u8_SendCommand(0x01);
	Loc_u8_Retval |= HAL_LCD_u8_SendCommand(0x06);
	return Loc_u8_Retval;
}

/************************************************************************
 * description : 8 BIT Mode Initialization
 * INPUT Arg   : No Args
 * RETURN      : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/
STD_TYPE HAL_u8_LCD_8BitModeInit(void)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	Loc_u8_Retval  = HAL_LCD_u8_SendCommand(0x38);
	Loc_u8_Retval |= HAL_LCD_u8_SendCommand(0x0F);
	_delay_ms(250);
	Loc_u8_Retval |= HAL_LCD_u8_SendCommand(0x01);
	Loc_u8_Retval |= HAL_LCD_u8_SendCommand(0x06);
	return Loc_u8_Retval;
}

/************************************************************************
 * description : Send Character to LCD
 * INPUT Arg   : Value Of Data in ASCII Table or Character
 * RETURN      : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/
STD_TYPE HAL_LCD_u8_WriteCharacter(u8 Loc_u8_character)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	Loc_u8_Retval = HAL_LCD_u8_SendData(Loc_u8_character);
	return Loc_u8_Retval;
}

/************************************************************************
 * description : Send String to LCD
 * INPUT Arg   : Pointer points to String or String
 * RETURN      : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/
STD_TYPE HAL_LCD_u8_WriteString(s8 *Ploc_u8_str)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	while(*Ploc_u8_str != '\0')
	{
		Loc_u8_Retval = HAL_LCD_u8_WriteCharacter(*Ploc_u8_str);
		Ploc_u8_str++;
	}
	return Loc_u8_Retval;
}

/************************************************************************
 * description : Clear Screen
 * INPUT Arg   : No Args
 * RETURN      : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/
STD_TYPE HAL_LCD_u8_ClearFullScreen(void)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	Loc_u8_Retval = HAL_LCD_u8_SendCommand(0x01);
	return Loc_u8_Retval;
}

/************************************************************************
 * description  : Clear Character (Print Space on This Location of Character of LCD)
 * INPUT Arg1   : Row (0 or 1)
 * INPUT Arg2   : Column (0:1:15)
 * RETURN       : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/
STD_TYPE HAL_LCD_u8_ClearCharacter(u8 Loc_u8_Row, u8 Loc_u8_Column)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	Loc_u8_Retval  = HAL_LCD_u8_GoTo(Loc_u8_Row,Loc_u8_Column);
	Loc_u8_Retval |= HAL_LCD_u8_WriteCharacter(' ');
	return Loc_u8_Retval;
}

/************************************************************************
 * description  : Go to Specific Location
 * INPUT Arg1   : Row (0 or 1)
 * INPUT Arg2   : Column (0:1:15)
 * RETURN       : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/
STD_TYPE HAL_LCD_u8_GoTo(u8 Loc_u8_Row, u8 Loc_u8_Column)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	if(Loc_u8_Row == 0 && Loc_u8_Column < 20)
	{
		Loc_u8_Retval = HAL_LCD_u8_SendCommand(0x80 + Loc_u8_Column);
	}
	else if(Loc_u8_Row == 1 && Loc_u8_Column < 20)
	{
		Loc_u8_Retval = HAL_LCD_u8_SendCommand(0x80 + 0x40 + Loc_u8_Column);
	}
	else if(Loc_u8_Row == 2 && Loc_u8_Column < 20)
	{
		Loc_u8_Retval = HAL_LCD_u8_SendCommand(0x80 + 0x14 + Loc_u8_Column);
	}
	else if(Loc_u8_Row == 3 && Loc_u8_Column < 20)
	{
		Loc_u8_Retval = HAL_LCD_u8_SendCommand(0x80 + 0x40 + 0x14 + Loc_u8_Column);
	}
	else
	{
		Loc_u8_Retval = HAL_LCD_u8_ClearFullScreen();
		Loc_u8_Retval = HAL_LCD_u8_GoTo(0,5);
		Loc_u8_Retval = HAL_LCD_u8_WriteString("Error !!");
		Loc_u8_Retval = E_NOT_OK;
	}
	return Loc_u8_Retval;
}

/************************************************************************
 * description : Write Character On LCD
 * INPUT Arg   : Pointer Points to Character or Character
 * RETURN      : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/
STD_TYPE HAL_LCD_u8_WriteCharacter1(u8 *Loc_u8_character)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	Loc_u8_Retval = HAL_LCD_u8_SendData(*Loc_u8_character);
	return Loc_u8_Retval;
}

/************************************************************************
 * description  : Write Custom Character On LCD
 * INPUT Arg1   : Column (0:1:7)
 * INPUT Arg2   : Pointer Points to The array of Character Or name of the array of custom character
 * RETURN       : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/
STD_TYPE HAL_LCD_u8_WriteCustomCharacter(u8 Loc_u8_Column,u8 *PLoc_u8_CustomCharacter)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	u8 Loc_u8_Index = ZERO;
	Loc_u8_Retval = HAL_LCD_u8_SendCommand(0x40+Loc_u8_Column*8);
	for(Loc_u8_Index = 0; Loc_u8_Index<=7; Loc_u8_Index++)
	{
		Loc_u8_Retval |= HAL_LCD_u8_SendData(PLoc_u8_CustomCharacter[Loc_u8_Index]);
	}
	return Loc_u8_Retval;
}

/************************************************************************
 * description  : Write Number On LCD
 * INPUT Arg1   : The Number you want print it
 * RETURN       : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/
STD_TYPE HAL_LCD_u8_WriteNumber(s32 Loc_s32_Num)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	u8 rem = 0;
	s8 arr[10];
	s8 i = 0;
	s8 j = 0;
	if(Loc_s32_Num == 0)
	{
		return HAL_LCD_u8_WriteCharacter('0');
	}
	else if(Loc_s32_Num < 0)
	{
		Loc_s32_Num *= -1;
		Loc_u8_Retval |= HAL_LCD_u8_WriteCharacter('-');
	}

	while (Loc_s32_Num > 0)
	{
		rem = Loc_s32_Num % 10;
		rem = rem + '0';
		arr[i] = (char)rem;
		Loc_s32_Num = Loc_s32_Num / 10;
		i++;
	}

	for(j=i-1; j>=0; j--) /*j>=0, j must be a signed number*/
	{
		Loc_u8_Retval |= HAL_LCD_u8_WriteCharacter(arr[j]);
	}
	return Loc_u8_Retval;
}
