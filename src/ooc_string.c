/**
* @file container.c
* @brief Object source file
*
* Implementation of @ref container.h
*
* @author Henry Zhu (Maknee)
* @date	8/2/2017
*/

#include "ooc_string.h"

StringVFTable stringVFTable =
{
	.containerVFTable = NULL_CONTAINER_VFTABLE,
	.c_str = NULL,
	.append = NULL,
	.find = NULL,
	.substring = NULL
};

TypeDescriptor stringTypeDescriptor =
{
	.pVFTable = &stringVFTable,
	.name = "String"
};

BaseClassDescriptor stringBaseClassArray[] =
{
	ContainerBaseClassDescriptor,
	StringBaseClassDescriptor
};

ClassHierarchyDescriptor stringClassHierarchyDescriptor =
{
	.attributes = CLASS_HIERARCHY_VIRTUAL_INHERITENCE,
	.numBaseClasses = 2,
	.pBaseClassArray = stringBaseClassArray
};

CompleteObjectLocator stringCompleteObjectLocator =
{
	.signature = 0x48454845,
	.pTypeDescriptor = &stringTypeDescriptor,
	.pClassHierarchyDescriptor = &stringClassHierarchyDescriptor
};

/*============================================================================
|	Static Helper member definitions
*===========================================================================*/

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

static void StringStrncat(String* this, String* other)
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

/*============================================================================
|	New Operator
*===========================================================================*/

void* NewString()
{
	//allocate a new string
	void* string = calloc(1, sizeof(String));

	//call constructor to set up string
	StringConstruct(string);
	return string;
}

/*============================================================================
|	Delete Operator
*===========================================================================*/

void DeleteString(void* this)
{
	//call destructor
	StringDestruct(this);

	//free the string's resources
	free(this);

	//NULL the pointer, so we don't have use after free vulns
	this = NULL;
}

/*============================================================================
|	Constructor
*===========================================================================*/

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

	//Initialize the vtable to a copy of this object's vtable
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

void* StringCopyConstruct(void* this)
{
	//allocate a new string
	void* copy_string = calloc(1, sizeof(String));

	//copy the contents of the string to the copied string
	memcpy(copy_string, this, sizeof(String));

	//check if the string was dynamically allocated
	if (CheckIfStringIsAllocated(this))
	{
		//copy the contents of the data into another area of the heap
		((String*)copy_string)->data.pBuf = calloc(1, ((String*)this)->capacity);
		memcpy(((String*)copy_string)->data.pBuf, ((String*)this)->data.pBuf, ((String*)this)->length);
	}
	//no need to consider the other case because we memcpy'd the entire struct above!

	return copy_string;
}

/*============================================================================
|	Destructor
*===========================================================================*/

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

bool StringEquals(void* this, void* other)
{
	return (!strcmp(StringToString(this), StringToString(other))) ? true : false;
}

char* StringToString(void* this)
{
	return ContainerToString(this);
}

bool StringAdd(void* this, void* item)
{
	String* this_string = (String*)this;
	String* other_string = (String*)item;

	//check if the new string can be appended
	size_t new_length = this_string->length + other_string->length;
	if (this_string->capacity < new_length)
	{
		//check whether or not the string is using an array or a dynamic pointer
		if (CheckIfStringIsAllocated(this))
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

				//keep the capacity at the limit
				this_string->capacity = DEFAULT_STRING_LENGTH;
			}
		}

		//update the length
		this_string->length = new_length;
	}
	return true;
}

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
	String* this_string = (String*)this;
	String* other_string = (String*)item;

	//find the substring's index in the current string
	size_t start = StringFind(this_string, other_string);

	//check if the substring exists
	if (start != NPOS)
	{
		//update the length
		size_t new_length = this_string->length - other_string->length;

		//check whether or not the string is using an array or a dynamic pointer
		if (CheckIfStringIsAllocated(this_string))
		{
			//fill the data after the substring into the data of the substring
			memmove(this_string->data.pBuf + start,
				this_string->data.pBuf + start + new_length + 1, this_string->length - start - new_length);
		}
		else
		{
			//fill the data after the substring into the data of the substring
			memmove(this_string->data.buf + start,
				this_string->data.buf + start + new_length + 1, this_string->length - start - new_length);
		}

		//update the length
		this_string->length = new_length;
		return true;
	}
	return false;
}

