/**
* @file ooc_vector_def.h
* @brief Vector class header
*
* Vector class implementation using SSO optimiziation
* Credits to: 
* <a href="https://stackoverflow.com/questions/2243366/how-to-implement-a-variable-length-vector-y-in-c">Motivation/idea for sso implementation</a>
* <a href="https://stackoverflow.com/questions/10315041/meaning-of-acronym-sso-in-the-context-of-stdvector">More sso idea/implementation</a>
* All derived classes must call donstructor and destructor
* All derived classes must override every function in vftable
* @author Henry Zhu (Maknee)
* @bug No know bugs.
* @note A vector holds up to 16 characters including the NULL terminator
* 		until the vector becomes dynamically allocated. This makes the vector
* 		implementation work well with vectors < 16 characters.
* @warning <b>NEVER</b> use the same vector more than once in a vector function call. 
* 		   It will corrupt the vector.
* @see ooc_vector.c
* @date	8/1/2017
* @todo {consider replacing C11's strcat_s}
*/

#pragma once

#include "container.h"
#include "template.h"

/*============================================================================
|   Defines
*===========================================================================*/

/**********************************************************************************************//**
 * @def		NPOS
 *
 * @brief	A macro that indicates that there was no match for a vector
 * @see		_VectorVFTable::find
 *
 * @def		NULL_VECTOR_VFTABLE
 * @brief	A macro that defines a null vector vftable template for classes
 * 			that inherit from the vector class
 **************************************************************************************************/

#define NPOS -1

#define NULL_VECTOR_VFTABLE                                     \
		{                                                       \
			{                                                   \
				{                                               \
					.pCompleteObjectLocator = NULL,             \
					.equals = NULL,                             \
					.toVector = NULL                            \
				},                                              \
				.add = NULL,                                    \
				.clear = NULL,                                  \
				.remove = NULL,                                 \
				.contains = NULL,                               \
				.copy = NULL,                                   \
				.isEmpty = NULL,                                \
				.size = NULL                                    \
			},                                                  \
			.c_str = NULL,                                      \
			.append = NULL,                                     \
			.find = NULL,                                       \
			.subvector = NULL                                   \
		}                                                        \

/*============================================================================
|   Object virtual function table definition
*===========================================================================*/

/**********************************************************************************************//**
 * @struct	_VectorVFTable
 *
 * @brief	Struct that contains the vftable of the vector class
 * 			Vector Methods\n\n
 * 			Overridden Methods\n
 * 			@ref Object Methods\n
 *			equals\n
 *			toVector\n
 *			@ref Container Methods\n
 *			add\n
 *			clear\n
 *			remove\n
 *			contains\n
 *			copy\n
 *			isEmpty\n
 *			size\n\n
 *			Class member methods\n
 *			set\n
 *			c_str\n
 *			append\n
 *			insert\n
 *			replace\n
 *			find\n
 *			subvector\n
 *			
 * @var		_VectorVFTable::containerVFTable
 * 			Pointer to the inherited container's virtual function table
 * 			
 * @var		_VectorVFTable::set
 * 			Pointer to a function sets the contents of the vector to a vector literal
 *			
 *			@param [in] this 
 *			The object
 *			@param [in] item 
 *			The vector literal
 *			@return
 *			Returns true if the vector's data was set, else false
 *			
 * @var		_VectorVFTable::c_str
 * 			Pointer to a function gives the raw char pointer.
 *			
 *			@param [in] this 
 *			The object
 *			@return
 *			Returns pointer to the raw vector data
 *			@warning
 *			If the pointer is returned, is it up to the <b>CODER</b> to not
 *			mess up the data and ensure that the char array is read-only. 
 *			If the data is corrupted, it is highly likely that
 *			the vector object will be corrupted and act strangely.
 *			
 * @var		_VectorVFTable::append
 * 			Pointer to a function that appends another vector to the current vector
 *
 *			@param [in] this
 *			The object
 *			@param [in] item 
 *			The vector to be added to the object
 *			@return
 *			Nothing
 *			@note The function should always successfully finish
 *			
 * @var		_VectorVFTable::insert
 * 			Pointer to a function that inserts the item into the vector at the index
 *
 *			@param [in] this
 *			The object
 *			@param [in] item 
 *			The vector to be added to the object
 *			@param [in] index
 *			Index where the item should be inserted into the object
 *			@return
 *			Returns true if the item was inserted at the index, else false
 *			
 * @var		_VectorVFTable::replace
 * 			Pointer to a function that replaces the item with the replacement vector in this vector
 *
 *			@param [in] this
 *			The object
 *			@param [in] item 
 *			The vector to be replaced
 *			@param [in] replacement
 *			The vector to replace the item with
 *			@return
 *			Returns true if all occurrences were replaced, else false
 *
 * @var		_VectorVFTable::find
 * 			Pointer to a function that finds the index of the first occurence of the vector to be found
 * 			
 *			@param [in] this
 *			The object
 *			@param [in] item
 *			The item to be found
 *			@return
 *			Returns index of the first occurence of the vector.
 *			@note
 *			Returns NPOS if no vector occurrence was found. @ref NPOS
 *			
 * @var		_VectorVFTable::subvector
 * 			Pointer to a function that returns a new subvector between two indices of a vector
 *
 *			@param [in] this
 *			The object
 *			@param [in] start
 *			The starting index
 *			@param [in] end
 *			The ending index
 *			@return
 *			Returns a new vector if a vector is formed, else NULL
 *			@warning
 *			Returns NULL if the indices are not within the vector's boundaries or the indices are
 *			swapped.
 **************************************************************************************************/

