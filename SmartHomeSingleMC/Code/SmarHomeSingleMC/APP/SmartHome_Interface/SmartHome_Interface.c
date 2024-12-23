/*
 * Bluetooth.c
 *
 *  Created on: Feb 4, 2024
 *      Author: Abdulrahman Ayman
 */
#include "SmartHome_Interface.h"
extern u8 m;
u8 volatile GLOB_u8LoginFlag = 0;
u8 volatile G_Keypad_Value;

enum SystemMode { USER_MODE, ADMIN_MODE };
enum SystemMode GLOB_ECurrentMode = ADMIN_MODE;

u8 GLOB_u8DoorCommandReceived[6] = {};
u8 GLOB_u8NewLine[5] = 			"\r\n";
//u8 GLOB_u8IDString[8] = {0} ;

/************************	Register Page Text	**********************/
//u8 GLOB_u8NewAdmin[16] =		"1 --> New Admin";

/************************	Home Page Text	**********************/
//u8 GLOB_u8WelcomeString[23] =	"Welcome to Lobby!\r\n" ;
//u8 GLOB_u8LoginString[15] = 	"1 --> LOGIN" ;
//u8 GLOB_u8RegisterString [20] = "2 --> Register" ;

/************************	Options Page Text	**********************/
//u8 GLOB_u8UserManagement[22] = 	"1 --> User Management" ;
//u8 GLOB_u8DevicesControl[22] = 	"2 --> Devices" ;
//u8 GLOB_u8DoorControl[20] =		"3 --> Door" ;
//u8 GLOB_u8Logout[13] = 			"0 --> Logout";

/************************	User Management Page	*******************/
//u8 GLOB_u8NewUser[19] 		=	"1 --> New User\r\n";
//u8 GLOB_u8RemoveUser[24] 	= 	"2 --> Remove User\r\n";
//u8 GLOB_u8RemoveAllUsers[27]= 	(u8*)"3 --> Remove All Users\r\n";
//u8 GLOB_u8GoBack[11] 		= 	"0 --> Back";
//u8 GLOB_u8GetListOfUsers[20] = 	"4 --> Users List"; (Target)
//u8 GLOB_u8NewUser[20] = 	"5 --> Reset Memory\r\n";


union {
	u8 volatile GLOB_u8AllFlags;
	struct GLOB_u8Flags{
		u8 volatile GLOB_u8Flag_LED1 	:1;
		u8 volatile GLOB_u8Flag_LED2 	:1;
		u8 volatile GLOB_u8Flag_LED3 	:1;
		u8 volatile GLOB_u8Flag_LED4 	:1;
		u8 volatile GLOB_u8Flag_LED5	:1;
		u8 volatile GLOB_u8Flag_Dimmer 	:1;
		u8 volatile GLOB_u8Flag_AC 	 	:1;
		u8 volatile GLOB_u8Flag_Door 	:1;

	}Flags;
}State;

const s8 LoginMassagesArray[5][20] PROGMEM = {
    "Welcome to Lobby!",		// #define WELCOME  	0
    "1--> LOGIN",				// #define LOGIN 		1
    "2--> Register",			// #define REGISTER 	2
    "3--> Devices State",		// #define STATES		3
    "*--> Disconnect"			// #define DISCONNECT	4
};
//	"Enter Your Username: "	,	// #define USER			5
//	"Enter Your Password: "	,	// #define PASSWORD		6




/*
u8 Welcome[] PROGMEM =  		"Welcome to Lobby!\r\n";
u8 Login[] PROGMEM =			"1 --> LOGIN\r\n";
u8 Register[] PROGMEM =			"2 --> Register\r\n";
u8 State[] PROGMEM =			"3 --> Devices State\r\n";
u8 Disconnect[] PROGMEM =		"* --> Disconnect\r\n";
u8 UserNameEntry[] PROGMEM =	"Enter Your Username: ";
u8 PasswordEntry[] PROGMEM =	"Enter Your Password: ";
*/

//Admins and Users.
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
	//Dimmer Init:
	HAL_MCP4018_POT_voidWriteStep(0);
	//Breakdown Alarm Init:
	HAL_Buzzer_u8BuzzerInit(Buzzer_Port,Buzzer_Pin);
	//AC Init:
	APP_LM35WithDCmotor_Void_LM35WithDCmotorinit();
	MCAL_TIMER_Timer0_Init(NORMAL,CLK_PRE1024,NORMAL_OC0);
	MCAL_TIMER_voidTimer0_OVFSetCallBack(APP_AC_Check);

	//LCD_INIT & KEYPAD_INIT
	HAL_KEYPAD_u8_KaypadInit();
	HAL_LCD_u8_LcdInit();

	//Enabling UART Receive complete Interrupt.
	MCAL_Interrupt_GIE_Enable();
	//MCAL_UART_voidReceiveCompleteInterruptEnable();
	MCAL_UART_voidReceiveCompleteSetCallBack(APP_Admin_Mode_Check);
	/*
	MCAL_TIMER_Timer0_InterruptOVF_Enable();
	 */


}

