#pragma once

#include "object.h"

/*============================================================================
|       Author:  Henry Zhu
+-----------------------------------------------------------------------------
|
|  Description:  Abstract container class of container classes (ex: string, vector, map...)
|				 All derived classes must call donstructor and destructor
|				 All derived classes must override every function in vftable
|
*===========================================================================*/

/*============================================================================
|   Defines
*===========================================================================*/

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
	.pBaseClassArray = &containerBaseClassArray
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


