/*
 * Registeration.c
 *
 *  Created on: Jan 30, 2024
 *      Author: Abdulrahman Ayman
 */
#include "Registeration.h"

//u8 GLOB_u8Location = 0;
//static u8 GLOB_u8UserCount;
//static u16 LOC_u16UserLocation = 0;

/*************************	Admin Section	****************************/

u8 Add_Admin(u16 LOC_u16AdminID,u16 LOC_u16AdminPassword)
{
	u8 LOC_u8CheckAdminIDExistance = 0, LOC_u8GetAdminsCount = 0 ;

	u16 LOC_u16LastLocation;

	LOC_u8CheckAdminIDExistance = Check_AdminID(LOC_u16AdminID);
	APP_Registeration_voidGetNumberOfAdmins(&LOC_u8GetAdminsCount);

	if ((LOC_u8GetAdminsCount < ADMINS_MAX_AMOUNT) && (LOC_u8GetAdminsCount >= ADMIN_DATABASE_EMPTY))
	{
		if((LOC_u16AdminID <= 9999 && LOC_u16AdminID >= 1000) && (LOC_u16AdminPassword <= 9999 && LOC_u16AdminPassword >= 1000))
		{
			if (LOC_u8CheckAdminIDExistance == ADMIN_NOT_FOUND)
			{

				u8 i=3,j=3, Admin[MAX_DIGITS] , Pass[MAX_DIGITS];
				//			static u16 LOC_u16CurrentLocation;

				while (LOC_u16AdminID != 0)
				{
					Admin[i] = (LOC_u16AdminID % 10);
					LOC_u16AdminID = (LOC_u16AdminID / 10);
					i--;
				}
				while (LOC_u16AdminPassword != 0)
				{
					Pass[j] = (LOC_u16AdminPassword % 10);
					LOC_u16AdminPassword = (LOC_u16AdminPassword / 10);
					j--;
				}


				//			LOC_u16UserLocation = (USER_LOCATION_TOP) + (LOC_u16CurrentLocation*8) ;

//				LOC_u16LastUserStartLocation = (USER_LOCATION_TOP - STEP);
				LOC_u16LastLocation = (ADMIN_LOCATION_TOP) + ( STEP * LOC_u8GetAdminsCount);

				for(i=0;i<4;i++)
				{
					//			HAL_EEPROM_voidWriteData(GLOB_u8Location++,User[i]);
					HAL_EEPROM_voidWriteData(LOC_u16LastLocation++,Admin[i]);
				}
				for(j=0;j<4;j++)
				{
					//			HAL_EEPROM_voidWriteData(GLOB_u8Location++,Pass[j]);
					HAL_EEPROM_voidWriteData(LOC_u16LastLocation++,Pass[j]);
				}

				//			GLOB_u8UserCount++;
				//LOC_u8GetUsersCount++;
				return ++LOC_u8GetAdminsCount;		//returning number of Admins add till now.
			}
			else
			{
				return ADMIN_ID_EXIST;	//if ID is already used.
			}

		}
		else
		{
			return INVALID_INPUT;	//If ID or password doesn't meet the 4 digit constraints.
		}

	}
	else
	{
		return FULL;
	}
}