//	MCAL_UART_voidSendString((u8*)"Welcome to Lobby!\r\n");
//	MCAL_UART_voidSendString((u8*)"1 --> LOGIN");
//	MCAL_UART_voidSendString(GLOB_u8NewLine);
//	MCAL_UART_voidSendString((u8*)"2 --> Register");
//	MCAL_UART_voidSendString(GLOB_u8NewLine);
//	MCAL_UART_voidSendString((u8*)"3 --> Devices State");
//	MCAL_UART_voidSendString(GLOB_u8NewLine);
//	MCAL_UART_voidSendString((u8*)"* --> Disconnect");
//	MCAL_UART_voidSendString(GLOB_u8NewLine);
void PrintMassage(u8 LOC_u8ReceivedArray[5][20],u8 LOC_u8StringIndex,u8 LOC_NewLineFlag)
{

	u8 LOC_u8Buffer[20];
	strcpy_P(LOC_u8Buffer, (PGM_P) LOC_u8ReceivedArray[LOC_u8StringIndex]);
	MCAL_UART_voidSendString(LOC_u8Buffer);
	if(LOC_NewLineFlag)
	{
		MCAL_UART_voidSendString(GLOB_u8NewLine);
	}
}

//Admins and Users.
void APP_Home_Page(void)
{

	if(GLOB_ECurrentMode == ADMIN_MODE)
	{
		APP_Admin_Choices();

	}
	else if(GLOB_ECurrentMode == USER_MODE)
	{
		APP_User_Choices();
	}
	else
	{
		/*Do Nothing.*/
	}
}


void APP_Admin_Choices(void)
{
	u8 LOC_u8FirstDataReceived = 0 ;
	PrintMassage(LoginMassagesArray,MSG_WELCOME,1);
	PrintMassage(LoginMassagesArray,MSG_LOGIN,1);
	PrintMassage(LoginMassagesArray,MSG_REGISTER,1);
	PrintMassage(LoginMassagesArray,MSG_STATES,1);
	PrintMassage(LoginMassagesArray,MSG_DISCONNECT,1);

	MCAL_UART_voidReceiveData(&LOC_u8FirstDataReceived);
	MCAL_UART_voidTransmitData(LOC_u8FirstDataReceived);
	MCAL_UART_voidSendString(GLOB_u8NewLine);
	switch(LOC_u8FirstDataReceived)
	{
	case '1':
		APP_Login_Page();
		break;
	case '2':
		APP_Register_Page();
		break;
	case '3':
		APP_Devices_Status();
		break;
	case '*':
		GLOB_ECurrentMode = USER_MODE;
		MCAL_UART_voidReceiveCompleteInterruptEnable();

		return;
		break;
	}

}

void APP_User_Choices(void)
{

	u16 LOC_u16UserID = 0;
//	G_Mainflag = 0;
	m=1;
	HAL_KEYPAD_u8_HomeKaypadButton(&G_Keypad_Value);
	if(G_Keypad_Value != 0)
	{
		LOC_u16UserID = APP_USERID_u8_AppUserID();
		APP_PASSWORD_u8_AppGetPassword(LOC_u16UserID);
	}
	APP_void_AppAfterFirstChoice();
}

//Admins and Users.
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

	MCAL_UART_voidSendString(GLOB_u8NewLine);
	LOC_u8Check_AdminPassword = Check_AdminPassword(LOC_u16ID,LOC_u16Pass);

	if(LOC_u8Check_AdminID == ADMIN_NOT_FOUND )
	{
		MCAL_UART_voidSendString((u8*)"USERNAME NOT FOUND!!!");
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		LOC_u8LoginFailed--;

		if (LOC_u8LoginFailed == 0)
		{
			MCAL_UART_voidSendString((u8*)"Max Tries!!!");
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
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		LOC_u8LoginFailed--;
		if (LOC_u8LoginFailed == 0)
		{
			MCAL_UART_voidSendString((u8*)"Max Tries!!!");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			while(1)
			{
				HAL_Buzzer_u8BuzzerMode(Buzzer_Port,Buzzer_Pin,Buzzer_ON);
			}

		}
		else
		{
			MCAL_UART_voidSendString((u8*)"Tries Left:");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidTransmitData((LOC_u8LoginFailed+'0'));
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			//			goto Pass;
			APP_Login_Page();
		}
	}
	else
	{
		LOC_u8LoginFailed = 3;
		MCAL_UART_voidSendString((u8*)"Welcome to Lobby!\r\n");
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		APP_Options_Page();

	}




}

//Admins.
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

		MCAL_UART_voidSendString((u8*)"1 --> New Admin");
		MCAL_UART_voidSendString(GLOB_u8NewLine);

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
				MCAL_UART_voidSendString(GLOB_u8NewLine);
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
				LOC_u8AdminEnteryFlag = Add_Admin(LOC_u16ID,LOC_u16Pass);
				MCAL_UART_voidSendString(((u8*)"Admin Registered Successfully"));
				MCAL_UART_voidSendString(GLOB_u8NewLine);
			}
			else
			{
				MCAL_UART_voidSendString((u8*)"Passwords Doesn't Match!!!");
				MCAL_UART_voidSendString(GLOB_u8NewLine);
				//			goto Pass;

			}

			break;

		case '0':
			MCAL_UART_voidTransmitData('0');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Back");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			//		Go back to the previous page
			LOC_u8BackFlag = 1;

			break;

		}
	}while(LOC_u8BackFlag != 1);


}

