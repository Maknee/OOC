/**
* @file ooc_object.h
* @brief Object class header
*
* Abstract base class of all classes in ooc.
* Every class must inherit from this class and implement the 
* necessary functions to ensure stability.
* 
* @author Henry Zhu (Maknee)
* @todo {Find a way to store CompleteObjectLocator in vtable at compile time
*	   Use macros to generate object base...}
* @note All derived classes must call ObjectConstructor and ObjectDestructor
* @note All derived classes must implement equals() and toString() in their vtable
* @warning All functions do not check if the object or item is NULL
* 		   nor do they check if the object or item is matches the
* 		   correct object or item. Unfortunately, it is up to
* 		   the <b>CODER</b> to ensure that the types are correct.
* @see object.c
* @todo {Maybe have an initialize/cleanup for the entire project? like for RTTI circular dependency@ref ObjectConstruct}
* @todo {Make macros for New and vftable calls...}
* @date	8/1/2017
*/

#pragma once

#include "ooc_rtti.h"
#include "ooc_error.h"

/**********************************************************************************************//**
 * @fn	void* check_calloc(size_t size);
 *
 * @brief	Call calloc with check
 *
 * @param	size	The size.
 *
 * @return	Null if it fails, else a pointer to a void.
 **************************************************************************************************/

void* check_calloc(size_t size);

/*============================================================================
|   Defines
*===========================================================================*/

/**********************************************************************************************//**
 * @def		NULL_OBJECT_VFTABLE
 *
 * @brief	A macro that defines a null object vftable template for classes
 * 			that inherit from the object class
 * 			
 * @see		Container_
 **************************************************************************************************/

#define NULL_OBJECT_VFTABLE                                     \
		.pCompleteObjectLocator = NULL,                         \
		.delete = NULL,                                         \
		.equals = NULL,                                         \
		.compareTo = NULL,                                      \
		.toString = NULL                                        \
		                                                        \

/*============================================================================
|   Object virtual function table definition
*===========================================================================*/

/**********************************************************************************************//**
 * @struct	ObjectVFTable
 *
 * @brief	Struct that contains the vftable of the object class
 * 			
 * @var		ObjectVFTable::pCompleteObjectLocator
 * 			Pointer to the object's complete object locator
 *
 * @var		ObjectVFTable::delete
 * 			Pointer to a function that calls delete on the object
 *
 *			@param [in] this
 *			The object
 *
 * @var		ObjectVFTable::equals
 * 			Pointer to a function that adds an item to the object
 *			
 *			@param [in] this 
 *			The object
 *			@param [in] other 
 *			The other object that is to be compared with
 *			@return bool
 *			Returns true if the objects are of the same type, returns false if the objects' types are different
 *			
 * @var		ObjectVFTable::toString
 * 			Pointer to a function that returns a char array of the object's type
 *
 *			@param [in] this
 *			The object
 *			@return 
 *			Pointer to a char array containing the object's RTTI name
 **************************************************************************************************/

typedef struct ObjectVFTable
{
	CompleteObjectLocator* pCompleteObjectLocator;
	void (*delete)(void* this);
	void* (*copy)(void* this);
	bool (*equals)(void* this, void* other);
	int (*compareTo)(void* this, void* other);
	char* (*toString)(void* this);
} ObjectVFTable;

/*============================================================================
|	Special class member function definitions
*===========================================================================*/

/*============================================================================
|	New Operator
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void* NewObject()
 * @brief	Object's new operator
 * 			
 *			Returns an allocated new object
 * 			
 * @return	An allocated object
 * @warning	Object is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void* NewObject();

/*============================================================================
|	Delete Operator
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void DeleteObject(void* this)
 * @brief	Object's delete operator
 * 			
 *			Deletes the allocated object
 *
 * @param	[in] this
 * 			Object to be deleted
 * 			
 * @return	Nothing
 * @warning	Object is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void DeleteObject(void* this);

/*============================================================================
|	Constructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void ObjectConstruct(void* this)
 * @brief	Object's constructor
 * 			
 *			Setups the vftable by completing the RTTI dependency
 *			and memcpys the table into the object's vftable
 *
 * @param	[in] this
 * 			Object to be initialized
 * 			
 * @return	Nothing
 * @note	All derived classes constructors must call the object constructor
 * @todo	{Find a way to not use memcpy for setting up the vftable...}
 **************************************************************************************************/

void ObjectConstruct(void* this);

