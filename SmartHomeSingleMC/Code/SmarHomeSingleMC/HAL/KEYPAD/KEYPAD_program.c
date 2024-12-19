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




#include "KEYPAD_interface.h"
#include "KEYPAD_config.h"
#include "KEYPAD_private.h"
#include "../AC/AC.h"


/*extern u8 volatile G_FanFlag;
extern u8 volatile G_FanFlagOn;
extern u8 volatile G_FanFlagOff;
extern u8 volatile G_FanControlFlag;
extern u8 volatile G_LM35;*/
//extern void APP_FAN_void_AppFanReadWithoutWrite(void);


/*****************************************************************************************/



/************************************ Implementation Section ******************************/

/************************************************************************
 * description : KEYPAD Initialize Its Pin As OUTPUT
 * INPUT Arg   : No Args
 * RETURN      : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/
STD_TYPE HAL_KEYPAD_u8_KaypadInit(void)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	Loc_u8_Retval  = MCAL_DIO_u8SetPinDirection(KEYPAD_R0_PORT,KEYPAD_R0_PIN,PIN_INPUT);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinDirection(KEYPAD_R1_PORT,KEYPAD_R1_PIN,PIN_INPUT);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinDirection(KEYPAD_R2_PORT,KEYPAD_R2_PIN,PIN_INPUT);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinDirection(KEYPAD_R3_PORT,KEYPAD_R3_PIN,PIN_INPUT);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinDirection(KEYPAD_C0_PORT,KEYPAD_C0_PIN,PIN_OUTPUT);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinDirection(KEYPAD_C1_PORT,KEYPAD_C1_PIN,PIN_OUTPUT);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinDirection(KEYPAD_C2_PORT,KEYPAD_C2_PIN,PIN_OUTPUT);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinDirection(KEYPAD_C3_PORT,KEYPAD_C3_PIN,PIN_OUTPUT);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(KEYPAD_R0_PORT,KEYPAD_R0_PIN,PIN_HIGH);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(KEYPAD_R1_PORT,KEYPAD_R1_PIN,PIN_HIGH);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(KEYPAD_R2_PORT,KEYPAD_R2_PIN,PIN_HIGH);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(KEYPAD_R3_PORT,KEYPAD_R3_PIN,PIN_HIGH);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(KEYPAD_C0_PORT,KEYPAD_C0_PIN,PIN_HIGH);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(KEYPAD_C1_PORT,KEYPAD_C1_PIN,PIN_HIGH);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(KEYPAD_C2_PORT,KEYPAD_C2_PIN,PIN_HIGH);
	Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(KEYPAD_C3_PORT,KEYPAD_C3_PIN,PIN_HIGH);
	return Loc_u8_Retval;
}

/************************************************************************
 * description : KEYPAD Initialize Its Pin As OUTPUT
 * INPUT Arg   : Address of variable
 * RETURN      : Execution Status (OK OR NOT_OK)
 * **********************************************************************
 **/

