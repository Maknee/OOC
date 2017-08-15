/**
* @file ooc_vector.h
* @brief Vector class header
*
* Vector class implementation\n
* Unfortunately, documentation won't generate from this... :( Look at source code for info.
*			
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

#ifdef T

#include "container.h"
#include "template.h"

/*============================================================================
|   Defines
*===========================================================================*/

/**********************************************************************************************//**
 * @def		DEFAULT_VECTOR_CAPACITY
 *
 * @brief	A macro that defines the default capacity of a vector
 * @see		_Vector
 * 			
 * @def		NULL_VECTOR_VFTABLE
 * @brief	A macro that defines a null vector vftable template for classes
 * 			that inherit from the vector class
 **************************************************************************************************/

#define DEFAULT_VECTOR_CAPACITY 16

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
			.set = NULL,                                        \
			.get = NULL,                                        \
			.push_front = NULL,                                 \
			.push_back = NULL.                                  \
			.insert = NULL,                                     \
			.find = NULL                                        \
			.replace = NULL                                     \
		}                                                       \

/*============================================================================
|   Object virtual function table definition
*===========================================================================*/

/**********************************************************************************************//**
 * @def	DEFINE_VECTOR_VFTABLE
 *
 * @brief	Macro contain templated vftable of the vector class
 * 			Vector Methods\n
 * 			Overridden Methods\n
 * 			@ref Object Methods\n
 *			equals\n
 *			toString\n
 *			@ref Container Methods\n
 *			add\n
 *			clear\n
 *			remove\n
 *			contains\n
 *			copy\n
 *			isEmpty\n
 *			size\n
 *			Class member methods\n
 *			set\n
 *			get\n
 *			push_front\n
 *			push_back\n
 *			replace\n
 *			find\n
 *			replace\n
 **************************************************************************************************/

//have to use macro to define vftable because macros can't be
//used in struct declaration

//also super class has to templated... not exactly what I call
//perfect inheritence
#define DEFINE_VECTOR_VFTABLE                                  \
	typedef struct CAT(CAT(_Vector, T), VFTable)               \
	{                                                          \
		CompleteObjectLocator* pCompleteObjectLocator;         \
		bool(*equals)(void* this, void* other);                \
		char* (*toString)(void* this);                         \
		                                                       \
		bool (*add)(void* this, T item);                       \
		void(*clear)(void* this);                              \
		bool(*remove)(void* this, T item);                     \
		bool(*contains)(void* this, T item);                   \
		void* (*copy)(void* this);                             \
		bool(*isEmpty)(void* this);                            \
		size_t(*size)(void* this);                             \
		                                                       \
		bool(*set)(void* this, const T* item, size_t num_elements); \
		T(*get)(void* this, int index, int* error_code);       \
		bool(*move_push_front)(void* this, T item);            \
		bool(*push_front)(void* this, T item);                 \
		bool(*move_push_back)(void* this, T item);             \
		bool(*push_back)(void* this, T item);                  \
		bool(*move_insert)(void* this, T item, int index);     \
		bool(*insert)(void* this, T item, int index);          \
		int(*find) (void* this, T item);                       \
		bool(*replace)(void* this, T to_replace, T replacement); \
	} CAT(CAT(Vector, T), VFTable);                            \

DEFINE_VECTOR_VFTABLE

/*============================================================================
|	Special class member function definitions
*===========================================================================*/

/*============================================================================
|	New Operator
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void* CAT(NewVector, T)()
 * @brief	Vector's new operator
 * 			
 *			Returns an allocated new vector
 * 			
 * @return	An allocated vector object or null if none could be allocated
 **************************************************************************************************/

void* CAT(NewVector, T)();

/*============================================================================
|	Delete Operator
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(DeleteVector, T)(void* this);
 *
 * @brief	Deletes and frees a vector's resources
 *
 * @param	[in] this
 * 			Object to be deleted
 * @return	Nothing
 **************************************************************************************************/

void CAT(DeleteVector, T)(void* this);

/*============================================================================
|	Constructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(VectorConstruct, T)(void* this);
 * @brief	Vector's constructor
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

void CAT(VectorConstruct, T)(void* this);

/*============================================================================
|	Copy Constructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void* CAT(VectorCopyConstruct, T)(void* this);
 * @brief	Vector's copy constructor
 * 			
 *			Returns a copy of the vector
 *
 * @param	[in] this
 * 			Vector to be used for copying
 * 			
 * @return	The copied vector
 * @note	Derived classes may implement a copy constructor, 
 * 			but it is not necessary
 * @note    This is a <b>DEEP</b> copy, which will dynamically allocate memory
 * 			for the vector and copy every element
 **************************************************************************************************/

