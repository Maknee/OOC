/**
* @file container.h
* @brief Container class header
*
* This file contains the information about the
* abstract container class of container classes 
* (ex: string, vector, map...).
* Every container class <b> MUST </b> inherit from this
* class and override the functions in the vftable.
* 
* @author Henry Zhu (Maknee)
* @bug No know bugs.
* @note All derived classes must call donstructor and destructor
* @note All derived classes must override every function in vftable
* @warning All functions do not check if the object or item is NULL
* 		   nor do they check if the object or item is matches the 
* 		   correct object or item. Unfortunately, it is up to 
* 		   the <b>CODER</b> to ensure that the types are correct. 
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
 *			@param [in] this 
 *			The object
 *			@param [in] item 
 *			The item to be added to the object
 *			@return
 *			Returns true if the item was added successfully, returns false if the item was added unsuccessfully		
 *			
 * @var		_ContainerVFTable::clear
 * 			Pointer to a function that clears all items in the container
 *
 *			@param [in] this
 *			The object
 *			@return 
 *			Nothing
 *			@note Does not clear the container itself. 
 *				  Clearing the container requires calling the destructor
 *			@note The function should always successfully finish
 *			
 * @var		_ContainerVFTable::remove
 * 			Pointer to a function that removes an item in the container
 *
 *			@param [in] this
 *			The object
 *			@param [in] item
 *			The item to be removed
 *			@return
 *			Returns true if the item was removed successfully, returns false if the item was removed unsuccessfully	
 *			
 * @var		_ContainerVFTable::contains
 * 			Pointer to a function that checks whether or not an item is in
 * 			the container
 *
 *			@param [in] this
 *			The object
 *			@param [in] item
 *			The item to be checked
 *			@return
 *			Returns true if the item is in the container, false if the item is not in the container
 *			
 * @var		_ContainerVFTable::isEmpty
 * 			Pointer to a function that checks whether or not the container
 * 			is empty
 *
 *			@param [in] this
 *			The object
 *			@return [in] bool
 *			Returns true if the container is empty, returns false if the container is not empty
 *			
 * @var		_ContainerVFTable::size
 * 			Pointer to a function that returns the number of elements
 * 			in the container
 *
 *			@param [in] this
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

/** 
 * @brief   Global static container vftable
 * @relates ContainerVFTable
 * @note	Cannot make this const since there is a circular reference with RTTI structs
 * @note	objectVFTable will be set in constructor
 */

