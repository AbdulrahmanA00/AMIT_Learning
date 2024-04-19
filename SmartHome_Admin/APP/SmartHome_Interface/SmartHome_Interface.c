/*
 * Bluetooth.c
 *
 *  Created on: Feb 4, 2024
 *      Author: Abdulrahman Ayman
 */
#include "SmartHome_Interface.h"

u8 volatile GLOB_u8LoginFlag = 0;

u8 GLOB_u8DoorCommandReceived[6] = {};
//u8 GLOB_u8IDString[8] = {0} ;

/************************	Register Page Text	**********************/
u8 GLOB_u8NewAdmin[16] =		"1 --> New Admin";

/************************	Home Page Text	**********************/
u8 GLOB_u8WelcomeString[23] =	"Welcome to Lobby!\r\n" ;
u8 GLOB_u8NewLine[5] = 			"\r\n";
u8 GLOB_u8LoginString[15] = 	"1 --> LOGIN" ;
u8 GLOB_u8RegisterString [20] = "2 --> Register" ;

/************************	Options Page Text	**********************/
u8 GLOB_u8UserManagement[22] = 	"1 --> User Management" ;
u8 GLOB_u8DevicesControl[22] = 	"2 --> Devices" ;
u8 GLOB_u8DoorControl[20] =		"3 --> Door" ;
u8 GLOB_u8Logout[13] = 			"0 --> Logout";

/************************	User Management Page	*******************/
u8 GLOB_u8NewUser[19] 		=	"1 --> New User\r\n";
u8 GLOB_u8RemoveUser[24] 	= 	"2 --> Remove User\r\n";
u8 GLOB_u8RemoveAllUsers[27]= 	"3 --> Remove All Users\r\n";
//u8 GLOB_u8GoBack[11] 		= 	"0 --> Back";
//u8 GLOB_u8GetListOfUsers[20] = 	"4 --> Users List"; (Target)
//u8 GLOB_u8NewUser[20] = 	"5 --> Reset Memory\r\n";


void APP_Init(void)
{
	//Communication Protocols Init:
	MCAL_TWI_voidMasterInit();
	MCAL_UART_voidInit();
	//Door Init;
	HAL_Servo_voidServoInit();
	//LEDs Init:
	HAL_LED_u8LedInit(LED1_Port,LED1_Pin);
	HAL_LED_u8LedInit(LED2_Port,LED2_Pin);
	HAL_LED_u8LedInit(LED3_Port,LED3_Pin);
	HAL_LED_u8LedInit(LED4_Port,LED4_Pin);
	HAL_LED_u8LedInit(LED5_Port,LED5_Pin);
	//Breakdown Alarm Init:
	HAL_Buzzer_u8BuzzerInit(Buzzer_Port,Buzzer_Pin);
	//Dimmer Init:
	HAL_MCP4018_POT_voidWriteStep(0);
	//AC Init:
	APP_LM35WithDCmotor_Void_LM35WithDCmotorinit();
	MCAL_TIMER_Timer0_Init(NORMAL,CLK_PRE1024,NORMAL_OC0);
	MCAL_TIMER_voidTimer0_OVFSetCallBack(APP_AC_Check);
/*
	MCAL_TIMER_Timer0_InterruptOVF_Enable();
	MCAL_Interrupt_GIE_Enable();
*/

}


void APP_Home_Page(void)
{
	u8 LOC_u8FirstDataReceived = 0 ;

	while(1)
	{
//		APP_LM35WithDCmotor_Void_LM35WithDCmotorOnOff();
		MCAL_UART_voidSendString(GLOB_u8WelcomeString);

		MCAL_UART_voidSendString(GLOB_u8LoginString);
//		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString(GLOB_u8RegisterString);
	//	MCAL_UART_voidSendString(GLOB_u8NewLine);


		MCAL_UART_voidReceiveData(&LOC_u8FirstDataReceived);
		switch(LOC_u8FirstDataReceived)
		{
		case '1':

//			APP_LM35WithDCmotor_Void_LM35WithDCmotorOnOff();
			MCAL_UART_voidTransmitData('1');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			APP_Login_Page();
		break;
		case '2':

//			APP_LM35WithDCmotor_Void_LM35WithDCmotorOnOff();
			MCAL_UART_voidTransmitData('2');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			APP_Register_Page();
		break;
		}
	}

}

