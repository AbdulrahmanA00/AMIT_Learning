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


#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_

/*******************************Includes Section *****************************************/


#include "..\..\MCAL\DIO\DIO.h"

/*******************************Macros Section *****************************************/

#define NC    0xFF
/*
 * Options :
 * 			PortA
 * 			PortB
 *			PortC
 * 			PortD
 * 			NC
 */

// if all control Pins on The same Port and Data Pins on The same port
#define LCD_CONTROL_PORT   NC
#define LCD_DATA_PORT      NC

/*
 * Options :
 * 			PortA
 * 			PortB
 *			PortC
 * 			PortD
 */
// if every pin on different Port
#define LCD_RS_PORT        PortD
#define LCD_RW_PORT        PortB
#define LCD_EN_PORT        PortD
#define LCD_D4_PORT        PortB
#define LCD_D5_PORT        PortD
#define LCD_D6_PORT        PortD
#define LCD_D7_PORT        PortD

/*
 * Options :
 * 			PIN0
 * 			PIN1
 * 			PIN2
 * 			PIN3
 * 			PIN4
 *		    PIN5
 * 			PIN6
 *			PIN7
 */
#define LCD_RS_PIN         PIN6
#define LCD_RW_PIN         PIN1
#define LCD_EN_PIN         PIN7
#define LCD_D4_PIN         PIN3
#define LCD_D5_PIN         PIN3
#define LCD_D6_PIN         PIN4
#define LCD_D7_PIN         PIN5

/*******************************Prototyping Section *****************************************/



#endif /* HAL_LCD_LCD_CONFIG_H_ */