void* CAT(VectorCopyConstruct, T)(void* this);

/*============================================================================
|	Destructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(VectorDestruct, T)(void* this);
 * @brief	Vector's destructor
 * 			
 *			Calls the super destructors and properly manages 
 *			the deletion of the vector's allocated resources
 *
 * @param	[in] this
 * 			Vector that should be freed of its used resources
 * 			
 * @return	Nothing
 **************************************************************************************************/

void CAT(VectorDestruct, T)(void* this);

/*============================================================================
|	Overridden member function definitions
*===========================================================================*/

/**********************************************************************************************//**
 * @fn		bool CAT(VectorEquals, T)(void* this, void* other);
 *
 * @brief	Checks if the type of the vector is equal to another object
 *
 * @param	[in] this 
 * 			The vector object
 * @param	[in] other
 * 			The other object
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool CAT(VectorEquals, T)(void* this, void* other);

/**********************************************************************************************//**
 * @fn		char* CAT(VectorToString, T)(void* this);
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

char* CAT(VectorToString, T)(void* this);

/**********************************************************************************************//**
 * @fn		bool CAT(VectorAdd, T)(void* this, T item);
 *
 * @brief	Does the same as VectorPushBack
 *
 * @param	[in] this 
 * 			The vector
 * @param	[in] item
 * 			The item (element of the vector), not another <b>Vector</b>
 **************************************************************************************************/

bool CAT(VectorAdd, T)(void* this, T item);

/**********************************************************************************************//**
 * @fn		void CAT(VectorClear, T)(void* this);
 *
 * @brief	Clears the contents of the vector
 * 			
 *			Sets the length to 0, 
 *			sets the capacity to @ref DEFAULT_VECTOR_CAPACITY,
 *			and zeros out the data
 *			
 * @param	[in] this 
 * 			The vector
 * @return	Nothing
 **************************************************************************************************/

void CAT(VectorClear, T)(void* this);

/**********************************************************************************************//**
 * @fn		bool VectorRemove(void* this, void* item)
 *
 * @brief	Remove the subvector in a vector
 *			
 * @param	[in] this
 * 			The vector
 * @param	[in] item
 * 			The item (element of the vector), not another <b>Vector</b>
 * @return	Returns true if the item was removed,
 * 			returns false if the item couldn't be found or removed
 * @note    Removes the all occurences of the item in the vector
 * @note	Function will not resize the capacity. 
 * 			The overhead of free is most likely not worth resizing the capacity
 **************************************************************************************************/

bool CAT(VectorRemove, T)(void* this, T item);

/**********************************************************************************************//**
 * @fn		bool CAT(VectorContains, T)(void* this, T item);
 *
 * @brief	Remove the item in a vector
 *			
 * @param	[in] this
 * 			The vector
 * @param	[in] item
 * 			The item (element of the vector), not another <b>Vector</b>
 * @return	Returns true if the item was is in the vector,
 * 			returns false if the item couldn't be found
 **************************************************************************************************/

bool CAT(VectorContains, T)(void* this, T item);

/**********************************************************************************************//**
 * @fn	void* CAT(VectorCopy, T)(void* this);
 * @brief	Vector's copy function
 * 			
 *			Returns a deep copy of the vector
 *
 * @param	[in] this
 * 			Vector to be used for copying
 * 			
 * @return	The copied vector
 * @note	Calls copy constructor @ref VectorCopyConstruct
 * @note    This is a <b>DEEP</b> copy, which will dynamically allocate memory
 * 			for the pBuf if the current vector has dynamically allocated memory
 **************************************************************************************************/

void* CAT(VectorCopy, T)(void* this);

/**********************************************************************************************//**
 * @fn		bool CAT(VectorIsEmpty, T)(void* this);
 *
 * @brief	Checks if the vector is empty
 *			
 * @param	[in] this
 * 			The vector
 * @return	Returns true if the vector is empty, 
 * 			returns false if the vector is not empty
 **************************************************************************************************/

bool CAT(VectorIsEmpty, T)(void* this);

/**********************************************************************************************//**
 * @fn		size_t CAT(VectorSize, T)(void* this);
 *
 * @brief	Returns the number of elements in the vector
 *			
 * @param	[in] this
 * 			The vector
 * @return	Returns the length of the vector
 * @note	Includes NULL terminator
 **************************************************************************************************/