void APP_Login_Page(void)
{
	u8  LOC_u8Check_AdminID = 0 ,LOC_u8Check_AdminPassword = 0,LOC_u8Buffer = 0;
	u16 i=0,j=0, LOC_u16ID =0,LOC_u16Pass = 0;
	static u8 LOC_u8LoginFailed = 3;

//	Login:

	i = 1000;
	MCAL_UART_voidSendString((u8*)"Enter Your Username: ");
	do
	{
		MCAL_UART_voidReceiveData(&LOC_u8Buffer);
		MCAL_UART_voidTransmitData((LOC_u8Buffer));
		LOC_u16ID += ((LOC_u8Buffer-'0') * i);
		i /= 10;

	}while(i != 0);

	MCAL_UART_voidSendString(GLOB_u8NewLine);
	LOC_u8Check_AdminID = Check_AdminID(LOC_u16ID);

//	Pass:
	j = 1000;
	MCAL_UART_voidSendString((u8*)"Enter Your Password: ");
	do
	{
		MCAL_UART_voidReceiveData(&LOC_u8Buffer);
		MCAL_UART_voidTransmitData((LOC_u8Buffer));
		LOC_u16Pass += ((LOC_u8Buffer-'0') * j);
		j /= 10;
	}while(j != 0);

//	MCAL_UART_voidSendString(GLOB_u8NewLine);
	LOC_u8Check_AdminPassword = Check_AdminPassword(LOC_u16ID,LOC_u16Pass);

	if(LOC_u8Check_AdminID == ADMIN_NOT_FOUND )
	{
		MCAL_UART_voidSendString((u8*)"USERNAME NOT FOUND!!!");
	//	MCAL_UART_voidSendString(GLOB_u8NewLine);
		LOC_u8LoginFailed--;

		if (LOC_u8LoginFailed == 0)
		{
			MCAL_UART_voidSendString((u8*)"You have Reached Maximum Tries!!!");
			while(1)
			{
				HAL_Buzzer_u8BuzzerMode(Buzzer_Port,Buzzer_Pin,Buzzer_ON);
			}
		}
		else
		{

			MCAL_UART_voidSendString((u8*)"Tries Left: ");
			MCAL_UART_voidTransmitData((LOC_u8LoginFailed+'0'));
			MCAL_UART_voidSendString(GLOB_u8NewLine);

			APP_Login_Page();
			//goto Login;
		}
	}
	else if (LOC_u8Check_AdminPassword == PASSWORD_NOT_MATCHED)
	{
		MCAL_UART_voidSendString((u8*)"WRONG PASSWORD!!!");
		//MCAL_UART_voidSendString(GLOB_u8NewLine);
		LOC_u8LoginFailed--;
		if (LOC_u8LoginFailed == 0)
		{
			MCAL_UART_voidSendString((u8*)"You have Reached Maximum Tries!!!");
			//MCAL_UART_voidSendString(GLOB_u8NewLine);
			while(1)
			{
				HAL_Buzzer_u8BuzzerMode(Buzzer_Port,Buzzer_Pin,Buzzer_ON);
			}

		}
		else
		{
			MCAL_UART_voidSendString((u8*)"Tries Left:");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidTransmitData((LOC_u8LoginFailed+'0'));
			MCAL_UART_voidSendString(GLOB_u8NewLine);
//			goto Pass;
			APP_Login_Page();
		}
	}
	else
	{
			LOC_u8LoginFailed = 3;
			MCAL_UART_voidSendString(GLOB_u8WelcomeString);
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
			APP_Options_Page();

	}




}



