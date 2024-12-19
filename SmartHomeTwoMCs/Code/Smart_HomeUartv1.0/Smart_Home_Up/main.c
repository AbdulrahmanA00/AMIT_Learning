#include"main.h"



void main (void)
{
	APP_Init();
	APP_STATE_void_AppStateInit();
	while(1)
	{
		APP_Home_Page();
		//MCAL_INT_u8_SetGlabalInterrupt(GIE);
	}
}

