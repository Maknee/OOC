#pragma once

#include "container.h"
/*============================================================================
|       Author:  Henry Zhu
+-----------------------------------------------------------------------------
|
|  Description:  Abstract container class of container classes (ex: string, vector, map...)
|				 All derived classes must call donstructor and destructor
|				 All derived classes must override every function in vftable
|
*===========================================================================*/

/*============================================================================
|   Defines
*===========================================================================*/

//15 characters + 1 null byte
#define DEFAULT_STRING_LENGTH 15 + 1

#define NULL_STRING_VFTABLE                                 \
		{                                                   \
			.containerVFTable =                                               \
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

typedef struct _String String;

typedef struct _StringVFTable
{
	ContainerVFTable containerVFTable;
	char* (*c_str)(void* this);
	char* (*append)(void* this, char* value);
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

//Cannot make this const since there is a circluar reference with RTTI structs

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
|           | attributes = 0 (NONE)                     |
|           | numBaseClasses = 1 (Ccontainer class)     |
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

static TypeDescriptor stringTypeDescriptor =
{
	.pVFTable = &stringVFTable,
	.name = "String"
};

#define StringBaseClassDescriptor   					\
		{												\
			.numContainedClasses = 2,					\
			.pTypeDescriptor = &stringTypeDescriptor    \
		}												\

static BaseClassDescriptor stringBaseClassArray[] =
{
	ContainerBaseClassDescriptor,
	StringBaseClassDescriptor
};

static ClassHierarchyDescriptor stringClassHierarchyDescriptor =
{
	.attributes = 0,
	.numBaseClasses = 1,
	.pBaseClassArray = stringBaseClassArray
};

static CompleteObjectLocator stringCompleteObjectLocator =
{
	.signature = 0x48454845,
	.pTypeDescriptor = &stringTypeDescriptor,
	.pClassHierarchyDescriptor = &stringClassHierarchyDescriptor
};

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
	return StringToString(this);
}

//Helper functions for StringAdd
static bool CheckIfStringIsAllocated(String* this)
{
	return this->capacity >= DEFAULT_STRING_LENGTH;
}

void StringStrncat(String* this, String* other)
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

		this_string->length = new_length;
	}
	return true;
}

void StringClear(void* this)
{

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


