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
* @date	8/1/2017
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
#define DEFAULT_STRING_LENGTH 15 + 1

#define NPOS -1

#define NULL_STRING_VFTABLE                                 \
		{                                                   \
			.containerVFTable =                             \
			{                                               \
				.objectVFTable =                            \
				{                                           \
					.pCompleteObjectLocator = NULL,         \
					.equals = NULL,                         \
					.toString = NULL                        \
				},                                          \
				.add = NULL,                                \
				.clear = NULL,                              \
				.remove = NULL,                             \
				.contains = NULL,                           \
				.isEmpty = NULL,                            \
				.size = NULL                                \
			},                                              \
			.c_str = NULL,                                  \
			.append = NULL,                                 \
			.find = NULL,                                   \
			.substring = NULL                               \
		}                                                   \

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
	ContainerVFTable containerVFTable;
	char* (*c_str)(void* this);
	void (*append)(void* this, char* value);
	int (*find) (void* this, char* value);
	String* (*substring)(void* this, int start, int end);
} StringVFTable;

/*============================================================================
|	Overridden member function definitions
*===========================================================================*/

bool StringEquals(void* this, void* other);
char* StringToString(void* this);
bool StringAdd(void* this, void* item);
void StringClear(void* this);
bool StringRemove(void* this, void* item);
bool StringContains(void* this, void* item);
bool StringIsEmpty(void* this);
int StringSize(void* this);

/*============================================================================
|	Class member definitions
*===========================================================================*/

/*============================================================================
|   Container virtual function table instance
*===========================================================================*/

/**
* @brief   Global static string vftable
* @relates StringVFTable
* @note	Cannot make this const since there is a circular reference with RTTI structs
* @note	containerVFTable will be set in constructor
*/

static StringVFTable stringVFTable =
{
	.containerVFTable = NULL_CONTAINER_VFTABLE,                                      
	.c_str = NULL,
	.append = NULL,
	.find = NULL,
	.substring = NULL
};

/*============================================================================
|   Container class definition
*===========================================================================*/

//https://stackoverflow.com/questions/10315041/meaning-of-acronym-sso-in-the-context-of-stdstring
//SSO implementation

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
 * 			Value that contains the current number of characters in the string
 *			@note
 *			Includes the NULL terminator
 *			
 * @var		_String::capacity
 * 			Value that contains that maximum characters that string can hold.
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
* @brief	Global static string type descriptor
*
* 			Contains the a pointer to the string vftable
* 			and the name of "String" to indicate that this
* 			is the string class
*/

static TypeDescriptor stringTypeDescriptor =
{
	.pVFTable = &stringVFTable,
	.name = "String"
};

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
 * @brief	Global static string base class descriptor array
 *
 * 			Contains the container base descriptor and
 * 			its own base class descriptor (string base descriptor)
 */

static BaseClassDescriptor stringBaseClassArray[] =
{
	ContainerBaseClassDescriptor,
	StringBaseClassDescriptor
};

/**
* @brief	Global static string class hierarchy descriptor
*
* 			String class hierarchy descriptor is marked as virtual
* 			since it inherits from the container class.
* 			numBaseClasses is one since container inherits from only one class
* 			pBaseClassArray points to the container's base class descriptor
*			@ref containerBaseClassArray
*/

static ClassHierarchyDescriptor stringClassHierarchyDescriptor =
{
	.attributes = CLASS_HIERARCHY_VIRTUAL_INHERITENCE,
	.numBaseClasses = 1,
	.pBaseClassArray = stringBaseClassArray
};

/**
* @brief	Global static string complete object locator
*
* 			Contains the signature to indicate that this struct contains
* 			RTTI information.
* 			pTypeDescriptor points to the string's type descriptor
* 			pClassHierarchyDescriptor points to the string's class hierarchy descriptor
*/

static CompleteObjectLocator stringCompleteObjectLocator =
{
	.signature = 0x48454845,
	.pTypeDescriptor = &stringTypeDescriptor,
	.pClassHierarchyDescriptor = &stringClassHierarchyDescriptor
};

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

void* NewString()
{
	return NULL;
}

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
 * 			Container string to be deleted
 * 			
 * @return	Nothing
 * @note	If NULL is passed, an attempt to free NULL will be made
 **************************************************************************************************/

void DeleteString(void* this)
{
	return NULL;
}

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

void StringConstruct(void* this)
{
	//call super class's constructor (ObjectConstruct)
	ContainerConstruct(this);

	//Override Object's methods
	//=========================

	//Set the vtable's complete object locator to complete the RTTI circle
	stringVFTable.containerVFTable.objectVFTable.pCompleteObjectLocator = &stringCompleteObjectLocator;

	//Set the equals function
	stringVFTable.containerVFTable.objectVFTable.equals = &StringEquals;

	//Set the toString
	stringVFTable.containerVFTable.objectVFTable.toString = &StringToString;

	//Override Container's methods
	//==========================

	stringVFTable.containerVFTable.clear = &StringClear;
	stringVFTable.containerVFTable.remove = &StringRemove;
	stringVFTable.containerVFTable.contains = &StringContains;
	stringVFTable.containerVFTable.isEmpty = &StringIsEmpty;
	stringVFTable.containerVFTable.size = &StringSize;

	//Initialize the vtable to point to this object's vtable
	memcpy(((String*)this)->container.object.pVFTable, &stringVFTable, sizeof(StringVFTable));

	//Initialize member variables

	//capacity excludes Null terminator
	((String*)this)->capacity = DEFAULT_STRING_LENGTH - 1;
	((String*)this)->length = 0;

	//Null out buffer
	memset(((String*)this)->data.buf, 0, sizeof(((String*)this)->data.buf));
}

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
 **************************************************************************************************/

