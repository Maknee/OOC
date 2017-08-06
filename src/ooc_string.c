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
	NULL_CONTAINER_VFTABLE,
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
	CHECK_NULL(this, false);
	return this->capacity > DEFAULT_STRING_LENGTH;
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
	CHECK_NULL_NO_RET(this);
	CHECK_NULL_NO_RET(other);
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
		//this line will never execute in StringAdd
		/*
		if (CheckIfStringIsAllocated(other))
		{
			strncat(this->data.buf, other->data.pBuf, other->length);
		}
		else
		*/
		if (!CheckIfStringIsAllocated(other))
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
	void* string = check_calloc(sizeof(String));

	//allocate vftable
	((String*)string)->container.object.pVFTable = check_calloc(sizeof(StringVFTable));

	//call constructor to set up string
	StringConstruct(string);
	return string;
}

/*============================================================================
|	Delete Operator
*===========================================================================*/

void DeleteString(void* this)
{
	CHECK_NULL_NO_RET(this);
	
	//call destructor
	StringDestruct(this);

	//free vftable
	free(((String*)this)->container.object.pVFTable);

	//free the string's resources
	free(this);

	//NULL the pointer, so we don't have use after free vulns
	//... forgot that this is a copy of a pointer on the stack, 
	//it doesn't actually modify the actual pointer.
	//therefore freeing is enforced in the macro
	//this = NULL;
}

/*============================================================================
|	Constructor
*===========================================================================*/

void StringConstruct(void* this)
{
	CHECK_NULL_NO_RET(this);

	//call super class's constructor (ObjectConstruct)
	ContainerConstruct(this);

	//Override Object's methods
	//=========================

	//Set the vtable's complete object locator to complete the RTTI circle
	stringVFTable.pCompleteObjectLocator = &stringCompleteObjectLocator;

	//Set the equals function
	stringVFTable.equals = &StringEquals;

	//Set the toString
	stringVFTable.toString = &StringToString;

	//Override Container's methods
	//==========================

	stringVFTable.add = &StringAdd;
	stringVFTable.clear = &StringClear;
	stringVFTable.remove = &StringRemove;
	stringVFTable.contains = &StringContains;
	stringVFTable.copy = &StringCopy;
	stringVFTable.isEmpty = &StringIsEmpty;
	stringVFTable.size = &StringSize;

	//Initialize class member methods
	//==========================

	stringVFTable.set = &StringSet;
	stringVFTable.c_str = &StringC_Str;
	stringVFTable.append = &StringAppend;
	stringVFTable.insert = &StringInsert;
	stringVFTable.replace = &StringReplace;
	stringVFTable.find = &StringFind;
	stringVFTable.substring = &StringSubstring;

	//Initialize the vtable to a copy of this object's vtable
	memcpy(((String*)this)->container.object.pVFTable, &stringVFTable, sizeof(StringVFTable));

	//Initialize member variables

	//capacity excludes Null terminator
	((String*)this)->capacity = DEFAULT_STRING_LENGTH;
	((String*)this)->length = 0;

	//Null out buffer
	memset(((String*)this)->data.buf, 0, sizeof(((String*)this)->data.buf));
}

/*============================================================================
|	Copy Constructor
*===========================================================================*/

void* StringCopyConstruct(void* this)
{
	CHECK_NULL(this, NULL);
	
	//allocate a new string
	void* copy = NewString();

	//cast to string
	String* this_string = (String*)this;
	String* copy_string = (String*)copy;

	//copy the contents of the string to the copied string except for vftable (which is contained in Container struct inside the String struct)
	memcpy(&copy_string->length, &this_string->length, sizeof(this_string->length));
	memcpy(&copy_string->capacity, &this_string->capacity, sizeof(this_string->capacity));
	memcpy(copy_string->data.buf, this_string->data.buf, sizeof(this_string->data.buf));

	//check if the string was dynamically allocated
	if (CheckIfStringIsAllocated(this))
	{
		//copy the contents of the data into another area of the heap
		copy_string->data.pBuf = check_calloc(this_string->capacity);
		memcpy(copy_string->data.pBuf, this_string->data.pBuf, this_string->length + 1);
	}
	//no need to consider the other case because we memcpy'd the entire struct above!

	return copy;
}

/*============================================================================
|	Destructor
*===========================================================================*/

void StringDestruct(void* this)
{
	CHECK_NULL_NO_RET(this);

	ContainerDestruct(this);

	//free dynamically allocated memory only if the size of the string
	//is greater than the default string length (size of char array buffer)
	if (((String*)this)->capacity > DEFAULT_STRING_LENGTH)
	{
		free(((String*)this)->data.pBuf);
	}
}

