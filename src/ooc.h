/**
* @file ooc.h
* @brief Main OOC header file
*
* Contains necessary macros and defines for OOC
* 
* @note	Includes every header and initializes templates. 
* 		Make changes here as necessary to fit requirements
* @warning
* @date	8/4/2017
*/

#pragma once
#include "rtti.h"
#include "object.h"
#include "container.h"
#include "ooc_string.h"

/**********************************************************************************************//**
 * @def	GET_FIRST_ARG(arg, ...)
 *
 * @brief	Gets the first argument of a macro
 *
 * @param	args	The arguments
 * 
 * @def	New(type)
 *
 * @brief	A macro that calls new for a class and returns an object
 * @param	type	The class
 * @return	An object
 *  
 * @def	Delete(type, object)
 *
 * @brief	A macro that calls new for a class and returns an object
 * 			
 * @param	type	The class
 * @param	object	the object to be deleted
 * 
 * @def	Call(type, function, ...)
 *
 * @brief	A macro that calls a function in an object
 * 			
 * @param	type		The class
 * @param	function	The object's member method
 * @param	...			Variable arguments providing additional information.
 * @note    The first parameter in the variable arguments must be the <b>object</b> because every member
 * 			function passes <b>this</b> as the first argument
 **************************************************************************************************/

//bug in VS... //https://stackoverflow.com/questions/4750688/how-to-single-out-the-first-parameter-sent-to-a-macro-taking-only-a-variadic-par
#define GET_FIRST_ARG_(arg, ...) arg
#define GET_FIRST_ARG(args) GET_FIRST_ARG_ args

#define New(type) New ## type()

#define Delete(type, object)                                    \
		Delete ## type(object);                                 \
		object = NULL                                           \

#define Call(type, function, ...) ((type ## VFTable*)((Object*)GET_FIRST_ARG((__VA_ARGS__)))->pVFTable)->function(__VA_ARGS__)

 /* Test for GCC > 4.9.0 */
#if GCC_VERSION > 40900
//implement _Generic
#define Call_GCC
#endif



