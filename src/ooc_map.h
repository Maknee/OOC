/**
* @file ooc_map.h
* @brief Map class header
*
* Map class implementation\n
* Unfortunately, documentation won't generate from this... :( Look at source code for info.
*			
* @author Henry Zhu (Maknee)
* @bug No know bugs.
* @note A map holds up to 16 characters including the NULL terminator
* 		until the map becomes dynamically allocated. This makes the map
* 		implementation work well with maps < 16 characters.
* @warning <b>NEVER</b> use the same map more than once in a map function call. 
* 		   It will corrupt the map.
* @see ooc_map.c
* @date	8/1/2017
* @todo {consider replacing C11's strcat_s}
*/

#if defined(K) && defined (V)

#include "container.h"
#include "template.h"

/*============================================================================
|   Defines
*===========================================================================*/

/**********************************************************************************************//**
 * @def		DEFAULT_MAP_CAPACITY
 *
 * @brief	A macro that defines the default capacity of a map
 * @see		_Map
 * 			
 * @def		NULL_MAP_VFTABLE
 * @brief	A macro that defines a null map vftable template for classes
 * 			that inherit from the map class
 **************************************************************************************************/

#define ENTRY CAT(Entry, CAT(K, V))

#define NULL_MAP_VFTABLE                                        \
		{                                                       \
			{                                                   \
				{                                               \
					.pCompleteObjectLocator = NULL,             \
					.equals = NULL,                             \
					.toMap = NULL                               \
				},                                              \
				.add = NULL,                                    \
				.clear = NULL,                                  \
				.remove = NULL,                                 \
				.contains = NULL,                               \
				.copy = NULL,                                   \
				.isEmpty = NULL,                                \
				.size = NULL                                    \
			},                                                  \
			.map = NULL,                                        \
			.get = NULL,                                        \
			.push_front = NULL,                                 \
			.push_back = NULL.                                  \
			.insert = NULL,                                     \
			.find = NULL                                        \
			.replace = NULL                                     \
		}                                                       \

/*============================================================================
|   Map Iterator
*===========================================================================*/

#define DEFINE_MAP_ITERATOR                                    \
	typedef struct CAT(CAT(_Map, CAT(K, V)), Iterator)         \
	{                                                          \
		int index;                                             \
		ENTRY* data;                                           \
	} *CAT(CAT(Map, CAT(K, V)), Iterator);                     \

DEFINE_MAP_ITERATOR

/*============================================================================
|   Object virtual function table definition
*===========================================================================*/

/**********************************************************************************************//**
 * @def	DEFINE_MAP_VFTABLE
 *
 * @brief	Macro contain templated vftable of the map class
 * 			Map Methods\n
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
 *			map\n
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
#define DEFINE_MAP_VFTABLE                                     \
	typedef struct CAT(CAT(_Map, CAT(K, V)), VFTable)          \
	{                                                          \
		struct _ObjectVFTable;                                 \
		                                                       \
		bool(*add)(void* this, ENTRY entry);                   \
		void(*clear)(void* this);                              \
		bool(*remove)(void* this, ENTRY entry);                \
		bool(*contains)(void* this, ENTRY entry);              \
		void* (*copy)(void* this);                             \
		bool(*isEmpty)(void* this);                            \
		size_t(*size)(void* this);                             \
		                                                       \
		bool(*set)(void* this, const ENTRY* entries, size_t num_elements); \
		bool(*move_insert)(void* this, ENTRY entry);                \
		bool(*insert)(void* this, ENTRY entry);                     \
		ENTRY*(*find) (void* this, ENTRY entry);                       \
		bool(*replace)(void* this, ENTRY to_replace, ENTRY replacement); \
		CAT(CAT(Map, CAT(K, V)), Iterator) (*begin)(void* this);      \
		bool(*next)(void* this, CAT(CAT(Map, CAT(K, V)), Iterator) iterator); \
		CAT(CAT(Map, CAT(K, V)), Iterator) (*end)(void* this, CAT(CAT(Map, CAT(K, V)), Iterator) iterator); \
	} CAT(CAT(Map, CAT(K, V)), VFTable);                            \

DEFINE_MAP_VFTABLE

/*============================================================================
|	Special class member function definitions
*===========================================================================*/