size_t CAT(VectorSize, T)(void* this);

/*============================================================================
|	Class member definitions
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	bool CAT(VectorSet, T)(void* this, const T* item, size_t num_elements);
 *
 * @brief	Sets the vector to an array of elements
 *
 * @param	[in] this
 * 			The vector
 * @param	[in] item
 * 			The item (element of the vector), not another <b>Vector</b>
 * @param	[in] num_elements
 * 			The number of elements to be placed
 * @note	Use initializer list macro for this
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool CAT(VectorSet, T)(void* this, const T* item, size_t num_elements);

/**********************************************************************************************//**
 * @fn	T CAT(VectorGet, T)(void* this, int index, int* error_code);
 *
 * @brief	Ca ts.
 *
 * @param	[in] this
 * 			The vector
 * @param	[in] index
 * 			The index of the item
 * @param	[in] error_code
 * 			Error code will be -1 if the index was out of bounds
 * 			
 * @return	Returns the element. Error code will be set to -1 if 
 * 			no element was returned
 **************************************************************************************************/

T CAT(VectorGet, T)(void* this, int index, int* error_code);

/**********************************************************************************************//**
 * @fn	bool CAT(VectorMovePushFront, T)(void* this, T item);
 *
 * @brief	Pushes the item in front of the vector by moving the item
 *
 * @param	[in] this
 * 			The vector
 * @param	[in] item
 * 			The item (element of the vector), not another <b>Vector</b>
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool CAT(VectorMovePushFront, T)(void* this, T item);


/**********************************************************************************************//**
 * @fn	bool CAT(VectorPushFront, T)(void* this, T item);
 *
 * @brief	Pushes a copy of the item in front of the vector
 *
 * @param	[in] this
 * 			The vector
 * @param	[in] item
 * 			The item (element of the vector), not another <b>Vector</b>
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool CAT(VectorPushFront, T)(void* this, T item);


/**********************************************************************************************//**
 * @fn	bool CAT(VectorMovePushBack, T)(void* this, T item);
 *
 * @brief	Pushes the item in front of the vector by moving the item
 *
 * @param	[in] this
 * 			The vector
 * @param	[in] item
 * 			The item (element of the vector), not another <b>Vector</b>
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool CAT(VectorMovePushBack, T)(void* this, T item);

/**********************************************************************************************//**
 * @fn	bool CAT(VectorPushBack, T)(void* this, T item);
 *
 * @brief	Pushes a copy of the item in back of the vector
 *
 * @param	[in] this
 * 			The vector
 * @param	[in] item
 * 			The item (element of the vector), not another <b>Vector</b>
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool CAT(VectorPushBack, T)(void* this, T item);

/**********************************************************************************************//**
 * @fn	bool CAT(VectorMoveInsert, T)(void* this, T item, int index);
 *
 * @brief	Inserts the item at the index in the vector by moving the item.\n
 * 			Everything after the index will be shifted to the right
 * 			
 * @param	[in] this
 * 			The vector
 * @param	[in] item
 * 			The item (element of the vector), not another <b>Vector</b>
 * @param	[in] index
 * 			The index to be index
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool CAT(VectorMoveInsert, T)(void* this, T item, int index);

/**********************************************************************************************//**
 * @fn	bool CAT(VectorInsert, T)(void* this, T item, int index);
 *
 * @brief	Inserts a copy of the item at the index in the vector.\n
 * 			Everything after the index will be shifted to the right
 * 			
 * @param	[in] this
 * 			The vector
 * @param	[in] item
 * 			The item (element of the vector), not another <b>Vector</b>
 * @param	[in] index
 * 			The index to be index
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool CAT(VectorInsert, T)(void* this, T item, int index);

/**********************************************************************************************//**
 * @fn	int CAT(VectorFind, T) (void* this, T item);
 *
 * @brief	Finds the index of the element in the vector
 *
 * @param	[in] this
 * 			The vector
 * @param	[in] item
 * 			The item (element of the vector), not another <b>Vector</b>
 *
 * @return	Index of the element. NPOS if none were found
 **************************************************************************************************/

int CAT(VectorFind, T) (void* this, T item);

