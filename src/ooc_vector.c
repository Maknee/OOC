#if defined(T) && defined(T_EQUALS)

#include "template.h"

//can't define this as Vector since name collision
#define VECTOR CAT(Vector, T)

#define VectorVFTable CAT(VECTOR, VFTable)
#define vectorVFTable CAT(CAT(vector, T), VFTable)

VectorVFTable vectorVFTable =
{
	.pCompleteObjectLocator = NULL,
	.equals = NULL,
	.toString = NULL,
	.add = NULL,
	.clear = NULL,
	.remove = NULL,
	.contains = NULL,
	.copy = NULL,
	.isEmpty = NULL,
	.size = NULL,
	.set = NULL,
	.get = NULL,
	.push_front = NULL,
	.push_back = NULL,
	.insert = NULL,
	.find = NULL,
	.replace = NULL
};

TypeDescriptor CAT(vectorTypeDescriptor, T) =
{
	.pVFTable = &vectorVFTable,
	.name = STRINGIFY(Vector(T))
};

BaseClassDescriptor CAT(vectorBaseClassArray, T)[] =
{
	ContainerBaseClassDescriptor,
	VectorBaseClassDescriptor(T)
};

ClassHierarchyDescriptor CAT(vectorClassHierarchyDescriptor, T) =
{
	.attributes = CLASS_HIERARCHY_VIRTUAL_INHERITENCE,
	.numBaseClasses = 2,
	.pBaseClassArray = CAT(vectorBaseClassArray, T)
};

CompleteObjectLocator CAT(vectorCompleteObjectLocator, T) =
{
	.signature = 0x48454845,
	.pTypeDescriptor = &CAT(vectorTypeDescriptor, T),
	.pClassHierarchyDescriptor = &CAT(vectorClassHierarchyDescriptor, T)
};

/*============================================================================
|	New Operator
*===========================================================================*/

void* CAT(NewVector, T)()
{
	//allocate a new vector
	void* this = check_calloc(sizeof(struct CAT(_Vector, T)));

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	//allocate vftable
	this_vector->container.object.pVFTable = check_calloc(sizeof(VectorVFTable));

	//call constructor to set up string
	CAT(VectorConstruct, T)(this);

	return this;
}

/*============================================================================
|	Delete Operator
*===========================================================================*/

void CAT(DeleteVector, T)(void* this)
{
	CHECK_NULL_NO_RET(this);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	//call destructor
	CAT(VectorDestruct, T)(this);

	//free vftable
	free(this_vector->container.object.pVFTable);

	//free the string's resources
	free(this);
}

void CAT(VectorConstruct, T)(void* this)
{
	CHECK_NULL_NO_RET(this);

	//call super class's constructor (ObjectConstruct)
	ContainerConstruct(this);

	//Override Object's methods
	//=========================

	//Set the vtable's complete object locator to complete the RTTI circle
	vectorVFTable.pCompleteObjectLocator = &CAT(vectorCompleteObjectLocator, T);

	//Set the equals function
	vectorVFTable.equals = &CAT(VectorEquals, T);

	//Set the toString
	vectorVFTable.toString = &CAT(VectorToString, T);

	//Override Container's methods
	//==========================

	vectorVFTable.add = &CAT(VectorAdd, T);
	vectorVFTable.clear = &CAT(VectorClear, T);
	vectorVFTable.remove = &CAT(VectorRemove, T);
	vectorVFTable.contains = &CAT(VectorContains, T);
	vectorVFTable.copy = &CAT(VectorCopy, T);
	vectorVFTable.isEmpty = &CAT(VectorIsEmpty, T);
	vectorVFTable.size = &CAT(VectorSize, T);
	
	//Initialize class member methods
	//==========================

	vectorVFTable.set = &CAT(VectorSet, T);
	vectorVFTable.get = &CAT(VectorGet, T);
	vectorVFTable.push_front = &CAT(VectorPushFront, T);
	vectorVFTable.push_back = &CAT(VectorPushBack, T);
	vectorVFTable.insert = &CAT(VectorInsert, T);
	vectorVFTable.find = &CAT(VectorFind, T);
	vectorVFTable.replace = &CAT(VectorReplace, T);
	
	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	//Initialize the vtable to a copy of this object's vtable
	memcpy(this_vector->container.object.pVFTable, &vectorVFTable, sizeof(VectorVFTable));

	//Initialize member variables

	//capacity excludes Null terminator
	this_vector->capacity = DEFAULT_VECTOR_CAPACITY;
	this_vector->size = 0;

	//allocate buffer of DEFAULT_VECTOR_CAPACITY elements
	this_vector->data = calloc(1, sizeof(T) * this_vector->capacity);
}