void APP_Register_Page(void)
{
	u8 LOC_u8Input = 0 ,LOC_u8BackFlag = 0;

/*
	MCAL_UART_voidSendString(GLOB_u8NewUser);
	MCAL_UART_voidSendString(GLOB_u8RemoveUser);
	MCAL_UART_voidSendString(GLOB_u8RemoveAllUsers);
*/

	do
	{
		u8 LOC_u8BufferA = 0,LOC_u8BufferB = 0,LOC_u8BufferC = 0, LOC_u8CheckID = 0,LOC_u8AdminEnteryFlag = 0;
		u16 LOC_u16ID = 0,LOC_u16Pass = 0,LOC_u16PassConfirm = 0,i = 0,j = 0,k = 0;

		MCAL_UART_voidSendString(GLOB_u8NewAdmin);
	//	MCAL_UART_voidSendString(GLOB_u8NewLine);

		MCAL_UART_voidSendString(BACK);

		MCAL_UART_voidReceiveData(&LOC_u8Input);

		switch(LOC_u8Input)
		{
		case '1':



			i = 1000;
			MCAL_UART_voidSendString((u8*)"Enter Your Username: ");
			do
			{
				MCAL_UART_voidReceiveData(&LOC_u8BufferA);
				MCAL_UART_voidTransmitData((LOC_u8BufferA));
				LOC_u16ID = LOC_u16ID + ((LOC_u8BufferA - '0') * i);
				i /= 10;

			}while(i != 0);

			MCAL_UART_voidSendString(GLOB_u8NewLine);

			LOC_u8CheckID = Check_AdminID(LOC_u16ID);
			if(LOC_u8CheckID != ADMIN_NOT_FOUND)
			{
				MCAL_UART_voidSendString((u8*)"USERNAME ALREADY EXIST!!!");
		//		MCAL_UART_voidSendString(GLOB_u8NewLine);
				APP_Register_Page();
				//	goto ID;
			}
			else {/*Do Nothing*/}

			//		Pass:
			j = 1000;
			MCAL_UART_voidSendString((u8*)"Enter Your Password: ");
			do
			{
				MCAL_UART_voidReceiveData(&LOC_u8BufferB);
				MCAL_UART_voidTransmitData((LOC_u8BufferB));
				LOC_u16Pass = LOC_u16Pass + ((LOC_u8BufferB - '0') * j);
				j /= 10;
			}while(j != 0);
//			MCAL_UART_voidSendString(GLOB_u8NewLine);


			k = 1000;
			MCAL_UART_voidSendString((u8*)"Confirm Password: ");
			do
			{
				MCAL_UART_voidReceiveData(&LOC_u8BufferC);
				MCAL_UART_voidTransmitData((LOC_u8BufferC));
				LOC_u16PassConfirm = LOC_u16PassConfirm + ((LOC_u8BufferC - '0') * k);
				k /= 10;
			}while(k != 0);

			MCAL_UART_voidSendString(GLOB_u8NewLine);
			if(LOC_u16PassConfirm == LOC_u16Pass)
			{
				LOC_u8AdminEnteryFlag = Add_Admin(LOC_u16ID,LOC_u16Pass);
				MCAL_UART_voidSendString(((u8*)"Admin Registered Successfully"));
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
			}
			else
			{
				MCAL_UART_voidSendString((u8*)"Passwords Doesn't Match!!!");
	//			MCAL_UART_voidSendString(GLOB_u8NewLine);
				//			goto Pass;

			}

			break;

		case '0':
			MCAL_UART_voidTransmitData('0');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Back");
		//	MCAL_UART_voidSendString(GLOB_u8NewLine);
	//		Go back to the previous page
			LOC_u8BackFlag = 1;

			break;

		}
	}while(LOC_u8BackFlag != 1);


}


void APP_Options_Page(void)
{
	u8 LOC_u8Option = 0;
	u8 LOC_u8LogoutFlag = 0;
	do
	{
	APP_LM35WithDCmotor_Void_LM35WithDCmotorOnOff();
	MCAL_UART_voidSendString(GLOB_u8UserManagement);
//	MCAL_UART_voidSendString(GLOB_u8NewLine);
	MCAL_UART_voidSendString(GLOB_u8DevicesControl);
//	MCAL_UART_voidSendString(GLOB_u8NewLine);
	MCAL_UART_voidSendString(GLOB_u8DoorControl);
//	MCAL_UART_voidSendString(GLOB_u8NewLine);
	MCAL_UART_voidSendString(GLOB_u8Logout);
//	MCAL_UART_voidSendString(GLOB_u8NewLine);

	MCAL_UART_voidReceiveData(&LOC_u8Option);
	switch(LOC_u8Option)
	{
	case '1':
		LOC_u8LogoutFlag = 0;

		MCAL_UART_voidTransmitData('1');
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		APP_UserManagement_Page();

		break;
	case '2':
		LOC_u8LogoutFlag = 0;
		MCAL_UART_voidTransmitData('2');
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		APP_DeviceControl_Page();
		break;
	case '3':
		LOC_u8LogoutFlag = 0;
		MCAL_UART_voidTransmitData('3');
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		APP_DoorControl_Page();
		break;
	case '0':
		MCAL_UART_voidTransmitData('0');
		MCAL_UART_voidSendString(GLOB_u8NewLine);
//		Logout code
		MCAL_UART_voidSendString((u8*)"Logging Out");
		_delay_ms(100);
		MCAL_UART_voidTransmitData('.');
		_delay_ms(100);
		MCAL_UART_voidTransmitData('.');
		_delay_ms(100);
		MCAL_UART_voidTransmitData('.');
		_delay_ms(100);
		MCAL_UART_voidSendString(GLOB_u8NewLine);

		LOC_u8LogoutFlag = 1;
		break;
	}

	}while(LOC_u8LogoutFlag != 1);

}

