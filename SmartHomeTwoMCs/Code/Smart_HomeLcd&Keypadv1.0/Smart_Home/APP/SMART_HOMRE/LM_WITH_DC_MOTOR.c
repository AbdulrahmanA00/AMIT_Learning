/*
 * LM_WITH_DC_MOTOR.c
 *
 * Created: 1/31/2024 2:15:58 PM
 *  Author: hp
 */ 
#include "LM_WITH_DC_MOTOR.h"

extern u8 volatile G_FanFlag;
extern void APP_DEVICES_void_AppGetAnyDeviceOn(void);
void APP_LM35WithDCmotor_Void_LM35WithDCmotorinit(void)
{
		LM35_Init();
		HAL_DCMOTOR_void_DcMotorInit();
}

void APP_LM35WithDCmotor_Void_LM35WithDCmotorOnOff(void)
{
    //while (1)
	if(G_FanFlag == 0)
    {
	    int Tempreture_Sensor_read = LM35_Read();
	    static int fan_on_off = fan_off ;
	   // HAL_LCD_u8LCD_DisplayNumber(Tempreture_Sensor_read);
	    
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

	    //_delay_ms(1000);

    }

	
}