/*============================================================================
|	Overridden member functions
*===========================================================================*/

bool StringEquals(void* this, void* other)
{
	CHECK_NULL(this, false);
	CHECK_NULL(other, false);

	return (!strcmp(StringC_Str(this), StringC_Str(other)) ? true : false);
}

char* StringToString(void* this)
{
	CHECK_NULL(this, NULL);

	return ContainerToString(this);
}

bool StringSet(void* this, const char* item)
{
	CHECK_NULL(this, false);
	CHECK_NULL(item, false);

	String* this_string = (String*)this;

	//check if the new string can be appended
	size_t new_length = strlen(item);
	
	//check whether or not the string is using an array or a dynamic pointer
	if (CheckIfStringIsAllocated(this))
	{
		if (this_string->capacity < new_length)
		{
			//this string capacity should be increased
			this_string->capacity = new_length * 2;

			//this string is dynamically allocated, so realloc with twice the length
			this_string->data.pBuf = realloc(this_string->data.pBuf, this_string->capacity);
		}

		//copy the other string's data
		memcpy(this_string->data.pBuf, item, new_length);
		
		//zero out the rest of the string's data
		memset(this_string->data.pBuf + new_length, 0, this_string->capacity - new_length);
	}
	else
	{
		//this string might need to dynamically allocated. 
		if (new_length > DEFAULT_STRING_LENGTH)
		{
			//this string should already/become dynamically allocated now
			this_string->capacity = new_length * 2;

			//allocate a tmp to make sure that pBuf pointer doesn't
			//overwrite buf's data. We need to copy buf's data and then set 
			//pBuf to point to a copy of buf's data
			char* tmp = check_calloc(this_string->capacity);

			//copy the other string's data
			memcpy(tmp, item, new_length);
			
			//zero out the rest of the string's data
			memset(tmp + new_length, 0, this_string->capacity - new_length);

			//set the pBuf to tmp
			this_string->data.pBuf = tmp;
		}
		else
		{
			//keep the capacity at the limit
			this_string->capacity = DEFAULT_STRING_LENGTH;

			//copy the other string's data
			memcpy(this_string->data.buf, item, new_length);

			//zero out the rest of the string's data
			memset(this_string->data.buf + new_length, 0, this_string->capacity - new_length);
		}
	}

	//update the length
	this_string->length = new_length;

	return true;
}

bool StringAdd(void* this, void* item)
{
	CHECK_NULL(this, false);
	CHECK_NULL(item, false);

	String* this_string = (String*)this;
	String* other_string = (String*)item;

	//check if the new string can be appended
	size_t new_length = this_string->length + other_string->length;

	//check whether or not the string is using an array or a dynamic pointer
	if (CheckIfStringIsAllocated(this))
	{
		if (this_string->capacity < new_length)
		{
			//this string capacity should be increased
			this_string->capacity = new_length * 2;

			//this string is dynamically allocated, so realloc with twice the length
			this_string->data.pBuf = realloc(this_string->data.pBuf, this_string->capacity);
		}

		//copy the other string's data
		StringStrncat(this_string, other_string);
	}
	else
	{
		//this string might need to dynamically allocated. 
		if (new_length > DEFAULT_STRING_LENGTH)
		{
			//this string should already/become dynamically allocated now
			this_string->capacity = new_length * 2;

			//allocate a tmp to make sure that pBuf pointer doesn't
			//overwrite buf's data. We need to copy buf's data and then set 
			//pBuf to point to a copy of buf's data
			char* tmp = check_calloc(this_string->capacity);

			//copy this string's data
			memcpy(tmp, this_string->data.buf, this_string->length);

			//zero out the rest of the string's data
			memset(tmp + new_length, 0, this_string->capacity - new_length);

			//set pbuf to the tmp
			this_string->data.pBuf = tmp;

			//copy the other string's data
			StringStrncat(this_string, other_string);
		}
		else
		{
			//keep the capacity at the limit
			this_string->capacity = DEFAULT_STRING_LENGTH;

			//copy the other string's data
			StringStrncat(this_string, other_string);
		}
	}

	//update the length
	this_string->length = new_length;
	
	return true;
}

