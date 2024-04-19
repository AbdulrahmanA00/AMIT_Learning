/*
 * Registeration.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Abdulrahman Ayman
 */

#ifndef APP_REGISTERATION_REGISTERATION_H_
#define APP_REGISTERATION_REGISTERATION_H_

#include"../../HAL/EEPROM/EEPROM.h"

u8 Add_Admin(u16 LOC_u16AdminID,u16 LOC_u16AdminPassword);		//Add Admin ID and Password To memory.
u8 Remove_Admin(u16 LOC_u16AdminID);							//Removes Admin ID and Password from memory.
u8 Check_AdminID(u16 LOC_u16AdminID);
u8 Check_AdminPassword(u16 LOC_u16AdminID,u16 LOC_u16AdminPassword);

void APP_Registeration_voidGetNumberOfAdmins(u8* LOC_Pu8AdminsNumber);
void APP_Registeration_voidDeleteAllUsers(void);
void APP_Registeration_voidResetMemory(void);

u8 Add_User(u16 LOC_u16UserID,u16 LOC_u16UserPassword);			//Add User ID and Password To memory.
u8 Check_UserID(u16 LOC_u16UserID);
u8 Check_UserPassword(u16 LOC_u16UserID,u16 LOC_u16UserPassword);
u8 Remove_User(u16 LOC_u16UserID);							//Removes User ID and Password from memory.

void APP_Registeration_voidGetNumberOfUsers(u8* LOC_Pu8UsersNumber);




#define INVALID_INPUT  -1
#define MAX_DIGITS		4
#define MAX_DETAILS		8
#define STEP 			8
#define CLEAR_DATA 		255

#define USER_DATABASE_EMPTY	0
#define USERS_MIN_AMOUNT	1
#define USERS_MAX_AMOUNT	24
#define USER_FOUND			0xAA
#define USER_NOT_FOUND		0xBB
#define USER_ID_EXIST		0xCC
#define USER_ADDED_SUCCESSFULLY			1
#define USER_REMOVED_SUCCESSFULLY		2
#define FULL				222

#define PASSWORD_MATCHED		77
#define PASSWORD_NOT_MATCHED	88

#define ADMIN_NOT_FOUND			0xBB
#define ADMIN_ID_EXIST			0xCC
#define ADMIN_DATABASE_EMPTY 0
#define ADMINS_MIN_AMOUNT	1
#define ADMINS_MAX_AMOUNT	12
#define ADMIN_LOCATION_TOP	0X00	//Admin 1 Location.
#define ADMIN_LOCATION_BOT	0X58	//Admin 12 Location.
#define ADMIN_REMOVED_SUCCESSFULLY	2

#define USER_LOCATION_TOP	0X60	//User 1 Location.
#define USER_LOCATION_BOT	280 	//User 24 Location.

#define MEMORY_TOP		0
#define MEMORY_BOT		1016UL
#endif /* APP_REGISTERATION_REGISTERATION_H_ */
