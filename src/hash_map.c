#if defined(K) && defined(V)

#include "template.h"

#define DEBUG_PRINT(fmt, ...)                                   \
        do { fprintf(stderr, "%s : %d : %s(): " fmt, __FILE__,  \
                                __LINE__, __func__, __VA_ARGS__); } while (0)

#define CHECK_NULL(ptr, return_type)                            \
		if (!ptr)                                               \
		{                                                       \
			DEBUG_PRINT("%s\n", "Error! " #ptr " is NULL");     \
			return return_type;                                 \
		}                                                       \

#define CHECK_NULL_NO_RET(ptr)                                  \
		if (!ptr)                                               \
		{                                                       \
			DEBUG_PRINT("%s\n", "Error! " #ptr " is NULL");     \
			return;                                             \
		}                                                       \

//can't define this as HashMap since name collision
#define HASHMAP CAT(HashMap, CAT(K, V))
#define HASHMAPNODE CAT(HashMapNode, CAT(K, V))

#define HashMapVFTable CAT(HASHMAP, VFTable)
#define hashMapVFTable CAT(CAT(HashMap, CAT(K, V)), vfTable)

#define ENTRY CAT(Entry, CAT(K, V))

HashMapVFTable hashMapVFTable =
{
	.set = CAT(HashMapSet, CAT(K, V)),
	.get = CAT(HashMapGet, CAT(K, V)),
	.delete = CAT(HashMapDelete, CAT(K, V)),
	.load = CAT(HashMapLoad, CAT(K, V))
};

/*============================================================================
|	Helper functions
*===========================================================================*/

static HASHMAPNODE CAT(HashMapNewNode, CAT(K, V))(K key, V value)
{
	HASHMAPNODE new_node = calloc(1, sizeof(struct CAT(_HashMapNode, CAT(K, V))));

	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;

	return new_node;
}

#define NewNode(key, value) CAT(HashMapNewNode, CAT(K, V))(key, value)

static HASHMAPNODE CAT(HashMapDeleteNode, CAT(K, V))(HASHMAPNODE node)
{
	HASHMAPNODE next = node->next;

	K_DELETE(node->key);
	V_DELETE(node->value);
	free(node);

	return next;
}

#define DeleteNode(node) CAT(HashMapDeleteNode, CAT(K, V))(node)

static void CAT(HashMapClear, CAT(K, V))(void* this)
{
	CHECK_NULL_NO_RET(this);

	//cast to hash_map
	HASHMAP this_hash_map = (HASHMAP)this;

	for (size_t i = 0; i < this_hash_map->size; i++)
	{
		//get the next node in the table
		HASHMAPNODE node = this_hash_map->table[i];

		//check if the node is null, if so move on
		if (node == NULL)
			continue;

		//if not, iterate through the chain and remove every node
		while (node->next != NULL)
		{
			HASHMAPNODE temp = node;
			node = node->next;
			K_DELETE(temp->key);
			V_DELETE(temp->value);
			free(temp);
			temp = NULL;
		}
	}
}

#define ClearTable(this) CAT(HashMapClear, CAT(K, V))(this)

/*============================================================================
|	New Operator
*===========================================================================*/

void* CAT(NewHashMap, CAT(K, V))(size_t size)
{
	//allocate a new hash_map
	void* this = calloc(1, sizeof(struct CAT(_HashMap, CAT(K, V))));

	//cast to hash_map
	HASHMAP this_hash_map = (HASHMAP)this;

	//make vftable point to the right vftable
	this_hash_map->pVFTable = (void*)&hashMapVFTable;

	//call constructor to hash_map up string
	CAT(HashMapConstruct, CAT(K, V))(this, size);

	return this;
}

/*============================================================================
|	Delete Operator
*===========================================================================*/

void CAT(DeleteHashMap, CAT(K, V))(void* this)
{
	CHECK_NULL_NO_RET(this);

	//cast to hash_map
	HASHMAP this_hash_map = (HASHMAP)this;

	//call destructor
	CAT(HashMapDestruct, CAT(K, V))(this);

	//null the (casted) vftable
	this_hash_map->pVFTable = NULL;

	//free the string's resources
	free(this);
}

/*============================================================================
|	Constructor
*===========================================================================*/

void CAT(HashMapConstruct, CAT(K, V))(void* this, size_t size)
{
	CHECK_NULL_NO_RET(this);
	
	//cast to hash_map
	HASHMAP this_hash_map = (HASHMAP)this;
	
	//Initialize member variables
	//==========================

	this_hash_map->current_size = 0;

	//hash_map size
	this_hash_map->size = size;

	//initialize table
	this_hash_map->table = calloc(1, sizeof(HASHMAPNODE) * size);
}

/*============================================================================
|	Destructor
*===========================================================================*/

void CAT(HashMapDestruct, CAT(K, V))(void* this)
{
	CHECK_NULL_NO_RET(this);

	//clear the tables
	ClearTable(this);
}

bool CAT(HashMapSet, CAT(K, V))(void* this, K key, V value)
{
	CHECK_NULL(this, false);

	//cast to hash map
	HASHMAP this_hash_map = (HASHMAP)this;

	//get the hash index of key
	size_t hash_index = HASH_FUNCTION(key) % this_hash_map->size;

	//get the node at the index of the table
	HASHMAPNODE node = this_hash_map->table[hash_index];

	//(Collision) if a node exists already, replace a node with the same key or append to end of chain
	if (node)
	{
		//check if we need to replace the node because the node exists already
		HASHMAPNODE prev = NULL;

		do
		{
			//replace if they are equal
			if (K_EQUAL(key, node->key))
			{
				//move the key and value into the new node
				HASHMAPNODE new_node = NewNode(key, value);

				//link the previous to the current if not null
				if (prev != NULL)
				{
					prev->next = new_node;
				}
				//if prev is null, we know that this node is replacing the first node in the index of the table
				else
				{
					this_hash_map->table[hash_index] = new_node;
				}

				//link the new node with the next node
				new_node->next = node->next;

				//delete the current node
				DeleteNode(node);

				return true;
			}
			//we did not encounter them being equal
			else
			{
				//update prev and move onto the next
				prev = node;
				node = node->next;
			}
		} while (node && node->next != NULL);

		//if we haven't replaced a node, add the new node to the end of the chain and check if limit has been succeeded
		if (this_hash_map->current_size != this_hash_map->size)
		{
			//move the key and value into the new node
			HASHMAPNODE new_node = NewNode(key, value);

			node->next = new_node;

			//increase size
			this_hash_map->current_size++;

			return true;
		}
	}

	//check if we are at limit
	if (this_hash_map->current_size == this_hash_map->size)
	{
		return false;
	}

	//move the key and value into the new node
	HASHMAPNODE new_node = NewNode(key, value);

	//No collision, expected O(1) insertion :)
	this_hash_map->table[hash_index] = new_node;
	
	//increase size
	this_hash_map->current_size++;

	return true;
}

const V* CAT(HashMapGet, CAT(K, V))(void* this, K key)
{
	CHECK_NULL(this, NULL);

	//cast to hash map
	HASHMAP this_hash_map = (HASHMAP)this;

	//get the hash index of key
	size_t hash_index = HASH_FUNCTION(key) % this_hash_map->size;

	//get the node at the index of the table
	HASHMAPNODE node = this_hash_map->table[hash_index];

	//if a node exists already, search through chain for key
	if (node)
	{
		do
		{
			//check if the current key is equal
			if (K_EQUAL(key, node->key))
			{
				//found the value
				return &node->value;
			}
			//we did not encounter them being equal
			else
			{
				//move onto next
				node = node->next;
			}
		} while (node->next != NULL);
	}

	//No node, return null
	return NULL;
}

bool CAT(HashMapDelete, CAT(K, V))(void* this, K key)
{
	CHECK_NULL(this, false);

	//cast to hash map
	HASHMAP this_hash_map = (HASHMAP)this;

	//get the hash index of key
	size_t hash_index = HASH_FUNCTION(key) % this_hash_map->size;

	//get the node at the index of the table
	HASHMAPNODE node = this_hash_map->table[hash_index];

	//if a node exists already, search through chain with node that has the same key
	if (node)
	{
		//check if we need to replace the node because the node exists already
		HASHMAPNODE prev = NULL;

		do
		{
			//replace if they are equal
			if (K_EQUAL(key, node->key))
			{
				//link the previous to next node if not null
				if (prev != NULL)
				{
					prev->next = node->next;
				}
				
				//decrease the current size
				this_hash_map->current_size--;

				//delete the current node
				DeleteNode(node);

				return true;
			}
			//we did not encounter key being equal
			else
			{
				//update prev and move onto the next
				prev = node;
				node = node->next;
			}
		} while (node->next != NULL);
	}
	
	//Could not find the node to delete
	return false;
}

float CAT(HashMapLoad, CAT(K, V))(void* this)
{
	CHECK_NULL(this, 0.0f);

	//cast to hash map
	HASHMAP this_hash_map = (HASHMAP)this;

	//return load factor
	return (float)this_hash_map->current_size / (float)this_hash_map->size;
}

/*============================================================================
|	Class member definitions
*===========================================================================*/

#undef NewNode
#undef DeleteNode
#undef ClearTable

#undef HASHMAP
#undef HASHMAPNODE

#undef HashMapVFTable
#undef hashMapVFTable

#endif
