/*
 * AC.h
 *
 *  Created on: Feb 10, 2024
 *      Author: Abdulrahman Ayman
 */

#ifndef HAL_AC_AC_H_
#define HAL_AC_AC_H_

/*
 * LM_WITH_DC_MOTOR.h
 *
 * Created: 2/1/2024 10:50:17 PM
 *  Author: hp
 */


#ifndef LM_WITH_DC_MOTOR_H_
#define LM_WITH_DC_MOTOR_H_


#include "../../HAL/LM35/LM35.h"
#include "../../HAL/DC_Motor/DC_Motor.h"


#define TURN_DC_ON_TEMP   28
#define TURN_DC_OFF_TEMP  21
#define fan_on            1
#define fan_off           0
#define motor_speed       7


void APP_LM35WithDCmotor_Void_LM35WithDCmotorinit(void);
void APP_LM35WithDCmotor_Void_LM35WithDCmotorOnOff(void);

#endif /* LM_WITH_DC_MOTOR_H_ */


#endif /* HAL_AC_AC_H_ */