/*============================================================================
|	New Operator
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void* CAT(NewMap, CAT(K, V))()
 * @brief	Map's new operator
 * 			
 *			Returns an allocated new map
 * 			
 * @return	An allocated map object or null if none could be allocated
 **************************************************************************************************/

void* CAT(NewMap, CAT(K, V))();

/*============================================================================
|	Delete Operator
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(DeleteMap, CAT(K, V))(void* this);
 *
 * @brief	Deletes and frees a map's resources
 *
 * @param	[in] this
 * 			Object to be deleted
 * @return	Nothing
 **************************************************************************************************/

void CAT(DeleteMap, CAT(K, V))(void* this);

/*============================================================================
|	Constructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(MapConstruct, CAT(K, V))(void* this);
 * @brief	Map's constructor
 * 			
 *			Mapups the vftable by completing the RTTI dependency
 *			and memcpys the table into the object's vftable
 *
 * @param	[in] this
 * 			Object to be initialized
 * 			
 * @return	Nothing
 * @todo	{Find a way to not use memcpy for mapting up the vftable...}
 **************************************************************************************************/

void CAT(MapConstruct, CAT(K, V))(void* this);

/*============================================================================
|	Copy Constructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void* CAT(MapCopyConstruct, CAT(K, V))(void* this);
 * @brief	Map's copy constructor
 * 			
 *			Returns a copy of the map
 *
 * @param	[in] this
 * 			Map to be used for copying
 * 			
 * @return	The copied map
 * @note	Derived classes may implement a copy constructor, 
 * 			but it is not necessary
 * @note    This is a <b>DEEP</b> copy, which will dynamically allocate memory
 * 			for the map and copy every element
 **************************************************************************************************/

void* CAT(MapCopyConstruct, CAT(K, V))(void* this);

/*============================================================================
|	Destructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(MapDestruct, CAT(K, V))(void* this);
 * @brief	Map's destructor
 * 			
 *			Calls the super destructors and properly manages 
 *			the deletion of the map's allocated resources
 *
 * @param	[in] this
 * 			Map that should be freed of its used resources
 * 			
 * @return	Nothing
 **************************************************************************************************/

void CAT(MapDestruct, CAT(K, V))(void* this);

/*============================================================================
|	Overridden member function definitions
*===========================================================================*/

/**********************************************************************************************//**
 * @fn		bool CAT(MapEquals, CAT(K, V))(void* this, void* other);
 *
 * @brief	Checks if the type of the map is equal to another object
 *
 * @param	[in] this 
 * 			The map object
 * @param	[in] other
 * 			The other object
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool CAT(MapEquals, CAT(K, V))(void* this, void* other);

/**********************************************************************************************//**
 * @fn		int CAST(MapCompareTo, CAT(K, V))(void* this, void* other);
 *
 * @brief	Checks if the type of the map is equal to another object
 *
 * @param	[in] this 
 * 			The object
 * @param	[in] other
 * 			The other object
 *
 * @return	0 if it succeeds, negative or positive if it fails.
 **************************************************************************************************/

int CAT(MapCompareTo, CAT(K, V))(void* this, void* other);

/**********************************************************************************************//**
 * @fn		char* CAT(MapToString, CAT(K, V))(void* this);
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

char* CAT(MapToString, CAT(K, V))(void* this);

/**********************************************************************************************//**
 * @fn		bool CAT(MapAdd, CAT(K, V))(void* this, ENTRY entry);
 *
 * @brief	Does the same as MapPushBack
 *
 * @param	[in] this 
 * 			The map
 * @param	[in] item
 * 			The item (element of the map), not another <b>Map</b>
 **************************************************************************************************/

