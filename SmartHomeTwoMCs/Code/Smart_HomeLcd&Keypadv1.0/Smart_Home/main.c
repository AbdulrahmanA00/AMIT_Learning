#include"main.h"
 u16 volatile G_u16_checkID;
void main(void)
{
	APP_STATE_void_AppStateInit();
	HAL_KEYPAD_u8_KaypadInit();
	HAL_LCD_u8_LcdInit();
	HAL_LED_u8AllLedsInit();
	HAL_Buzzer_u8BuzzerInit(Buzzer_Port,Buzzer_Pin);
	APP_LM35WithDCmotor_Void_LM35WithDCmotorinit();
	MCAL_TWI_voidMasterInit();
	while(1)
	{
		G_LogoutFlag = ZERO;
		HAL_KEYPAD_u8_HomeKaypadButton(&G_Keypad_Value);
		if(G_Keypad_Value != ZERO)
		{
			G_u16_checkID = APP_USERID_u8_AppUserID();
			APP_PASSWORD_u8_AppGetPassword(G_u16_checkID);
		}
		APP_void_AppHomePage();
	}
}
