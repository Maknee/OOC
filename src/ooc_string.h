/**
* @file ooc_string.h
* @brief String class header
*
* String class implementation using SSO optimiziation
* Credits to: 
* <a href="https://stackoverflow.com/questions/2243366/how-to-implement-a-variable-length-string-y-in-c">Motivation/idea for sso implementation</a>
* <a href="https://stackoverflow.com/questions/10315041/meaning-of-acronym-sso-in-the-context-of-stdstring">More sso idea/implementation</a>
* All derived classes must call donstructor and destructor
* All derived classes must override every function in vftable
* @author Henry Zhu (Maknee)
* @bug No know bugs.
* @note A string holds up to 16 characters including the NULL terminator
* 		until the string becomes dynamically allocated. This makes the string
* 		implementation work well with strings < 16 characters.
* @warning
* @see ooc_string.c
* @date	8/1/2017
* @todo {consider replacing C11's strcat_s}
*/

#pragma once

#include "container.h"

/*============================================================================
|   Defines
*===========================================================================*/

/**********************************************************************************************//**
 * @def		DEFAULT_STRING_LENGTH
 *
 * @brief	A macro that defines the default length of a string before
 * 			the string becomes dynamically allocated. 
 * @see		_String
 * 
 * @def		NPOS
 *
 * @brief	A macro that indicates that there was no match for a string
 * @see		_StringVFTable::find
 *
 * @def		NULL_STRING_VFTABLE
 * @brief	A macro that defines a null string vftable template for classes
 * 			that inherit from the string class
 **************************************************************************************************/

//15 characters + 1 null byte
#define DEFAULT_STRING_LENGTH 15

#define NPOS -1

