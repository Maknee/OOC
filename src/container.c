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

ContainerVFTable ContainervfTable =
{
	NULL_OBJECT_VFTABLE,
	.add = NULL,
	.clear = NULL,
	.remove = NULL,
	.contains = NULL,
	.isEmpty = NULL,
	.size = NULL
};

TypeDescriptor containerTypeDescriptor =
{
	.pVFTable = &ContainervfTable,
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
	//No use since this is an abstract class
	DEBUG_PRINT("%s\n", "Warning! Calling new on an abstract class!");
	return NULL;
}

/*============================================================================
|	Delete Operator
*===========================================================================*/

void DeleteContainer(void* this)
{
	//No use since this is an abstract class
	DEBUG_PRINT("%s\n", "Warning! Calling delete on an abstract class!");
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
	ContainervfTable.pCompleteObjectLocator = &containerCompleteObjectLocator;
	ContainervfTable.delete = &DeleteContainer;
	ContainervfTable.equals = &ContainerEquals;
	ContainervfTable.compareTo = &ContainerCompareTo;
	ContainervfTable.toString = &ContainerToString;

	//Initialize the vtable to point to this object's vtable
	memcpy(((Container)this)->object.pVFTable, &ContainervfTable, sizeof(ContainerVFTable));

	//Make the objectpVFTable point to the same table initially
	((Container)this)->object.objectpVFTable = ((Container)this)->object.pVFTable;
}

/*============================================================================
|	Copy Constructor
*===========================================================================*/

void* ContainerCopyConstruct(void* this)
{
	DEBUG_PRINT("%s\n", "Warning! Calling copy constructor on an abstract class!");
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
	CHECK_NULL(this, false);
	CHECK_NULL(other, false);

	return (!strcmp(ContainerToString(this), ContainerToString(other))) ? true : false;
}

int ContainerCompareTo(void* this, void* other)
{
	CHECK_NULL(this, false);
	CHECK_NULL(other, false);

	return strcmp(ContainerToString(this), ContainerToString(other));
}

char* ContainerToString(void* this)
{
	CHECK_NULL(this, NULL);

	return ObjectToString(this);
}

