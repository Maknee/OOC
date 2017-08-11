/**
* @file template.h
* @brief Template header file
*
* Includes macros for templates
* 
* @warning
* @date	8/7/2017
*/

#pragma once
#include "ooc_string.h"
#define EXPAND(x) x

//https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms
#define PRIMITIVE_CAT(a, b) a##b
#define CAT(a, b) PRIMITIVE_CAT(a, b)

#define STRINGIFY_EXPANSION(x) #x
#define STRINGIFY(x) STRINGIFY_EXPANSION(x)

#define ADD_PARERENTHSIS_EXPANSION(x) (x)
#define ADD_PARERENTHSIS(x) ADD_PARERENTHSIS_EXPANSION(x)

#define NPOS -1

#define Downcast

//https ://stackoverflow.com/questions/2124339/c-preprocessor-va-args-number-of-arguments
//doesn't work with empty
#define PP_NARG(...) \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())

#define PP_NARG_(...) \
         EXPAND(PP_ARG_N(__VA_ARGS__))

#define PP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N

#define PP_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

//INITIALIZER LIST

#define INITIALIZER_LIST(type, ...) (type[]) {__VA_ARGS__, 0}, PP_NARG(__VA_ARGS__)

//TEMPLATES
typedef struct _String* StringPtr;



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

#define PRIMITIVE_CAT_VA(a, ...) a ## __VA_ARGS__
#define CAT_VA(a, ...) PRIMITIVE_CAT_VA(a, __VA_ARGS__)

//bug in VS... //https://stackoverflow.com/questions/4750688/how-to-single-out-the-first-parameter-sent-to-a-macro-taking-only-a-variadic-par
#define GET_FIRST_ARG_(arg, ...) arg
#define GET_FIRST_ARG(args) GET_FIRST_ARG_ args

//use NewExpansion to expand New for nested macros
#define NewExpansion(type) New ## type()
#define New(type) NewExpansion(type)

#define DeleteExpansion(type, object)                         \
		Delete ## type(object);                               \
		object = NULL                                         \

#define Delete(type, object) DeleteExpansion(type, object)

#define CallExpansion(type, function, ...) ((type ## VFTable*)((Object*)GET_FIRST_ARG((__VA_ARGS__)))->pVFTable)->function(__VA_ARGS__)
#define Call(type, function, ...) CallExpansion(type, function, __VA_ARGS__)

//CASTS

#define Upcast(type, object)                                  \
	((type ## VFTable*)object)->pVFTable)->pCompleteObjectLocator->pClassHierarchyDescriptor->pBaseClassArray
\

//TEMPLATES

#define Vector(type) Vector ## type





#define GCC_VERSION (__GNUC__ * 10000 \
                               + __GNUC_MINOR__ * 100 \
                               + __GNUC_PATCHLEVEL__)

 /* Test for GCC > 4.9.0 */
#if GCC_VERSION > 40900
//implement _Generic
#define Call_GCC
#endif