u8 Remove_Admin(u16 LOC_u16AdminID)
{
	u8 LOC_u8DigitCounter,LOC_u8AdminIDArray[MAX_DIGITS],LOC_u8ConfirmClearFlag = 0 ,LOC_u8AdminCheck = 0,LOC_u8GetLastAdmin, LOC_u8AdminDetails_Read[MAX_DETAILS] ,LOC_u8TransferArray[MAX_DETAILS] = {0} ;
	u16 LOC_u16RemovedAdminLocation,LOC_u16LastAdminStartLocation = 0,LOC_u16LastLocation;

	LOC_u8AdminCheck = Check_AdminID(LOC_u16AdminID);
	APP_Registeration_voidGetNumberOfAdmins(&LOC_u8GetLastAdmin);

/*
	while (LOC_u16UserID != 0)
	{
		LOC_u8UserIDArray[i] = (LOC_u16UserID % 10);
		LOC_u16UserID = (LOC_u16UserID / 10);
		i--;
	}
*/



	LOC_u16LastAdminStartLocation = (ADMIN_LOCATION_TOP - STEP);

	if ((LOC_u8AdminCheck <= ADMINS_MAX_AMOUNT) && (LOC_u8AdminCheck >= USERS_MIN_AMOUNT))
	{
		LOC_u16LastLocation = (LOC_u16LastAdminStartLocation ) + ( STEP * LOC_u8GetLastAdmin);

		if (LOC_u8AdminCheck == LOC_u8GetLastAdmin)
		{
			for(LOC_u8DigitCounter =0;LOC_u8DigitCounter<MAX_DETAILS;LOC_u8DigitCounter++)
			{

//				HAL_EEPROM_voidReadData(LOC_u16LastLocation,&LOC_u8TransferArray[LOC_u8DigitCounter]);
				HAL_EEPROM_voidWriteData(LOC_u16LastLocation,CLEAR_DATA);
				LOC_u8ConfirmClearFlag++;
				LOC_u16LastLocation++;
			}

		}
		else
		{

			for(LOC_u8DigitCounter =0;LOC_u8DigitCounter<MAX_DETAILS;LOC_u8DigitCounter++)
			{

				HAL_EEPROM_voidReadData(LOC_u16LastLocation,&LOC_u8TransferArray[LOC_u8DigitCounter]);
				HAL_EEPROM_voidWriteData(LOC_u16LastLocation,CLEAR_DATA);
				LOC_u8ConfirmClearFlag++;
				LOC_u16LastLocation++;
			}

			LOC_u16RemovedAdminLocation = (LOC_u16LastAdminStartLocation ) + ( STEP * LOC_u8AdminCheck);

			for(LOC_u8DigitCounter =0;LOC_u8DigitCounter<MAX_DETAILS;LOC_u8DigitCounter++)
			{

				//			HAL_EEPROM_voidReadData(LOC_u16LastLocation,&LOC_u8TransferArray[LOC_u8DigitCounter]);
				HAL_EEPROM_voidWriteData(LOC_u16RemovedAdminLocation,LOC_u8TransferArray[LOC_u8DigitCounter]);
				//			LOC_u8ConfirmClearFlag++;
				LOC_u16RemovedAdminLocation++;
			}
			return ADMIN_REMOVED_SUCCESSFULLY;
		}
	}
	else
	{
		//Do Nothing. (Meaning that no user found with that ID or Database is empty)
	}


		return ADMIN_NOT_FOUND;
}



u8 Check_AdminID(u16 LOC_u16AdminID)
{
	u8 i=3,LOC_u8AdminNumberFlag = 0, LOC_u8IDMatchedFlag = 0 ,LOC_u8AdminID_Read[MAX_DIGITS] , LOC_u8AdminIDArray[MAX_DIGITS], LOC_u8DigitCounter = 0;

	u16 LOC_u16AdminLocationVariable = ADMIN_LOCATION_TOP,LOC_u16AdminLocationVariableDigits ;


	while (LOC_u16AdminID != 0)
	{
		LOC_u8AdminIDArray[i] = (LOC_u16AdminID % 10);
		LOC_u16AdminID = (LOC_u16AdminID / 10);
		i--;
	}


	for(;LOC_u16AdminLocationVariable <= ADMIN_LOCATION_BOT;LOC_u16AdminLocationVariable += STEP)
	{
		LOC_u8AdminNumberFlag++;
		LOC_u16AdminLocationVariableDigits = LOC_u16AdminLocationVariable;
		for(LOC_u8DigitCounter =0;LOC_u8DigitCounter<MAX_DIGITS;LOC_u8DigitCounter++)
		{

			HAL_EEPROM_voidReadData(LOC_u16AdminLocationVariableDigits,&LOC_u8AdminID_Read[LOC_u8DigitCounter]);
			if (LOC_u8AdminID_Read[LOC_u8DigitCounter] == LOC_u8AdminIDArray[LOC_u8DigitCounter])
			{
				LOC_u8IDMatchedFlag++;
				LOC_u16AdminLocationVariableDigits++;
			}
			else
			{
				LOC_u8IDMatchedFlag = 0;
				break;
			}

		}
		if(LOC_u8IDMatchedFlag == 4)
		{
			return LOC_u8AdminNumberFlag;
		}
		else
		{
			//Remain in the loop.
		}
	}

	return ADMIN_NOT_FOUND;
}