//Admin and Users(Except Door).
void APP_Options_Page(void)
{
	u8 LOC_u8Option = 0;
	u8 LOC_u8LogoutFlag = 0;
	do
	{
		MCAL_UART_voidSendString((u8*)"1 --> User Management");
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"2 --> Devices");
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"3 --> Door");
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"0 --> Logout");
		MCAL_UART_voidSendString(GLOB_u8NewLine);

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
			_delay_ms(50);
			MCAL_UART_voidTransmitData('.');
			_delay_ms(50);
			MCAL_UART_voidTransmitData('.');
			_delay_ms(50);
			MCAL_UART_voidTransmitData('.');
			_delay_ms(50);
			MCAL_UART_voidSendString(GLOB_u8NewLine);

			LOC_u8LogoutFlag = 1;
			//APP_Home_Page();
			break;
		}

	}while(LOC_u8LogoutFlag != 1);

}

//Admin.
void APP_UserManagement_Page(void)
{
	u8 LOC_u8Option = 0 ,LOC_u8BackFlag = 0 ;
	do
	{


		MCAL_UART_voidSendString((u8*)"1 --> New User\r\n");
		MCAL_UART_voidSendString((u8*)"2 --> Remove User\r\n");
		MCAL_UART_voidSendString((u8*)"3 --> Remove All Users\r\n");
		MCAL_UART_voidSendString(BACK);

		MCAL_UART_voidReceiveData(&LOC_u8Option);

		switch(LOC_u8Option)
		{
		case '1':
			MCAL_UART_voidTransmitData('1');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Add New User");
			MCAL_UART_voidSendString(GLOB_u8NewLine);

			//		Registering user (Same as Admin but different functions)
			APP_RegisterNewUser_Page();

			break;
		case '2':
			MCAL_UART_voidTransmitData('2');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Remove/Delete User");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			APP_RemoveUser_Page();	//Function to remove user with given ID
			break;
		case '3':
			MCAL_UART_voidTransmitData('3');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Remove/Delete ALL Users");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			//		Delete all users
			APP_DeleteAllUsers_Page();
			break;
		case '0':
			MCAL_UART_voidTransmitData('0');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Back");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			//		Go back to the previous page
			LOC_u8BackFlag = 1;
			break;
		}

	}
	while(LOC_u8BackFlag != 1);
}

//Admin and Users.
void APP_DeviceControl_Page(void)
{
	u8 LOC_u8Option = 0 ,LOC_u8BackFlag = 0 ;
	do
	{
		MCAL_UART_voidSendString((u8*)"1. Lights\r\n");
		MCAL_UART_voidSendString((u8*)"2. AC\r\n");
		MCAL_UART_voidSendString((u8*)"3. Devices Status\r\n");
		MCAL_UART_voidSendString(BACK);

		MCAL_UART_voidReceiveData(&LOC_u8Option);
			MCAL_UART_voidTransmitData(LOC_u8Option);
			MCAL_UART_voidSendString(GLOB_u8NewLine);

		switch(LOC_u8Option)
		{
		case '1':
			MCAL_UART_voidSendString((u8*)"Lights:");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			LOC_u8BackFlag = 0;

			APP_RoomLights_Page();

			break;
		case '2':
			MCAL_UART_voidSendString((u8*)"AC:");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			LOC_u8BackFlag = 0;
			APP_AC_Contol_Page();
			break;
		case '3':
			MCAL_UART_voidSendString((u8*)"Running Devices:");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			LOC_u8BackFlag = 0;
			APP_Devices_Status();
			break;
		case '0':
			MCAL_UART_voidSendString((u8*)"Back");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			//		Go back to the previous page
			LOC_u8BackFlag = 1;
			break;
		}

	}
	while(LOC_u8BackFlag != 1);

}

//Admin.
void APP_DoorControl_Page(void)
{
	u8 LOC_u8Break = 0;


	do
	{
//		u8 LOC_u8LoopCounter =0
		u8 LOC_u8OpenFlag[5] = "open" ,LOC_u8CloseFlag[6] = "close";
		u8 LOC_u8CheckOpen = 1,LOC_u8CheckClose = 1, LOC_u8BackFlag[5] = "back",LOC_u8CheckBack=1 ;
		MCAL_UART_voidSendString((u8*)"Choose by Typing: ");
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"open");
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"close");
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"back");
		MCAL_UART_voidSendString(GLOB_u8NewLine);


		MCAL_UART_voidReceiveString(GLOB_u8DoorCommandReceived);
		MCAL_UART_voidSendString((u8*)"You Entered: ");
		MCAL_UART_voidSendString(GLOB_u8DoorCommandReceived);



		/*
		for(LOC_u8LoopCounter = 0;LOC_u8LoopCounter <= 3 ;LOC_u8LoopCounter++)
		{
			MCAL_UART_voidReceiveData(&GLOB_u8DoorCommandReceived[LOC_u8LoopCounter]);
			MCAL_UART_voidTransmitData(GLOB_u8DoorCommandReceived[LOC_u8LoopCounter]);

		}
		 */
		MCAL_UART_voidSendString(GLOB_u8NewLine);

		LOC_u8CheckBack = (u8)strcmp(LOC_u8BackFlag,GLOB_u8DoorCommandReceived);
		LOC_u8CheckOpen = (u8)strcmp(LOC_u8OpenFlag,GLOB_u8DoorCommandReceived);
		LOC_u8CheckClose = (u8)strcmp(LOC_u8CloseFlag,GLOB_u8DoorCommandReceived);


		/*
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
				MCAL_UART_voidSendString(GLOB_u8NewLine);

				LOC_u8Break = 0;
			}
		}
		 */
		if (LOC_u8CheckOpen == 0)
		{
			MCAL_UART_voidSendString((u8*)"OPENNING!");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			_delay_ms(1000);
			HAL_Servo_voidServoOpenDoor();
			State.Flags.GLOB_u8Flag_Door = 1;
			//Open Door (Servo)

			LOC_u8Break = 0;
		}
		else if (LOC_u8CheckClose == 0)
		{
			MCAL_UART_voidSendString((u8*)"CLOSING!");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			_delay_ms(1000);
			HAL_Servo_voidServoCloseDoor();
			//Close Door (Servo)
			State.Flags.GLOB_u8Flag_Door = 0;

			LOC_u8Break = 0;
		}
		else if (LOC_u8CheckBack == 0)
		{
			MCAL_UART_voidSendString((u8*)"BACKING!");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			//Go back to options
			LOC_u8Break = 1;
		}
		else
		{
			//Invalid Option
			MCAL_UART_voidSendString((u8*)"Wrong Input!");
			MCAL_UART_voidSendString(GLOB_u8NewLine);

			LOC_u8Break = 0;

		}

	}
	while(LOC_u8Break != 1);
}