void StringClear(void* this)
{
	CHECK_NULL_NO_RET(this);

	String* this_string = (String*)this;

	//check if the string was dynamically allocated
	if (CheckIfStringIsAllocated(this))
	{
		//deallocate the dynamically allocated data
		free(this_string->data.pBuf);
	}
	
	//update the length and capacity
	this_string->length = 0;
	this_string->capacity = DEFAULT_STRING_LENGTH;

	//clear the data out
	memset(this_string->data.buf, 0, sizeof(this_string->data.buf));
}

bool StringRemove(void* this, void* item)
{
	CHECK_NULL(this, false);
	CHECK_NULL(item, false);

	String* this_string = (String*)this;
	String* other_string = (String*)item;

	//find the substring's index in the current string
	int found = StringFind(this_string, other_string);

	//check if the substring exists
	if (found != NPOS)
	{
		//cast found to size_t from int, now we know that the value isn't negative
		size_t start = (size_t)found;

		//update the length
		size_t new_length = this_string->length - other_string->length;

		//check whether or not the string is using an array or a dynamic pointer
		if (CheckIfStringIsAllocated(this_string))
		{
			//fill the data after the substring into the data of the substring
			memmove(this_string->data.pBuf + start,
				this_string->data.pBuf + this_string->length - new_length, new_length);
			//replace the rest with nulls
			memset(this_string->data.pBuf + new_length, 0, this_string->length - new_length);
		}
		else
		{
			//fill the data after the substring into the data of the substring
			memmove(this_string->data.buf + start,
				this_string->data.buf + this_string->length - new_length, new_length);
			//replace the rest with nulls
			memset(this_string->data.buf + new_length, 0, this_string->length - new_length);
		}

		//update the length
		this_string->length = new_length;
		return true;
	}
	return false;
}

bool StringContains(void* this, void* item)
{
	CHECK_NULL(this, false);
	CHECK_NULL(item, false);

	return (StringFind(this, item) != NPOS) ? true : false;
}

void* StringCopy(void* this)
{
	CHECK_NULL(this, NULL);

	return StringCopyConstruct(this);
}

bool StringIsEmpty(void* this)
{
	CHECK_NULL(this, false);
	
	return ((String*)this)->length == 0;
}

size_t StringSize(void* this)
{
	CHECK_NULL(this, false);
	
	return ((String*)this)->length + 1;
}

/*============================================================================
|	Class member functions
*===========================================================================*/

