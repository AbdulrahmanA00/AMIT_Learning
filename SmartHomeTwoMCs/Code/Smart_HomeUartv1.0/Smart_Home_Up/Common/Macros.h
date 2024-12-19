/*
 * BITWISE.h
 *
 *  Created on: Sep 22, 2023
 *      Author: 2023
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

#define SET_BIT(REG,BIT) 	REG|=(1<<BIT)
#define GET_BIT(REG,BIT) 	((REG>>BIT)& 1)
#define CLR_BIT(REG,BIT) 	REG&=~(1<<BIT)
#define TOGGLE_BIT(REG,BIT) REG^=(1<<BIT)
#define IS_BIT_SET(REG,BIT) ((REG & (1 << BIT)) != 0)




#endif /* COMMON_MACROS_H_ */
