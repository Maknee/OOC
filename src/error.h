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

#ifdef OUTPUT_ERRORS

#define DEBUG_PRINT(fmt, ...)                                   \
        do { fprintf(stderr, "%s : %d : %s(): " fmt, __FILE__,  \
                                __LINE__, __func__, __VA_ARGS__); } while (0)

#define DEBUG_PRINT_AND_EXIT(fmt, ...)                          \
		DEBUG_PRINT(fmt, __VA_ARGS__);                          \
		exit(-1);                                               \

#define CHECK_NULL(ptr, return_type)                            \
		if (!ptr)                                               \
		{                                                       \
			DEBUG_PRINT("%s\n", "Error! " #ptr " is NULL");     \
			return return_type;                                 \
		}                                                       \

#define CHECK_NULL_EXIT(ptr, fmt, ...)                          \
		if (!ptr)                                               \
		{                                                       \
			DEBUG_PRINT(fmt, __VA_ARGS__);                      \
			exit(-1);                                           \
		}                                                       \

#define CHECK_NULL_NO_RET(ptr)                                  \
		if (!ptr)                                               \
		{                                                       \
			DEBUG_PRINT("%s\n", "Error! " #ptr " is NULL");     \
			return;                                             \
		}                                                       \


#else
#define DEBUG_PRINT(fmt, ...)
#define DEBUG_PRINT_AND_EXIT(fmt, ...)
#define CHECK_NULL(ptr, return_type)
#define CHECK_NULL_EXIT(ptr, fmt, ...) 
#define CHECK_NULL_NO_RET(ptr)
#endif