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

#define MAX_CLASS_NAME_LENGTH                80

#define CLASS_HIERARCHY_VIRTUAL_INHERITENCE  0x1
#define CLASS_HIERARCHY_MULTIPLE_INHERTIENCE 0x3

typedef struct _String String;
typedef struct _TypeDescriptor TypeDescriptor;
typedef struct _ClassHierarchyDescriptor ClassHierarchyDescriptor;
typedef struct _BaseClassDescriptor BaseClassDescriptor;

typedef struct _CompleteObjectLocator
{
	uint32_t signature;
	struct _TypeDescriptor* pTypeDescriptor;
	struct _ClassHierarchyDescriptor* pClassHierarchyDescriptor;
} CompleteObjectLocator;

//Contains the classes details and names
typedef struct _TypeDescriptor
{
	void* pVFTable;
	char name[MAX_CLASS_NAME_LENGTH];
} TypeDescriptor;


typedef struct _ClassHierarchyDescriptor
{
	uint32_t attributes;
	uint32_t numBaseClasses;
	struct _BaseClassDescriptor (*pBaseClassArray)[]; //pointer to array
} ClassHierarchyDescriptor;

typedef struct _BaseClassDescriptor
{
	uint32_t numContainedClasses;
	struct _TypeDescriptor* pTypeDescriptor;
} BaseClassDescriptor;

