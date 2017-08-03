/**
* @file object.c
* @brief Object class header
*
* Implementation of @ref object.h
*
* @author Henry Zhu (Maknee)
* @date	8/1/2017
*/

#include "object.h"

ObjectVFTable objectVFTable =
{
	.pCompleteObjectLocator = NULL,
	.equals = &ObjectEquals,
	.toString = &ObjectToString
};

/**
* @brief	Global extern object type descriptor
*
* 			Contains the a pointer to the object vftable
* 			and the name of "Object" to indicate that this
* 			is the object class
*/

TypeDescriptor objectTypeDescriptor =
{
	.pVFTable = &objectVFTable,
	.name = "Object"
};