void APP_UserManagement_Page(void)
{
	u8 LOC_u8Option = 0 ,LOC_u8BackFlag = 0 ;
	do
	{


		MCAL_UART_voidSendString(GLOB_u8NewUser);
		MCAL_UART_voidSendString(GLOB_u8RemoveUser);
		MCAL_UART_voidSendString(GLOB_u8RemoveAllUsers);
		MCAL_UART_voidSendString(BACK);

		MCAL_UART_voidReceiveData(&LOC_u8Option);

		switch(LOC_u8Option)
		{
		case '1':
			MCAL_UART_voidTransmitData('1');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Add New User");
	//		MCAL_UART_voidSendString(GLOB_u8NewLine);

			//		Registering user (Same as Admin but different functions)
			APP_RegisterNewUser_Page();

			break;
		case '2':
			MCAL_UART_voidTransmitData('2');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Remove/Delete User");
	//		MCAL_UART_voidSendString(GLOB_u8NewLine);
			APP_RemoveUser_Page();	//Function to remove user with given ID
			break;
		case '3':
			MCAL_UART_voidTransmitData('3');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Remove/Delete ALL Users");
		//	MCAL_UART_voidSendString(GLOB_u8NewLine);
			//		Delete all users
			APP_DeleteAllUsers_Page();
			break;
		case '0':
			MCAL_UART_voidTransmitData('0');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Back");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
			//		Go back to the previous page
			LOC_u8BackFlag = 1;
			break;
		}

	}
	while(LOC_u8BackFlag != 1);
}

void APP_DeviceControl_Page(void)
{
	u8 LOC_u8Option = 0 ,LOC_u8BackFlag = 0 ;
	do
	{
		MCAL_UART_voidSendString((u8*)"1. Lights\r\n");
		MCAL_UART_voidSendString((u8*)"2. AC\r\n");
		MCAL_UART_voidSendString(BACK);

		MCAL_UART_voidReceiveData(&LOC_u8Option);

		switch(LOC_u8Option)
		{
		case '1':
			MCAL_UART_voidTransmitData('1');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Lights:");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
			LOC_u8BackFlag = 0;

			APP_RoomLights_Page();

			break;
		case '2':
			MCAL_UART_voidTransmitData('2');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"AC:");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
			LOC_u8BackFlag = 0;
			APP_AC_Contol_Page();
			break;
		case '0':
			MCAL_UART_voidTransmitData('0');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Back");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
			//		Go back to the previous page
			LOC_u8BackFlag = 1;
			break;
		}

	}
	while(LOC_u8BackFlag != 1);

}
void APP_DoorControl_Page(void)
{
	u8 LOC_u8Break = 0;


	do
	{
		u8 LOC_u8LoopCounter =0,LOC_u8OpenFlag[5] = "open" ,LOC_u8CloseFlag[6] = "clos";
		u8 LOC_u8CheckOpen = 0,LOC_u8CheckClose = 0, LOC_u8BackFlag[5] = "back",LOC_u8CheckBack=0 ;
		MCAL_UART_voidSendString((u8*)"Choose by Typing: ");
//		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"open");
//		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"clos");
//		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"back");
//		MCAL_UART_voidSendString(GLOB_u8NewLine);


		for(LOC_u8LoopCounter = 0;LOC_u8LoopCounter <= 3 ;LOC_u8LoopCounter++)
		{
			MCAL_UART_voidReceiveData(&GLOB_u8DoorCommandReceived[LOC_u8LoopCounter]);
			MCAL_UART_voidTransmitData(GLOB_u8DoorCommandReceived[LOC_u8LoopCounter]);

		}
			MCAL_UART_voidSendString(GLOB_u8NewLine);

		for(LOC_u8LoopCounter = 0 ; GLOB_u8DoorCommandReceived[LOC_u8LoopCounter] != 0 ; LOC_u8LoopCounter++)
		{
			if(GLOB_u8DoorCommandReceived[LOC_u8LoopCounter] == LOC_u8OpenFlag[LOC_u8LoopCounter])
			{
				LOC_u8CheckOpen++;
			}
			else if (GLOB_u8DoorCommandReceived[LOC_u8LoopCounter] == LOC_u8CloseFlag[LOC_u8LoopCounter])
			{
				LOC_u8CheckClose++;
			}
			else if (GLOB_u8DoorCommandReceived[LOC_u8LoopCounter] == LOC_u8BackFlag[LOC_u8LoopCounter])
			{
				LOC_u8CheckBack++;
			}
			else
			{
				MCAL_UART_voidSendString((u8*)"Wrong Input!");
	//			MCAL_UART_voidSendString(GLOB_u8NewLine);

				LOC_u8Break = 0;
			}
		}
		if (LOC_u8CheckOpen == 4)
		{
			MCAL_UART_voidSendString((u8*)"OPENNING!");
	//		MCAL_UART_voidSendString(GLOB_u8NewLine);
			_delay_ms(1000);
			HAL_Servo_voidServoOpenDoor();
			//Open Door (Servo)

				LOC_u8Break = 0;
		}
		else if (LOC_u8CheckClose == 4)
		{
			MCAL_UART_voidSendString((u8*)"CLOSING!");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
			_delay_ms(1000);
			HAL_Servo_voidServoCloseDoor();
			//Close Door (Servo)

				LOC_u8Break = 0;
		}
		else if (LOC_u8CheckBack == 4)
		{
			MCAL_UART_voidSendString((u8*)"BACKING!");
	//		MCAL_UART_voidSendString(GLOB_u8NewLine);
			//Go back to options
				LOC_u8Break = 1;
		}
		else
		{
			//Invalid Option
		}

	}
	while(LOC_u8Break != 1);
}


