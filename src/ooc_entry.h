/**
* @file ooc_entry.h
* @brief Entry class header
*
* Entry class implementation\n
* Unfortunately, documentation won't generate from this... :( Look at source code for info.
*			
* @author Henry Zhu (Maknee)
* @bug No know bugs.
* @see ooc_entry.c
* @date	8/21/2017
*/

#if defined(K) && defined (V)

#define OOC_V1

#include "ooc_container.h"
#include "ooc_template.h"

/*============================================================================
|   Defines
*===========================================================================*/

/*============================================================================
|   Object virtual function table definition
*===========================================================================*/

/**********************************************************************************************//**
 * @def	DEFINE_ENTRY_VFTABLE
 *
 * @brief	Macro contain templated vftable of the entry class
 * 			Entry Methods\n
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
 *			entry\n
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

typedef struct CAT(Entry_, CAT(K, V)) *CAT(Entry, CAT(K, V));

#define ENTRY CAT(Entry, CAT(K, V))
#define EntryVFTable CAT(ENTRY, VFTable)

#define DEFINE_ENTRY_VFTABLE                                  \
	typedef struct CAT(CAT(Entry_, CAT(K, V)), VFTable)       \
	{                                                         \
		CompleteObjectLocator* pCompleteObjectLocator;        \
		void (*delete)(ENTRY this);                          \
		ENTRY (*copy)(ENTRY this);                          \
        bool (*equals)(ENTRY this, ENTRY other);            \
		int (*compareTo)(ENTRY this, ENTRY other);          \
		char* (*toString)(ENTRY this);                       \
		                                                      \
		bool (*move_set_key)(ENTRY this, K item);             \
		bool (*set_key)(ENTRY this, K item);                  \
		K* (*get_key)(ENTRY this);                            \
		bool (*move_set_value)(ENTRY this, V item);           \
		bool (*set_value)(ENTRY this, V item);                \
		V* (*get_value)(ENTRY this);                          \
	} CAT(CAT(Entry, CAT(K, V)), VFTable);                    \

DEFINE_ENTRY_VFTABLE

/*============================================================================
|	Special class member function definitions
*===========================================================================*/

/*============================================================================
|	New Operator
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	ENTRY CAT(NewEntry, CAT(K, V))()
 * @brief	Entry's new operator
 * 			
 *			Returns an allocated new entry
 * 			
 * @return	An allocated entry object or null if none could be allocated
 **************************************************************************************************/

ENTRY CAT(NewEntry, CAT(K, V))();

/*============================================================================
|	Delete Operator
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(DeleteEntry, CAT(K, V))(ENTRY this);
 *
 * @brief	Deletes and frees a entry's resources
 *
 * @param	[in] this
 * 			Object to be deleted
 * @return	Nothing
 **************************************************************************************************/

void CAT(DeleteEntry, CAT(K, V))(ENTRY this);

/*============================================================================
|	Constructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(EntryConstruct, CAT(K, V))(ENTRY this);
 * @brief	Entry's constructor
 * 			
 *			Entryups the vftable by completing the RTTI dependency
 *			and memcpys the table into the object's vftable
 *
 * @param	[in] this
 * 			Object to be initialized
 * 			
 * @return	Nothing
 * @todo	{Find a way to not use memcpy for entryting up the vftable...}
 **************************************************************************************************/

void CAT(EntryConstruct, CAT(K, V))(ENTRY this);

/*============================================================================
|	Copy Constructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	ENTRY CAT(EntryCopyConstruct, CAT(K, V))(ENTRY this);
 * @brief	Entry's copy constructor
 * 			
 *			Returns a copy of the entry
 *
 * @param	[in] this
 * 			Entry to be used for copying
 * 			
 * @return	The copied entry
 * @note	Derived classes may implement a copy constructor, 
 * 			but it is not necessary
 * @note    This is a <b>DEEP</b> copy, which will dynamically allocate memory
 * 			for the entry and copy every element
 **************************************************************************************************/

ENTRY CAT(EntryCopyConstruct, CAT(K, V))(ENTRY this);

/*============================================================================
|	Destructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(EntryDestruct, CAT(K, V))(ENTRY this);
 * @brief	Entry's destructor
 * 			
 *			Calls the super destructors and properly manages 
 *			the deletion of the entry's allocated resources
 *
 * @param	[in] this
 * 			Entry that should be freed of its used resources
 * 			
 * @return	Nothing
 **************************************************************************************************/

void CAT(EntryDestruct, CAT(K, V))(ENTRY this);

/*============================================================================
|	Overridden member function definitions
*===========================================================================*/

/**********************************************************************************************//**
 * @fn		bool CAT(EntryEquals, CAT(K, V))(ENTRY this, ENTRY other);
 *
 * @brief	Checks if the type of the entry is equal to another object
 *
 * @param	[in] this 
 * 			The entry object
 * @param	[in] other
 * 			The other object
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool CAT(EntryEquals, CAT(K, V))(ENTRY this, ENTRY other);

/**********************************************************************************************//**
 * @fn		int CAST(EntryCompareTo, CAT(K, V))(ENTRY this, ENTRY other);
 *
 * @brief	Checks if the type of the entry is equal to another object
 *
 * @param	[in] this 
 * 			The object
 * @param	[in] other
 * 			The other object
 *
 * @return	0 if it succeeds, negative or positive if it fails.
 **************************************************************************************************/

