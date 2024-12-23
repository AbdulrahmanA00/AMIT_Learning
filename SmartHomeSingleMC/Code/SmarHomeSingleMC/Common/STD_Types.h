/*
 * STD.h
 *
 *  Created on: Sep 22, 2023
 *      Author: 2023
 */

#ifndef COMMON_STD_TYPES_H_
#define COMMON_STD_TYPES_H_
#include <stdio.h>
typedef unsigned char 			u8;            //this file contains data types.
typedef char 					i8;
typedef unsigned short int 		u16;
typedef short int 				i16;
typedef unsigned long int 		u32;
typedef long int 				i32;
typedef float 					f32;
typedef double 					d64;
typedef enum {false, true} 		bool;
typedef u8 STD_TYPE;

typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;
typedef signed long long s64;
typedef double f64;
typedef struct
{
	u8 C0:1;
	u8 C1:1;
	u8 C2:1;
	u8 C3:1;
	u8 C4:1;
	u8 C5:1;
	u8 C6:1;
}u7;
typedef struct
{
	u7 r0;
	u7 r1;
	u7 r2;
	u7 r3;
	u7 r4;
}Custom_char;

#define ISR(VectNum)      void  VectNum(void)__attribute__((signal)); \
      	  	  	  	  	  void VectNum(void)

#define EOK  0
#define E_NOT_OK  1
#define NULL   ((void*)0)

#endif /* COMMON_STD_TYPES_H_ */