typedef struct _Vector Vector;

typedef struct _VectorVFTable
{
	struct _ContainerVFTable;
	bool (*set)(void* this, T* item);
	T* (*get)(void* this, int index);
	bool (*push_front)(void* this, T* item);
	bool (*push_back)(void* this, T* item);
	bool (*insert)(void* this, T* item, int index);
	int (*find) (void* this, T* item);
	T* (*data)(void* this);
} VectorVFTable;

/*============================================================================
|   Container class definition
*===========================================================================*/

/**********************************************************************************************//**
 * @struct	_Vector
 *
 * @brief	The vector struct, which contains necessary fields for implementing a vector\n
 * 			See @ref VectorVFTable for avaliable vector functions
 * 			
 * @var		_Vector::container
 * 			Since the container inherits from the container class,
 * 			it must contain the container's class
 *			@see _Container
 *			
 * @var		_Vector::length
 * 			item that contains the current number of characters in the vector
 *			@note
 *			Includes the NULL terminator
 *			
 * @var		_Vector::capacity
 * 			item that contains that maximum characters that vector can hold.
 *			@note
 *			If the allocated vector is larger than capacity, the vector functions
 *			will try to increase the capacity @ref VectorAdd
 *			
 * @var		_Vector::data
 *			Union that contains an array of chars or a pointer to a
 *			dynamically allocated array of chars depending on the length
 *			of the vector
 *			
 * @var		_Vector::data
 *			Char pointer to a dynamically allocated char array if the size of 
 *			the vector is greater than @ref DEFAULT_VECTOR_LENGTH
 *			@note
 *			It is not necessary for the coder to manually deallocate this memory.
 *			The coder can assume that the allocated data will be free'd with the destructor
 *			@see
 *			VectorDestruct
 **************************************************************************************************/

typedef struct _Vector
{
	Container container;
	size_t length;
	size_t capacity;
	void* data;
} Vector;

/**********************************************************************************************//**
 * @def	VectorBaseClassDescriptor
 *
 * @brief	A macro that defines vector base class descriptor.
 * 			
 *			Num contained classes is two since the vector inherits from 
 *			container, which inherits from object.
 **************************************************************************************************/

#define VectorBaseClassDescriptor   					\
		{												\
			.numContainedClasses = 2,					\
			.pTypeDescriptor = &vectorTypeDescriptor    \
		}												\