int CAT(EntryCompareTo, CAT(K, V))(ENTRY this, ENTRY other);

/**********************************************************************************************//**
 * @fn		char* CAT(EntryToString, CAT(K, V))(ENTRY this);
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

char* CAT(EntryToString, CAT(K, V))(ENTRY this);

/**********************************************************************************************//**
 * @fn		bool CAT(EntryAdd, CAT(K, V))(ENTRY this, T item);
 *
 * @brief	Does the same as EntryPushBack
 *
 * @param	[in] this 
 * 			The entry
 * @param	[in] item
 * 			The item (element of the entry), not another <b>Entry</b>
 **************************************************************************************************/

ENTRY CAT(EntryCopy, CAT(K, V))(ENTRY this);
bool CAT(EntryMoveSetKey, CAT(K, V))(ENTRY this, K item);
bool CAT(EntrySetKey, CAT(K, V))(ENTRY this, K item);
K* CAT(EntryGetKey, CAT(K, V))(ENTRY this);
bool CAT(EntryMoveSetValue, CAT(K, V))(ENTRY this, V item);
bool CAT(EntrySetValue, CAT(K, V))(ENTRY this, V item);
V* CAT(EntryGetValue, CAT(K, V))(ENTRY this);

/*============================================================================
|   Container virtual function table instance
*===========================================================================*/

CAT(CAT(Entry, CAT(K, V)), VFTable) CAT(CAT(Entry, CAT(K, V)), vfTable);

/**********************************************************************************************//**
 * @def	DEFINE_ENTRY
 *
 * @brief	The entry struct, which contains necessary fields for implementing a entry\n See
 * 			@ref EntryVFTable for avaliable entry functions.\n
 * 			Class members\n
 * 			container\n
 * 			size\n
 *			capacity\n
 *			data\n
 **************************************************************************************************/

#define DEFINE_ENTRY                                           \
	typedef struct CAT(Entry_, CAT(K, V))                      \
	{                                                          \
		struct Object_ object;                                 \
		K key;                                                 \
		V value;                                               \
	} *CAT(Entry, CAT(K, V));                                  \

DEFINE_ENTRY

/*============================================================================
|   RTTI (Have to declare in reverse order, so compiler knows that structs are defined already)
|   VFTable         <===============\
|   | CompleteObjectLocator         |
|       | Signature = "HEHE"        |
|       | TypeDescriptor            |
|           | pVFTable =============/   <===============\
|           | name = Class's name ("Entry")            |
|       | ClassHierarchyDescriptor                      |
|           | attributes = 1 (VIRTUAL)                  |
|           | numBaseClasses = 2 (Container, Entry)    |
|           | BaseClassArrayDescriptor                  |
|               [                                       |
|                   ContainerBaseClassDescriptor        |
|                       | numContainedClasses (1)       |
|                       | TypeDescriptor =====> Container's pVFTable
|                   EntryBaseClassDescriptor           |
|                       | numContainedClasses (2)	    |
|                       | TypeDescriptor ===============/
|               ]
*===========================================================================*/

/**
* @brief	Global entry type descriptor
*
* 			Contains the a pointer to the entry vftable
* 			and the name of "Entry" to indicate that this
* 			is the entry class
*/

TypeDescriptor CAT(entryTypeDescriptor, CAT(K, V));

/**********************************************************************************************//**
 * @def	EntryBaseClassDescriptor
 *
 * @brief	A macro that defines entry base class descriptor.
 * 			
 *			Num contained classes is two since the entry inherits from 
 *			container, which inherits from object.
 **************************************************************************************************/

#define EntryBaseClassDescriptor(x)   				 	       \
		{												       \
			.numContainedClasses = 2,				 	       \
			.pTypeDescriptor = &CAT(entryTypeDescriptor, x)   \
		}												       \

 /**
 * @brief	Global entry base class descriptor array
 *
 * 			Contains the container base descriptor and
 * 			its own base class descriptor (entry base descriptor)
 */

BaseClassDescriptor CAT(entryBaseClassArray, CAT(K, V))[2];

/**
* @brief	Global entry class hierarchy descriptor
*
* 			Entry class hierarchy descriptor is marked as virtual
* 			since it inherits from the ooc_container.class.
* 			numBaseClasses is one since container inherits from only one class
* 			pBaseClassArray points to the container's base class descriptor
*			@ref entryBaseClassArray
*/

ClassHierarchyDescriptor CAT(entryClassHierarchyDescriptor, CAT(K, V));

/**
* @brief	Global entry complete object locator
*
* 			Contains the signature to indicate that this struct contains
* 			RTTI information.
* 			pTypeDescriptor points to the entry's type descriptor
* 			pClassHierarchyDescriptor points to the entry's class hierarchy descriptor
*/

CompleteObjectLocator CAT(entryCompleteObjectLocator, CAT(K, V));

/*============================================================================
|	Overridden member functions
*===========================================================================*/

/*============================================================================
|	Class member functions
*===========================================================================*/

#undef ENTRY
#undef EntryVFTable

#endif
