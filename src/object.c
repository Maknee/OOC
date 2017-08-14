/**
* @file object.c
* @brief Object source file
*
* Implementation of @ref object.h
*
* @author Henry Zhu (Maknee)
* @date	8/2/2017
*/

#include "object.h"

void* check_calloc(size_t size)
{
	void* result = calloc(1, size);
	CHECK_NULL_EXIT(result, "%s%zu\n", "Error! Exiting... Could not be allocate size of: ", size);
	return result;
}

ObjectVFTable ObjectvfTable =
{
	.pCompleteObjectLocator = NULL,
	.equals = &ObjectEquals,
	.toString = &ObjectToString
};

TypeDescriptor objectTypeDescriptor =
{
	.pVFTable = &ObjectvfTable,
	.name = "Object"
};

BaseClassDescriptor objectBaseClassArray[] =
{
	ObjectBaseClassDescriptor
};

ClassHierarchyDescriptor objectClassHierarchyDescriptor =
{
	.attributes = CLASS_HIERARCHY_NO_INHERITENCE,
	.numBaseClasses = 1,
	.pBaseClassArray = objectBaseClassArray
};

CompleteObjectLocator objectCompleteObjectLocator =
{
	.signature = 0x48454845,
	.pTypeDescriptor = &objectTypeDescriptor,
	.pClassHierarchyDescriptor = &objectClassHierarchyDescriptor
};

/*============================================================================
|	New Operator
*===========================================================================*/

void* NewObject()
{
	//No use since this is an abstract class
	DEBUG_PRINT("%s\n", "Warning! Calling new on an abstract class!");
	return NULL;
}

/*============================================================================
|	Delete Operator
*===========================================================================*/

void DeleteObject(void* this)
{
	//No use since this is an abstract class
	DEBUG_PRINT("%s\n", "Warning! Calling delete on an abstract class!");
}

/*============================================================================
|	Constructor
*===========================================================================*/

void ObjectConstruct(void* this)
{
	//Set the vtable's complete object locator to complete the RTTI circle
	ObjectvfTable.pCompleteObjectLocator = &objectCompleteObjectLocator;

	//(Actual C++)Initialize the vtable to point to this object's vtable
	//(OOC)Memcpy the entire VFTable into the table pointed by pVFTable
	//Reason: There would be no reason to call superclass's constructor
	//if it's just setting the pointer and the base class will set the pointer
	//again...
	//Reason 2: No need to malloc vftables :)
	//Why? because this will set the derived's global vtable
	//The C++ way:
	//((Object*)this)->pVFTable = &ObjectvfTable;
	memcpy(((Object*)this)->pVFTable, &ObjectvfTable, sizeof(ObjectVFTable));
}


/*============================================================================
|	Copy Constructor
*===========================================================================*/

void* ObjectCopyConstruct(void* this)
{
	DEBUG_PRINT("%s\n", "Warning! Calling copy constructor on an abstract class!");
	return NULL;
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
	CHECK_NULL(this, false);
	CHECK_NULL(other, false);

	return (!strcmp(ObjectToString(this), ObjectToString(other))) ? true : false;
}

char* ObjectToString(void* this)
{
	CHECK_NULL(this, NULL);

	ObjectVFTable* pThisObjectVFTable = (ObjectVFTable*)((Object*)this)->pVFTable;
	return pThisObjectVFTable->pCompleteObjectLocator->pTypeDescriptor->name;
}


