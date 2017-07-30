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
|   Defines
*===========================================================================*/

#define NULL_OBJECT_VFTABLE                                 \
        {                                                   \
			.pCompleteObjectLocator = NULL,                 \
			.equals = NULL,                                 \
			.toString = NULL                                \
		}                                                   \

/*============================================================================
|   Object virtual function table definition
*===========================================================================*/

typedef struct _ObjectVFTable
{
	CompleteObjectLocator* pCompleteObjectLocator;
	bool (*equals)(void* this, void* other);
	char* (*toString)(void* this);
} ObjectVFTable;

/*============================================================================
|	Overridden member function definitions
*===========================================================================*/

/*============================================================================
|	Class member definitions
|	Note: this is a special case since this is the base class
|	due to the fact there's nothing overwriting the vtable's values
*===========================================================================*/

bool ObjectEquals(void* this, void* other);
char* ObjectToString(void* this);

/*============================================================================
|   Object virtual function table instance
*===========================================================================*/

//Cannot make this const since there is a circluar reference with RTTI structs
static ObjectVFTable objectVFTable =
{
	.pCompleteObjectLocator = NULL,
	.equals = &ObjectEquals,
	.toString = &ObjectToString
};

/*============================================================================
|   Object class definition
*===========================================================================*/

typedef struct _Object
{
	void* pVFTable;
} Object;

/*============================================================================
|   RTTI (Have to declare in reverse order, so compiler knows that structs are defined already)
|   VFTable         <===============\
|   | CompleteObjectLocator         |
|       | Signature = "HEHE"        |
|       | TypeDescriptor            |
|           | pVFTable =============/   <===============\
|           | name = Class's name ("Object")            |
|       | ClassHierarchyDescriptor                      |
|           | attributes = 0 (NONE)                     |
|           | numBaseClasses = 1 (Object class)         |
|           | BaseClassArrayDescriptor                  |
|               [                                       |
|                   ObjectBaseClassDescriptor           |
|                       | numContainedClasses (0)       |
|                       | TypeDescriptor ===============/
|               ]
*===========================================================================*/

static TypeDescriptor objectTypeDescriptor =
{
	.pVFTable = &objectVFTable,
	.name = "Object"
};

#define ObjectBaseClassDescriptor                           \
        {                                                   \
			.numContainedClasses = 0,                       \
			.pTypeDescriptor = &objectTypeDescriptor        \
		}                                                   \

static BaseClassDescriptor objectBaseClassArray[] =
{
	ObjectBaseClassDescriptor
};

static ClassHierarchyDescriptor objectClassHierarchyDescriptor =
{
	.attributes = 0,
	.numBaseClasses = 1,
	.pBaseClassArray = objectBaseClassArray
};

static CompleteObjectLocator objectCompleteObjectLocator =
{
	.signature = 0x48454845,
	.pTypeDescriptor = &objectTypeDescriptor,
	.pClassHierarchyDescriptor = &objectClassHierarchyDescriptor
};

/*============================================================================
|	Constructor
*===========================================================================*/

void ObjectConstruct(void* this)
{
	//Set the vtable's complete object locator to complete the RTTI circle
	objectVFTable.pCompleteObjectLocator = &objectCompleteObjectLocator;

	//(Actual C++)Initialize the vtable to point to this object's vtable
	//(OOC)Memcpy the entire VFTable into the table pointed by pVFTable
	//Reason: There would be no reason to call superclass's constructor
	//if it's just setting the pointer and the base class will set the pointer
	//again...
	//Reason 2: No need to malloc vftables :)
	//Why? because this will set the derived's global vtable
	//((Object*)this)->pVFTable = &objectVFTable;
	memcpy(((Object*)this)->pVFTable, &objectVFTable, sizeof(ObjectVFTable));
}

/*============================================================================
|	Destructor
*===========================================================================*/

void ObjectDestruct(void* this)
{
	//No use since this is an abstract class
}

/*============================================================================
|	Overridden member functions
*===========================================================================*/

/*============================================================================
|	Class member functions
*===========================================================================*/

bool ObjectEquals(void* this, void* other)
{
	return (!strcmp(ObjectToString(this), ObjectToString(other))) ? true : false;
}

char* ObjectToString(void* this)
{
	ObjectVFTable* pThisObjectVFTable = (ObjectVFTable*)((Object*)this)->pVFTable;
	return pThisObjectVFTable->pCompleteObjectLocator->pTypeDescriptor->name;
}