//Admin.
void APP_RegisterNewUser_Page(void)
{
	u8 LOC_u8Option = 0,LOC_u8BackFlag = 0;
	do
	{

		MCAL_UART_voidSendString((u8*)"1 --> New User\r\n");
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString(BACK);

		MCAL_UART_voidReceiveData(&LOC_u8Option);

		switch(LOC_u8Option)
		{
		case '1':
			MCAL_UART_voidTransmitData('1');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"New User:");
			MCAL_UART_voidSendString(GLOB_u8NewLine);

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
				MCAL_UART_voidSendString(GLOB_u8NewLine);
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
				MCAL_UART_voidSendString(GLOB_u8NewLine);
				LOC_u8BackFlag = 1;
			}
			else
			{
				MCAL_UART_voidSendString((u8*)"Passwords Doesn't Match!!!");
				MCAL_UART_voidSendString(GLOB_u8NewLine);
				//			goto Pass;
				LOC_u8BackFlag = 0;
			}

			break;


			//			break;

		case '0':
			MCAL_UART_voidTransmitData('0');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Back");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			//		Go back to the previous page
			LOC_u8BackFlag = 1;
			break;
		}
	}
	while (LOC_u8BackFlag != 1);
}

//Admin.
void APP_RemoveUser_Page(void)
{
//	u8 LOC_u8Option = 0,LOC_u8BackFlag = 0;
//	do
//	{
//
//		MCAL_UART_voidSendString((u8*)"1 --> Remove User");
//		MCAL_UART_voidSendString(GLOB_u8NewLine);
//		MCAL_UART_voidSendString(BACK);
//
//		MCAL_UART_voidReceiveData(&LOC_u8Option);
//
//		switch(LOC_u8Option)
//		{
//		case '1':
//			MCAL_UART_voidTransmitData('1');
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
//			MCAL_UART_voidSendString((u8*)"Remove User: ");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
//
//			u8 LOC_u8BufferA = 0, LOC_u8CheckConfirmation = 0,LOC_u8UserRemoveFlag = 0;
//			u16 LOC_u16ID = 0,i = 0;
//
//
//			i = 1000;
//			MCAL_UART_voidSendString((u8*)"Enter UserID To Be Removed: ");
//			do
//			{
//				MCAL_UART_voidReceiveData(&LOC_u8BufferA);
//				MCAL_UART_voidTransmitData((LOC_u8BufferA));
//				LOC_u16ID = LOC_u16ID + ((LOC_u8BufferA - '0') * i);
//				i /= 10;
//
//			}while(i != 0);
//
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
//
//			MCAL_UART_voidSendString((u8*)"1 --> Confirm Removing User");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
//			MCAL_UART_voidSendString((u8*)"0 --> Cancel");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
//
//			MCAL_UART_voidReceiveData(&LOC_u8CheckConfirmation);
//
//			if(LOC_u8CheckConfirmation == '1')
//			{
//				MCAL_UART_voidTransmitData('1');
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
//				MCAL_UART_voidSendString((u8*)"REMOVING USER ...");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
//				LOC_u8UserRemoveFlag = Remove_User(LOC_u16ID);
//				_delay_ms(1000);
//				if (LOC_u8UserRemoveFlag == USER_REMOVED_SUCCESSFULLY)
//				{
//					MCAL_UART_voidSendString((u8*)"USER REMOVED SUCCESSFULLY !!");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
//					LOC_u8BackFlag = 1;
//
//				}
//				else if (LOC_u8UserRemoveFlag == USER_NOT_FOUND)
//				{
//					MCAL_UART_voidSendString((u8*)"USER NOT FOUND !!");
//					MCAL_UART_voidSendString(GLOB_u8NewLine);
//					LOC_u8BackFlag = 0;
//				}
//				else{/*Do Nothing*/}
//			}
//			else if (LOC_u8CheckConfirmation == '0')
//			{
//				MCAL_UART_voidTransmitData('0');
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
//				MCAL_UART_voidSendString((u8*)"Cancel ...");
//				MCAL_UART_voidSendString(GLOB_u8NewLine);
//				_delay_ms(1000);
//				LOC_u8BackFlag = 1;
//			}
//			break;
//
//
//		case '0':
//			MCAL_UART_voidTransmitData('0');
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
//			MCAL_UART_voidSendString((u8*)"Back");
//			MCAL_UART_voidSendString(GLOB_u8NewLine);
//			//		Go back to the previous page
//			LOC_u8BackFlag = 1;
//			break;
//		default:
//			MCAL_UART_voidSendString((u8*)"Invalid Input!");
//			LOC_u8BackFlag = 0;
//			break;
//		}
//	}
//	while (LOC_u8BackFlag != 1);
//
}