void APP_RegisterNewUser_Page(void)
{
	u8 LOC_u8Option = 0,LOC_u8BackFlag = 0;
	do
	{

		MCAL_UART_voidSendString(GLOB_u8NewUser);
//		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString(BACK);

		MCAL_UART_voidReceiveData(&LOC_u8Option);

		switch(LOC_u8Option)
		{
		case '1':
			MCAL_UART_voidTransmitData('1');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"New User:");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);

			u8 LOC_u8BufferA = 0,LOC_u8BufferB = 0,LOC_u8BufferC = 0, LOC_u8CheckID = 0,LOC_u8UserEnteryFlag = 0;
			u16 LOC_u16ID = 0,LOC_u16Pass = 0,LOC_u16PassConfirm = 0,i = 0,j = 0,k = 0;


			i = 1000;
			MCAL_UART_voidSendString((u8*)"Enter Username: ");
			do
			{
				MCAL_UART_voidReceiveData(&LOC_u8BufferA);
				MCAL_UART_voidTransmitData((LOC_u8BufferA));
				LOC_u16ID = LOC_u16ID + ((LOC_u8BufferA - '0') * i);
				i /= 10;

			}while(i != 0);

			MCAL_UART_voidSendString(GLOB_u8NewLine);

			LOC_u8CheckID = Check_UserID(LOC_u16ID);
			if(LOC_u8CheckID != ADMIN_NOT_FOUND)
			{
				MCAL_UART_voidSendString((u8*)"USERNAME ALREADY EXIST!!!");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
//				LOC_u8BackFlag = 1;
				break;
				APP_RegisterNewUser_Page();

				//	goto ID;
			}
			else {/*Do Nothing*/}

			//		Pass:
			j = 1000;
			MCAL_UART_voidSendString((u8*)"Enter Your Password: ");
			do
			{
				MCAL_UART_voidReceiveData(&LOC_u8BufferB);
				MCAL_UART_voidTransmitData((LOC_u8BufferB));
				LOC_u16Pass = LOC_u16Pass + ((LOC_u8BufferB - '0') * j);
				j /= 10;
			}while(j != 0);
			MCAL_UART_voidSendString(GLOB_u8NewLine);


			k = 1000;
			MCAL_UART_voidSendString((u8*)"Confirm Password: ");
			do
			{
				MCAL_UART_voidReceiveData(&LOC_u8BufferC);
				MCAL_UART_voidTransmitData((LOC_u8BufferC));
				LOC_u16PassConfirm = LOC_u16PassConfirm + ((LOC_u8BufferC - '0') * k);
				k /= 10;
			}while(k != 0);

			MCAL_UART_voidSendString(GLOB_u8NewLine);
			if(LOC_u16PassConfirm == LOC_u16Pass)
			{
				LOC_u8UserEnteryFlag = Add_User(LOC_u16ID,LOC_u16Pass);
				MCAL_UART_voidSendString(((u8*)"User Registered Successfully"));
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
				LOC_u8BackFlag = 1;
			}
			else
			{
				MCAL_UART_voidSendString((u8*)"Passwords Doesn't Match!!!");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
				//			goto Pass;
				LOC_u8BackFlag = 0;
			}

			break;


//			break;

		case '0':
			MCAL_UART_voidTransmitData('0');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Back");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
	//		Go back to the previous page
			LOC_u8BackFlag = 1;
			break;
		}
	}
	while (LOC_u8BackFlag != 1);
}