void* CAT(VectorCopyConstruct, T)(void* this)
{
	CHECK_NULL(this, NULL);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	//allocate a new vector
	void* copy = CAT(NewVector, T)();

	//cast to vector
	VECTOR copy_vector = (VECTOR)copy;

	//copy the contents of the string to the copied vector except for vftable (which is contained in Container struct inside the String struct)
	memcpy(&copy_vector->size, &this_vector->size, sizeof(this_vector->size));
	memcpy(&copy_vector->capacity, &this_vector->capacity, sizeof(this_vector->capacity));
	//memcpy(copy_vector->data, this_vector->data, this_vector->capacity);

	//iterate through each item and copy
	for (size_t i = 0; i < this_vector->size; i++)
	{
		*(copy_vector->data + i) = T_COPY(copy_vector->data + i);
	}

	return copy;
}

void CAT(VectorDestruct, T)(void* this)
{
	CHECK_NULL_NO_RET(this);

	//call super destructor
	ContainerDestruct(this);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	//iterate through each item and delete
	for (size_t i = 0; i < this_vector->size; i++)
	{
		T_DELETE(this_vector->data);
	}

	//free dynamically allocated memory
	free(this_vector->data);
}

/*============================================================================
|	Overridden member function definitions
*===========================================================================*/

bool CAT(VectorEquals, T)(void* this, void* other)
{
	CHECK_NULL(this, false);
	CHECK_NULL(other, false);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	//cast to vector
	VECTOR other_vector = (VECTOR)other;

	//compare memory to see if contents are the same
	return (!memcmp(this_vector->data, other_vector->data, this_vector->size));
}

char* CAT(VectorToString, T)(void* this)
{
	CHECK_NULL(this, NULL);

	return ContainerToString(this);
}

static void CAT(VectorRealloc, T)(void* this, size_t new_size)
{
	CHECK_NULL_NO_RET(this);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	if (new_size > this_vector->capacity)
	{
		//make capacity twice the new length and realloc
		this_vector->capacity = new_size * 2;
		this_vector->data = realloc(this_vector->data, sizeof(T) * this_vector->capacity);
	}
}

bool CAT(VectorAdd, T)(void* this, T item)
{
	CHECK_NULL(this, false);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	//create new size variable
	size_t new_size = this_vector->size + 1;

	//realloc vector if necessary
	CAT(VectorRealloc, T)(this, new_size);

	//append the new vector's data to the end of the old vector's data
	T* end_of_vector_data = this_vector->data + sizeof(T) * this_vector->size;
	memcpy(end_of_vector_data, &item, sizeof(T));

	//update the size
	this_vector->size = new_size;

	return true;
}

void CAT(VectorClear, T)(void* this)
{
	CHECK_NULL_NO_RET(this);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	//iterate through each item and delete
	for (size_t i = 0; i < this_vector->size; i++)
	{
		T_DELETE(this_vector->data);
	}

	//NULL out vector's data
	memset(this_vector->data, 0, this_vector->capacity);

	//update the size
	this_vector->size = 0;
}

bool CAT(VectorRemove, T)(void* this, T item)
{
	CHECK_NULL(this, false);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;
	
	//iterate through each 
	for (size_t i = 0; i < sizeof(T) * this_vector->size; i += sizeof(T))
	{
		//get pointer to the data
		T* this_t = this_vector->data + i;

		//check if the values are the same
		if (T_EQUALS(*this_t, item))
		{
			T* end_of_vector = this_vector->data + (sizeof(T) * this_vector->size);

			//delete the item
			T_DELETE(this_t);

			//remove the current item and shift everything to the left
			memmove(this_t, this_t + 1, (size_t)(end_of_vector - (this_t + 1)));

			//zero out the remaining one
			memset(end_of_vector - sizeof(T), 0, sizeof(T));

			//update size
			this_vector->size--;
		}
	}
	return true;
}

bool CAT(VectorContains, T)(void* this, T item)
{
	CHECK_NULL(this, false);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	//iterate through each 
	for (size_t i = 0; i < sizeof(T) * this_vector->size; i += sizeof(T))
	{
		T* this_t = this_vector->data + i;

		//check if the values are the same
		if (T_EQUALS(*this_t, item))
		{
			return true;
		}
	}

	return false;
}

void* CAT(VectorCopy, T)(void* this)
{
	CHECK_NULL(this, NULL);

	return CAT(VectorCopyConstruct, T)(this);
}

