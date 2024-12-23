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

#ifndef HAL_KEYPAD_KEYPAD_CONFIG_H_
#define HAL_KEYPAD_KEYPAD_CONFIG_H_

/*******************************Includes Section *****************************************/

/*******************************Macros Section *****************************************/

/*
 * Options :
 * 			PortA
 * 			PortB
 *			PortC
 * 			PortD
 */
#define KEYPAD_R0_PORT   PortC
#define KEYPAD_R1_PORT   PortC
#define KEYPAD_R2_PORT   PortC
#define KEYPAD_R3_PORT   PortC
#define KEYPAD_C0_PORT   PortD
#define KEYPAD_C1_PORT   PortD
#define KEYPAD_C2_PORT   PortA
#define KEYPAD_C3_PORT   PortD

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
#define KEYPAD_R0_PIN	 PIN2
#define KEYPAD_R1_PIN	 PIN5
#define KEYPAD_R2_PIN	 PIN6
#define KEYPAD_R3_PIN	 PIN7
#define KEYPAD_C0_PIN	 PIN2
#define KEYPAD_C1_PIN	 PIN3
#define KEYPAD_C2_PIN	 PIN2
#define KEYPAD_C3_PIN	 PIN6

/*******************************Prototyping Section *****************************************/

#endif /* HAL_KEYPAD_KEYPAD_CONFIG_H_ */
