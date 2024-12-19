/*
 * Buzzer.h
 *
 *  Created on: Sep 25, 2023
 *      Author: 2023
 */

#ifndef HAL_BUZZER_BUZZER_H_
#define HAL_BUZZER_BUZZER_H_
#include "../../MCAL/DIO/DIO.h"
#define Buzzer_OFF 0
#define Buzzer_ON 1
#define Buzzer_TOG 2
#define Buzzer_Port PortB
#define Buzzer_Pin Pin0
STD_TYPE HAL_Buzzer_u8BuzzerInit(u8 LOC_u8BuzzerPortID, u8 LOC_u8BuzzerPinID);
STD_TYPE HAL_Buzzer_u8BuzzerMode(u8 LOC_u8BuzzerPortID, u8 LOC_u8BuzzerPinID, u8 LOC_u8BuzzerMode);


#endif /* HAL_BUZZER_BUZZER_H_ */