//Admin.
void APP_DeleteAllUsers_Page(void)
{
//	u8 LOC_u8Option = 0;
//	MCAL_UART_voidSendString((u8*)"1.Confirm ");
//	MCAL_UART_voidSendString(GLOB_u8NewLine);
//	MCAL_UART_voidSendString((u8*)"0.Cancel ");
//	MCAL_UART_voidSendString(GLOB_u8NewLine);
//	MCAL_UART_voidReceiveData(&LOC_u8Option);
//
//	switch(LOC_u8Option)
//	{
//	case '1':
//		MCAL_UART_voidTransmitData('1');
//		MCAL_UART_voidSendString(GLOB_u8NewLine);
//		MCAL_UART_voidSendString((u8*)"Deleting ...");
//		MCAL_UART_voidSendString(GLOB_u8NewLine);
//		APP_Registeration_voidDeleteAllUsers();
//		_delay_ms(1000);
//
//		break;
//	case '0':
//		MCAL_UART_voidTransmitData('0');
//		MCAL_UART_voidSendString(GLOB_u8NewLine);
//		MCAL_UART_voidSendString((u8*)"Cancel ...");
//		MCAL_UART_voidSendString(GLOB_u8NewLine);
//		_delay_ms(1000);
//		break;
//	}
//
}

const s8 RoomsMassages[][20] PROGMEM = {
    "0--> Back",			// #define MSG_BACK			0
    "1--> Turn ON",			// #define MSG_LIGHT_ON 	1
    "2--> Turn OFF",		// #define MSG_LIGHT_OFF	2
    "3--> Toggle ",			// #define MSG_LIGHT_TOG	3
};

void PrintLightOptions (void)
{
	PrintMassage(RoomsMassages,MSG_LIGHT_ON,NEWLINE);
	PrintMassage(RoomsMassages,MSG_LIGHT_OFF,NEWLINE);
	PrintMassage(RoomsMassages,MSG_LIGHT_TOG,NEWLINE);
	PrintMassage(RoomsMassages,MSG_BACK,NEWLINE);

}
//void APP_RoomLights_Page_Optimized(void)
//{
//	u8 LOC_u8BackFlag = 0 ;
//	do
//	{
//		u8 LOC_u8Option = 0,LOC_u8LED1_Option =0,LOC_u8Dimmer = 0;
//		//Print(Light,7) this function should print all lights options from an array that is stored in flash.
//		MCAL_UART_voidReceiveData(&LOC_u8Option);
//		//Function for option inside a certain room and it should return 1 if back option is chosen.
//
//
//
//	}while(LOC_u8BackFlag!=1);
//}