u8 Check_AdminPassword(u16 LOC_u16AdminID,u16 LOC_u16AdminPassword)
{
	u8 i=3,LOC_u8AdminCheck = 0,LOC_u8PassMatchedFlag = 0,LOC_u8DigitCounter,LOC_u8AdminPasswordArray[MAX_DIGITS], LOC_u8AdminPass_Read[MAX_DIGITS];
	u16 LOC_u16AdminStartLocation = (ADMIN_LOCATION_TOP-MAX_DIGITS),LOC_u16PassLocationVariableDigits;
	LOC_u8AdminCheck = Check_AdminID(LOC_u16AdminID);

	//Save password in an array to save time when checking.
	while (LOC_u16AdminPassword != 0)
	{
		LOC_u8AdminPasswordArray[i] = (LOC_u16AdminPassword % 10);
		LOC_u16AdminPassword = (LOC_u16AdminPassword / 10);
		i--;
	}


	if ((LOC_u8AdminCheck <= ADMINS_MAX_AMOUNT) && (LOC_u8AdminCheck >= ADMINS_MIN_AMOUNT))
	{
		LOC_u16PassLocationVariableDigits = (LOC_u16AdminStartLocation ) + (2 * MAX_DIGITS * LOC_u8AdminCheck);
			for(LOC_u8DigitCounter =0;LOC_u8DigitCounter<MAX_DIGITS;LOC_u8DigitCounter++)
			{

				HAL_EEPROM_voidReadData(LOC_u16PassLocationVariableDigits,&LOC_u8AdminPass_Read[LOC_u8DigitCounter]);
				if (LOC_u8AdminPass_Read[LOC_u8DigitCounter] == LOC_u8AdminPasswordArray[LOC_u8DigitCounter])
				{
					LOC_u8PassMatchedFlag++;
					LOC_u16PassLocationVariableDigits++;
				}
				else
				{
					LOC_u8PassMatchedFlag = 0;
					break;
				}

			}
			if(LOC_u8PassMatchedFlag == MAX_DIGITS)
			{
				return PASSWORD_MATCHED;
			}
			else
			{
				return PASSWORD_NOT_MATCHED;
			}
	}
	else
	{
		return ADMIN_NOT_FOUND;
	}


}


void APP_Registeration_voidGetNumberOfAdmins(u8* LOC_Pu8AdminsNumber)
{
	u16 LOC_u16LocationVariable = ADMIN_LOCATION_TOP;
	u8 LOC_u8AdminNumber = 0,LOC_u8NumberCheck = 0;
	for(;LOC_u16LocationVariable <= ADMIN_LOCATION_BOT;LOC_u16LocationVariable += STEP)
	{
		HAL_EEPROM_voidReadData(LOC_u16LocationVariable,&LOC_u8NumberCheck);
		if(LOC_u8NumberCheck != 255)
		{
			LOC_u8AdminNumber++;
		}
		else
		{
			/*Do nothing*/
		}
	}
	*LOC_Pu8AdminsNumber = LOC_u8AdminNumber;

}

void APP_Registeration_voidDeleteAllUsers(void)
{
	u16 LOC_u16UserLocationVariable = USER_LOCATION_TOP,LOC_u16UserLocationVariableDigits;
	u8 LOC_u8UserDetails;
	for(;LOC_u16UserLocationVariable <= USER_LOCATION_BOT;LOC_u16UserLocationVariable += STEP)
	{
		LOC_u16UserLocationVariableDigits = LOC_u16UserLocationVariable;
		for(LOC_u8UserDetails =0;LOC_u8UserDetails<MAX_DETAILS;LOC_u8UserDetails++)
		{
			HAL_EEPROM_voidWriteData(LOC_u16UserLocationVariableDigits++,CLEAR_DATA);
		}
	}
}

