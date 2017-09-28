/**
* @file ooc_map.h
* @brief HashMap class header
*
* HashMap class implementation\n
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

#include "template.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*============================================================================
|   Defines
*===========================================================================*/

/*============================================================================
|   HashMap virtual function table definition
*===========================================================================*/

/**********************************************************************************************//**
 * @def	DEFINE_HASH_MAP_VFTABLE
 *
 * @brief	Macro contain templated vftable of the map class
 * 			HashMap Methods\n
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
#define DEFINE_HASH_MAP_VFTABLE                                \
	typedef struct CAT(CAT(_HashMap, CAT(K, V)), VFTable)      \
	{                                                          \
		bool(*set)(void* this, K key, V value);                \
		const V*(*get)(void* this, K key);                     \
		bool(*delete)(void* this, K key);                      \
		float(*load)(void* this);                              \
	} CAT(CAT(HashMap, CAT(K, V)), VFTable);                   \

DEFINE_HASH_MAP_VFTABLE

/*============================================================================
|	Special class member function definitions
*===========================================================================*/

/*============================================================================
|	New Operator
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void* CAT(NewHashMap, CAT(K, V))(size_t size)
 * @brief	HashMap's new operator
 * 			
 *			Returns an allocated new map
 * 			
 * @return	An allocated map object or null if none could be allocated
 **************************************************************************************************/

void* CAT(NewHashMap, CAT(K, V))(size_t size);

/*============================================================================
|	Delete Operator
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(DeleteHashMap, CAT(K, V))(void* this);
 *
 * @brief	Deletes and frees a map's resources
 *
 * @param	[in] this
 * 			Object to be deleted
 * @return	Nothing
 **************************************************************************************************/

void CAT(DeleteHashMap, CAT(K, V))(void* this);

/*============================================================================
|	Constructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(HashMapConstruct, CAT(K, V))(void* this, size_t size);
 * @brief	HashMap's constructor
 * 			
 *			HashMapups the vftable by completing the RTTI dependency
 *			and memcpys the table into the object's vftable
 *
 * @param	[in] this
 * 			Object to be initialized
 * 			
 * @return	Nothing
 * @todo	{Find a way to not use memcpy for mapting up the vftable...}
 **************************************************************************************************/

void CAT(HashMapConstruct, CAT(K, V))(void* this, size_t size);

/*============================================================================
|	Destructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(HashMapDestruct, CAT(K, V))(void* this);
 * @brief	HashMap's destructor
 * 			
 *			Calls the super destructors and properly manages 
 *			the deletion of the map's allocated resources
 *
 * @param	[in] this
 * 			HashMap that should be freed of its used resources
 * 			
 * @return	Nothing
 **************************************************************************************************/

void CAT(HashMapDestruct, CAT(K, V))(void* this);

/*============================================================================
|	Class member definitions
*===========================================================================*/

/**********************************************************************************************//**
 * @fn		bool CAT(HashMapContains, CAT(K, V))(void* this, ENTRY entry);
 *
 * @brief	Remove the item in a map
 *			
 * @param	[in] this
 * 			The map
 * @param	[in] item
 * 			The item (element of the map), not another <b>HashMap</b>
 * @return	Returns true if the item was is in the map,
 * 			returns false if the item couldn't be found
 **************************************************************************************************/

bool CAT(HashMapSet, CAT(K, V))(void* this, K key, V value);

/**********************************************************************************************//**
 * @fn	void* CAT(HashMapCopy, CAT(K, V))(void* this);
 * @brief	HashMap's copy function
 * 			
 *			Returns a deep copy of the map
 *
 * @param	[in] this
 * 			HashMap to be used for copying
 * 			
 * @return	The copied map
 * @note	Calls copy constructor @ref HashMapCopyConstruct
 * @note    This is a <b>DEEP</b> copy, which will dynamically allocate memory
 * 			for the pBuf if the current map has dynamically allocated memory
 **************************************************************************************************/

const V* CAT(HashMapGet, CAT(K, V))(void* this, K key);

/**********************************************************************************************//**
 * @fn		bool CAT(HashMapIsEmpty, CAT(K, V))(void* this);
 *
 * @brief	Checks if the map is empty
 *			
 * @param	[in] this
 * 			The map
 * @return	Returns true if the map is empty, 
 * 			returns false if the map is not empty
 **************************************************************************************************/

bool CAT(HashMapDelete, CAT(K, V))(void* this, K key);

/**********************************************************************************************//**
 * @fn		size_t CAT(HashMapSize, CAT(K, V))(void* this);
 *
 * @brief	Returns the number of elements in the map
 *			
 * @param	[in] this
 * 			The map
 * @return	Returns the length of the map
 * @note	Includes NULL terminator
 **************************************************************************************************/

float CAT(HashMapLoad, CAT(K, V))(void* this);

/*============================================================================
|   HashMap class definition
*===========================================================================*/

#define DEFINE_HASH_MAPNODE                                         \
	typedef struct CAT(_HashMapNode, CAT(K, V))                     \
	{                                                          \
		K key;                                                 \
		V value;								    			\
		struct CAT(_HashMapNode, CAT(K, V))* next;             \
	} *CAT(HashMapNode, CAT(K, V));                                 \

DEFINE_HASH_MAPNODE

/**********************************************************************************************//**
 * @def	DEFINE_HASH_MAP
 *
 * @brief	The map struct, which contains necessary fields for implementing a map\n See
 * 			@ref HashMapVFTable for avaliable map functions.\n
 * 			Class members\n
 * 			container\n
 * 			size\n
 *			capacity\n
 *			data\n
 **************************************************************************************************/

#define DEFINE_HASH_MAP                                        \
	typedef struct CAT(_HashMap, CAT(K, V))                    \
	{                                                          \
		void* pVFTable;                                        \
		size_t current_size;                                   \
		size_t size;                                           \
		CAT(HashMapNode, CAT(K, V))* table;                    \
	} *CAT(HashMap, CAT(K, V));                                \

DEFINE_HASH_MAP

#undef ENTRY

#endif