bool CAT(VectorIsEmpty, T)(void* this)
{
	CHECK_NULL(this, false);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	return this_vector->size > 0;
}

size_t CAT(VectorSize, T)(void* this)
{
	CHECK_NULL(this, false);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	return this_vector->size;
}

bool CAT(VectorSet, T)(void* this, const T* item, size_t num_elements)
{
	CHECK_NULL(this, false);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	//get the data
	T* this_vector_data = this_vector->data;

	//zero out the data
	memset(this_vector_data, 0, this_vector->capacity);

	//make size zero
	this_vector->size = 0;

	//loop until null
	for (size_t i = 0; i < num_elements; i++)
	{
		//get pointer to element
		T* item_ptr = (T*)(item + i);

		//copy the element 
		memcpy(this_vector_data, item_ptr, sizeof(T));

		//create new size variable
		size_t new_size = this_vector->size + 1;

		//realloc vector if necessary
		CAT(VectorRealloc, T)(this, new_size);

		//go to next element in vector
		this_vector_data++;

		//update length
		this_vector->size++;
	}

	return true;
}

T CAT(VectorGet, T)(void* this, int index, int* error_code)
{
	CHECK_NULL(this, false);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	//check for out of bounds
	if (index == NPOS || index < 0 || index > (int)this_vector->size)
	{
		//set error code
		*error_code = 1;
		
		return (T) { 0 };
	}

	//get the data
	T* this_vector_data = this_vector->data;

	//set error code
	*error_code = 0;

	//return data at index
	return *(this_vector_data + index);
}

bool CAT(VectorPushFront, T)(void* this, T item)
{
	CHECK_NULL(this, false);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	//create new size variable
	size_t new_size = this_vector->size + 1;

	//realloc vector if necessary
	CAT(VectorRealloc, T)(this, new_size);

	//get the beginning of the vector
	T* begin_of_vector = this_vector->data;

	//shift everything to the left by one element
	memmove(begin_of_vector + 1, begin_of_vector, this_vector->size);

	//insert element into beginning
	memcpy(begin_of_vector, &item, sizeof(T));

	//update size
	this_vector->size++;
	
	return true;
}

bool CAT(VectorPushBack, T)(void* this, T item)
{
	CHECK_NULL(this, false);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	//create new size variable
	size_t new_size = this_vector->size + 1;

	//realloc vector if necessary
	CAT(VectorRealloc, T)(this, new_size);

	//get the end of the vector
	T* end_of_vector = this_vector->data + (sizeof(T) * this_vector->size);

	//insert element into end
	memcpy(end_of_vector, &item, sizeof(T));

	//update size
	this_vector->size++;

	return true;
}

bool CAT(VectorInsert, T)(void* this, T item, int index)
{
	CHECK_NULL(this, false);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	//create new size variable
	size_t new_size = this_vector->size + 1;

	//realloc vector if necessary
	CAT(VectorRealloc, T)(this, new_size);

	//get the insertion index of the vector
	T* index_of_vector = this_vector->data;

	//get the end of the vector
	T* end_of_vector = this_vector->data;

	//shift everything to the left by one element
	memmove(index_of_vector + 1, index_of_vector, (size_t)(end_of_vector - index_of_vector));

	//insert element into beginning
	memcpy(index_of_vector, &item, sizeof(T));

	//update size
	this_vector->size++;

	return true;
}

int CAT(VectorFind, T) (void* this, T item)
{
	CHECK_NULL(this, false);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	//check for out of bounds
	for (size_t i = 0; i < this_vector->size; i++)
	{
		//get pointer to the data
		T* this_t = this_vector->data + i;

		//check for equality
		if (T_EQUALS(*this_t, item))
		{
			return (int)i;
		}
	}

	//return NPOS if nothing was found
	return NPOS;
}

bool CAT(VectorReplace, T)(void* this, T to_replace, T replacement)
{
	CHECK_NULL(this, false);

	//cast to vector
	VECTOR this_vector = (VECTOR)this;

	//check if any were replaced
	bool replaced = false;

	//check for out of bounds
	for (size_t i = 0; i < this_vector->size; i++)
	{
		//get pointer to the data
		T* this_t = this_vector->data + i;

		//check for equality
		if (T_EQUALS(*this_t, to_replace))
		{
			replaced = true;

			//delete the item
			T_DELETE(this_t);

			//replace the element
			memcpy(this_t, &replacement, sizeof(T));
		}
	}

	return replaced;
}

/*============================================================================
|	Class member definitions
*===========================================================================*/

#undef VECTOR

#undef VectorVFTable
#undef vectorVFTable

#endif