static ContainerVFTable containerVFTable =
{
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

/**********************************************************************************************//**
 * @struct	_Container
 *
 * @brief	The container struct, which only contains the inherited Object class
 * 			
 * @var		_Container::object
 * 			Since the container inherits from the object class,
 * 			it must contain the object's class
 *			@see _Object
 **************************************************************************************************/

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
|           | name = Class's name ("Container")         |
|       | ClassHierarchyDescriptor                      |
|           | attributes = 1 (VIRTUAL)                  |
|           | numBaseClasses = 2 (Object, Container)    |
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

/**
* @brief	Global static container type descriptor
* 			
* 			Contains the a pointer to the container vftable
* 			and the name of "Container" to indicate that this
* 			is the container class
*/

static TypeDescriptor containerTypeDescriptor =
{
	.pVFTable = &containerVFTable,
	.name = "Container"
};

/**********************************************************************************************//**
 * @def	ContainerBaseClassDescriptor
 *
 * @brief	A macro that defines container base class descriptor.
 * 			
 *			Num contained classes is one since the container inherits from
 *			object.
 *			The type descriptor points to the container type descriptor
 **************************************************************************************************/

#define ContainerBaseClassDescriptor					    \
		{                                                   \
			.numContainedClasses = 1,                       \
			.pTypeDescriptor = &containerTypeDescriptor     \
		}                                                   \

 /**
 * @brief	Global static container base class descriptor array
 *
 * 			Contains the object base descriptor and
 * 			its own base class descriptor (container base descriptor)
 */

static BaseClassDescriptor containerBaseClassArray[] =
{
	ObjectBaseClassDescriptor,
	ContainerBaseClassDescriptor
};

/**
* @brief	Global static container class hierarchy descriptor
*
* 			Container class hierarchy descriptor is marked as virtual
* 			since it inherits from the object class.
* 			numBaseClasses is two since container inherits from only one class
* 			pBaseClassArray points to the container's base class descriptor
*			@ref containerBaseClassArray
*/

static ClassHierarchyDescriptor containerClassHierarchyDescriptor =
{
	.attributes = CLASS_HIERARCHY_VIRTUAL_INHERITENCE,
	.numBaseClasses = 2,
	.pBaseClassArray = containerBaseClassArray
};

/**
* @brief	Global static container complete object locator
*
* 			Contains the signature to indicate that this struct contains
* 			RTTI information.
* 			pTypeDescriptor points to the container's type descriptor
* 			pClassHierarchyDescriptor points to the container's class hierarchy descriptor
*/

static CompleteObjectLocator containerCompleteObjectLocator =
{
	.signature = 0x48454845,
	.pTypeDescriptor = &containerTypeDescriptor,
	.pClassHierarchyDescriptor = &containerClassHierarchyDescriptor
};

/*============================================================================
|	New Operator
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void* NewContainer()
 * @brief	Container's new operator
 * 			
 *			Returns an allocated new container
 * 			
 * @return	An allocated container object
 * @warning	Container is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void* NewContainer()
{
	return NULL;
}

/*============================================================================
|	Delete Operator
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void DeleteContainer(void* this)
 * @brief	Container's delete operator
 * 			
 *			Deletes the allocated object
 *
 * @param	[in] this
 * 			Container object to be deleted
 * 			
 * @return	Nothing
 * @warning	Container is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void DeleteContainer(void* this)
{
	return NULL;
}

/*============================================================================
|	Constructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void ContainerConstruct(void* this)
 * @brief	Container's constructor
 * 			
 *			Calls the super constructors, setups the vftable 
 *			and initializes class's member variables 
 *
 * @param	[in] this
 * 			Container object to be initialized
 * 			
 * @return	Nothing
 **************************************************************************************************/

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

/**********************************************************************************************//**
 * @fn	void* ContainerCopyConstruct(void* this)
 * @brief	Container's copy constructor
 * 			
 *			Returns a copy of the container object
 *
 * @param	[in] this
 * 			Container object to be used for copying
 * 			
 * @return	The copied container object
 * @note	Derived classes may implement a copy constructor, 
 * 			but it is not necessary
 * @warning	Container is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void* ContainerCopyConstruct(void* this)
{
	return NULL;
}

/*============================================================================
|	Destructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void ContainerDestruct(void* this)
 * @brief	Container's destructor
 * 			
 *			Calls the super destructors and properly manages 
 *			the deletion of the object's allocated resources
 *
 * @param	[in] this
 * 			Container object that should be freed of its used resources
 * 			
 * @return	Nothing
 * @warning	Container is an abstract class, so
 * 			even though this calls @ref ObjectDestruct
 * 			nothing is actually executed
 **************************************************************************************************/

void ContainerDestruct(void* this)
{
	//No use since this is an abstract class
	ObjectDestruct(this);
}

/*============================================================================
|	Overridden member functions
*===========================================================================*/

/**********************************************************************************************//**
 * @fn		bool ContainerEquals(void* this, void* other);
 *
 * @brief	Checks if the type of the container is equal to another container
 *
 * @param	[in] this 
 * 			The object
 * @param	[in] other
 * 			The other object
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool ContainerEquals(void* this, void* other)
{
	return (!strcmp(ContainerToString(this), ContainerToString(other))) ? true : false;
}

/**********************************************************************************************//**
 * @fn		bool ContainerToString(void* this);
 *
 * @brief	Gives the object's type name.
 * 			Is used for casts.
 * 			Can be useful for debugging.
 *
 * @param	[in] this 
 * 			The object
 *
 * @return	Returns a pointer to the object's name
 **************************************************************************************************/

char* ContainerToString(void* this)
{
	return ObjectToString(this);
}

/*============================================================================
|	Class member functions
*===========================================================================*/