STD_TYPE HAL_KEYPAD_u8_KaypadButton(u8 *Ploc_u8_ButtuonValue)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	u16 Loc_u16_Counter = 0;
	u8 ch[4][4] = {{7,8,9,'/'},
				   {4,5,6,'*'},
	               {1,2,3,'-'},
				   {'N',0,'=','+'}};
	u8 ROWS_PORT[4]   = {KEYPAD_R3_PORT, KEYPAD_R2_PORT, KEYPAD_R1_PORT, KEYPAD_R0_PORT};
	u8 COLUMS_PORT[4] = {KEYPAD_C3_PORT, KEYPAD_C2_PORT, KEYPAD_C1_PORT, KEYPAD_C0_PORT};
	u8 ROWS_PIN[4]    = {KEYPAD_R3_PIN, KEYPAD_R2_PIN, KEYPAD_R1_PIN, KEYPAD_R0_PIN};
	u8 COLUMS_PIN[4]  = {KEYPAD_C3_PIN, KEYPAD_C2_PIN, KEYPAD_C1_PIN, KEYPAD_C0_PIN};
	u8 row = 0;
	u8 column = 0;
	u8 r = 0;
	u8 c = 0;
	u8 flag = 0;
	u8 value = 0;
	if(Ploc_u8_ButtuonValue != NULL)
	{
		while(1)
		{
			//APP_LM35WithDCmotor_Void_LM35WithDCmotorOnOff();
			//APP_FAN_void_AppFanReadWithoutWrite();
			c = 3;
			for(column =0; column <= 3; column++)
			{
				r = 4;
				Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(COLUMS_PORT[column],COLUMS_PIN[column],PIN_LOW);
				for(row = 4; row <= 7; row++)
				{
					r--;
					Loc_u8_Retval |= MCAL_DIO_u8GetPinValue(ROWS_PORT[row-4],ROWS_PIN[row-4],&value);
					if(value == PIN_LOW)
					{
						flag = 1;
						while(value == PIN_LOW)
						{
							Loc_u8_Retval |= MCAL_DIO_u8GetPinValue(ROWS_PORT[row-4],ROWS_PIN[row-4],&value);
						}
						*Ploc_u8_ButtuonValue = ch[r][c];
						break;
					}
				}
				if(flag == 1)
				{
					break;
				}
				c--;
				Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(COLUMS_PORT[column],COLUMS_PIN[column],PIN_HIGH);
			}
			if(flag == 1)
			{
				break;
			}
			Loc_u16_Counter++;
			if(Loc_u16_Counter == 0)
			{
				*Ploc_u8_ButtuonValue = 0;
				break;
			}
		}
	}
	else
	{
		//Do Nothing
	}
	return Loc_u8_Retval;
}

STD_TYPE HAL_KEYPAD_u8_KaypadButton1(u8 *Ploc_u8_ButtuonValue)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	u16 Loc_u16_Counter = 0;
	u8 ch[4][4] = {{7,8,9,'/'},
				   {4,5,6,'*'},
	               {1,2,3,'-'},
				   {'N',0,'=','+'}};
	u8 ROWS_PORT[4]   = {KEYPAD_R3_PORT, KEYPAD_R2_PORT, KEYPAD_R1_PORT, KEYPAD_R0_PORT};
	u8 COLUMS_PORT[4] = {KEYPAD_C3_PORT, KEYPAD_C2_PORT, KEYPAD_C1_PORT, KEYPAD_C0_PORT};
	u8 ROWS_PIN[4]    = {KEYPAD_R3_PIN, KEYPAD_R2_PIN, KEYPAD_R1_PIN, KEYPAD_R0_PIN};
	u8 COLUMS_PIN[4]  = {KEYPAD_C3_PIN, KEYPAD_C2_PIN, KEYPAD_C1_PIN, KEYPAD_C0_PIN};
	u8 row = 0;
	u8 column = 0;
	u8 r = 0;
	u8 c = 0;
	u8 flag = 0;
	u8 value = 0;
	if(Ploc_u8_ButtuonValue != NULL)
	{
		while(1)
		{

			//APP_LM35WithDCmotor_Void_LM35WithDCmotorOnOff();
			//APP_FAN_void_AppFanReadWithoutWrite();
			c = 3;
			for(column =0; column <= 3; column++)
			{
				r = 4;
				Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(COLUMS_PORT[column],COLUMS_PIN[column],PIN_LOW);
				for(row = 4; row <= 7; row++)
				{
					r--;
					Loc_u8_Retval |= MCAL_DIO_u8GetPinValue(ROWS_PORT[row-4],ROWS_PIN[row-4],&value);
					if(value == PIN_LOW)
					{
						flag = 1;
						while(value == PIN_LOW)
						{
							Loc_u8_Retval |= MCAL_DIO_u8GetPinValue(ROWS_PORT[row-4],ROWS_PIN[row-4],&value);
						}
						*Ploc_u8_ButtuonValue = ch[r][c];
						break;
					}
				}
				if(flag == 1)
				{
					break;
				}
				c--;
				Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(COLUMS_PORT[column],COLUMS_PIN[column],PIN_HIGH);
			}
			if(flag == 1)
			{
				break;
			}
			Loc_u16_Counter++;
			if(Loc_u16_Counter == 0)
			{
				*Ploc_u8_ButtuonValue = 0;
				break;
			}
		}
	}
	else
	{
		//Do Nothing
	}
	return Loc_u8_Retval;
}