/*============================================================================
|	Copy Constructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void* ObjectCopyConstruct(void* this)
 * @brief	Object's copy constructor
 * 			
 *			Returns a copy of the object
 *
 * @param	[in] this
 * 			Object to be used for copying
 * 			
 * @return	The copied object
 * @note	Derived classes may implement a copy constructor, 
 * 			but it is not necessary
 * @warning	Object is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void* ObjectCopyConstruct(void* this);

/*============================================================================
|	Destructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void ObjectDestruct(void* this)
 * @brief	Object's destructor
 * 			
 *			Calls the super destructors and properly manages 
 *			the deletion of the object's allocated resources
 *
 * @param	[in] this
 * 			Object that should be freed of its used resources
 * 			
 * @return	Nothing
 * @note	All derived classes destructors must call the object destructor
 * @warning	Object is an abstract class, so
 * 			nothing is actually executed
 **************************************************************************************************/

void ObjectDestruct(void* this);

/*============================================================================
|	Overridden member function definitions
*===========================================================================*/

/*============================================================================
|	Class member definitions
|	Note: this is a special case since this is the base class
|	due to the fact there's nothing overwriting the vtable's values
*===========================================================================*/

/**********************************************************************************************//**
 * @fn		bool ObjectEquals(void* this, void* other);
 *
 * @brief	Checks if the type of the object is equal to another object
 *
 * @param	[in] this 
 * 			The object
 * @param	[in] other
 * 			The other object
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool ObjectEquals(void* this, void* other);

/**********************************************************************************************//**
 * @fn		int ObjectCompareTo(void* this, void* other);
 *
 * @brief	Checks if the type of the object is equal to another object
 *
 * @param	[in] this 
 * 			The object
 * @param	[in] other
 * 			The other object
 *
 * @return	0 if it succeeds, negative or positive if it fails.
 **************************************************************************************************/

int ObjectCompareTo(void* this, void* other);

/**********************************************************************************************//**
 * @fn		bool ObjectToString(void* this);
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

char* ObjectToString(void* this);

/*============================================================================
|   Object virtual function table instance
*===========================================================================*/

/**
* @brief   Global object vftable
* @relates ObjectVFTable
* @note	Cannot make this const since there is a circular reference with RTTI structs
* @note	ObjectvfTable will be set in constructor
*/

extern ObjectVFTable ObjectvfTable;

/*============================================================================
|   Object class definition
*===========================================================================*/

/**********************************************************************************************//**
 * @struct	Object_
 *
 * @brief	The object struct which contains the base vftable
 * 			
 * @var		Object_::pVFTable
 * 			The vftable (may be casted vftable)
 * @var		Object_::objectpVFTable
 * 			The actual aftable (will never be casted)
 **************************************************************************************************/

typedef struct Object_
{
	void* pVFTable;
	void* objectpVFTable;
} *Object;

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

/**
* @brief	Global object type descriptor
*
* 			Contains the a pointer to the object vftable
* 			and the name of "Object" to indicate that this
* 			is the object class
*/

extern TypeDescriptor objectTypeDescriptor;

/**********************************************************************************************//**
 * @def	ObjectBaseClassDescriptor
 *
 * @brief	A macro that defines object base class descriptor.
 * 			
 *			Num contained classes is none since the object is the base class
 **************************************************************************************************/

#define ObjectBaseClassDescriptor                           \
        {                                                   \
			.numContainedClasses = 0,                       \
			.pTypeDescriptor = &objectTypeDescriptor        \
		}                                                   \

 /**
 * @brief	Global object base class descriptor array
 *
 * 			Contains the object base descriptor (itself)
 */

extern BaseClassDescriptor objectBaseClassArray[1];

/**
* @brief	Global object class hierarchy descriptor
*
* 			Object class hierarchy descriptor is no inheritence since
* 			the class does not inherit from any other class
* 			numBaseClasses is one since object inherits from only one class
* 			pBaseClassArray points to the object's base class descriptor
*			@ref objectBaseClassArray
*/

extern ClassHierarchyDescriptor objectClassHierarchyDescriptor;
/**
* @brief	Global object complete object locator
*
* 			Contains the signature to indicate that this struct contains
* 			RTTI information.
* 			pTypeDescriptor points to the object's type descriptor
* 			pClassHierarchyDescriptor points to the object's class hierarchy descriptor
*/

extern CompleteObjectLocator objectCompleteObjectLocator;

/*============================================================================
|	Overridden member functions
*===========================================================================*/

/*============================================================================
|	Class member functions
*===========================================================================*/
