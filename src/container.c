/**
* @file container.c
* @brief Object source file
*
* Implementation of @ref container.h
*
* @author Henry Zhu (Maknee)
* @date	8/2/2017
*/

#include "container.h"

ContainerVFTable containerVFTable =
{
	.objectVFTable = NULL_OBJECT_VFTABLE,
	.add = NULL,
	.clear = NULL,
	.remove = NULL,
	.contains = NULL,
	.isEmpty = NULL,
	.size = NULL
};

TypeDescriptor containerTypeDescriptor =
{
	.pVFTable = &containerVFTable,
	.name = "Container"
};

BaseClassDescriptor containerBaseClassArray[] =
{
	ObjectBaseClassDescriptor,
	ContainerBaseClassDescriptor
};

ClassHierarchyDescriptor containerClassHierarchyDescriptor =
{
	.attributes = CLASS_HIERARCHY_VIRTUAL_INHERITENCE,
	.numBaseClasses = 2,
	.pBaseClassArray = containerBaseClassArray
};

CompleteObjectLocator containerCompleteObjectLocator =
{
	.signature = 0x48454845,
	.pTypeDescriptor = &containerTypeDescriptor,
	.pClassHierarchyDescriptor = &containerClassHierarchyDescriptor
};

/*============================================================================
|	New Operator
*===========================================================================*/

void* NewContainer()
{
	return NULL;
}

/*============================================================================
|	Delete Operator
*===========================================================================*/

void DeleteContainer(void* this)
{

}

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
|	Copy Constructor
*===========================================================================*/

void* ContainerCopyConstruct(void* this)
{
	return NULL;
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

/*============================================================================
|	Class member functions
*===========================================================================*/

bool ContainerEquals(void* this, void* other)
{
	return (!strcmp(ContainerToString(this), ContainerToString(other))) ? true : false;
}

char* ContainerToString(void* this)
{
	return ObjectToString(this);
}