//Admin and Users.
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
		MCAL_UART_voidTransmitData(LOC_u8Option);
		MCAL_UART_voidSendString(GLOB_u8NewLine);

		switch(LOC_u8Option)
		{
		case '1':
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			u8 LOC_u8InsideRoom1 = 0;
			do
			{

				MCAL_UART_voidSendString((u8*)"Room 1 Light:");
				MCAL_UART_voidSendString(GLOB_u8NewLine);

				PrintLightOptions();
				MCAL_UART_voidReceiveData(&LOC_u8LED1_Option);
				MCAL_UART_voidTransmitData(LOC_u8LED1_Option);
				MCAL_UART_voidSendString(GLOB_u8NewLine);

				switch(LOC_u8LED1_Option)
				{
				case '1':
					MCAL_UART_voidSendString((u8*)"ON...");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_ON);
					State.Flags.GLOB_u8Flag_LED1 = 1;
					LOC_u8InsideRoom1 = 0;
					break;
				case '2':
					MCAL_UART_voidSendString((u8*)"OFF...");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_OFF);
					State.Flags.GLOB_u8Flag_LED1 = 0;
					LOC_u8InsideRoom1 = 0;
					break;
				case '3':
					MCAL_UART_voidSendString((u8*)"Toggling...");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED1_Port,LED1_Pin,LED_TOG);
					State.Flags.GLOB_u8Flag_LED1 = !State.Flags.GLOB_u8Flag_LED1;

					LOC_u8InsideRoom1 = 0;
					break;
				case '0':
					MCAL_UART_voidSendString((u8*)"Back");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					LOC_u8InsideRoom1 = 1;
					break;
				}

			}
			while(LOC_u8InsideRoom1 == 0);

			LOC_u8BackFlag = 0;


			break;
		case '2':
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			u8 LOC_u8InsideRoom2 = 0 ;

			do
			{

				MCAL_UART_voidSendString((u8*)"Room 2 Light:");
				MCAL_UART_voidSendString(GLOB_u8NewLine);

				PrintLightOptions();

				MCAL_UART_voidReceiveData(&LOC_u8LED2_Option);
				MCAL_UART_voidTransmitData(LOC_u8LED2_Option);
				MCAL_UART_voidSendString(GLOB_u8NewLine);

				switch(LOC_u8LED2_Option)
				{
				case '1':
					MCAL_UART_voidSendString((u8*)"ON...");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_ON);
					State.Flags.GLOB_u8Flag_LED2 = 1;
					LOC_u8InsideRoom2 = 0;
					break;
				case '2':
					MCAL_UART_voidSendString((u8*)"OFF...");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_OFF);
					State.Flags.GLOB_u8Flag_LED2 = 0;
					LOC_u8InsideRoom2 = 0;
					break;
				case '3':
					MCAL_UART_voidSendString((u8*)"Toggling...");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED2_Port,LED2_Pin,LED_TOG);
					State.Flags.GLOB_u8Flag_LED2 = !State.Flags.GLOB_u8Flag_LED2;

					LOC_u8InsideRoom2 = 0;
					break;
				case '0':
					MCAL_UART_voidSendString((u8*)"Back");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					LOC_u8InsideRoom2 = 1;
					break;

				}

			}while(LOC_u8InsideRoom2 == 0);

			LOC_u8BackFlag = 0;

			break;
		case '3':
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			u8 LOC_u8InsideRoom3 = 0 ;
			do
			{

				MCAL_UART_voidSendString((u8*)"Room 3 Light:");
				MCAL_UART_voidSendString(GLOB_u8NewLine);


				PrintLightOptions();
				MCAL_UART_voidReceiveData(&LOC_u8LED3_Option);
				MCAL_UART_voidTransmitData(LOC_u8LED3_Option);
				MCAL_UART_voidSendString(GLOB_u8NewLine);

				switch(LOC_u8LED3_Option)
				{
				case '1':
					MCAL_UART_voidSendString((u8*)"ON...");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_ON);
					State.Flags.GLOB_u8Flag_LED3 = 1;

					LOC_u8InsideRoom3 = 0;
					break;
				case '2':
					MCAL_UART_voidSendString((u8*)"OFF...");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_OFF);
					State.Flags.GLOB_u8Flag_LED3=0;

					LOC_u8InsideRoom3 = 0;
					break;
				case '3':
					MCAL_UART_voidSendString((u8*)"Toggling...");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED3_Port,LED3_Pin,LED_TOG);
					State.Flags.GLOB_u8Flag_LED3 = !State.Flags.GLOB_u8Flag_LED3;

					LOC_u8InsideRoom3 = 0;
					break;
				case '0':
					MCAL_UART_voidSendString((u8*)"Back");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					LOC_u8InsideRoom3 = 1;
					break;

				}

			}while(LOC_u8InsideRoom3 == 0);


			LOC_u8BackFlag = 0;

			break;
		case '4':
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			u8 LOC_u8InsideRoom4 = 0 ;
			do
			{

				MCAL_UART_voidSendString((u8*)"Room 4 Light:");
				MCAL_UART_voidSendString(GLOB_u8NewLine);

				PrintLightOptions();
				MCAL_UART_voidReceiveData(&LOC_u8LED4_Option);
				MCAL_UART_voidTransmitData(LOC_u8LED4_Option);
				MCAL_UART_voidSendString(GLOB_u8NewLine);

				switch(LOC_u8LED4_Option)
				{
				case '1':
					MCAL_UART_voidSendString((u8*)"ON...");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_ON);
					State.Flags.GLOB_u8Flag_LED4 = 1;

					LOC_u8InsideRoom4 = 0;
					break;
				case '2':
					MCAL_UART_voidSendString((u8*)"OFF...");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_OFF);
					State.Flags.GLOB_u8Flag_LED4 = 0;

					LOC_u8InsideRoom4 = 0;
					break;
				case '3':
					MCAL_UART_voidSendString((u8*)"Toggling...");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED4_Port,LED4_Pin,LED_TOG);
					State.Flags.GLOB_u8Flag_LED4 = !State.Flags.GLOB_u8Flag_LED4;

					LOC_u8InsideRoom4 = 0;
					break;
				case '0':
					MCAL_UART_voidSendString((u8*)"Back");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					LOC_u8InsideRoom4 = 1;
					break;

				}

			}while(LOC_u8InsideRoom4 == 0);

			LOC_u8BackFlag = 0;

			break;
		case '5':
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			u8 LOC_u8InsideRoom5 = 0 ;
			do
			{

				MCAL_UART_voidSendString((u8*)"Room 5 Light:");
				MCAL_UART_voidSendString(GLOB_u8NewLine);

				PrintLightOptions();
				MCAL_UART_voidReceiveData(&LOC_u8LED5_Option);
				MCAL_UART_voidTransmitData(LOC_u8LED5_Option);
				MCAL_UART_voidSendString(GLOB_u8NewLine);

				switch(LOC_u8LED5_Option)
				{
				case '1':
					MCAL_UART_voidSendString((u8*)"ON...");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_ON);
					State.Flags.GLOB_u8Flag_LED5 = 1;

					LOC_u8InsideRoom5 = 0;
					break;
				case '2':
					MCAL_UART_voidSendString((u8*)"OFF...");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_OFF);
					State.Flags.GLOB_u8Flag_LED5 = 0;

					LOC_u8InsideRoom5 = 0;
					break;
				case '3':
					MCAL_UART_voidSendString((u8*)"Toggling...");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					HAL_LED_u8LedMode(LED5_Port,LED5_Pin,LED_TOG);
					State.Flags.GLOB_u8Flag_LED5 = !State.Flags.GLOB_u8Flag_LED5;

					LOC_u8InsideRoom5 = 0;
					break;
				case '0':
					MCAL_UART_voidSendString((u8*)"Back");
					MCAL_UART_voidSendString(GLOB_u8NewLine);
					LOC_u8InsideRoom5 = 1;
					break;

				}

			}while(LOC_u8InsideRoom5 == 0);


			LOC_u8BackFlag = 0;

			break;
		case '6':
			LOC_u8Dimmer =0;
			/*
			MCAL_UART_voidSendString((u8*)"Dimmer:");
			 */
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"Choose Brightness level (0 <--> 9):");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidReceiveData(&LOC_u8Dimmer);
			MCAL_UART_voidTransmitData(LOC_u8Dimmer);
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			HAL_MCP4018_POT_voidWriteStep(((LOC_u8Dimmer-'0')*14));


			LOC_u8BackFlag = 0;
			//Dimmer Function
			break;
		case '0':
			MCAL_UART_voidSendString((u8*)"Back");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			//		Go back to the previous page
			LOC_u8BackFlag = 1;
			break;
		}

	}
	while(LOC_u8BackFlag != 1);

}