void APP_Registeration_voidResetMemory(void)
{
	u16 LOC_u16LocationVariable = MEMORY_TOP,LOC_u16LocationVariableDigits;
	u8 LOC_u8UserDetails;
	for(;LOC_u16LocationVariable <= MEMORY_BOT;LOC_u16LocationVariable += STEP)
	{
		LOC_u16LocationVariableDigits = LOC_u16LocationVariable;
		for(LOC_u8UserDetails =0;LOC_u8UserDetails<MAX_DETAILS;LOC_u8UserDetails++)
		{
			HAL_EEPROM_voidWriteData(LOC_u16LocationVariableDigits++,CLEAR_DATA);
		}
	}
}


/*************************	User Section	****************************/
u8 Add_User(u16 LOC_u16UserID,u16 LOC_u16UserPassword)
{
	u8 LOC_u8CheckUserIDExistance = 0, LOC_u8GetUsersCount = 0 ;

	u16 LOC_u16LastLocation;

	LOC_u8CheckUserIDExistance = Check_UserID(LOC_u16UserID);
	APP_Registeration_voidGetNumberOfUsers(&LOC_u8GetUsersCount);

	if ((LOC_u8GetUsersCount < USERS_MAX_AMOUNT) && (LOC_u8GetUsersCount >= USER_DATABASE_EMPTY))
	{
		if((LOC_u16UserID <= 9999 && LOC_u16UserID >= 1000) && (LOC_u16UserPassword <= 9999 && LOC_u16UserPassword >= 1000))
		{
			if (LOC_u8CheckUserIDExistance == USER_NOT_FOUND)
			{

				u8 i=3,j=3, User[MAX_DIGITS] , Pass[MAX_DIGITS];
				//			static u16 LOC_u16CurrentLocation;

				while (LOC_u16UserID != 0)
				{
					User[i] = (LOC_u16UserID % 10);
					LOC_u16UserID = (LOC_u16UserID / 10);
					i--;
				}
				while (LOC_u16UserPassword != 0)
				{
					Pass[j] = (LOC_u16UserPassword % 10);
					LOC_u16UserPassword = (LOC_u16UserPassword / 10);
					j--;
				}


				//			LOC_u16UserLocation = (USER_LOCATION_TOP) + (LOC_u16CurrentLocation*8) ;

//				LOC_u16LastUserStartLocation = (USER_LOCATION_TOP - STEP);
				LOC_u16LastLocation = (USER_LOCATION_TOP) + ( STEP * LOC_u8GetUsersCount);

				for(i=0;i<4;i++)
				{
					//			HAL_EEPROM_voidWriteData(GLOB_u8Location++,User[i]);
					HAL_EEPROM_voidWriteData(LOC_u16LastLocation++,User[i]);
				}
				for(j=0;j<4;j++)
				{
					//			HAL_EEPROM_voidWriteData(GLOB_u8Location++,Pass[j]);
					HAL_EEPROM_voidWriteData(LOC_u16LastLocation++,Pass[j]);
				}

				//			GLOB_u8UserCount++;
				//LOC_u8GetUsersCount++;
				return ++LOC_u8GetUsersCount;		//returning number of users add till now.
			}
			else
			{
				return USER_ID_EXIST;	//if ID is already used.
			}

		}
		else
		{
			return INVALID_INPUT;	//If ID or password doesn't meet the 4 digit constraints.
		}

	}
	else
	{
		return FULL;
	}
}