bool CAT(MapAdd, CAT(K, V))(void* this, ENTRY entry);

/**********************************************************************************************//**
 * @fn		void CAT(MapClear, CAT(K, V))(void* this);
 *
 * @brief	Clears the contents of the map
 * 			
 *			Maps the length to 0, 
 *			maps the capacity to @ref DEFAULT_MAP_CAPACITY,
 *			and zeros out the data
 *			
 * @param	[in] this 
 * 			The map
 * @return	Nothing
 **************************************************************************************************/

void CAT(MapClear, CAT(K, V))(void* this);

/**********************************************************************************************//**
 * @fn		bool MapRemove(void* this, void* item)
 *
 * @brief	Remove the submap in a map
 *			
 * @param	[in] this
 * 			The map
 * @param	[in] item
 * 			The item (element of the map), not another <b>Map</b>
 * @return	Returns true if the item was removed,
 * 			returns false if the item couldn't be found or removed
 * @note    Removes the all occurences of the item in the map
 * @note	Function will not resize the capacity. 
 * 			The overhead of free is most likely not worth resizing the capacity
 **************************************************************************************************/

bool CAT(MapRemove, CAT(K, V))(void* this, ENTRY entry);

/**********************************************************************************************//**
 * @fn		bool CAT(MapContains, CAT(K, V))(void* this, ENTRY entry);
 *
 * @brief	Remove the item in a map
 *			
 * @param	[in] this
 * 			The map
 * @param	[in] item
 * 			The item (element of the map), not another <b>Map</b>
 * @return	Returns true if the item was is in the map,
 * 			returns false if the item couldn't be found
 **************************************************************************************************/

bool CAT(MapContains, CAT(K, V))(void* this, ENTRY entry);

/**********************************************************************************************//**
 * @fn	void* CAT(MapCopy, CAT(K, V))(void* this);
 * @brief	Map's copy function
 * 			
 *			Returns a deep copy of the map
 *
 * @param	[in] this
 * 			Map to be used for copying
 * 			
 * @return	The copied map
 * @note	Calls copy constructor @ref MapCopyConstruct
 * @note    This is a <b>DEEP</b> copy, which will dynamically allocate memory
 * 			for the pBuf if the current map has dynamically allocated memory
 **************************************************************************************************/

void* CAT(MapCopy, CAT(K, V))(void* this);

/**********************************************************************************************//**
 * @fn		bool CAT(MapIsEmpty, CAT(K, V))(void* this);
 *
 * @brief	Checks if the map is empty
 *			
 * @param	[in] this
 * 			The map
 * @return	Returns true if the map is empty, 
 * 			returns false if the map is not empty
 **************************************************************************************************/

bool CAT(MapIsEmpty, CAT(K, V))(void* this);

/**********************************************************************************************//**
 * @fn		size_t CAT(MapSize, CAT(K, V))(void* this);
 *
 * @brief	Returns the number of elements in the map
 *			
 * @param	[in] this
 * 			The map
 * @return	Returns the length of the map
 * @note	Includes NULL terminator
 **************************************************************************************************/

size_t CAT(MapSize, CAT(K, V))(void* this);