void APP_RemoveUser_Page(void)
{
	u8 LOC_u8Option = 0,LOC_u8BackFlag = 0;
	do
	{

		MCAL_UART_voidSendString((u8*)"1 --> Remove User");
//		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString(BACK);

		MCAL_UART_voidReceiveData(&LOC_u8Option);

		switch(LOC_u8Option)
		{
		case '1':
			MCAL_UART_voidTransmitData('1');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Remove User: ");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);

			u8 LOC_u8BufferA = 0, LOC_u8CheckConfirmation = 0,LOC_u8UserRemoveFlag = 0;
			u16 LOC_u16ID = 0,i = 0;


			i = 1000;
			MCAL_UART_voidSendString((u8*)"Enter UserID To Be Removed: ");
			do
			{
				MCAL_UART_voidReceiveData(&LOC_u8BufferA);
				MCAL_UART_voidTransmitData((LOC_u8BufferA));
				LOC_u16ID = LOC_u16ID + ((LOC_u8BufferA - '0') * i);
				i /= 10;

			}while(i != 0);

			MCAL_UART_voidSendString(GLOB_u8NewLine);

			MCAL_UART_voidSendString((u8*)"1 --> Confirm Removing User");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"0 --> Cancel");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);

			MCAL_UART_voidReceiveData(&LOC_u8CheckConfirmation);

			if(LOC_u8CheckConfirmation == '1')
			{
				MCAL_UART_voidTransmitData('1');
				MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"REMOVING USER ...");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
				LOC_u8UserRemoveFlag = Remove_User(LOC_u16ID);
				_delay_ms(1000);
				if (LOC_u8UserRemoveFlag == USER_REMOVED_SUCCESSFULLY)
				{
					MCAL_UART_voidSendString((u8*)"USER REMOVED SUCCESSFULLY !!");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					LOC_u8BackFlag = 1;

				}
				else if (LOC_u8UserRemoveFlag == USER_NOT_FOUND)
				{
					MCAL_UART_voidSendString((u8*)"USER NOT FOUND !!");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					LOC_u8BackFlag = 0;
				}
				else{/*Do Nothing*/}
			}
			else if (LOC_u8CheckConfirmation == '0')
			{
				MCAL_UART_voidTransmitData('0');
				MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"Cancel ...");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
				_delay_ms(1000);
				LOC_u8BackFlag = 1;
			}
			break;


		case '0':
			MCAL_UART_voidTransmitData('0');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Back");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
	//		Go back to the previous page
			LOC_u8BackFlag = 1;
			break;
		default:
			MCAL_UART_voidSendString((u8*)"Invalid Input!");
			LOC_u8BackFlag = 0;
			break;
		}
	}
	while (LOC_u8BackFlag != 1);

}

void APP_DeleteAllUsers_Page(void)
{
	u8 LOC_u8Option = 0;
	MCAL_UART_voidSendString((u8*)"1.Confirm ");
//	MCAL_UART_voidSendString(GLOB_u8NewLine);
	MCAL_UART_voidSendString((u8*)"0.Cancel ");
//	MCAL_UART_voidSendString(GLOB_u8NewLine);
	MCAL_UART_voidReceiveData(&LOC_u8Option);

	switch(LOC_u8Option)
	{
	case '1':
		MCAL_UART_voidTransmitData('1');
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"Deleting ...");
//		MCAL_UART_voidSendString(GLOB_u8NewLine);
		APP_Registeration_voidDeleteAllUsers();
		_delay_ms(1000);

		break;
	case '0':
		MCAL_UART_voidTransmitData('0');
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"Cancel ...");
//		MCAL_UART_voidSendString(GLOB_u8NewLine);
		_delay_ms(1000);
		break;
	}

}




