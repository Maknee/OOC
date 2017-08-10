/**
* @file ooc_vector.h
* @brief Vector class header
*
* Vector class implementation using SSO optimiziation
* Credits to: 
* <a href="http://arnold.uthar.net/index.php?n=Work.TemplatesC"
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
 * @struct	CAT(CAT(_Vector, T), VFTable)
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
 * @var		CAT(CAT(_Vector, T), VFTable)::pCompleteObjectLocator
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

typedef struct CAT(_Vector, T) CAT(Vector, T);

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
		bool(*push_front)(void* this, T item);                 \
		bool(*push_back)(void* this, T item);                  \
		bool(*insert)(void* this, T item, int index);          \
		int(*find) (void* this, T item);                       \
		bool (*replace)(void* this, T to_replace, T replacement); \
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
 * @return	An allocated vector object
 **************************************************************************************************/

void* CAT(NewVector, T)();

/*============================================================================
|	Delete Operator
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(DeleteVector, T)(void* this);
 * @brief	Vector's delete operator
 * 			
 *			Deletes the allocated vector
 *
 * @param	[in] this
 * 			Vector object to be deleted
 * 			
 * @return	Nothing
 * @warning If NULL is passed, an attempt to free NULL will be made
 **************************************************************************************************/

void CAT(DeleteVector, T)(void* this);

/*============================================================================
|	Constructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void VectorConstruct(void* this)
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
 * @fn	void* VectorCopyConstruct(void* this)
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
 * 			for the pBuf if the current vector has dynamically allocated memory
 * @note	Does not memcpy the vtable (just points to the same vtable as the current vector)
 **************************************************************************************************/

void* CAT(VectorCopyConstruct, T)(void* this);

/*============================================================================
|	Destructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void VectorDestruct(void* this)
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
 * @fn		bool VectorEquals(void* this, void* other);
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
 * @fn		bool VectorToVector(void* this);
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
 * @fn		bool VectorAdd(void* this, void* item)
 *
 * @brief	Concatenates the two vectors
 * 			
 *			The vectors are concatenated by:
 *			Checking the new length
 *			Checking whether or not the current vector was dynamically allocated
 *			If so, just call realloc and append
 *			If not, then two cases appear with a vector that is externally allocated
 *			If the new length is greater than limit length, then make the pointer dynamic
 *			If the new length is less, then append to length
 *
 * @param	[in] this 
 * 			The vector
 * @param	[in] item
 * 			The other vector
 * @return	Returns true if the vector was added correctly, 
 * 			returns false if the vector was not added correctly
 * @note	Function only appends an object vector to another object vector,
 * 			<b>NOT</b> a vector object to a char pointer. @ref VectorAppend
 * @todo	{find a case when the function should fail}
 * @todo	{figure out a way to merge this function and VectorAppend}
 **************************************************************************************************/

bool CAT(VectorAdd, T)(void* this, T item);

/**********************************************************************************************//**
 * @fn		void VectorClear(void* this)
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
 *			
 *			
 * @param	[in] this
 * 			The vector
 * @param	[in] item
 * 			The subvector
 * @return	Returns true if the subvector was removed, 
 * 			returns false if the subvector couldn't be found or removed
 * @note    Removes the first occurence of the item in the vector
 * @note	Function will not resize the capacity. 
 * 			The overhead of free is most likely not worth resizing the capacity
 **************************************************************************************************/

bool CAT(VectorRemove, T)(void* this, T item);

/**********************************************************************************************//**
 * @fn		bool VectorContains(void* this, void* item)
 *
 * @brief	Remove the subvector in a vector
 *			
 * @param	[in] this
 * 			The vector
 * @param	[in] item
 * 			The subvector
 * @return	Returns true if the subvector was is in the vector, 
 * 			returns false if the subvector couldn't be found
 **************************************************************************************************/

bool CAT(VectorContains, T)(void* this, T item);

/**********************************************************************************************//**
 * @fn	void* VectorCopy(void* this)
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
 * @note	Does not memcpy the vtable (just points to the same vtable as the current vector)
 **************************************************************************************************/

void* CAT(VectorCopy, T)(void* this);

/**********************************************************************************************//**
 * @fn		bool VectorIsEmpty(void* this)
 *
 * @brief	Checks if the vector is empty
 *			
 * @param	[in] this
 * 			The vector
 * @return	Returns true if the subvector is empty, 
 * 			returns false if the subvector is not empty
 **************************************************************************************************/

bool CAT(VectorIsEmpty, T)(void* this);

/**********************************************************************************************//**
 * @fn		int VectorSize(void* this)
 *
 * @brief	Returns the length of the vector
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

bool CAT(VectorSet, T)(void* this, const T* item, size_t num_elements);
T CAT(VectorGet, T)(void* this, int index, int* error_code);
bool CAT(VectorPushFront, T)(void* this, T item);
bool CAT(VectorPushBack, T)(void* this, T item);
bool CAT(VectorInsert, T)(void* this, T item, int index);
int CAT(VectorFind, T) (void* this, T item);
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

CAT(CAT(Vector, T), VFTable) CAT(CAT(vector, T), VFTable);

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
 * @var		_Vector::data::buf
 *			Array of chars of length @ref DEFAULT_VECTOR_CAPACITY, which is allocated
 *			directory in the vector struct
 *			
 * @var		_Vector::data::pBuf
 *			Char pointer to a dynamically allocated char array if the size of 
 *			the vector is greater than @ref DEFAULT_VECTOR_CAPACITY
 *			@note
 *			It is not necessary for the coder to manually deallocate this memory.
 *			The coder can assume that the allocated data will be free'd with the destructor
 *			@see
 *			VectorDestruct
 **************************************************************************************************/

#define DEFINE_VECTOR                                          \
	typedef struct CAT(_Vector, T)                             \
	{                                                          \
		Container container;                                   \
		size_t size;                                           \
		size_t capacity;                                       \
		T* data;                                               \
	}CAT(Vector, T);                                           \

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