/**********************************************************************************************//**
 * @fn	bool CAT(VectorReplace, T)(void* this, T to_replace, T replacement);
 *
 * @brief	Replaces the elements with another element
 * 			Deallocates previous element, and allocates a copy of the replacement element
 * 			
 * @param	[in] this
 * 			The vector
 * @param	[in] to_replace
 * 			The item (element of the vector), not another <b>Vector</b> to be replaced
 * @param	[in] replacement
 * 			The item (element of the vector), not another <b>Vector</b> that replaces the item
 *
 * @return	Index of the element. NPOS if none were found
 **************************************************************************************************/

bool CAT(VectorReplace, T)(void* this, T to_replace, T replacement);

/*============================================================================
|   Container virtual function table instance
*===========================================================================*/

/**
* @brief   Global vector vftable
* @relates VectorVFTable
* @note	Cannot make this const since there is a circular reference with RTTI structs
* @note	containerVFTable will be set in constructor
*/

CAT(CAT(Vector, T), VFTable) CAT(CAT(Vector, T), vfTable);

/*============================================================================
|   Container class definition
*===========================================================================*/

/**********************************************************************************************//**
 * @def	DEFINE_VECTOR
 *
 * @brief	The vector struct, which contains necessary fields for implementing a vector\n See
 * 			@ref VectorVFTable for avaliable vector functions.\n
 * 			Class members\n
 * 			container\n
 * 			size\n
 *			capacity\n
 *			data\n
 **************************************************************************************************/

#define DEFINE_VECTOR                                          \
	typedef struct CAT(_Vector, T)                             \
	{                                                          \
		struct _Container container;                           \
		size_t size;                                           \
		size_t capacity;                                       \
		T* data;                                               \
	} *CAT(Vector, T);                                           \

DEFINE_VECTOR

/*============================================================================
|   RTTI (Have to declare in reverse order, so compiler knows that structs are defined already)
|   VFTable         <===============\
|   | CompleteObjectLocator         |
|       | Signature = "HEHE"        |
|       | TypeDescriptor            |
|           | pVFTable =============/   <===============\
|           | name = Class's name ("Vector")            |
|       | ClassHierarchyDescriptor                      |
|           | attributes = 1 (VIRTUAL)                  |
|           | numBaseClasses = 2 (Container, Vector)    |
|           | BaseClassArrayDescriptor                  |
|               [                                       |
|                   ContainerBaseClassDescriptor        |
|                       | numContainedClasses (1)       |
|                       | TypeDescriptor =====> Container's pVFTable
|                   VectorBaseClassDescriptor           |
|                       | numContainedClasses (2)	    |
|                       | TypeDescriptor ===============/
|               ]
*===========================================================================*/

/**
* @brief	Global vector type descriptor
*
* 			Contains the a pointer to the vector vftable
* 			and the name of "Vector" to indicate that this
* 			is the vector class
*/

TypeDescriptor CAT(vectorTypeDescriptor, T);

/**********************************************************************************************//**
 * @def	VectorBaseClassDescriptor
 *
 * @brief	A macro that defines vector base class descriptor.
 * 			
 *			Num contained classes is two since the vector inherits from 
 *			container, which inherits from object.
 **************************************************************************************************/

#define VectorBaseClassDescriptor(x)   				 	       \
		{												       \
			.numContainedClasses = 2,				 	       \
			.pTypeDescriptor = &CAT(vectorTypeDescriptor, x)   \
		}												       \

 /**
 * @brief	Global vector base class descriptor array
 *
 * 			Contains the container base descriptor and
 * 			its own base class descriptor (vector base descriptor)
 */

BaseClassDescriptor CAT(vectorBaseClassArray, T)[2];

/**
* @brief	Global vector class hierarchy descriptor
*
* 			Vector class hierarchy descriptor is marked as virtual
* 			since it inherits from the container class.
* 			numBaseClasses is one since container inherits from only one class
* 			pBaseClassArray points to the container's base class descriptor
*			@ref vectorBaseClassArray
*/

ClassHierarchyDescriptor CAT(vectorClassHierarchyDescriptor, T);

/**
* @brief	Global vector complete object locator
*
* 			Contains the signature to indicate that this struct contains
* 			RTTI information.
* 			pTypeDescriptor points to the vector's type descriptor
* 			pClassHierarchyDescriptor points to the vector's class hierarchy descriptor
*/

CompleteObjectLocator CAT(vectorCompleteObjectLocator, T);

/*============================================================================
|	Overridden member functions
*===========================================================================*/

/*============================================================================
|	Class member functions
*===========================================================================*/

#endif
