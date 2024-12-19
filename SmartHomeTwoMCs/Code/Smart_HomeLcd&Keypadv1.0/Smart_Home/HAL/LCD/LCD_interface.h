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


#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_

/*******************************Includes Section *****************************************/

#include "..\..\Common\MCU.h"
#include "..\..\Common\Macros.h"
#include "..\..\Common\STD_Types.h"

#include "..\..\MCAL\DIO\DIO.h"

#include "LCD_private.h"
#include "LCD_config.h"

/*******************************Macros Section *****************************************/

/*******************************Prototyping Section *****************************************/

STD_TYPE HAL_LCD_u8_LcdPinInit(u8 Loc_u8_LcdPortID, u8 Loc_u8_LcdPinID);
STD_TYPE HAL_LCD_u8_LcdInit(void);
STD_TYPE HAL_LCD_u8_SendCommandInit(void);
STD_TYPE HAL_LCD_u8_SendCommand(u8 Loc_u8_Command);
STD_TYPE HAL_LCD_u8_SendDataInit(void);
STD_TYPE HAL_LCD_u8_SendData(u8 Loc_u8_Data);
STD_TYPE HAL_u8_LCD_4BitModeInit(void);
STD_TYPE HAL_u8_LCD_8BitModeInit(void);
STD_TYPE HAL_LCD_u8_WriteCharacter(u8 Loc_u8_character);
STD_TYPE HAL_LCD_u8_WriteString(s8 *Ploc_u8_str);
STD_TYPE HAL_LCD_u8_GoTo(u8 Loc_u8_Row, u8 Loc_u8_Column);
STD_TYPE HAL_LCD_u8_ClearFullScreen(void);
STD_TYPE HAL_LCD_u8_WriteCustomCharacter(u8 Loc_u8_Column,u8 *PLoc_u8_CustomCharacter);
STD_TYPE HAL_LCD_u8_ClearCharacter(u8 Loc_u8_Row, u8 Loc_u8_Column);
STD_TYPE HAL_LCD_u8_WriteCharacter1(u8 *Loc_u8_character);
STD_TYPE HAL_LCD_u8_WriteNumber(s32 Loc_s32_Num);

#endif /* HAL_LCD_LCD_INTERFACE_H_ */
