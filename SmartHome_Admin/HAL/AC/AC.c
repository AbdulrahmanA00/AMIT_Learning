/*
 * AC.c
 *
 *  Created on: Feb 10, 2024
 *      Author: Abdulrahman Ayman
 */
#include"AC.h"

u8 volatile G_FanFlag=0;
//extern void APP_DEVICES_void_AppGetAnyDeviceOn(void);


void APP_LM35WithDCmotor_Void_LM35WithDCmotorinit(void)
{
		LM35_Init();
		HAL_DCMOTOR_void_DcMotorInit();
}

void APP_LM35WithDCmotor_Void_LM35WithDCmotorOnOff(void)
{

	if(G_FanFlag == 0)
    {
	    u8 Tempreture_Sensor_read =LM35_Read();
	    static u8 fan_on_off = fan_off ;


	    if (Tempreture_Sensor_read>TURN_DC_ON_TEMP)
	    {
		    fan_on_off=fan_on;
	    }
	    else if (Tempreture_Sensor_read<TURN_DC_OFF_TEMP)
	    {
		    fan_on_off=fan_off;
	    }

	    if (fan_on_off==fan_on)
	    {
		    HAL_DCMOTOR_void_DcMotorClockWise(motor_speed);
	    }
	    else if(fan_on_off==fan_off)
	    {
		    HAL_DCMOTOR_void_DcMotorStop();
	    }


    }


}