/*============================================================================
|	Class member definitions
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	bool CAT(MapSet, CAT(K, V))(void* this, const ENTRY entry item, size_t num_elements);
 *
 * @brief	Maps the map to an array of elements
 *
 * @param	[in] this
 * 			The map
 * @param	[in] item
 * 			The item (element of the map), not another <b>Map</b>
 * @param	[in] num_elements
 * 			The number of elements to be placed
 * @note	Use initializer list macro for this
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool CAT(MapSet, CAT(K, V))(void* this, const ENTRY* entry, size_t num_elements);

/**********************************************************************************************//**
 * @fn	bool CAT(MapMoveInsert, CAT(K, V))(void* this, ENTRY entry)
 *
 * @brief	Inserts the item at the index in the map by moving the item.\n
 * 			Everything after the index will be shifted to the right
 * 			
 * @param	[in] this
 * 			The map
 * @param	[in] item
 * 			The item (element of the map), not another <b>Map</b>
 * @param	[in] index
 * 			The index to be index
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool CAT(MapMoveInsert, CAT(K, V))(void* this, ENTRY entry);

/**********************************************************************************************//**
 * @fn	bool CAT(MapInsert, CAT(K, V))(void* this, ENTRY entry);
 *
 * @brief	Inserts a copy of the item at the index in the map.\n
 * 			Everything after the index will be shifted to the right
 * 			
 * @param	[in] this
 * 			The map
 * @param	[in] item
 * 			The item (element of the map), not another <b>Map</b>
 * @param	[in] index
 * 			The index to be index
 *
 * @return	True if it succeeds, false if it fails.
 **************************************************************************************************/

bool CAT(MapInsert, CAT(K, V))(void* this, ENTRY entry);

/**********************************************************************************************//**
 * @fn	ENTRY* entry CAT(MapFind, CAT(K, V)) (void* this, ENTRY entry)
 *
 * @brief	Finds the index of the element in the map
 *
 * @param	[in] this
 * 			The map
 * @param	[in] item
 * 			The item (element of the map), not another <b>Map</b>
 *
 * @return	Index of the element. NPOS if none were found
 **************************************************************************************************/

ENTRY* CAT(MapFind, CAT(K, V)) (void* this, ENTRY entry);

/**********************************************************************************************//**
 * @fn	bool CAT(MapReplace, CAT(K, V))(void* this, T to_replace, T replacement);
 *
 * @brief	Replaces the elements with another element
 * 			Deallocates previous element, and allocates a copy of the replacement element
 * 			
 * @param	[in] this
 * 			The map
 * @param	[in] to_replace
 * 			The item (element of the map), not another <b>Map</b> to be replaced
 * @param	[in] replacement
 * 			The item (element of the map), not another <b>Map</b> that replaces the item
 *
 * @return	Index of the element. NPOS if none were found
 **************************************************************************************************/

bool CAT(MapReplace, CAT(K, V))(void* this, ENTRY to_replace, ENTRY replacement);

/**********************************************************************************************//**
 * @fn		StringIterator StringBegin(void* this)
 *
 * @brief   Returns an iterator starting at the beginning of a string
 *
 *			@param[in] this
 *			The object
 *			@return
 *			Returns a string iterator
 **************************************************************************************************/

CAT(CAT(Map, CAT(K, V)), Iterator) CAT(MapBegin, CAT(K, V))(void* this);

/**********************************************************************************************//**
 * @fn		bool StringNext(void* this, StringIterator* iterator)
 *
 * @brief   Advances string iterator
 *
 *			@param[in] this
 *			The object
 *			@return
 *			Returns a string iterator
 **************************************************************************************************/

bool CAT(MapNext, CAT(K, V))(void* this, CAT(CAT(Map, CAT(K, V)), Iterator) iterator);

/**********************************************************************************************//**
 * @fn		StringIterator StringEnd(void* this)
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

CAT(CAT(Map, CAT(K, V)), Iterator) CAT(MapEnd, CAT(K, V))(void* this, CAT(CAT(Map, CAT(K, V)), Iterator) iterator);

/*============================================================================
|   Container virtual function table instance
*===========================================================================*/

/**
* @brief   Global map vftable
* @relates MapVFTable
* @note	Cannot make this const since there is a circular reference with RTTI structs
* @note	containerVFTable will be map in constructor
*/

CAT(CAT(Map, CAT(K, V)), VFTable) CAT(CAT(Map, CAT(K, V)), vfTable);

/*============================================================================
|   Map class definition
*===========================================================================*/

