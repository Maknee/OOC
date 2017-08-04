/** 
* @file rtti.h
* @brief Object oriented class definition header (RTTI)
* 		 
* This file contains the necessary struct definitions 
* for implmenting RTTI every object oriented class 
* <b> should </b> inherit from this header.
* 
* @author Henry Zhu (Maknee)
* @bug No know bugs.
* @note
* @warning
* @date	8/1/2017
*/

#pragma once

//TEMPLATE HOLDER...

/*============================================================================
|       Author:  Henry Zhu
+-----------------------------------------------------------------------------
|
|  Description:  Abstract base class of all classes in ooc
|				 All derived classes must call ObjectConstructor and ObjectDestructor
|				 All derived classes must implement equals() and toString() in their vtable
|
|   Known Bugs:  None
|	To do: Find a way to store CompleteObjectLocator in vtable at compile time
|		   Use macros to generate object base...
*===========================================================================*/

/*============================================================================
|   Defines
*===========================================================================*/



/*============================================================================
|   Object virtual function table definition
*===========================================================================*/



/*============================================================================
|	Overridden member function definitions
*===========================================================================*/



/*============================================================================
|	Class member definitions
*===========================================================================*/



/*============================================================================
|   Object virtual function table instance
*===========================================================================*/



/*============================================================================
|   Object class definition
*===========================================================================*/



/*============================================================================
|   RTTI (Have to declare in reverse order, so compiler knows that structs are defined already)
|   VFTable         <===============\
|   | CompleteObjectLocator         |
|       | Signature = "HZ"          |
|       | TypeDescriptor            |
|           | pVFTable =============/   <===============\
|           | name = Class's name ("Object")            |
|       | ClassHierarchyDescriptor                      |
|           | attributes = 0 (NONE)                     |
|           | numBaseClasses = 1 (Object class)         |
|           | BaseClassArrayDescriptor                  |
|               [                                       |
|                   ObjectBaseClassDescriptor           |
|                       | numContainedClasses (None)    |
|                       | TypeDescriptor ===============/
|               ]
*===========================================================================*/



/*============================================================================
|	Constructor
*===========================================================================*/



/*============================================================================
|	Destructor
*===========================================================================*/



/*============================================================================
|	Overridden member functions
*===========================================================================*/



/*============================================================================
|	Class member functions
*===========================================================================*/

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/**********************************************************************************************//**
 * @def		MAX_CLASS_NAME_LENGTH
 *
 * @brief	A macro that defines maximum class name length.
 * @see		_TypeDescriptor
 * 
 * @def		CLASS_HIERARCHY_NO_INHERITENCE
 * @brief	A macro that idicates if a class is using no inheritence
 * @see		_ClassHierarchyDescriptor
 * 			
 * @def		CLASS_HIERARCHY_VIRTUAL_INHERITENCE
 * @brief	A macro that idicates if a class is using virtual inheritence
 * @see		_ClassHierarchyDescriptor
 *
 * @def		CLASS_HIERARCHY_MULTIPLE_INHERTIENCE
 * @brief	A macro that idicates if a class is using multiple inheritence
 * @see		_ClassHierarchyDescriptor
 * @warning Multiple inhertience not implemented yet
 **************************************************************************************************/

#define MAX_CLASS_NAME_LENGTH                80

#define CLASS_HIERARCHY_NO_INHERITENCE	     0x0
#define CLASS_HIERARCHY_VIRTUAL_INHERITENCE  0x1
#define CLASS_HIERARCHY_MULTIPLE_INHERTIENCE 0x3

typedef struct _TypeDescriptor TypeDescriptor;
typedef struct _ClassHierarchyDescriptor ClassHierarchyDescriptor;
typedef struct _BaseClassDescriptor BaseClassDescriptor;

/**********************************************************************************************//**
 * @struct	_CompleteObjectLocator
 *
 * @brief	Struct that contains the necessary information to identify a class's type,
 * 			super classes and name. A class's vftable points to this struct.
 *
 * @var		_CompleteObjectLocator::signature
 * 			Value that contains the signature to indicate that this is the object locator struct
 *
 * @var		_CompleteObjectLocator::pTypeDescriptor
 * 			Pointer to the class's type descriptor 
 * 			@see _TypeDescriptor
 *
 * @var		_CompleteObjectLocator::pClassHierarchyDescriptor
 * 			Pointer to the class's hierarchy descriptor
 *			@see _ClassHierarchyDescriptor
 **************************************************************************************************/

typedef struct _CompleteObjectLocator
{
	uint32_t signature;
	struct _TypeDescriptor* pTypeDescriptor;
	struct _ClassHierarchyDescriptor* pClassHierarchyDescriptor;
} CompleteObjectLocator;

/**********************************************************************************************//**
 * @struct	_TypeDescriptor
 *
 * @brief	Struct that contains the necessary information used
 * 			to locate the correct virtual function table
 * 			and verify the object's name
 * 			
 * @var		_TypeDescriptor::pVFTable
 * 			Pointer to the type's virtual function table
 * 			
 * @var		_TypeDescriptor::name	
 * 			Char array that contains the class's name
 **************************************************************************************************/

typedef struct _TypeDescriptor
{
	void* pVFTable;
	char name[MAX_CLASS_NAME_LENGTH];
} TypeDescriptor;

/**********************************************************************************************//**
 * @struct	_ClassHierarchyDescriptor
 *
 * @brief	Struct that contains information in order to locate the class's super classes
 * 			
 * @var		_ClassHierarchyDescriptor::attributes
 * 			Value that contains indicates whether the class has inheritence or not
 * 			
 * @var		_ClassHierarchyDescriptor::numBaseClasses
 * 			Value that contains number of classes that the class inherits from
 *			@note Number includes itself
 *
 * @var		_ClassHierarchyDescriptor::pBaseClassArray
 * 			Pointer to an array of base class descriptors contain
 * 			information about the super classes that the class inherits 
 **************************************************************************************************/

typedef struct _ClassHierarchyDescriptor
{
	uint32_t attributes;
	uint32_t numBaseClasses;
	struct _BaseClassDescriptor *pBaseClassArray; //pointer to array
} ClassHierarchyDescriptor;

/**********************************************************************************************//**
 * @struct	_BaseClassDescriptor
 *
 * @brief	Struct that contains information about inherited classes
 * 			
 * @var		_BaseClassDescriptor::numContainedClasses
 * 			Value that contains the number of inherited classes the inherited class has
 *			@note Value does not include the class itself in the count
 *			@note Value contains the inherited class's inherited classes
 * 			
 * @var		_BaseClassDescriptor::pTypeDescriptor
 * 			Pointer to the inherited class's type descriptor, which contains information 
 * 			about the vftable and the class's name
 **************************************************************************************************/

typedef struct _BaseClassDescriptor
{
	uint32_t numContainedClasses;
	struct _TypeDescriptor* pTypeDescriptor;
} BaseClassDescriptor;