//Admin and Users.
void APP_AC_Contol_Page(void)
{
	u8 LOC_u8Option = 0,LOC_u8BackFlag = 0;
	do
	{

		MCAL_UART_voidSendString((u8*)"1.Manual");
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"2.AUTO");
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"0.BACK ");
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidReceiveData(&LOC_u8Option);
		MCAL_UART_voidTransmitData(LOC_u8Option);
		MCAL_UART_voidSendString(GLOB_u8NewLine);


		switch(LOC_u8Option)
		{
		case '1':
			APP_AC_Manual();
			LOC_u8BackFlag = 0;

			break;
		case '2':
			MCAL_UART_voidSendString((u8*)"AUTO");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_TIMER_Timer0_InterruptOVF_Enable();
			LOC_u8BackFlag = 0;

			break;
		case '0':
			MCAL_UART_voidSendString((u8*)"BACK");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			_delay_ms(10);
			LOC_u8BackFlag = 1;

			break;
		}
	}while(LOC_u8BackFlag != 1);


}

void APP_AC_Manual(void)
{
	u8 LOC_u8Option = 0,LOC_u8BackFlag = 0;
	do
	{

		MCAL_UART_voidSendString((u8*)"1.ON");
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"2.OFF");
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidSendString((u8*)"0.BACK ");
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidReceiveData(&LOC_u8Option);
		MCAL_UART_voidTransmitData(LOC_u8Option);
		MCAL_UART_voidSendString(GLOB_u8NewLine);

		switch(LOC_u8Option)
		{
		case '1':
			MCAL_UART_voidSendString((u8*)"ON");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_TIMER_Timer0_InterruptOVF_Disable();
			_delay_ms(100);
			HAL_DCMOTOR_void_DcMotorClockWise(7);
			State.Flags.GLOB_u8Flag_AC = 1;
			LOC_u8BackFlag = 0;

			break;
		case '2':
			MCAL_UART_voidSendString((u8*)"OFF");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_TIMER_Timer0_InterruptOVF_Disable();
			_delay_ms(100);
			HAL_DCMOTOR_void_DcMotorStop();
			State.Flags.GLOB_u8Flag_AC = 0;
			LOC_u8BackFlag = 0;

			break;
		case '0':
			MCAL_UART_voidSendString((u8*)"BACK");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			_delay_ms(100);
			LOC_u8BackFlag = 1;

			break;
		}
	}while(LOC_u8BackFlag != 1);

}