STD_TYPE HAL_KEYPAD_u8_HomeKaypadButton(u8 *Ploc_u8_ButtuonValue)
{
	u8 Loc_u8_Retval = E_NOT_OK;
	u8 ch[4][4] = {{7,8,9,'/'},
				   {4,5,6,'*'},
	               {1,2,3,'-'},
				   {'N',0,'=','+'}};
	u8 ROWS_PORT[4]   = {KEYPAD_R3_PORT, KEYPAD_R2_PORT, KEYPAD_R1_PORT, KEYPAD_R0_PORT};
	u8 COLUMS_PORT[4] = {KEYPAD_C3_PORT, KEYPAD_C2_PORT, KEYPAD_C1_PORT, KEYPAD_C0_PORT};
	u8 ROWS_PIN[4]    = {KEYPAD_R3_PIN, KEYPAD_R2_PIN, KEYPAD_R1_PIN, KEYPAD_R0_PIN};
	u8 COLUMS_PIN[4]  = {KEYPAD_C3_PIN, KEYPAD_C2_PIN, KEYPAD_C1_PIN, KEYPAD_C0_PIN};
	u8 row = 0;
	u8 column = 0;
	u8 r = 0;
	u8 c = 0;
	u8 flag = 0;
	u8 value = 0;
	if(Ploc_u8_ButtuonValue != NULL)
	{
		while(1)
		{
			/*MCAL_UART_voidReceiveData(&G_FanFlagOn);
			if(G_FanFlagOn == 1)
			{

			}*/

/*
			if(G_FanControlFlag == 0)
			{
				G_LM35 = LM35_Read();
				if((G_LM35 > TURN_DC_ON_TEMP) && (G_FanFlagOn == 0))
				{
					G_FanFlagOn = 1;
					G_FanFlag = 1;
					G_FanFlagOff = 0;
					HAL_DCMOTOR_void_DcMotorClockWise(motor_speed);
					APP_DEVICES_void_AppGetAnyDeviceOn();
				}
				else if((G_LM35 < TURN_DC_OFF_TEMP) && (G_FanFlagOff == 0))
				{
					G_FanFlagOff = 1;
					G_FanFlag = 0;
					G_FanFlagOn = 0;
					HAL_DCMOTOR_void_DcMotorStop();
					APP_DEVICES_void_AppGetAnyDeviceOn();
				}
				else if((G_LM35 > TURN_DC_OFF_TEMP) && (G_LM35 < TURN_DC_ON_TEMP))
				{
					G_FanFlagOn = 0;
					G_FanFlagOff = 0;
				}
			}
*/
			c = 3;
			for(column =0; column <= 3; column++)
			{
				r = 4;
				Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(COLUMS_PORT[column],COLUMS_PIN[column],PIN_LOW);
				for(row = 4; row <= 7; row++)
				{
					r--;
					Loc_u8_Retval |= MCAL_DIO_u8GetPinValue(ROWS_PORT[row-4],ROWS_PIN[row-4],&value);
					if(value == PIN_LOW)
					{
						flag = 1;
						while(value == PIN_LOW)
						{
							Loc_u8_Retval |= MCAL_DIO_u8GetPinValue(ROWS_PORT[row-4],ROWS_PIN[row-4],&value);
						}
						*Ploc_u8_ButtuonValue = ch[r][c];
						break;
					}
				}
				if(flag == 1)
				{
					break;
				}
				c--;
				Loc_u8_Retval |= MCAL_DIO_u8SetPinValue(COLUMS_PORT[column],COLUMS_PIN[column],PIN_HIGH);
			}
			if(flag == 1)
			{
				break;
			}
		}
	}
	else
	{
		//Do Nothing
	}
	return Loc_u8_Retval;
}

