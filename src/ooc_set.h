/**
* @file ooc_set.h
* @brief Set class header
*
* Set class implementation\n
* Unfortunately, documentation won't generate from this... :( Look at source code for info.
*			
* @author Henry Zhu (Maknee)
* @bug No know bugs.
* @note A set holds up to 16 characters including the NULL terminator
* 		until the set becomes dynamically allocated. This makes the set
* 		implementation work well with sets < 16 characters.
* @warning <b>NEVER</b> use the same set more than once in a set function call. 
* 		   It will corrupt the set.
* @see ooc_set.c
* @date	8/1/2017
* @todo {consider replacing C11's strcat_s}
*/

#ifdef T

#define OOC_V1

#include "template.h"

/*============================================================================
|   Defines
*===========================================================================*/

/**********************************************************************************************//**
 * @def		DEFAULT_SET_CAPACITY
 *
 * @brief	A macro that defines the default capacity of a set
 * @see		_Set
 * 			
 * @def		NULL_SET_VFTABLE
 * @brief	A macro that defines a null set vftable template for classes
 * 			that inherit from the set class
 **************************************************************************************************/

#define NULL_SET_VFTABLE                                        \
		{                                                       \
			{                                                   \
				{                                               \
					.pCompleteObjectLocator = NULL,             \
					.equals = NULL,                             \
					.toSet = NULL                               \
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
|   Set Iterator
*===========================================================================*/

#define DEFINE_SET_ITERATOR                                 \
	typedef struct CAT(CAT(_Set, T), Iterator)              \
	{                                                          \
		int index;                                             \
		T* data;                                               \
	} *CAT(CAT(Set, T), Iterator);                          \

DEFINE_SET_ITERATOR

/*============================================================================
|   Object virtual function table definition
*===========================================================================*/

/**********************************************************************************************//**
 * @def	DEFINE_SET_VFTABLE
 *
 * @brief	Macro contain templated vftable of the set class
 * 			Set Methods\n
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
 *			begin\n
 *			next\n
 *			end\n
 **************************************************************************************************/

//have to use macro to define vftable because macros can't be
//used in struct declaration

//also super class has to templated... not exactly what I call
//perfect inheritence

typedef struct CAT(_Set, T) *CAT(Set, T);

#define SET CAT(Set, T)
#define SetVFTable CAT(SET, VFTable)

#define DEFINE_SET_VFTABLE                                     \
	typedef struct CAT(CAT(_Set, T), VFTable)                  \
	{                                                          \
		CompleteObjectLocator* pCompleteObjectLocator;         \
		void (*delete)(SET this);                              \
		SET (*copy)(SET this);                                 \
        bool (*equals)(SET this, SET other);                   \
		int (*compareTo)(SET this, SET other);                 \
		char* (*toString)(SET this);                           \
                                                               \
		bool (*add)(SET this, T item);                         \
		void(*clear)(SET this);                                \
		bool(*remove)(SET this, T item);                       \
		bool(*contains)(SET this, T item);                     \
		bool(*isEmpty)(SET this);                              \
		size_t(*size)(SET this);                               \
		                                                       \
		bool(*set)(SET this, const T* item, size_t num_elements); \
		bool(*move_insert)(SET this, T item);                  \
		bool(*insert)(SET this, T item);                       \
		T*(*find) (SET this, T item);                          \
		bool(*replace)(SET this, T to_replace, T replacement); \
		CAT(CAT(Set, T), Iterator) (*begin)(SET this);         \
		bool(*next)(SET this, CAT(CAT(Set, T), Iterator) iterator); \
		CAT(CAT(Set, T), Iterator) (*end)(SET this, CAT(CAT(Set, T), Iterator) iterator); \
	} CAT(CAT(Set, T), VFTable);                               \

DEFINE_SET_VFTABLE

/*============================================================================
|	Special class member function definitions
*===========================================================================*/

/*============================================================================
|	New Operator
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	SET CAT(NewSet, T)()
 * @brief	Set's new operator
 * 			
 *			Returns an allocated new set
 * 			
 * @return	An allocated set object or null if none could be allocated
 **************************************************************************************************/

SET CAT(NewSet, T)();

/*============================================================================
|	Delete Operator
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(DeleteSet, T)(SET this);
 *
 * @brief	Deletes and frees a set's resources
 *
 * @param	[in] this
 * 			Object to be deleted
 * @return	Nothing
 **************************************************************************************************/

void CAT(DeleteSet, T)(SET this);

/*============================================================================
|	Constructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(SetConstruct, T)(SET this);
 * @brief	Set's constructor
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

void CAT(SetConstruct, T)(SET this);

/*============================================================================
|	Copy Constructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	SET CAT(SetCopyConstruct, T)(SET this);
 * @brief	Set's copy constructor
 * 			
 *			Returns a copy of the set
 *
 * @param	[in] this
 * 			Set to be used for copying
 * 			
 * @return	The copied set
 * @note	Derived classes may implement a copy constructor, 
 * 			but it is not necessary
 * @note    This is a <b>DEEP</b> copy, which will dynamically allocate memory
 * 			for the set and copy every element
 **************************************************************************************************/

SET CAT(SetCopyConstruct, T)(SET this);

/*============================================================================
|	Destructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(SetDestruct, T)(SET this);
 * @brief	Set's destructor
 * 			
 *			Calls the super destructors and properly manages 
 *			the deletion of the set's allocated resources
 *
 * @param	[in] this
 * 			Set that should be freed of its used resources
 * 			
 * @return	Nothing
 **************************************************************************************************/

void CAT(SetDestruct, T)(SET this);

/*============================================================================
|	Overridden member function definitions
*===========================================================================*/

/**********************************************************************************************//**
 * @fn		bool CAT(SetEquals, T)(SET this, SET other);
 *
 * @brief	Checks if the type of the set is equal to another object
 *
 * @param	[in] this 
 * 			The set object
 * @param	[in] other
 * 			The other object
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool CAT(SetEquals, T)(SET this, SET other);

/**********************************************************************************************//**
 * @fn		int CAST(SetCompareTo, T)(SET this, SET other);
 *
 * @brief	Checks if the type of the set is equal to another object
 *
 * @param	[in] this 
 * 			The object
 * @param	[in] other
 * 			The other object
 *
 * @return	0 if it succeeds, negative or positive if it fails.
 **************************************************************************************************/

int CAT(SetCompareTo, T)(SET this, SET other);

/**********************************************************************************************//**
 * @fn		char* CAT(SetToString, T)(SET this);
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

char* CAT(SetToString, T)(SET this);

/**********************************************************************************************//**
 * @fn		bool CAT(SetAdd, T)(SET this, T item);
 *
 * @brief	Does the same as SetPushBack
 *
 * @param	[in] this 
 * 			The set
 * @param	[in] item
 * 			The item (element of the set), not another <b>Set</b>
 **************************************************************************************************/

bool CAT(SetAdd, T)(SET this, T item);

/**********************************************************************************************//**
 * @fn		void CAT(SetClear, T)(SET this);
 *
 * @brief	Clears the contents of the set
 * 			
 *			Sets the length to 0, 
 *			sets the capacity to @ref DEFAULT_SET_CAPACITY,
 *			and zeros out the data
 *			
 * @param	[in] this 
 * 			The set
 * @return	Nothing
 **************************************************************************************************/

void CAT(SetClear, T)(SET this);

/**********************************************************************************************//**
 * @fn		bool SetRemove(SET this, SET item)
 *
 * @brief	Remove the subset in a set
 *			
 * @param	[in] this
 * 			The set
 * @param	[in] item
 * 			The item (element of the set), not another <b>Set</b>
 * @return	Returns true if the item was removed,
 * 			returns false if the item couldn't be found or removed
 * @note    Removes the all occurences of the item in the set
 * @note	Function will not resize the capacity. 
 * 			The overhead of free is most likely not worth resizing the capacity
 **************************************************************************************************/

bool CAT(SetRemove, T)(SET this, T item);

/**********************************************************************************************//**
 * @fn		bool CAT(SetContains, T)(SET this, T item);
 *
 * @brief	Remove the item in a set
 *			
 * @param	[in] this
 * 			The set
 * @param	[in] item
 * 			The item (element of the set), not another <b>Set</b>
 * @return	Returns true if the item was is in the set,
 * 			returns false if the item couldn't be found
 **************************************************************************************************/

bool CAT(SetContains, T)(SET this, T item);

/**********************************************************************************************//**
 * @fn	SET CAT(SetCopy, T)(SET this);
 * @brief	Set's copy function
 * 			
 *			Returns a deep copy of the set
 *
 * @param	[in] this
 * 			Set to be used for copying
 * 			
 * @return	The copied set
 * @note	Calls copy constructor @ref SetCopyConstruct
 * @note    This is a <b>DEEP</b> copy, which will dynamically allocate memory
 * 			for the pBuf if the current set has dynamically allocated memory
 **************************************************************************************************/

SET CAT(SetCopy, T)(SET this);

/**********************************************************************************************//**
 * @fn		bool CAT(SetIsEmpty, T)(SET this);
 *
 * @brief	Checks if the set is empty
 *			
 * @param	[in] this
 * 			The set
 * @return	Returns true if the set is empty, 
 * 			returns false if the set is not empty
 **************************************************************************************************/

bool CAT(SetIsEmpty, T)(SET this);

/**********************************************************************************************//**
 * @fn		size_t CAT(SetSize, T)(SET this);
 *
 * @brief	Returns the number of elements in the set
 *			
 * @param	[in] this
 * 			The set
 * @return	Returns the length of the set
 * @note	Includes NULL terminator
 **************************************************************************************************/

size_t CAT(SetSize, T)(SET this);

/*============================================================================
|	Class member definitions
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	bool CAT(Set_Set, T)(SET this, const T* item, size_t num_elements);
 *
 * @brief	Sets the set to an array of elements
 *
 * @param	[in] this
 * 			The set
 * @param	[in] item
 * 			The item (element of the set), not another <b>Set</b>
 * @param	[in] num_elements
 * 			The number of elements to be placed
 * @note	Use initializer list macro for this
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool CAT(Set_Set, T)(SET this, const T* item, size_t num_elements);

/**********************************************************************************************//**
 * @fn	bool CAT(SetMoveInsert, T)(SET this, T item)
 *
 * @brief	Inserts the item at the index in the set by moving the item.\n
 * 			Everything after the index will be shifted to the right
 * 			
 * @param	[in] this
 * 			The set
 * @param	[in] item
 * 			The item (element of the set), not another <b>Set</b>
 * @param	[in] index
 * 			The index to be index
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool CAT(SetMoveInsert, T)(SET this, T item);

/**********************************************************************************************//**
 * @fn	bool CAT(SetInsert, T)(SET this, T item);
 *
 * @brief	Inserts a copy of the item at the index in the set.\n
 * 			Everything after the index will be shifted to the right
 * 			
 * @param	[in] this
 * 			The set
 * @param	[in] item
 * 			The item (element of the set), not another <b>Set</b>
 * @param	[in] index
 * 			The index to be index
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool CAT(SetInsert, T)(SET this, T item);

/**********************************************************************************************//**
 * @fn	T* CAT(SetFind, T) (SET this, T item)
 *
 * @brief	Finds the index of the element in the set
 *
 * @param	[in] this
 * 			The set
 * @param	[in] item
 * 			The item (element of the set), not another <b>Set</b>
 *
 * @return	Index of the element. NPOS if none were found
 **************************************************************************************************/

T* CAT(SetFind, T) (SET this, T item);

/**********************************************************************************************//**
 * @fn	bool CAT(SetReplace, T)(SET this, T to_replace, T replacement);
 *
 * @brief	Replaces the elements with another element
 * 			Deallocates previous element, and allocates a copy of the replacement element
 * 			
 * @param	[in] this
 * 			The set
 * @param	[in] to_replace
 * 			The item (element of the set), not another <b>Set</b> to be replaced
 * @param	[in] replacement
 * 			The item (element of the set), not another <b>Set</b> that replaces the item
 *
 * @return	Index of the element. NPOS if none were found
 **************************************************************************************************/

bool CAT(SetReplace, T)(SET this, T to_replace, T replacement);

/**********************************************************************************************//**
 * @fn		StringIterator StringBegin(SET this)
 *
 * @brief   Returns an iterator starting at the beginning of a string
 *
 *			@param[in] this
 *			The object
 *			@return
 *			Returns a string iterator
 **************************************************************************************************/

CAT(CAT(Set, T), Iterator) CAT(SetBegin, T)(SET this);

/**********************************************************************************************//**
 * @fn		bool StringNext(SET this, StringIterator* iterator)
 *
 * @brief   Advances string iterator
 *
 *			@param[in] this
 *			The object
 *			@return
 *			Returns a string iterator
 **************************************************************************************************/

bool CAT(SetNext, T)(SET this, CAT(CAT(Set, T), Iterator) iterator);

/**********************************************************************************************//**
 * @fn		StringIterator StringEnd(SET this)
 *
 * @brief   Returns an iterator starting at end of the string
 *
 *			@param[in] this
 *			The object
 *			@param [in] iterator
 *			A pointer to an iterator
 *			@return
 *			Returns a string iterator
 **************************************************************************************************/

CAT(CAT(Set, T), Iterator) CAT(SetEnd, T)(SET this, CAT(CAT(Set, T), Iterator) iterator);

/*============================================================================
|   Container virtual function table instance
*===========================================================================*/

/**
* @brief   Global set vftable
* @relates SetVFTable
* @note	Cannot make this const since there is a circular reference with RTTI structs
* @note	containerVFTable will be set in constructor
*/

CAT(CAT(Set, T), VFTable) CAT(CAT(Set, T), vfTable);

/*============================================================================
|   Set class definition
*===========================================================================*/

#define DEFINE_SETNODE                                         \
	typedef struct CAT(_SetNode, T)                            \
	{                                                          \
		T data;                                                \
		struct CAT(_SetNode, T)* children[2];                  \
		bool color;                                            \
	} *CAT(SetNode, T);                                        \

DEFINE_SETNODE

int CAT(SetTest, T)(CAT(SetNode, T) root, int indent);

/**********************************************************************************************//**
 * @def	DEFINE_SET
 *
 * @brief	The set struct, which contains necessary fields for implementing a set\n See
 * 			@ref SetVFTable for avaliable set functions.\n
 * 			Class members\n
 * 			container\n
 * 			size\n
 *			capacity\n
 *			data\n
 **************************************************************************************************/

#define DEFINE_SET                                             \
	typedef struct CAT(_Set, T)                                \
	{                                                          \
		struct _Container container;                           \
		size_t size;                                           \
		CAT(SetNode, T) root;                                  \
	} *CAT(Set, T);                                            \

DEFINE_SET

/*============================================================================
|   RTTI (Have to declare in reverse order, so compiler knows that structs are defined already)
|   VFTable         <===============\
|   | CompleteObjectLocator         |
|       | Signature = "HEHE"        |
|       | TypeDescriptor            |
|           | pVFTable =============/   <===============\
|           | name = Class's name ("Set")            |
|       | ClassHierarchyDescriptor                      |
|           | attributes = 1 (VIRTUAL)                  |
|           | numBaseClasses = 2 (Container, Set)    |
|           | BaseClassArrayDescriptor                  |
|               [                                       |
|                   ContainerBaseClassDescriptor        |
|                       | numContainedClasses (1)       |
|                       | TypeDescriptor =====> Container's pVFTable
|                   SetBaseClassDescriptor           |
|                       | numContainedClasses (2)	    |
|                       | TypeDescriptor ===============/
|               ]
*===========================================================================*/

/**
* @brief	Global set type descriptor
*
* 			Contains the a pointer to the set vftable
* 			and the name of "Set" to indicate that this
* 			is the set class
*/

TypeDescriptor CAT(setTypeDescriptor, T);

/**********************************************************************************************//**
 * @def	SetBaseClassDescriptor
 *
 * @brief	A macro that defines set base class descriptor.
 * 			
 *			Num contained classes is two since the set inherits from 
 *			container, which inherits from object.
 **************************************************************************************************/

#define SetBaseClassDescriptor(x)   				 	       \
		{												       \
			.numContainedClasses = 2,				 	       \
			.pTypeDescriptor = &CAT(setTypeDescriptor, x)   \
		}												       \

 /**
 * @brief	Global set base class descriptor array
 *
 * 			Contains the container base descriptor and
 * 			its own base class descriptor (set base descriptor)
 */

BaseClassDescriptor CAT(setBaseClassArray, T)[2];

/**
* @brief	Global set class hierarchy descriptor
*
* 			Set class hierarchy descriptor is marked as virtual
* 			since it inherits from the container class.
* 			numBaseClasses is one since container inherits from only one class
* 			pBaseClassArray points to the container's base class descriptor
*			@ref setBaseClassArray
*/

ClassHierarchyDescriptor CAT(setClassHierarchyDescriptor, T);

/**
* @brief	Global set complete object locator
*
* 			Contains the signature to indicate that this struct contains
* 			RTTI information.
* 			pTypeDescriptor points to the set's type descriptor
* 			pClassHierarchyDescriptor points to the set's class hierarchy descriptor
*/

CompleteObjectLocator CAT(setCompleteObjectLocator, T);

/*============================================================================
|	Overridden member functions
*===========================================================================*/

/*============================================================================
|	Class member functions
*===========================================================================*/

#endif
