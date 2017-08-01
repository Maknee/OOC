/**
* @file container.h
* @brief Container class definition header
*
* This file contains the information about the
* abstract container class of container classes 
* (ex: string, vector, map...).
* Every container class <b> MUST </br> inherit from this
* class and override the functions in the vftable.
* 
* @author Henry Zhu (Maknee)
* @bug No know bugs.
* @note All derived classes must call donstructor and destructor
* @note All derived classes must override every function in vftable
* @warning
* @date	8/1/2017
*/

#pragma once

#include "object.h"

/*============================================================================
|   Defines
*===========================================================================*/

/**********************************************************************************************//**
 * @def		NULL_CONTAINER_VFTABLE
 *
 * @brief	A macro that defines a null container vftable template for classes
 * 			that inherit from the container class
 * 			
 * @see		_String
 * @see		_List
 **************************************************************************************************/

#define NULL_CONTAINER_VFTABLE                              \
        {                                                   \
			.objectVFTable =                                \
			{                                               \
				.pCompleteObjectLocator = NULL,             \
				.equals = NULL,                             \
				.toString = NULL                            \
			},                                              \
			.add = NULL,                                    \
			.clear = NULL,                                  \
			.remove = NULL,                                 \
			.contains = NULL,                               \
			.isEmpty = NULL,                                \
			.size = NULL                                    \
		}                                                   \

/*============================================================================
|   Object virtual function table definition
*===========================================================================*/

/**********************************************************************************************//**
 * @struct	_ContainerVFTable
 *
 * @brief	Struct that contains the vftable of the container class
 * 			
 * @var		_ContainerVFTable::objectVFTable
 * 			Pointer to the inherited object's virtual function table
 * 			
 * @var		_ContainerVFTable::add
 * 			Pointer to a function that adds an item to the container
 *			
 *			@param this 
 *			The object
 *			@param item 
 *			The item to be added to the object
 *			@return bool
 *			Returns true if the item was added successfully
 *			Returns false if the item was added unsuccessfully		
 *			
 * @var		_ContainerVFTable::clear
 * 			Pointer to a function that clears all items in the container
 *
 *			@param this
 *			The object
 *			@note Does not clear the container itself. 
 *				  Clearing the container requires calling the destructor
 *			@note The function should always successfully finish
 *			
 * @var		_ContainerVFTable::remove
 * 			Pointer to a function that removes an item in the container
 *
 *			@param this
 *			The object
 *			@param item
 *			The item to be removed
 *			@return bool
 *			Returns true if the item was removed successfully
 *			Returns false if the item was removed unsuccessfully	
 *			
 * @var		_ContainerVFTable::contains
 * 			Pointer to a function that checks whether or not an item is in
 * 			the container
 *
 *			@param this
 *			The object
 *			@param item
 *			The item to be checked
 *			@return bool
 *			Returns true if the item is in the container
 *			Returns false if the item is not in the container
 *			
 * @var		_ContainerVFTable::isEmpty
 * 			Pointer to a function that checks whether or not the container
 * 			is empty
 *
 *			@param this
 *			The object
 *			@return bool
 *			Returns true if the container is empty
 *			Returns false if the container is not empty
 *			
 * @var		_ContainerVFTable::size
 * 			Pointer to a function that returns the number of elements
 * 			in the container
 *
 *			@param this
 *			The object
 *			@return int
 *			Returns number of elements in the container
 **************************************************************************************************/

typedef struct _ContainerVFTable
{
	ObjectVFTable objectVFTable;
	bool (*add)(void* this, void* item);
	void (*clear)(void* this);
	bool (*remove)(void* this, void* item);
	bool (*contains)(void* this, void* item);

	bool (*isEmpty)(void* this);
	int (*size)(void* this);
} ContainerVFTable;

/*============================================================================
|	Overridden member function definitions
*===========================================================================*/

bool ContainerEquals(void* this, void* other);
char* ContainerToString(void* this);

/*============================================================================
|	Class member definitions
*===========================================================================*/

/*============================================================================
|   Container virtual function table instance
*===========================================================================*/

//Cannot make this const since there is a circluar reference with RTTI structs

static ContainerVFTable containerVFTable =
{
	//objectVFTable will be set in constructor
	.objectVFTable = NULL_OBJECT_VFTABLE,
	.add = NULL,
	.clear = NULL,
	.remove = NULL,
	.contains = NULL,
	.isEmpty = NULL,
	.size = NULL
};

/*============================================================================
|   Container class definition
*===========================================================================*/

typedef struct _Container
{
	Object object;
} Container;

/*============================================================================
|   RTTI (Have to declare in reverse order, so compiler knows that structs are defined already)
|   VFTable         <===============\
|   | CompleteObjectLocator         |
|       | Signature = "HEHE"        |
|       | TypeDescriptor            |
|           | pVFTable =============/   <===============\
|           | name = Class's name ("Conatiner")         |
|       | ClassHierarchyDescriptor                      |
|           | attributes = 0 (NONE)                     |
|           | numBaseClasses = 1 (Object class)         |
|           | BaseClassArrayDescriptor                  |
|               [                                       |
|                   ObjectBaseClassDescriptor           |
|                       | numContainedClasses (None)    |
|                       | TypeDescriptor =====> Object's pVFTable
|                   ContainerBaseClassDescriptor        |
|                       | numContainedClasses (1)	    |
|                       | TypeDescriptor ===============/
|               ]
*===========================================================================*/

static TypeDescriptor containerTypeDescriptor =
{
	.pVFTable = &containerVFTable,
	.name = "Container"
};

#define ContainerBaseClassDescriptor					    \
		{                                                   \
			.numContainedClasses = 1,                       \
			.pTypeDescriptor = &containerTypeDescriptor     \
		}                                                   \

static BaseClassDescriptor containerBaseClassArray[] =
{
	ObjectBaseClassDescriptor,
	ContainerBaseClassDescriptor
};

static ClassHierarchyDescriptor containerClassHierarchyDescriptor =
{
	.attributes = 0,
	.numBaseClasses = 1,
	.pBaseClassArray = containerBaseClassArray
};

static CompleteObjectLocator containerCompleteObjectLocator =
{
	.signature = 0x48454845,
	.pTypeDescriptor = &containerTypeDescriptor,
	.pClassHierarchyDescriptor = &containerClassHierarchyDescriptor
};

/*============================================================================
|	Constructor
*===========================================================================*/

void ContainerConstruct(void* this)
{
	//call super class's constructor (ObjectConstruct)
	ObjectConstruct(this);

	//Override super's methods

	//Set the vtable's complete object locator to complete the RTTI circle
	containerVFTable.objectVFTable.pCompleteObjectLocator = &containerCompleteObjectLocator;

	//Set the equals function
	containerVFTable.objectVFTable.equals = &ContainerEquals;

	//Set the toString
	containerVFTable.objectVFTable.toString = &ContainerToString;

	//Initialize the vtable to point to this object's vtable
	memcpy(((Container*)this)->object.pVFTable, &containerVFTable, sizeof(ContainerVFTable));
}

/*============================================================================
|	Destructor
*===========================================================================*/

void ContainerDestruct(void* this)
{
	//No use since this is an abstract class
	ObjectDestruct(this);
}

/*============================================================================
|	Overridden member functions
*===========================================================================*/

bool ContainerEquals(void* this, void* other)
{
	return (!strcmp(ContainerToString(this), ContainerToString(other))) ? true : false;
}

char* ContainerToString(void* this)
{
	return ObjectToString(this);
}

/*============================================================================
|	Class member functions
*===========================================================================*/