//Admin and Users.
void APP_Devices_Status(void)
{
	u8 LOC_u8Option=0,LOC_u8BackFlag=0;
	do
	{
		if(State.Flags.GLOB_u8Flag_Door){MCAL_UART_voidSendString((u8*)"Door: Open"); 	MCAL_UART_voidSendString(GLOB_u8NewLine);}
		else{MCAL_UART_voidSendString((u8*)"Door: Closed");					MCAL_UART_voidSendString(GLOB_u8NewLine);}

		if(State.Flags.GLOB_u8Flag_AC){MCAL_UART_voidSendString((u8*)"AC: ON");			MCAL_UART_voidSendString(GLOB_u8NewLine);}
		else{MCAL_UART_voidSendString((u8*)"AC: OFF");						MCAL_UART_voidSendString(GLOB_u8NewLine);}

		if(State.Flags.GLOB_u8Flag_LED1){MCAL_UART_voidSendString((u8*)"LED1: ON");		MCAL_UART_voidSendString(GLOB_u8NewLine);}
		else{MCAL_UART_voidSendString((u8*)"LED1: OFF");					MCAL_UART_voidSendString(GLOB_u8NewLine);}
		if(State.Flags.GLOB_u8Flag_LED2){MCAL_UART_voidSendString((u8*)"LED2: ON");		MCAL_UART_voidSendString(GLOB_u8NewLine);}
		else{MCAL_UART_voidSendString((u8*)"LED2: OFF");					MCAL_UART_voidSendString(GLOB_u8NewLine);}
		if(State.Flags.GLOB_u8Flag_LED3){MCAL_UART_voidSendString((u8*)"LED3: ON");		MCAL_UART_voidSendString(GLOB_u8NewLine);}
		else{MCAL_UART_voidSendString((u8*)"LED3: OFF");					MCAL_UART_voidSendString(GLOB_u8NewLine);}
		if(State.Flags.GLOB_u8Flag_LED4){MCAL_UART_voidSendString((u8*)"LED4: ON");		MCAL_UART_voidSendString(GLOB_u8NewLine);}
		else{MCAL_UART_voidSendString((u8*)"LED4: OFF");					MCAL_UART_voidSendString(GLOB_u8NewLine);}
		if(State.Flags.GLOB_u8Flag_LED5){MCAL_UART_voidSendString((u8*)"LED5: ON");		MCAL_UART_voidSendString(GLOB_u8NewLine);}
		else{MCAL_UART_voidSendString((u8*)"LED5: OFF");					MCAL_UART_voidSendString(GLOB_u8NewLine);}

		MCAL_UART_voidSendString((u8*)"0.BACK ");
		MCAL_UART_voidSendString(GLOB_u8NewLine);
		MCAL_UART_voidReceiveData(&LOC_u8Option);

		switch(LOC_u8Option)
		{
		default:
/*
			if(GLOB_u8Flag_Door){MCAL_UART_voidSendString((u8*)"Door: Open"); 	MCAL_UART_voidSendString(GLOB_u8NewLine);}
			else{MCAL_UART_voidSendString((u8*)"Door: Closed");					MCAL_UART_voidSendString(GLOB_u8NewLine);}

			if(GLOB_u8Flag_AC){MCAL_UART_voidSendString((u8*)"AC: ON");			MCAL_UART_voidSendString(GLOB_u8NewLine);}
			else{MCAL_UART_voidSendString((u8*)"AC: OFF");						MCAL_UART_voidSendString(GLOB_u8NewLine);}

			if(GLOB_u8Flag_LED1){MCAL_UART_voidSendString((u8*)"LED1: ON");		MCAL_UART_voidSendString(GLOB_u8NewLine);}
			else{MCAL_UART_voidSendString((u8*)"LED1: OFF");					MCAL_UART_voidSendString(GLOB_u8NewLine);}
			if(GLOB_u8Flag_LED1){MCAL_UART_voidSendString((u8*)"LED2: ON");		MCAL_UART_voidSendString(GLOB_u8NewLine);}
			else{MCAL_UART_voidSendString((u8*)"LED2: OFF");					MCAL_UART_voidSendString(GLOB_u8NewLine);}
			if(GLOB_u8Flag_LED1){MCAL_UART_voidSendString((u8*)"LED3: ON");		MCAL_UART_voidSendString(GLOB_u8NewLine);}
			else{MCAL_UART_voidSendString((u8*)"LED3: OFF");					MCAL_UART_voidSendString(GLOB_u8NewLine);}
			if(GLOB_u8Flag_LED1){MCAL_UART_voidSendString((u8*)"LED4: ON");		MCAL_UART_voidSendString(GLOB_u8NewLine);}
			else{MCAL_UART_voidSendString((u8*)"LED4: OFF");					MCAL_UART_voidSendString(GLOB_u8NewLine);}
			if(GLOB_u8Flag_LED1){MCAL_UART_voidSendString((u8*)"LED5: ON");		MCAL_UART_voidSendString(GLOB_u8NewLine);}
			else{MCAL_UART_voidSendString((u8*)"LED5: OFF");					MCAL_UART_voidSendString(GLOB_u8NewLine);}
*/
			LOC_u8BackFlag = 0;


			break;

		case '0':
			MCAL_UART_voidTransmitData('0');
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			MCAL_UART_voidSendString((u8*)"BACK");
			MCAL_UART_voidSendString(GLOB_u8NewLine);
			_delay_ms(10);
			LOC_u8BackFlag = 1;

			break;
		}
	}while(LOC_u8BackFlag != 1);
}

//ISR(Timer0_OVF).
void APP_AC_Check(void)
{
	State.Flags.GLOB_u8Flag_AC = APP_LM35WithDCmotor_Void_LM35WithDCmotorOnOff();
}

//ISR(UART_RX_Complete).
void APP_Admin_Mode_Check(void)
{
	u8 Receive;
	Receive = UDR;
	if(Receive == ADMIN_KEY)
	{
		if(GLOB_ECurrentMode == USER_MODE)
		{
			GLOB_ECurrentMode = ADMIN_MODE;
			//MCAL_Interrupt_GIE_Enable();
			MCAL_UART_voidReceiveCompleteInterruptDisable();
			APP_Home_Page();
		}
/*
		else if(GLOB_ECurrentMode == ADMIN_MODE)
		{
			GLOB_ECurrentMode = USER_MODE;
			//APP_Home_Page();
		}
*/
		else {/*Do Nothing*/}
	}
	else {/*Do Nothing*/}
}