void APP_RoomLights_Page(void)
{
	u8 LOC_u8BackFlag = 0 ;

	do
	{
		u8 LOC_u8Option = 0,LOC_u8LED1_Option =0,LOC_u8LED2_Option =0,LOC_u8LED3_Option =0,LOC_u8LED4_Option =0,LOC_u8LED5_Option =0,LOC_u8Dimmer = 0;

		MCAL_UART_voidSendString(LIGHT1);
		MCAL_UART_voidSendString(LIGHT2);
		MCAL_UART_voidSendString(LIGHT3);
		MCAL_UART_voidSendString(LIGHT4);
		MCAL_UART_voidSendString(LIGHT5);
		MCAL_UART_voidSendString(DIMMER);
		MCAL_UART_voidSendString(BACK);


		MCAL_UART_voidReceiveData(&LOC_u8Option);

		switch(LOC_u8Option)
		{
		case '1':
			MCAL_UART_voidTransmitData('1');
			u8 LOC_u8InsideRoom1 = 0 ;
			do
			{

				MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"Room 1 Light:");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);

				MCAL_UART_voidSendString((u8*)"1 --> Turn ON Light");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"2 --> Turn OFF Light");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"3 --> Toggle Light");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"0 --> Back");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);

				MCAL_UART_voidReceiveData(&LOC_u8LED1_Option);

				switch(LOC_u8LED1_Option)
				{
				case '1':
					MCAL_UART_voidTransmitData('1');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"ON...");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_ON);
					LOC_u8InsideRoom1 = 0;
					break;
				case '2':
					MCAL_UART_voidTransmitData('2');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"OFF...");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_OFF);
					LOC_u8InsideRoom1 = 0;
					break;
				case '3':
					MCAL_UART_voidTransmitData('3');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"Toggling...");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_TOG);
					LOC_u8InsideRoom1 = 0;
					break;
				case '0':
					MCAL_UART_voidTransmitData('0');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"Back");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					LOC_u8InsideRoom1 = 1;
					break;
				}

			}
			while(LOC_u8InsideRoom1 == 0);

			LOC_u8BackFlag = 0;


			break;
		case '2':
			MCAL_UART_voidTransmitData('2');
			u8 LOC_u8InsideRoom2 = 0 ;

			do
			{

				MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"Room 2 Light:");
	//			MCAL_UART_voidSendString(GLOB_u8NewLine);

				MCAL_UART_voidSendString((u8*)"1 --> Turn ON Light");
	//			MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"2 --> Turn OFF Light");
	//			MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"3 --> Toggle Light");
	//			MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"0 --> Back");
	//			MCAL_UART_voidSendString(GLOB_u8NewLine);

				MCAL_UART_voidReceiveData(&LOC_u8LED2_Option);

				switch(LOC_u8LED2_Option)
				{
				case '1':
					MCAL_UART_voidTransmitData('1');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"ON...");
	//				MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_ON);
					LOC_u8InsideRoom2 = 0;
					break;
				case '2':
					MCAL_UART_voidTransmitData('2');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"OFF...");
	//				MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_OFF);
					LOC_u8InsideRoom2 = 0;
					break;
				case '3':
					MCAL_UART_voidTransmitData('3');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"Toggling...");
		//			MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_TOG);
					LOC_u8InsideRoom2 = 0;
					break;
				case '0':
					MCAL_UART_voidTransmitData('0');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"Back");
			//		MCAL_UART_voidSendString(GLOB_u8NewLine);
					LOC_u8InsideRoom2 = 1;
					break;

				}

			}while(LOC_u8InsideRoom2 == 0);

			LOC_u8BackFlag = 0;

			break;
		case '3':
			MCAL_UART_voidTransmitData('3');
			u8 LOC_u8InsideRoom3 = 0 ;
			do
			{

				MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"Room 3 Light:");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);

				MCAL_UART_voidSendString((u8*)"1 --> Turn ON Light");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"2 --> Turn OFF Light");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"3 --> Toggle Light");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString(BACK);

				MCAL_UART_voidReceiveData(&LOC_u8LED3_Option);

				switch(LOC_u8LED3_Option)
				{
				case '1':
					MCAL_UART_voidTransmitData('1');
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"ON...");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_ON);
					LOC_u8InsideRoom3 = 0;
					break;
				case '2':
					MCAL_UART_voidTransmitData('2');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"OFF...");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_OFF);
					LOC_u8InsideRoom3 = 0;
					break;
				case '3':
					MCAL_UART_voidTransmitData('3');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"Toggling...");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_TOG);
					LOC_u8InsideRoom3 = 0;
					break;
				case '0':
					MCAL_UART_voidTransmitData('0');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"Back");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					LOC_u8InsideRoom3 = 1;
					break;

				}

			}while(LOC_u8InsideRoom3 == 0);


			LOC_u8BackFlag = 0;

			break;
		case '4':
			MCAL_UART_voidTransmitData('4');
			u8 LOC_u8InsideRoom4 = 0 ;
			do
			{

				MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"Room 4 Light:");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);

				MCAL_UART_voidSendString((u8*)"1 --> Turn ON Light");
	//			MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"2 --> Turn OFF Light");
		//		MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"3 --> Toggle Light");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString(BACK);

				MCAL_UART_voidReceiveData(&LOC_u8LED4_Option);

				switch(LOC_u8LED4_Option)
				{
				case '1':
					MCAL_UART_voidTransmitData('1');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"ON...");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_ON);
					LOC_u8InsideRoom4 = 0;
					break;
				case '2':
					MCAL_UART_voidTransmitData('2');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"OFF...");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_OFF);
					LOC_u8InsideRoom4 = 0;
					break;
				case '3':
					MCAL_UART_voidTransmitData('3');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"Toggling...");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_TOG);
					LOC_u8InsideRoom4 = 0;
					break;
				case '0':
					MCAL_UART_voidTransmitData('0');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"Back");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					LOC_u8InsideRoom4 = 1;
					break;

				}

			}while(LOC_u8InsideRoom4 == 0);

			LOC_u8BackFlag = 0;

			break;
		case '5':
			MCAL_UART_voidTransmitData('5');
			u8 LOC_u8InsideRoom5 = 0 ;
			do
			{

				MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"Room 5 Light:");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);

				MCAL_UART_voidSendString((u8*)"1 --> Turn ON Light");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"2 --> Turn OFF Light");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString((u8*)"3 --> Toggle Light");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
				MCAL_UART_voidSendString(BACK);
