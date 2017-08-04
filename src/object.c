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

ObjectVFTable objectVFTable =
{
	.pCompleteObjectLocator = NULL,
	.equals = &ObjectEquals,
	.toString = &ObjectToString
};

TypeDescriptor objectTypeDescriptor =
{
	.pVFTable = &objectVFTable,
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
	//allocate a new object
	void* object = calloc(1, sizeof(Object));

	//allocate vftable
	((Object*)object)->pVFTable = calloc(1, sizeof(Object));

	//call constructor to set up object
	ObjectConstruct(object);

	return object;
}

/*============================================================================
|	Delete Operator
*===========================================================================*/

void DeleteObject(void* this)
{
	//call destructor
	ObjectDestruct(this);

	//free vftable
	free(((Object*)this)->pVFTable);

	//free the string's resources
	free(this);

	//NULL the pointer, so we don't have use after free vulns
	this = NULL;
}

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
	//The C++ way:
	//((Object*)this)->pVFTable = &objectVFTable;
	memcpy(((Object*)this)->pVFTable, &objectVFTable, sizeof(ObjectVFTable));
}


/*============================================================================
|	Copy Constructor
*===========================================================================*/

void* ObjectCopyConstruct(void* this)
{
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
	return (!strcmp(ObjectToString(this), ObjectToString(other))) ? true : false;
}

char* ObjectToString(void* this)
{
	ObjectVFTable* pThisObjectVFTable = (ObjectVFTable*)((Object*)this)->pVFTable;
	return pThisObjectVFTable->pCompleteObjectLocator->pTypeDescriptor->name;
}