void* StringCopyConstruct(void* this)
{
	return NULL;
}

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

void StringDestruct(void* this)
{
	ContainerDestruct(this);
	
	//free dynamically allocated memory only if the size of the string
	//is greater than the default string length (size of char array buffer)
	if (((String*)this)->capacity >= DEFAULT_STRING_LENGTH)
	{
		free(((String*)this)->data.pBuf);
	}
}

/*============================================================================
|	Overridden member functions
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

bool StringEquals(void* this, void* other)
{
	return (!strcmp(StringToString(this), StringToString(other))) ? true : false;
}

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

char* StringToString(void* this)
{
	return StringToString(this);
}

/**********************************************************************************************//**
 * @fn		bool CheckIfStringIsAllocated(String* this);
 *
 * @brief	Checks if a string has been dynamically allocated or
 * 			is allocated in the struct
 *
 * @param	[in] this 
 * 			The string
 *
 * @return	Returns true if the string is allocated, returns false if the string isn't allocated
 * @note	Helper function @see StringAdd
 **************************************************************************************************/

static bool CheckIfStringIsAllocated(String* this)
{
	return this->capacity >= DEFAULT_STRING_LENGTH;
}

/**********************************************************************************************//**
 * @fn		void StringStrncat(String* this, String* other)
 *
 * @brief	Checks if this and other string is allocated and 
 * 			concatenates the two strings correctly 
 *
 * @param	[in] this 
 * 			The string
 * @param	[in] other
 * 			The other string
 * @return	Nothing
 * @note	Helper function @see StringAdd
 **************************************************************************************************/

void StringStrncat(String* this, String* other)
{
	if (CheckIfStringIsAllocated(this))
	{
		if (CheckIfStringIsAllocated(other))
		{
			strncat(this->data.pBuf, other->data.pBuf, other->length);
		}
		else
		{
			strncat(this->data.pBuf, other->data.buf, other->length);
		}
	}
	else
	{
		if (CheckIfStringIsAllocated(other))
		{
			strncat(this->data.buf, other->data.pBuf, other->length);
		}
		else
		{
			strncat(this->data.buf, other->data.buf, other->length);
		}
	}
}

/**********************************************************************************************//**
 * @fn		void StringStrncat(String* this, String* other)
 *
 * @brief	Concatenates the two strings
 * 			
 *			The strings are concatenated by:
 *			Checking the new length
 *			Checking whether or not the current string was dynamically allocated
 *			If so, just call realloc and append
 *			If not, then two cases appear with a string that is statically allocated
 *			If the new length is greater than static limit length, then make the pointer dynamic
 *			If the new length is less, then append to static length
 *
 * @param	[in] this 
 * 			The string
 * @param	[in] other
 * 			The other string
 * @return	Returns true if the string was added correctly, 
 * 			returns false if the string was not added correctly
 * @todo	{find a case when the function should fail}
 **************************************************************************************************/

bool StringAdd(void* this, void* item)
{
	String* this_string = (String*)this;
	String* other_string = (String*)item;

	//check if the new string can be appended
	size_t new_length = this_string->length + other_string->length;
	if (this_string->capacity < new_length)
	{
		//check whether or not the string is using an array or a dynamic pointer
		if(CheckIfStringIsAllocated(this))
		{
			//this string is dynamically allocated, so realloc with twice the length
			this_string->data.pBuf = realloc(this_string->data.pBuf, new_length * 2);

			//copy the other string's data
			StringStrncat(this_string, other_string);
		}
		else
		{
			//this string might need to dynamically allocated. 
			if (new_length >= DEFAULT_STRING_LENGTH)
			{
				//this string should be dynamically allocated now
				this_string->capacity = new_length * 2;
				
				//allocate dynamically allocated string
				char* tmp = calloc(1, this_string->capacity);
				
				//copy this string's data
				memcpy(tmp, this_string->data.pBuf, this_string->length);
				
				//copy the other string's data
				StringStrncat(this_string, other_string);
			}
			else
			{
				//copy the other string's data
				StringStrncat(this_string, other_string);

				//only update the capacity to the new length
				this_string->capacity = new_length;
			}
		}

		//update the length
		this_string->length = new_length;
	}
	return true;
}

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

void StringClear(void* this)
{
	String* this_string = (String*)this;

	//update the length and capacity
	this_string->length = 0;
	this_string->capacity = DEFAULT_STRING_LENGTH;

	//check if the string was dynamically allocated
	if (CheckIfStringIsAllocated(this))
	{
		//deallocate the dynamically allocated data
		free(this_string->data.pBuf);
	}

	//clear the data out
	memset(this_string->data.buf, 0, sizeof(this_string->data.buf));
}

bool StringRemove(void* this, void* item)
{
	return false;
}

bool StringContains(void* this, void* item)
{
	return false;
}

bool StringIsEmpty(void* this)
{
	return false;
}

int StringSize(void* this)
{
	return 0;
}

/*============================================================================
|	Class member functions
*===========================================================================*/