//				MCAL_UART_voidSendString(GLOB_u8NewLine);

				MCAL_UART_voidReceiveData(&LOC_u8LED5_Option);

				switch(LOC_u8LED5_Option)
				{
				case '1':
					MCAL_UART_voidTransmitData('1');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"ON...");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_ON);
					LOC_u8InsideRoom5 = 0;
					break;
				case '2':
					MCAL_UART_voidTransmitData('2');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"OFF...");
	//				MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_OFF);
					LOC_u8InsideRoom5 = 0;
					break;
				case '3':
					MCAL_UART_voidTransmitData('3');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"Toggling...");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_TOG);
					LOC_u8InsideRoom5 = 0;
					break;
				case '0':
					MCAL_UART_voidTransmitData('0');
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					MCAL_UART_voidSendString((u8*)"Back");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
					LOC_u8InsideRoom5 = 1;
					break;

				}

			}while(LOC_u8InsideRoom5 == 0);


			LOC_u8BackFlag = 0;

			break;
		case '6':
			LOC_u8Dimmer =0;
			MCAL_UART_voidTransmitData('6');
/*
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Dimmer:");
*/
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Choose Brightness level (0 <--> 9):");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidReceiveData(&LOC_u8Dimmer);
			MCAL_UART_voidTransmitData(LOC_u8Dimmer);
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			HAL_MCP4018_POT_voidWriteStep(((LOC_u8Dimmer-'0')*14));


			LOC_u8BackFlag = 0;
			//Dimmer Function
			break;
		case '0':
			MCAL_UART_voidTransmitData('0');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Back");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
			//		Go back to the previous page
			LOC_u8BackFlag = 1;
			break;
		}

	}
	while(LOC_u8BackFlag != 1);

}

void APP_AC_Contol_Page(void)
{
	u8 LOC_u8Option = 0,LOC_u8BackFlag = 0;
	do
	{

		MCAL_UART_voidSendString((u8*)"1.ON");
//		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"2.OFF");
//		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"3.AUTO");
//		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"0.BACK ");
//		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidReceiveData(&LOC_u8Option);

		switch(LOC_u8Option)
		{
		case '1':
			MCAL_UART_voidTransmitData('1');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"ON");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_TIMER_Timer0_InterruptOVF_Disable();
			MCAL_Interrupt_GIE_Disable();
			_delay_ms(100);
			HAL_DCMOTOR_void_DcMotorClockWise(7);
			LOC_u8BackFlag = 0;

			break;
		case '2':
			MCAL_UART_voidTransmitData('2');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"OFF");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_TIMER_Timer0_InterruptOVF_Disable();
			MCAL_Interrupt_GIE_Disable();
			_delay_ms(100);
			HAL_DCMOTOR_void_DcMotorStop();
			LOC_u8BackFlag = 0;

			break;
		case '3':
			MCAL_UART_voidTransmitData('3');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"AUTO");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_TIMER_Timer0_InterruptOVF_Enable();
			MCAL_Interrupt_GIE_Enable();

			_delay_ms(10);
			LOC_u8BackFlag = 0;
			break;
		case '0':
			MCAL_UART_voidTransmitData('0');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"BACK");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
			_delay_ms(10);
			LOC_u8BackFlag = 1;

			break;
		}
	}while(LOC_u8BackFlag != 1);


}


void APP_AC_Check(void)
{
	APP_LM35WithDCmotor_Void_LM35WithDCmotorOnOff();
}