#define NULL_STRING_VFTABLE                                     \
		{                                                       \
			{                                                   \
				{                                               \
					.pCompleteObjectLocator = NULL,             \
					.equals = NULL,                             \
					.toString = NULL                            \
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
			.substring = NULL                                   \
		}                                                        \

/*============================================================================
|   Object virtual function table definition
*===========================================================================*/

/**********************************************************************************************//**
 * @struct	_StringVFTable
 *
 * @brief	Struct that contains the vftable of the container class
 * 			
 * @var		_StringVFTable::containerVFTable
 * 			Pointer to the inherited container's virtual function table
 * 			
 * @var		_StringVFTable::c_str
 * 			Pointer to a function gives the raw char pointer.
 *			
 *			@param [in] this 
 *			The object
 *			@return
 *			Returns pointer to the raw string data
 *			@warning
 *			If the pointer is returned, is it up to the <b>CODER</b> to not
 *			mess up the data and ensure that the char array is read-only. 
 *			If the data is corrupted, it is highly likely that
 *			the string object will be corrupted and act strangely.
 *			
 * @var		_StringVFTable::append
 * 			Pointer to a function that appends another string to the current string
 *
 *			@param [in] this
 *			The object
 *			@param [in] item 
 *			The string to be added to the object
 *			@return
 *			Nothing
 *			@note The function should always successfully finish
 *			
 * @var		_StringVFTable::find
 * 			Pointer to a function that finds the index of the first occurence of the string to be found
 * 			
 *			@param [in] this
 *			The object
 *			@param [in] item
 *			The item to be found
 *			@return
 *			Returns index of the first occurence of the string.
 *			@note
 *			Returns NPOS if no string occurrence was found. @ref NPOS
 *			
 * @var		_StringVFTable::substring
 * 			Pointer to a function that returns a new substring between two indices of a string
 *
 *			@param [in] this
 *			The object
 *			@param [in] start
 *			The starting index
 *			@param [in] end
 *			The ending index
 *			@return
 *			Returns a new string if a string is formed, else NULL
 *			@warning
 *			Returns NULL if the indices are not within the string's boundaries or the indices are
 *			swapped.
 **************************************************************************************************/

typedef struct _String String;

typedef struct _StringVFTable
{
	struct _ContainerVFTable;
	bool (*set)(void* this, const char* item);
	char* (*c_str)(void* this);
	bool (*append)(void* this, const char* item);
	int (*find) (void* this, void* item);
	void* (*substring)(void* this, int start, int end);
} StringVFTable;

/*============================================================================
|	Special class member function definitions
*===========================================================================*/

/*============================================================================
|	New Operator
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void* NewString()
 * @brief	String's new operator
 * 			
 *			Returns an allocated new string
 * 			
 * @return	An allocated string object
 **************************************************************************************************/

void* NewString();

/*============================================================================
|	Delete Operator
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void DeleteString(void* this)
 * @brief	String's delete operator
 * 			
 *			Deletes the allocated string
 *
 * @param	[in] this
 * 			String object to be deleted
 * 			
 * @return	Nothing
 * @warning If NULL is passed, an attempt to free NULL will be made
 **************************************************************************************************/

void DeleteString(void* this);

/*============================================================================
|	Constructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void StringConstruct(void* this)
 * @brief	String's constructor
 * 			
 *			Setups the vftable by completing the RTTI dependency
 *			and memcpys the table into the object's vftable
 *
 * @param	[in] this
 * 			Object to be initialized
 * 			
 * @return	Nothing
 * @todo	{Find a way to not use memcpy for setting up the vftable...}
 **************************************************************************************************/

void StringConstruct(void* this);

/*============================================================================
|	Copy Constructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void* StringCopyConstruct(void* this)
 * @brief	String's copy constructor
 * 			
 *			Returns a copy of the string
 *
 * @param	[in] this
 * 			String to be used for copying
 * 			
 * @return	The copied string
 * @note	Derived classes may implement a copy constructor, 
 * 			but it is not necessary
 * @note    This is a <b>DEEP</b> copy, which will dynamically allocate memory
 * 			for the pBuf if the current string has dynamically allocated memory
 * @note	Does not memcpy the vtable (just points to the same vtable as the current string)
 **************************************************************************************************/

void* StringCopyConstruct(void* this);

/*============================================================================
|	Destructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void StringDestruct(void* this)
 * @brief	String's destructor
 * 			
 *			Calls the super destructors and properly manages 
 *			the deletion of the string's allocated resources
 *
 * @param	[in] this
 * 			String that should be freed of its used resources
 * 			
 * @return	Nothing
 **************************************************************************************************/

void StringDestruct(void* this);

/*============================================================================
|	Overridden member function definitions
*===========================================================================*/

/**********************************************************************************************//**
 * @fn		bool StringEquals(void* this, void* other);
 *
 * @brief	Checks if the type of the string is equal to another object
 *
 * @param	[in] this 
 * 			The string object
 * @param	[in] other
 * 			The other object
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool StringEquals(void* this, void* other);

/**********************************************************************************************//**
 * @fn		bool StringToString(void* this);
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

char* StringToString(void* this);

/**********************************************************************************************//**
 * @fn		bool StringAdd(void* this, void* item)
 *
 * @brief	Concatenates the two strings
 * 			
 *			The strings are concatenated by:
 *			Checking the new length
 *			Checking whether or not the current string was dynamically allocated
 *			If so, just call realloc and append
 *			If not, then two cases appear with a string that is externally allocated
 *			If the new length is greater than limit length, then make the pointer dynamic
 *			If the new length is less, then append to length
 *
 * @param	[in] this 
 * 			The string
 * @param	[in] item
 * 			The other string
 * @return	Returns true if the string was added correctly, 
 * 			returns false if the string was not added correctly
 * @note	Function only appends an object string to another object string,
 * 			<b>NOT</b> a string object to a char pointer. @ref StringAppend
 * @todo	{find a case when the function should fail}
 * @todo	{figure out a way to merge this function and StringAppend}
 **************************************************************************************************/

bool StringAdd(void* this, void* item);

/**********************************************************************************************//**
 * @fn		void StringClear(String* this)
 *
 * @brief	Clears the contents of the string
 * 			
 *			Sets the length to 0, 
 *			sets the capacity to @ref DEFAULT_STRING_LENGTH,
 *			and zeros out the data
 *			
 * @param	[in] this 
 * 			The string
 * @return	Nothing
 **************************************************************************************************/

void StringClear(void* this);

/**********************************************************************************************//**
 * @fn		bool StringRemove(void* this, void* item)
 *
 * @brief	Remove the substring in a string
 *			
 *			
 *			
 * @param	[in] this
 * 			The string
 * @param	[in] item
 * 			The substring
 * @return	Returns true if the substring was removed, 
 * 			returns false if the substring couldn't be found or removed
 * @note	Function will not resize the capacity. 
 * 			The overhead of free is most likely not worth resizing the capacity
 **************************************************************************************************/

bool StringRemove(void* this, void* item);

/**********************************************************************************************//**
 * @fn		bool StringContains(void* this, void* item)
 *
 * @brief	Remove the substring in a string
 *			
 * @param	[in] this
 * 			The string
 * @param	[in] item
 * 			The substring
 * @return	Returns true if the substring was is in the string, 
 * 			returns false if the substring couldn't be found
 **************************************************************************************************/

bool StringContains(void* this, void* item);

/**********************************************************************************************//**
 * @fn	void* StringCopy(void* this)
 * @brief	String's copy function
 * 			
 *			Returns a deep copy of the string
 *
 * @param	[in] this
 * 			String to be used for copying
 * 			
 * @return	The copied string
 * @note	Calls copy constructor @ref StringCopyConstruct
 * @note    This is a <b>DEEP</b> copy, which will dynamically allocate memory
 * 			for the pBuf if the current string has dynamically allocated memory
 * @note	Does not memcpy the vtable (just points to the same vtable as the current string)
 **************************************************************************************************/

void* StringCopy(void* this);

/**********************************************************************************************//**
 * @fn		bool StringIsEmpty(void* this)
 *
 * @brief	Checks if the string is empty
 *			
 * @param	[in] this
 * 			The string
 * @return	Returns true if the substring is empty, 
 * 			returns false if the substring is not empty
 **************************************************************************************************/

bool StringIsEmpty(void* this);

/**********************************************************************************************//**
 * @fn		int StringSize(void* this)
 *
 * @brief	Returns the length of the string
 *			
 * @param	[in] this
 * 			The string
 * @return	Returns the length of the string
 **************************************************************************************************/

size_t StringSize(void* this);

/*============================================================================
|	Class member definitions
*===========================================================================*/

/**********************************************************************************************//**
 * @fn		bool StringSet(void* this, void* item)
 *
 * @brief	Concatenates the two strings
 * 			
 *			The strings are concatenated by:
 *			Checking the new length
 *			Checking whether or not the current string was dynamically allocated
 *			If so, just call realloc and append
 *			If not, then two cases appear with a string that is externally allocated
 *			If the new length is greater than limit length, then make the pointer dynamic
 *			If the new length is less, then append to length
 *
 * @param	[in] this 
 * 			The string
 * @param	[in] item
 * 			The char array
 * @return	Returns true if the string was set correctly, 
 * 			returns false if the string was not set correctly
 * @note	Function sets a string to a char array, not a string object @ref StringCopy to copy another string
 * @todo	{find a case when the function should fail}
 **************************************************************************************************/

bool StringSet(void* this, const char* item);

/**********************************************************************************************//**
 * @fn		char* StringC_Str(void* this)
 *
 * @brief	Returns a pointer to the raw data of a string
 *			
 * @param	[in] this
 * 			The string
 * @return	Returns pointer to raw data
 **************************************************************************************************/

char* StringC_Str(void* this);

/**********************************************************************************************//**
 * @fn		bool StringAppend(void* this, char* item);
 *
 * @brief	Appends one string with a char pointer
 *			
 * @param	[in] this
 * 			The string
 * @param	[in] item
 * 			The pointer to a char array 
 * @return	Returns true if the char array was added correctly, 
 * 			returns false if the char array was not added correctly
 * @note	Function appends a char pointer to an array, <b>NOT</b>
 * 			a string object to another string object. @ref StringAdd
 * @todo	{find a way for this function to return false}
 **************************************************************************************************/

bool StringAppend(void* this, const char* item);

/**********************************************************************************************//**
 * @fn		int StringFind(void* this, void* item)
 *
 * @brief	Returns the index of the first occurence of the substring
 *			
 * @param	[in] this
 * 			The string
 * @param	[in] item
 * 			The substring to be found
 * @return	Returns the index
 **************************************************************************************************/

int StringFind(void* this, void* item);

/**********************************************************************************************//**
 * @fn		void* StringSubstring(void* this, int start, int end);
 *
 * @brief	Finds the substrings of of the string if possible
 *			
 * @param	[in] this
 * 			The string
 * @param	[in] start
 * 			The beginning of the substring
 * @param	[in] end
 * 			The end of the substring
 * @return	Returns a new allocated substring
 * @warning	Returns NULL if substring could not be found
 **************************************************************************************************/

void* StringSubstring(void* this, int start, int end);

/*============================================================================
|   Container virtual function table instance
*===========================================================================*/

/**
* @brief   Global string vftable
* @relates StringVFTable
* @note	Cannot make this const since there is a circular reference with RTTI structs
* @note	containerVFTable will be set in constructor
*/

StringVFTable stringVFTable;

/*============================================================================
|   Container class definition
*===========================================================================*/

/**********************************************************************************************//**
 * @struct	_String
 *
 * @brief	The string struct, which contains necessary fields for implementing a string
 * 			
 * @var		_String::container
 * 			Since the container inherits from the container class,
 * 			it must contain the container's class
 *			@see _Container
 *			
 * @var		_String::length
 * 			item that contains the current number of characters in the string
 *			@note
 *			Includes the NULL terminator
 *			
 * @var		_String::capacity
 * 			item that contains that maximum characters that string can hold.
 *			@note
 *			If the allocated string is larger than capacity, the string functions
 *			will try to increase the capacity @ref StringAdd
 *			
 * @var		_String::data
 *			Union that contains an array of chars or a pointer to a
 *			dynamically allocated array of chars depending on the length
 *			of the string
 *			
 * @var		_String::data::buf
 *			Array of chars of length @ref DEFAULT_STRING_LENGTH, which is allocated
 *			directory in the string struct
 *			
 * @var		_String::data::pBuf
 *			Char pointer to a dynamically allocated char array if the size of 
 *			the string is greater than @ref DEFAULT_STRING_LENGTH
 *			@note
 *			It is not necessary for the coder to manually deallocate this memory.
 *			The coder can assume that the allocated data will be free'd with the destructor
 *			@see
 *			StringDestruct
 **************************************************************************************************/

typedef struct _String
{
	Container container;
	size_t length;
	size_t capacity;
	union
	{
		char buf[DEFAULT_STRING_LENGTH];
		char* pBuf;
	} data;
} String;


/*============================================================================
|   RTTI (Have to declare in reverse order, so compiler knows that structs are defined already)
|   VFTable         <===============\
|   | CompleteObjectLocator         |
|       | Signature = "HEHE"        |
|       | TypeDescriptor            |
|           | pVFTable =============/   <===============\
|           | name = Class's name ("String")            |
|       | ClassHierarchyDescriptor                      |
|           | attributes = 1 (VIRTUAL)                  |
|           | numBaseClasses = 2 (Container, String)    |
|           | BaseClassArrayDescriptor                  |
|               [                                       |
|                   ContainerBaseClassDescriptor        |
|                       | numContainedClasses (1)       |
|                       | TypeDescriptor =====> Container's pVFTable
|                   StringBaseClassDescriptor           |
|                       | numContainedClasses (2)	    |
|                       | TypeDescriptor ===============/
|               ]
*===========================================================================*/

/**
* @brief	Global string type descriptor
*
* 			Contains the a pointer to the string vftable
* 			and the name of "String" to indicate that this
* 			is the string class
*/

TypeDescriptor stringTypeDescriptor;

/**********************************************************************************************//**
 * @def	StringBaseClassDescriptor
 *
 * @brief	A macro that defines string base class descriptor.
 * 			
 *			Num contained classes is two since the string inherits from 
 *			container, which inherits from object.
 **************************************************************************************************/

#define StringBaseClassDescriptor   					\
		{												\
			.numContainedClasses = 2,					\
			.pTypeDescriptor = &stringTypeDescriptor    \
		}												\

 /**
 * @brief	Global string base class descriptor array
 *
 * 			Contains the container base descriptor and
 * 			its own base class descriptor (string base descriptor)
 */

BaseClassDescriptor stringBaseClassArray[2];

/**
* @brief	Global string class hierarchy descriptor
*
* 			String class hierarchy descriptor is marked as virtual
* 			since it inherits from the container class.
* 			numBaseClasses is one since container inherits from only one class
* 			pBaseClassArray points to the container's base class descriptor
*			@ref stringBaseClassArray
*/

ClassHierarchyDescriptor stringClassHierarchyDescriptor;

/**
* @brief	Global string complete object locator
*
* 			Contains the signature to indicate that this struct contains
* 			RTTI information.
* 			pTypeDescriptor points to the string's type descriptor
* 			pClassHierarchyDescriptor points to the string's class hierarchy descriptor
*/

CompleteObjectLocator stringCompleteObjectLocator;

/*============================================================================
|	Overridden member functions
*===========================================================================*/

/*============================================================================
|	Class member functions
*===========================================================================*/