bool StringContains(void* this, void* item)
{
	return StringFind(this, item);
}

bool StringIsEmpty(void* this)
{
	return ((String*)this)->length == 0;
}

size_t StringSize(void* this)
{
	return ((String*)this)->length;
}

/*============================================================================
|	Class member functions
*===========================================================================*/

char* StringC_Str(void* this)
{
	String* this_string = (String*)this;
	if (CheckIfStringIsAllocated(this))
	{
		return this_string->data.pBuf;
	}
	else
	{
		return this_string->data.buf;
	}
}

bool StringAppend(void* this, char* item)
{
	String* this_string = (String*)this;
	size_t other_string_length = strlen(item);
	//check if the new string can be appended
	size_t new_length = this_string->length + other_string_length;
	if (this_string->capacity < new_length)
	{
		//check whether or not the string is using an array or a dynamic pointer
		if (CheckIfStringIsAllocated(this))
		{
			//this string is dynamically allocated, so realloc with twice the length
			this_string->data.pBuf = realloc(this_string->data.pBuf, new_length * 2);

			//copy the other string's data
			strncat(this_string->data.pBuf, item, strlen(item));
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
				strncat(this_string->data.pBuf, item, strlen(item));
			}
			else
			{
				//copy the other string's data
				strncat(this_string->data.buf, item, strlen(item));

				//keep the capacity at the limit
				this_string->capacity = DEFAULT_STRING_LENGTH;
			}
		}

		//update the length
		this_string->length = new_length;
	}
	return true;
}

int StringFind(void* this, void* item)
{
	//hey c has a function called strstr :)
	String* this_string = (String*)this;
	String* substring = (String*)item;

	// pointer to the first element of the substring in the string
	// if the substring was found
	char* pFound = NULL;

	if (CheckIfStringIsAllocated(this))
	{
		if (CheckIfStringIsAllocated(item))
		{
			pFound = strstr(this_string->data.pBuf, substring->data.pBuf);
		}
		else
		{
			pFound = strstr(this_string->data.pBuf, substring->data.buf);
		}
	}
	else
	{
		if (CheckIfStringIsAllocated(item))
		{
			pFound = strstr(this_string->data.buf, substring->data.pBuf);
		}
		else
		{
			pFound = strstr(this_string->data.buf, substring->data.buf);
		}
	}

	//if the substring wasn't found, return NPOS
	if (pFound == NULL)
	{
		return NPOS;
	}

	//calculate the index
	if (CheckIfStringIsAllocated(this))
	{
		return pFound - this_string->data.pBuf;
	}
	else
	{
		return pFound - this_string->data.buf;
	}
}

void* StringSubstring(void* this, size_t start, size_t end)
{
	//check if user made mistakes...
	if (start > end)
	{
		return NULL;
	}

	String* this_string = (String*)this;

	//check if indices are in bounds
	if (start > this_string->length || end > this_string->length)
	{
		return NULL;
	}

	//allocate a copy string using the copy constructor
	String* copy_string = StringCopyConstruct(this);

	//update the length of copy_string
	copy_string->length = end - start + 1;

	if (CheckIfStringIsAllocated(copy_string))
	{
		//use memmove to copy the data over because overlapping regions
		memmove(copy_string->data.pBuf, copy_string->data.pBuf + start, copy_string->length);

		//now zero out the rest
		memset(copy_string->data.pBuf + copy_string->length, 0, end - copy_string->length);
	}
	return copy_string;
}


