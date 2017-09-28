/**
* @file ooc_map.h
* @brief HashMap class header
*
* HashMap class implementation\n
*			
* @author Henry Zhu (Maknee)
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
 * @param	[in] size
 * 			the fixed size the hash map should be 
 *
 * @return	An allocated map
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
 *
 * @return	Nothing
 **************************************************************************************************/

void CAT(DeleteHashMap, CAT(K, V))(void* this);

/*============================================================================
|	Constructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(HashMapConstruct, CAT(K, V))(void* this, size_t size);
 * @brief	HashMap's constructor, intitializes member variables
 *
 * @param	[in] this
 * 			hash map to be initialized
 * 			
 * @param	[in] size
 * 			the fixed size the hash map should be 
 * @return	Nothing
 **************************************************************************************************/

void CAT(HashMapConstruct, CAT(K, V))(void* this, size_t size);

/*============================================================================
|	Destructor
*===========================================================================*/

/**********************************************************************************************//**
 * @fn	void CAT(HashMapDestruct, CAT(K, V))(void* this);
 * @brief	HashMap's destructor
 * 			
 *			Calls the destructor and properly manages 
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
 * @fn		bool CAT(HashMapSet, CAT(K, V))(void* this, K key, V value);
 *
 * @brief	Sets a key to a specific value in hash map. Could be replaced or added
 *			
 * @param	[in] this
 * 			The hash map
 * @param	[in] key
 *			key to be stored
 * @param	[in] value
 *			value to be stored
 * @return	Returns true if the item was added to the map,
 * 			returns false if the item could not be added
 **************************************************************************************************/

bool CAT(HashMapSet, CAT(K, V))(void* this, K key, V value);

/**********************************************************************************************//**
 * @fn		const V* CAT(HashMapGet, CAT(K, V))(void* this, K key);
 *
 * @brief	Gets the value if the key exists in the hashset
 *
 * @param	[in] this
 * 			the hash map
 * @param	[in] key
 *			key to be found
 * @return	A pointer to the const value, null if key does not exist
 **************************************************************************************************/

const V* CAT(HashMapGet, CAT(K, V))(void* this, K key);

/**********************************************************************************************//**
 * @fn		bool CAT(HashMapDelete, CAT(K, V))(void* this, K key);
 *
 * @brief	Deletes a key/value pair from the hash map if key was found
 *			
 * @param	[in] this
 * 			The map
 * @param	[in] key
 *			key to be found
 * @return	Returns true if the key/value was deleted
 * 			returns false if the key was not found
 **************************************************************************************************/

bool CAT(HashMapDelete, CAT(K, V))(void* this, K key);

/**********************************************************************************************//**
 * @fn		float CAT(HashMapLoad, CAT(K, V))(void* this);
 *
 * @brief	Returns the load on the hashmap
 *			
 * @param	[in] this
 * 			The map
 *
 * @return	Returns a float (load)
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

#endif