#define DEFINE_MAPNODE                                         \
	typedef struct CAT(_MapNode, CAT(K, V))                     \
	{                                                          \
		ENTRY entry;                                           \
		struct CAT(_MapNode, CAT(K, V))* children[2];           \
		bool color;                                            \
	} *CAT(MapNode, CAT(K, V));                                 \

DEFINE_MAPNODE

int CAT(MapTest, CAT(K, V))(CAT(MapNode, CAT(K, V)) root, int indent);

/**********************************************************************************************//**
 * @def	DEFINE_MAP
 *
 * @brief	The map struct, which contains necessary fields for implementing a map\n See
 * 			@ref MapVFTable for avaliable map functions.\n
 * 			Class members\n
 * 			container\n
 * 			size\n
 *			capacity\n
 *			data\n
 **************************************************************************************************/

#define DEFINE_MAP                                             \
	typedef struct CAT(_Map, CAT(K, V))                         \
	{                                                          \
		struct _Container container;                           \
		size_t size;                                           \
		CAT(MapNode, CAT(K, V)) root;                           \
	} *CAT(Map, CAT(K, V));                                            \

DEFINE_MAP

/*============================================================================
|   RTTI (Have to declare in reverse order, so compiler knows that structs are defined already)
|   VFTable         <===============\
|   | CompleteObjectLocator         |
|       | Signature = "HEHE"        |
|       | TypeDescriptor            |
|           | pVFTable =============/   <===============\
|           | name = Class's name ("Map")            |
|       | ClassHierarchyDescriptor                      |
|           | attributes = 1 (VIRTUAL)                  |
|           | numBaseClasses = 2 (Container, Map)    |
|           | BaseClassArrayDescriptor                  |
|               [                                       |
|                   ContainerBaseClassDescriptor        |
|                       | numContainedClasses (1)       |
|                       | TypeDescriptor =====> Container's pVFTable
|                   MapBaseClassDescriptor           |
|                       | numContainedClasses (2)	    |
|                       | TypeDescriptor ===============/
|               ]
*===========================================================================*/

/**
* @brief	Global map type descriptor
*
* 			Contains the a pointer to the map vftable
* 			and the name of "Map" to indicate that this
* 			is the map class
*/

TypeDescriptor CAT(mapTypeDescriptor, CAT(K, V));

/**********************************************************************************************//**
 * @def	MapBaseClassDescriptor
 *
 * @brief	A macro that defines map base class descriptor.
 * 			
 *			Num contained classes is two since the map inherits from 
 *			container, which inherits from object.
 **************************************************************************************************/

#define MapBaseClassDescriptor(x)   				 	       \
		{												       \
			.numContainedClasses = 2,				 	       \
			.pTypeDescriptor = &CAT(mapTypeDescriptor, x)   \
		}												       \

 /**
 * @brief	Global map base class descriptor array
 *
 * 			Contains the container base descriptor and
 * 			its own base class descriptor (map base descriptor)
 */

BaseClassDescriptor CAT(mapBaseClassArray, CAT(K, V))[2];

/**
* @brief	Global map class hierarchy descriptor
*
* 			Map class hierarchy descriptor is marked as virtual
* 			since it inherits from the container class.
* 			numBaseClasses is one since container inherits from only one class
* 			pBaseClassArray points to the container's base class descriptor
*			@ref mapBaseClassArray
*/

ClassHierarchyDescriptor CAT(mapClassHierarchyDescriptor, CAT(K, V));

/**
* @brief	Global map complete object locator
*
* 			Contains the signature to indicate that this struct contains
* 			RTTI information.
* 			pTypeDescriptor points to the map's type descriptor
* 			pClassHierarchyDescriptor points to the map's class hierarchy descriptor
*/

CompleteObjectLocator CAT(mapCompleteObjectLocator, CAT(K, V));

/*============================================================================
|	Overridden member functions
*===========================================================================*/

/*============================================================================
|	Class member functions
*===========================================================================*/

#undef ENTRY

#endif
