/**
* @file error.h
* @brief Main error handling header file
*
* Contains necessary macros and defines for errors
* 
* @note Every ooc header includes error handling
* @warning
* @date	8/4/2017
*/

#pragma once

#include <stdio.h>

#define OUTPUT_ERRORS

/**********************************************************************************************//**
 * @def	DEBUG_PRINT(fmt, ...)
 *
 * @brief	A macro used for error printing
 * @param	fmt	Describes the format to use.
 * @param	...	Variable arguments providing additional information.
 * Credits to:
 * @note * <a href="https://stackoverflow.com/questions/1644868/c-define-macro-for-debug-printing">Entire debug macro</a>
 **************************************************************************************************/

#define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)

#ifdef OUTPUT_ERRORS

#define DEBUG_PRINT(fmt, ...)                                   \
        do { fprintf(stderr, "%s : %d : %s(): " fmt, __FILE__,  \
                                __LINE__, __func__, __VA_ARGS__); } while (0)

#define DEBUG_PRINT_AND_EXIT(fmt, ...)                          \
		DEBUG_PRINT(fmt, __VA_ARGS__);                          \
		exit(-1);                                               \

#define CHECK_NULL_NO_RET(ptr)                                  \
		if (!ptr)                                               \
		{                                                       \
			DEBUG_PRINT("%s\n", "Error! " #ptr " is NULL");     \
			SetError(NULL_POINTER_ERROR);                       \
			return;                                             \
		}                                                       \

#define CHECK_NULL(ptr, return_type)                            \
		if (!ptr)                                               \
		{                                                       \
			DEBUG_PRINT("%s\n", "Error! " #ptr " is NULL");     \
			SetError(NULL_POINTER_ERROR);                       \
			return return_type;                                 \
		}                                                       \

#define CHECK_NULL_EXIT(ptr, fmt, ...)                          \
		if (!ptr)                                               \
		{                                                       \
			DEBUG_PRINT(fmt, __VA_ARGS__);                      \
			exit(-1);                                           \
		}      

#define NO_ERROR 0
#define OUT_OF_BOUNDS_ERROR 1
#define NULL_POINTER_ERROR 2

void ClearError();
void SetError(int error);
int CheckError();

#else
#define DEBUG_PRINT(fmt, ...)
#define DEBUG_PRINT_AND_EXIT(fmt, ...)
#define CHECK_NULL(ptr)
#endif