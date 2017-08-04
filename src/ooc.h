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

//will be templated
//#include "list.h"

#define New(type) New ## type ## ()
#define Delete(type, object) Delete ## type ## (object)
#define Call(type, object, function, ...) ((type ## VFTable*)((Object*)object)->pVFTable)-> ## function ## (__VA_ARGS__)
