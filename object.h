#pragma once

#include "ooc.h"

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
|
*===========================================================================*/

/*============================================================================
|   Object virtual function table definition
*===========================================================================*/

typedef struct _ObjectVFTable
{
	CompleteObjectLocator* pCompleteObjectLocator;
	bool (*equals)(void* this, void* other);
	String (*toString)(void* this);
} ObjectVFTable;

/*============================================================================
|   Object virtual function table instance
*===========================================================================*/

//Cannot make this const since there is a circluar reference with RTTI structs
static ObjectVFTable objectVFTable =
{
	.pCompleteObjectLocator = NULL,
	.equals = NULL,
	.toString = NULL
};

/*============================================================================
|   Object class definition
*===========================================================================*/

typedef struct _Object
{
	void* pObjectVFTable;
} Object;

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

static const TypeDescriptor objectTypeDescriptor =
{
	.pVFTable = &objectVFTable,
	.name = "Object"
};

#define ObjectBaseClassDescriptor						\
		{												\
			.numContainedClasses = 0,					\
			.pTypeDescriptor = &objectTypeDescriptor	\
		}												\

static const BaseClassDescriptor objectBaseClassArray[] =
{
	ObjectBaseClassDescriptor
};

static const ClassHierarchyDescriptor objectClassHierarchyDescriptor =
{
	.attributes = 0,
	.numBaseClasses = 1,
	.pBaseClassArray = &objectBaseClassArray
};

static const CompleteObjectLocator objectCompleteObjectLocator =
{
	.signature = "HZ",
	.pTypeDescriptor = &objectTypeDescriptor,
	.pClassHierarchyDescriptor = &objectClassHierarchyDescriptor
};

/*============================================================================
|	Constructor
*===========================================================================*/

void ObjectConstruct(void* this)
{
	//check if class passed is an allocated object
	if (this == NULL)
		return;

	//Initialize the vtable to point to this object's vtable
	((Object*)this)->pObjectVFTable = &objectVFTable;

	//Set the vtable's complete object locator to complete the RTTI circle
	objectVFTable.pCompleteObjectLocator = &objectCompleteObjectLocator;
}

/*============================================================================
|	Destructor
*===========================================================================*/

void ObjectDestruct(void* this)
{
	//No use since this is an abstract class
}