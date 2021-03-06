/**
* @file ooc_container.h
* @brief Container class header
*
* This file contains the information about the
* abstract ooc_container.class of ooc_container.classes 
* (ex: string, vector, map...).
* Every ooc_container.class <b> MUST </b> inherit from this
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
* @see ooc_container.c
* @date	8/1/2017
*/

#pragma once

#include "ooc_object.h"

/*============================================================================
|   Defines
*===========================================================================*/

/**********************************************************************************************//**
 * @def		NULL_CONTAINER_VFTABLE
 *
 * @brief	A macro that defines a null container vftable template for classes
 * 			that inherit from the ooc_container.class
 * 			
 * @see		_String
 * @see		_List
 **************************************************************************************************/

#define NULL_CONTAINER_VFTABLE                                  \
		NULL_OBJECT_VFTABLE,                                    \
		.add = NULL,                                            \
		.clear = NULL,                                          \
		.remove = NULL,                                         \
		.contains = NULL,                                       \
		.isEmpty = NULL,                                        \
		.size = NULL                                            \

/*============================================================================
|   Object virtual function table definition
*===========================================================================*/

/**********************************************************************************************//**
 * @struct	ContainerVFTable
 *
 * @brief	Struct that contains the vftable of the ooc_container.class
 * 			
 * @var		ContainerVFTable::objectVFTable
 * 			Pointer to the inherited object's virtual function table
 * 			
 * @var		ContainerVFTable::add
 * 			Pointer to a function that adds an item to the container
 *			
 *			@param [in] this 
 *			The object
 *			@param [in] item 
 *			The item to be added to the object
 *			@return
 *			Returns true if the item was added successfully, returns false if the item was added unsuccessfully		
 *			
 * @var		ContainerVFTable::clear
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
 * @var		ContainerVFTable::remove
 * 			Pointer to a function that removes an item in the container
 *
 *			@param [in] this
 *			The object
 *			@param [in] item
 *			The item to be removed
 *			@return
 *			Returns true if the item was removed successfully, returns false if the item was removed unsuccessfully	
 *			
 * @var		ContainerVFTable::contains
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
 * @var		ContainerVFTable::copy
 * 			Pointer to a function that copies the container and returns a pointer to the copy
 * 			the container
 *
 *			@param [in] this
 *			The object
 *			@return
 *			Returns a copy of the container or null if it cannot be copied
 * 
 * @var		ContainerVFTable::isEmpty
 * 			Pointer to a function that checks whether or not the container
 * 			is empty
 *
 *			@param [in] this
 *			The object
 *			@return [in] bool
 *			Returns true if the container is empty, returns false if the container is not empty
 *			
 * @var		ContainerVFTable::size
 * 			Pointer to a function that returns the number of elements
 * 			in the container
 *
 *			@param [in] this
 *			The object
 *			@return int
 *			Returns number of elements in the container
 **************************************************************************************************/

typedef struct ContainerVFTable
{
	CompleteObjectLocator* pCompleteObjectLocator;
	void(*delete)(void* this);
	void* (*copy)(void* this);
	bool(*equals)(void* this, void* other);
	int(*compareTo)(void* this, void* other);
	char* (*toString)(void* this);

	bool (*add)(void* this, void* item);
	void (*clear)(void* this);
	bool (*remove)(void* this, void* item);
	bool (*contains)(void* this, void* item);
	bool (*isEmpty)(void* this);
	size_t (*size)(void* this);
} ContainerVFTable;

/*============================================================================
|	Special class member function definitions
*===========================================================================*/

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

void* NewContainer();

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

void DeleteContainer(void* this);

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
 * @note	All derived class ooc_container.constructors must call the ooc_container.constructor
 **************************************************************************************************/

void ContainerConstruct(void* this);

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

void* ContainerCopyConstruct(void* this);

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
 * @note	All derived class container destructors must call the container destructor
 * @warning	Container is an abstract class, so
 * 			even though this calls @ref ObjectDestruct
 * 			nothing is actually executed
 **************************************************************************************************/

void ContainerDestruct(void* this);

/*============================================================================
|	Overridden member function definitions
*===========================================================================*/

/**********************************************************************************************//**
 * @fn		bool ContainerEquals(void* this, void* other);
 *
 * @brief	Checks if the type of the container is equal to ooc_container.container
 *
 * @param	[in] this 
 * 			The object
 * @param	[in] other
 * 			The other object
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool ContainerEquals(void* this, void* other);

/**********************************************************************************************//**
 * @fn		int ContainerCompareTo(void* this, void* other);
 *
 * @brief	Checks if the type of the container is equal to another object
 *
 * @param	[in] this 
 * 			The object
 * @param	[in] other
 * 			The other object
 *
 * @return	0 if it succeeds, negative or positive if it fails.
 **************************************************************************************************/

int ContainerCompareTo(void* this, void* other);

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

char* ContainerToString(void* this);

/*============================================================================
|	Class member definitions
*===========================================================================*/

/*============================================================================
|   Container virtual function table instance
*===========================================================================*/

/** 
 * @brief   Global container vftable
 * @relates ContainerVFTable
 * @note	Cannot make this const since there is a circular reference with RTTI structs
 * @note	objectVFTable will be set in constructor
 */

extern ContainerVFTable ContainervfTable;

/*============================================================================
|   Container class definition
*===========================================================================*/

/**********************************************************************************************//**
 * @struct	Container_
 *
 * @brief	The container struct, which only contains the inherited Object class
 * 			
 * @var		Container_::object
 * 			Since the container inherits from the object class,
 * 			it must contain the object's class
 *			@see Object_
 **************************************************************************************************/

typedef struct Container_
{
	struct Object_ object;
} *Container;

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
* @brief	Global container type descriptor
* 			
* 			Contains the a pointer to the container vftable
* 			and the name of "Container" to indicate that this
* 			is the ooc_container.class
*/

extern TypeDescriptor containerTypeDescriptor;

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
 * @brief	Global container base class descriptor array
 *
 * 			Contains the object base descriptor and
 * 			its own base class descriptor (container base descriptor)
 */

extern BaseClassDescriptor containerBaseClassArray[2];

/**
* @brief	Global ooc_container.class hierarchy descriptor
*
* 			Container class hierarchy descriptor is marked as virtual
* 			since it inherits from the object class.
* 			numBaseClasses is two since container inherits from only one class
* 			pBaseClassArray points to the container's base class descriptor
*			@ref containerBaseClassArray
*/

extern ClassHierarchyDescriptor containerClassHierarchyDescriptor;

/**
* @brief	Global ooc_container.complete object locator
*
* 			Contains the signature to indicate that this struct contains
* 			RTTI information.
* 			pTypeDescriptor points to the container's type descriptor
* 			pClassHierarchyDescriptor points to the container's class hierarchy descriptor
*/

extern CompleteObjectLocator containerCompleteObjectLocator;

/*============================================================================
|	Class member functions
*===========================================================================*/

/*============================================================================
|	Overridden member functions
*===========================================================================*/