u8 Remove_User(u16 LOC_u16UserID)
{
	u8 LOC_u8DigitCounter,LOC_u8UserIDArray[MAX_DIGITS],LOC_u8ConfirmClearFlag = 0 ,LOC_u8UserCheck = 0,LOC_u8GetLastUser, LOC_u8UserDetails_Read[MAX_DETAILS] ,LOC_u8TransferArray[MAX_DETAILS] = {0} ;
	u16 LOC_u16RemovedUserLocation,LOC_u16LastUserStartLocation = 0,LOC_u16LastLocation;

	LOC_u8UserCheck = Check_UserID(LOC_u16UserID);
	APP_Registeration_voidGetNumberOfUsers(&LOC_u8GetLastUser);

/*
	while (LOC_u16UserID != 0)
	{
		LOC_u8UserIDArray[i] = (LOC_u16UserID % 10);
		LOC_u16UserID = (LOC_u16UserID / 10);
		i--;
	}
*/



	LOC_u16LastUserStartLocation = (USER_LOCATION_TOP - STEP);

	if ((LOC_u8UserCheck <= USERS_MAX_AMOUNT) && (LOC_u8UserCheck >= USERS_MIN_AMOUNT))
	{
		LOC_u16LastLocation = (LOC_u16LastUserStartLocation ) + ( STEP * LOC_u8GetLastUser);

		if (LOC_u8UserCheck == LOC_u8GetLastUser)
		{
			for(LOC_u8DigitCounter =0;LOC_u8DigitCounter<MAX_DETAILS;LOC_u8DigitCounter++)
			{

//				HAL_EEPROM_voidReadData(LOC_u16LastLocation,&LOC_u8TransferArray[LOC_u8DigitCounter]);
				HAL_EEPROM_voidWriteData(LOC_u16LastLocation,CLEAR_DATA);
				LOC_u8ConfirmClearFlag++;
				LOC_u16LastLocation++;
			}
			return USER_REMOVED_SUCCESSFULLY;

		}
		else
		{

			for(LOC_u8DigitCounter =0;LOC_u8DigitCounter<MAX_DETAILS;LOC_u8DigitCounter++)
			{

				HAL_EEPROM_voidReadData(LOC_u16LastLocation,&LOC_u8TransferArray[LOC_u8DigitCounter]);
				HAL_EEPROM_voidWriteData(LOC_u16LastLocation,CLEAR_DATA);
				LOC_u8ConfirmClearFlag++;
				LOC_u16LastLocation++;
			}

			LOC_u16RemovedUserLocation = (LOC_u16LastUserStartLocation ) + ( STEP * LOC_u8UserCheck);

			for(LOC_u8DigitCounter =0;LOC_u8DigitCounter<MAX_DETAILS;LOC_u8DigitCounter++)
			{

				//			HAL_EEPROM_voidReadData(LOC_u16LastLocation,&LOC_u8TransferArray[LOC_u8DigitCounter]);
				HAL_EEPROM_voidWriteData(LOC_u16RemovedUserLocation,LOC_u8TransferArray[LOC_u8DigitCounter]);
				//			LOC_u8ConfirmClearFlag++;
				LOC_u16RemovedUserLocation++;
			}
			return USER_REMOVED_SUCCESSFULLY;
		}
	}
	else
	{
		//Do Nothing. (Meaning that no user found with that ID or Database is empty)
	}


		return USER_NOT_FOUND;
}