char* StringC_Str(void* this)
{
	CHECK_NULL(this, NULL);

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

bool StringAppend(void* this, const char* item)
{
	CHECK_NULL(this, false);
	CHECK_NULL(item, false);

	String* this_string = (String*)this;
	size_t other_string_length = strlen(item);

	//check if the new string can be appended
	size_t new_length = this_string->length + other_string_length;
	
	//check whether or not the string is using an array or a dynamic pointer
	if (CheckIfStringIsAllocated(this))
	{
		if (this_string->capacity < new_length)
		{
			//this string capacity should be increased
			this_string->capacity = new_length * 2;

			//this string is dynamically allocated, so realloc with twice the length
			this_string->data.pBuf = realloc(this_string->data.pBuf, this_string->capacity);
		}

		//copy the other string's data
		strncat(this_string->data.pBuf, item, new_length);
	}
	else
	{
		//this string might need to dynamically allocated. 
		if (new_length > DEFAULT_STRING_LENGTH)
		{
			//this string should already/become dynamically allocated now
			this_string->capacity = new_length * 2;

			//allocate a tmp to make sure that pBuf pointer doesn't
			//overwrite buf's data. We need to copy buf's data and then set 
			//pBuf to point to a copy of buf's data
			char* tmp = check_calloc(this_string->capacity);

			//copy this string's data
			memcpy(tmp, this_string->data.buf, this_string->length);
			
			//zero out the rest of the string's data
			memset(tmp + new_length, 0, this_string->capacity - new_length);

			//copy the other string's data
			strncat(tmp, item, new_length);

			//set the pBuf to tmp
			this_string->data.pBuf = tmp;
		}
		else
		{
			//keep the capacity at the limit
			this_string->capacity = DEFAULT_STRING_LENGTH;

			//copy the other string's data
			strncat(this_string->data.buf, item, new_length);
		}
	}

	//update the length
	this_string->length = new_length;

	return true;
}

bool StringInsert(void* this, void* item, int index)
{
	CHECK_NULL(this, false);

	//check if user made mistakes...
	if (index < 0)
	{
		return false;
	}

	String* this_string = (String*)this;
	String* other_string = (String*)item;

	//check if indices are in bounds
	if (index > (int)this_string->length)
	{
		return false;
	}

	size_t index_t = (size_t)index;

	//get the new length of the string
	size_t new_length = this_string->length + other_string->length;

	//check whether or not the string is using an array or a dynamic pointer
	if (CheckIfStringIsAllocated(this))
	{
		if (this_string->capacity < new_length)
		{
			//this string capacity should be increased
			this_string->capacity = new_length * 2;

			//this string is dynamically allocated, so realloc with twice the length
			this_string->data.pBuf = realloc(this_string->data.pBuf, this_string->capacity);
		}
		
		//shift the right side of the string, so that there is enough space
		//for the inserted string to be placed in
		memmove(this_string->data.pBuf + index_t + other_string->length, this_string->data.pBuf + index_t, other_string->length);

		//insert the other string's data into the index
		if (CheckIfStringIsAllocated(item))
		{
			memcpy(this_string->data.pBuf + index_t, other_string->data.pBuf, other_string->length);
		}
		else
		{
			memcpy(this_string->data.pBuf + index_t, other_string->data.buf, other_string->length);
		}
	}
	else
	{
		//this string might need to dynamically allocated. 
		if (new_length > DEFAULT_STRING_LENGTH)
		{
			//this string should already/become dynamically allocated now
			this_string->capacity = new_length * 2;

			//allocate a tmp to make sure that pBuf pointer doesn't
			//overwrite buf's data. We need to copy buf's data and then set 
			//pBuf to point to a copy of buf's data
			char* tmp = check_calloc(this_string->capacity);

			//copy this string's data
			memcpy(tmp, this_string->data.buf, this_string->length);

			//zero out the rest of the string's data
			memset(tmp + new_length, 0, this_string->capacity - new_length);

			//set pbuf to the tmp
			this_string->data.pBuf = tmp;

			//shift the right side of the string, so that there is enough space
			//for the inserted string to be placed in
			memmove(this_string->data.pBuf + index_t + other_string->length, this_string->data.pBuf + index_t, other_string->length);

			//insert the other string's data into the index
			if (CheckIfStringIsAllocated(item))
			{
				memcpy(this_string->data.pBuf + index_t, other_string->data.pBuf, other_string->length);
			}
			else
			{
				memcpy(this_string->data.pBuf + index_t, other_string->data.buf, other_string->length);
			}
		}
		else
		{
			//keep the capacity at the limit
			this_string->capacity = DEFAULT_STRING_LENGTH;

			//shift the right side of the string, so that there is enough space
			//for the inserted string to be placed in
			memmove(this_string->data.buf + index_t + other_string->length, this_string->data.buf + index_t, other_string->length);

			//insert the other string's data into the index
			if (CheckIfStringIsAllocated(item))
			{
				memcpy(this_string->data.buf + index_t, other_string->data.pBuf, other_string->length);
			}
			else
			{
				memcpy(this_string->data.buf + index_t, other_string->data.buf, other_string->length);
			}
		}
	}

	//update the length
	this_string->length = new_length;

	return true;
}

bool StringReplace(void* this, void* item, void* replacement)
{
	return true;
}

int StringFind(void* this, void* item)
{
	CHECK_NULL(this, -1);
	CHECK_NULL(item, -1);

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
		return (int)(pFound - this_string->data.pBuf);
	}
	else
	{
		return (int)(pFound - this_string->data.buf);
	}
}

void* StringSubstring(void* this, int start, int end)
{
	CHECK_NULL(this, NULL);
	
	//check if user made mistakes...
	if (start > end || start < 0 || end < 0)
	{
		return NULL;
	}

	String* this_string = (String*)this;

	//check if indices are in bounds
	if (start > (int)this_string->length || end > (int)this_string->length)
	{
		return NULL;
	}
	
	size_t start_t = (size_t)start;
	size_t end_t = (size_t)end;

	//allocate a copy string using the copy constructor
	//the copied string will be allocated like the parent string
	String* copy_string = StringCopyConstruct(this);

	//update the length of copy_string
	copy_string->length = end_t - start_t;

	if (CheckIfStringIsAllocated(this))
	{
		//use memmove to copy the data over because overlapping regions
		memmove(copy_string->data.pBuf, copy_string->data.pBuf + start_t, copy_string->length);

		//now zero out the rest
		memset(copy_string->data.pBuf + copy_string->length, 0, end_t - copy_string->length);
	}
	else
	{
		//use memmove to copy the data over because overlapping regions
		memmove(copy_string->data.buf, copy_string->data.buf + start_t, copy_string->length);

		//now zero out the rest
		memset(copy_string->data.buf + copy_string->length, 0, end_t - copy_string->length);
	}
	return copy_string;
}