u8 Check_UserID(u16 LOC_u16UserID)
{
	u8 i=3,LOC_u8UserNumberFlag = 0, LOC_u8IDMatchedFlag = 0 ,LOC_u8UserID_Read[MAX_DIGITS] , LOC_u8UserIDArray[MAX_DIGITS], LOC_u8DigitCounter = 0;

	u16 LOC_u16UserLocationVariable = USER_LOCATION_TOP,LOC_u16UserLocationVariableDigits ;


	while (LOC_u16UserID != 0)
	{
		LOC_u8UserIDArray[i] = (LOC_u16UserID % 10);
		LOC_u16UserID = (LOC_u16UserID / 10);
		i--;
	}


	for(;LOC_u16UserLocationVariable <= USER_LOCATION_BOT;LOC_u16UserLocationVariable += STEP)
	{
		LOC_u8UserNumberFlag++;
		LOC_u16UserLocationVariableDigits = LOC_u16UserLocationVariable;
		for(LOC_u8DigitCounter =0;LOC_u8DigitCounter<MAX_DIGITS;LOC_u8DigitCounter++)
		{

			HAL_EEPROM_voidReadData(LOC_u16UserLocationVariableDigits,&LOC_u8UserID_Read[LOC_u8DigitCounter]);
			if (LOC_u8UserID_Read[LOC_u8DigitCounter] == LOC_u8UserIDArray[LOC_u8DigitCounter])
			{
				LOC_u8IDMatchedFlag++;
				LOC_u16UserLocationVariableDigits++;
			}
			else
			{
				LOC_u8IDMatchedFlag = 0;
				break;
			}

		}
		if(LOC_u8IDMatchedFlag == 4)
		{
			return LOC_u8UserNumberFlag;
		}
		else
		{
			//Remain in the loop.
		}
	}

	return USER_NOT_FOUND;
}

u8 Check_UserPassword(u16 LOC_u16UserID,u16 LOC_u16UserPassword)
{
	u8 i=3,LOC_u8UserCheck = 0,LOC_u8PassMatchedFlag = 0,LOC_u8DigitCounter,LOC_u8UserPasswordArray[MAX_DIGITS], LOC_u8UserPass_Read[MAX_DIGITS];
	u16 LOC_u16UserStartLocation = (USER_LOCATION_TOP-MAX_DIGITS),LOC_u16PassLocationVariableDigits;
	LOC_u8UserCheck = Check_UserID(LOC_u16UserID);

	//Save password in an array to save time when checking.
	while (LOC_u16UserPassword != 0)
	{
		LOC_u8UserPasswordArray[i] = (LOC_u16UserPassword % 10);
		LOC_u16UserPassword = (LOC_u16UserPassword / 10);
		i--;
	}


	if ((LOC_u8UserCheck <= USERS_MAX_AMOUNT) && (LOC_u8UserCheck >= USERS_MIN_AMOUNT))
	{
		LOC_u16PassLocationVariableDigits = (LOC_u16UserStartLocation ) + (2 * MAX_DIGITS * LOC_u8UserCheck);
			for(LOC_u8DigitCounter =0;LOC_u8DigitCounter<MAX_DIGITS;LOC_u8DigitCounter++)
			{

				HAL_EEPROM_voidReadData(LOC_u16PassLocationVariableDigits,&LOC_u8UserPass_Read[LOC_u8DigitCounter]);
				if (LOC_u8UserPass_Read[LOC_u8DigitCounter] == LOC_u8UserPasswordArray[LOC_u8DigitCounter])
				{
					LOC_u8PassMatchedFlag++;
					LOC_u16PassLocationVariableDigits++;
				}
				else
				{
					LOC_u8PassMatchedFlag = 0;
					break;
				}

			}
			if(LOC_u8PassMatchedFlag == MAX_DIGITS)
			{
				return PASSWORD_MATCHED;
			}
			else
			{
				return PASSWORD_NOT_MATCHED;
			}
	}
	else
	{
		return USER_NOT_FOUND;
	}


}


void APP_Registeration_voidGetNumberOfUsers(u8* LOC_Pu8UsersNumber)
{
	u16 LOC_u16LocationVariable = USER_LOCATION_TOP;
	u8 LOC_u8UserNumber = 0,LOC_u8NumberCheck = 0;
	for(;LOC_u16LocationVariable <= USER_LOCATION_BOT;LOC_u16LocationVariable += STEP)
	{
		HAL_EEPROM_voidReadData(LOC_u16LocationVariable,&LOC_u8NumberCheck);
		if(LOC_u8NumberCheck != 255)
		{
			LOC_u8UserNumber++;
		}
		else
		{
			/*Do nothing*/
		}
	}
	*LOC_Pu8UsersNumber = LOC_u8UserNumber;

}


