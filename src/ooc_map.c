#if defined(K) && defined(V)

#include "template.h"

//can't define this as Map since name collision
#define MAP CAT(Map, CAT(K, V))
#define MAPNODE CAT(MapNode, CAT(K, V))

#define MapVFTable CAT(MAP, VFTable)
#define mapVFTable CAT(CAT(Map, CAT(K, V)), vfTable)

#define ENTRY CAT(Entry, CAT(K, V))

MapVFTable mapVFTable =
{
	NULL_OBJECT_VFTABLE,
	.add = NULL,
	.clear = NULL,
	.remove = NULL,
	.contains = NULL,
	.copy = NULL,
	.isEmpty = NULL,
	.size = NULL,
	.set = NULL,
	.insert = NULL,
	.find = NULL,
	.replace = NULL
};

TypeDescriptor CAT(mapTypeDescriptor, CAT(K, V)) =
{
	.pVFTable = &mapVFTable,
	//necessary for checking type Upcast macro (can't print pretty)
	.name = STRINGIFY(MAP)
	//print pretty vvvv
	//.name = STRINGIFY(Map(CAT(K, V)))
};

BaseClassDescriptor CAT(mapBaseClassArray, CAT(K, V))[] =
{
	ContainerBaseClassDescriptor,
	MapBaseClassDescriptor(CAT(K, V))
};

ClassHierarchyDescriptor CAT(mapClassHierarchyDescriptor, CAT(K, V)) =
{
	.attributes = CLASS_HIERARCHY_VIRTUAL_INHERITENCE,
	.numBaseClasses = 2,
	.pBaseClassArray = CAT(mapBaseClassArray, CAT(K, V))
};

CompleteObjectLocator CAT(mapCompleteObjectLocator, CAT(K, V)) =
{
	.signature = 0x48454845,
	.pTypeDescriptor = &CAT(mapTypeDescriptor, CAT(K, V)),
	.pClassHierarchyDescriptor = &CAT(mapClassHierarchyDescriptor, CAT(K, V))
};


/*============================================================================
|	Helper functions
*===========================================================================*/

static int CAT(MapIsRed, CAT(K, V))(MAPNODE node)
{
	return (node != NULL && node->color) ? (RED) : (BLACK);
}

#define IsRed(node) CAT(MapIsRed, CAT(K, V))(node)

/*============================================================================
|	Example Rotate left
|	   1
|     2 4
|      3 5
|
| first line
|	   1 <--- old root
|     2 4 <--- new root
|      3 5
|
| second line
|	   1 <--- old root
|     2 3            4 <--- new root
|                     5
|
| third line
|	   4 <--- new root
|     1 5
|    2 3
|*===========================================================================*/

static MAPNODE CAT(MapSingleRotate, CAT(K, V))(MAPNODE root, int direction)
{
	//get the opposite node
	MAPNODE new_root = root->children[!direction];

	//switch over opposite node's child as old root's child
	root->children[!direction] = new_root->children[direction];

	//update the new root to map the old root as its child
	new_root->children[direction] = root;

	//update the colors, so the tree is valid
	root->color = RED;
	new_root->color = BLACK;

	return new_root;
}

#define SingleRotate(root, direction) CAT(MapSingleRotate, CAT(K, V))(root, direction)

/*============================================================================
|	Example Double rotate left
|	                     5 <--- old root
|	                    / \
|                      3   7
|	                  / \ / \
|	                 2  4 6  9
|                           / \
|                          8   10
|
| first line
|	                     5
|	                    / \
|                      3   7 <--- current root
|	                  / \ / \
|	                 2  4 6  9
|                           / \
|                          8   10
|
|	                     5 <---old root maps new current root to be its child
|	                    / \
|                      3   6 <--- new current root
|	                  / \   \
|	                 2   4   7
|                             \
|                              9
|                             / \
|                            8   10
|
| second line
|                          6 <--- new current root
|	                      / \
|	       old root ---> 5   7
|                       /     \
|                      3       9
|                     / \     / \
|                    2   4   8   10
|*===========================================================================*/

static MAPNODE CAT(MapDoubleRotate, CAT(K, V))(MAPNODE root, int direction)
{
	//opposite rotate child?
	root->children[!direction] = SingleRotate(root->children[!direction], !direction);

	//rotate root
	return SingleRotate(root, direction);
}

#define DoubleRotate(root, direction) CAT(MapDoubleRotate, CAT(K, V))(root, direction)

static MAPNODE CAT(MapNewMoveNode, CAT(K, V))(ENTRY entry)
{
	MAPNODE new_node = check_calloc(sizeof(struct CAT(_MapNode, CAT(K, V))));

	new_node->entry = entry;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	new_node->color = RED;

	return new_node;
}

#define NewMoveNode(entry) CAT(MapNewMoveNode, CAT(K, V))(entry)

static MAPNODE CAT(MapNewNode, CAT(K, V))(ENTRY entry)
{
	MAPNODE new_node = check_calloc(sizeof(struct CAT(_MapNode, CAT(K, V))));

	new_node->entry = entry;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	new_node->color = RED;

	return new_node;
}

#define NewNode(entry) CAT(MapNewNode, CAT(K, V))(entry)

static MAPNODE CAT(MapCopyNode, CAT(K, V))(MAPNODE node)
{
	MAPNODE new_node = check_calloc(sizeof(struct CAT(_MapNode, CAT(K, V))));

	new_node->entry = Call(ENTRY, copy, node->entry);
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	new_node->color = node->color;

	return new_node;
}

#define CopyNode(node) CAT(MapCopyNode, CAT(K, V))(node)

/*
int CAT(MapTest, CAT(K, V))(CAT(MapNode, CAT(K, V)) root, int indent)
{
	if (root == NULL)
	{
		return 1;
	}
	else
	{
		MAPNODE left = root->children[LEFT];
		MAPNODE right = root->children[RIGHT];

		if (IsRed(root))
		{
			if (IsRed(left) || IsRed(right))
			{
				puts("RED VIOLATION");
				return 0;
			}
		}

		if ((left != NULL && T_COMPARE_TO(left->data, root->data) >= 0) || (right != NULL && T_COMPARE_TO(right->data, root->data) <= 0))
		{
			puts("BINARY TREE VIOLATION");
			return 0;
		}

		int right_height = CAT(MapTest, CAT(K, V))(right, indent + 4);

		for (int i = 0; i < indent; i++)
		{
			printf(" ");
		}
		if (right)
		{
			printf(" /\n");
			for (int i = 0; i < indent; i++)
			{
				printf(" ");
			}
		}

		//print root
		//printf("%d\n", root->data);

		if (left)
		{
			for (int i = 0; i < indent; i++)
			{
				printf(" ");
			}
			printf(" \\\n");
		}

		int left_height = CAT(MapTest, CAT(K, V))(left, indent + 4);

		if (left_height != 0 && right_height != 0 && left_height != right_height)
		{
			puts("BLACK VIOLATION");
			return 0;
		}

		if (left_height != 0 && right_height != 0)
		{
			return IsRed(root) ? left_height : left_height + 1;
		}
		else
		{
			return 0;
		}
	}
}
*/


/*============================================================================
|	New Operator
*===========================================================================*/

void* CAT(NewMap, CAT(K, V))()
{
	//allocate a new map
	void* this = check_calloc(sizeof(struct CAT(_Map, CAT(K, V))));

	//cast to map
	MAP this_map = (MAP)this;

	//allocate vftable
	this_map->container.object.pVFTable = check_calloc(sizeof(MapVFTable));

	//call constructor to map up string
	CAT(MapConstruct, CAT(K, V))(this);

	return this;
}

/*============================================================================
|	Delete Operator
*===========================================================================*/

void CAT(DeleteMap, CAT(K, V))(void* this)
{
	CHECK_NULL_NO_RET(this);

	//cast to map
	MAP this_map = (MAP)this;

	//call destructor
	CAT(MapDestruct, CAT(K, V))(this);

	//null the (casted) vftable
	this_map->container.object.pVFTable = NULL;

	//free vftable
	free(this_map->container.object.objectpVFTable);

	//free the string's resources
	free(this);
}

/*============================================================================
|	Constructor
*===========================================================================*/

void CAT(MapConstruct, CAT(K, V))(void* this)
{
	CHECK_NULL_NO_RET(this);

	//call super class's constructor (ObjectConstruct)
	ContainerConstruct(this);

	//Override Object's methods
	//=========================

	//Map the vtable's complete object locator to complete the RTTI circle
	mapVFTable.pCompleteObjectLocator = &CAT(mapCompleteObjectLocator, CAT(K, V));

	//Map the equals function
	mapVFTable.equals = &CAT(MapEquals, CAT(K, V));

	//Map the compareTo function
	mapVFTable.compareTo = &CAT(MapCompareTo, CAT(K, V));

	//Map the toString
	mapVFTable.toString = &CAT(MapToString, CAT(K, V));

	//Override Container's methods
	//==========================
	
	mapVFTable.add = &CAT(MapAdd, CAT(K, V));
	mapVFTable.clear = &CAT(MapClear, CAT(K, V));
	mapVFTable.remove = &CAT(MapRemove, CAT(K, V));
	mapVFTable.contains = &CAT(MapContains, CAT(K, V));
	mapVFTable.copy = &CAT(MapCopy, CAT(K, V));
	mapVFTable.isEmpty = &CAT(MapIsEmpty, CAT(K, V));
	mapVFTable.size = &CAT(MapSize, CAT(K, V));
	
	//Initialize class member methods
	//==========================

	mapVFTable.set = &CAT(MapSet, CAT(K, V));
	mapVFTable.move_insert = &CAT(MapMoveInsert, CAT(K, V));
	mapVFTable.insert = &CAT(MapInsert, CAT(K, V));
	mapVFTable.find = &CAT(MapFind, CAT(K, V));
	mapVFTable.replace = &CAT(MapReplace, CAT(K, V));
	mapVFTable.begin = &CAT(MapBegin, CAT(K, V));
	mapVFTable.next = &CAT(MapNext, CAT(K, V));
	mapVFTable.end = &CAT(MapEnd, CAT(K, V));

	//cast to map
	MAP this_map = (MAP)this;

	//Initialize the vtable to a copy of this object's vtable
	memcpy(this_map->container.object.pVFTable, &mapVFTable, sizeof(MapVFTable));

	//Make the objectpVFTable point to the same table initially
	this_map->container.object.objectpVFTable = this_map->container.object.pVFTable;

	//Initialize member variables

	//map size
	this_map->size = 0;

	//map root to NULL
	this_map->root = NULL;
}

/*============================================================================
|	Copy Constructor
*===========================================================================*/

static MAPNODE CAT(MapCopyHelper, CAT(K, V))(MAPNODE node, MAPNODE copy_node)
{
	if (node != NULL)
	{
		copy_node = CopyNode(node);
		copy_node->children[LEFT] = CAT(MapCopyHelper, CAT(K, V))(node->children[LEFT], copy_node->children[LEFT]);
		copy_node->children[RIGHT] = CAT(MapCopyHelper, CAT(K, V))(node->children[RIGHT], copy_node->children[RIGHT]);
		return copy_node;
	}
	return NULL;
}

void* CAT(MapCopyConstruct, CAT(K, V))(void* this)
{
	CHECK_NULL(this, NULL);

	//cast to map
	MAP this_map = (MAP)this;

	//allocate a new map
	void* copy = CAT(NewMap, CAT(K, V))();

	//cast to map
	MAP copy_map = (MAP)copy;

	//copy the contents of the string to the copied map except for vftable (which is contained in Container struct inside the String struct)
	copy_map->size = this_map->size;

	//copy tree
	copy_map->root = CAT(MapCopyHelper, CAT(K, V))(this_map->root, copy_map->root);

	return copy;
}

/*============================================================================
|	Destructor
*===========================================================================*/

void CAT(MapDestruct, CAT(K, V))(void* this)
{
	CHECK_NULL_NO_RET(this);

	//call super destructor
	ContainerDestruct(this);

	//call clear
	CAT(MapClear, CAT(K, V))(this);
}

/*============================================================================
|	Overridden member function definitions
*===========================================================================*/

static bool CAT(MapEqualsHelper, CAT(K, V))(MAPNODE node1, MAPNODE node2)
{
	//if either are null, quit
	if (node1 == NULL && node2 == NULL)
	{
		return true;
	}

	return (Call(ENTRY, equals, node1->entry, node2->entry) &&
		CAT(MapEqualsHelper, CAT(K, V))(node1->children[LEFT], node2->children[LEFT]) &&
		CAT(MapEqualsHelper, CAT(K, V))(node1->children[RIGHT], node2->children[RIGHT]));
}

bool CAT(MapEquals, CAT(K, V))(void* this, void* other)
{
	CHECK_NULL(this, false);
	CHECK_NULL(other, false);
	
	//cast to map
	MAP this_map = (MAP)this;

	//cast to map
	MAP other_map = (MAP)other;

	//Check if the sizes are the same
	if (this_map->size != other_map->size)
	{
		return false;
	}

	return CAT(MapEqualsHelper, CAT(K, V))(this_map->root, other_map->root);
}

static int CAT(MapCompareToHelper, CAT(K, V))(MAPNODE node1, MAPNODE node2)
{
	//if either are null, quit
	if (node1 == NULL && node2 == NULL)
	{
		return 0;
	}

	return (Call(ENTRY, compareTo, node1->entry, node2->entry) &&
		CAT(MapEqualsHelper, CAT(K, V))(node1->children[LEFT], node2->children[LEFT]) &&
		CAT(MapEqualsHelper, CAT(K, V))(node1->children[RIGHT], node2->children[RIGHT]));
}

int CAT(MapCompareTo, CAT(K, V))(void* this, void* other)
{
	CHECK_NULL(this, false);
	CHECK_NULL(other, false);

	//cast to map
	MAP this_map = (MAP)this;

	//cast to map
	MAP other_map = (MAP)other;

	//Check if the sizes are the same
	if (this_map->size != other_map->size)
	{
		//should work?
		return (int)this_map->size - (int)other_map->size;
	}

	return CAT(MapCompareToHelper, CAT(K, V))(this_map->root, other_map->root);
}

char* CAT(MapToString, CAT(K, V))(void* this)
{
	CHECK_NULL(this, NULL);

	return ContainerToString(this);
}

bool CAT(MapAdd, CAT(K, V))(void* this, ENTRY entry)
{
	return CAT(MapInsert, CAT(K, V))(this, entry);
}

void CAT(MapClear, CAT(K, V))(void* this)
{
	CHECK_NULL_NO_RET(this);

	//cast to map
	MAP this_map = (MAP)this;
	this_map->size = 0;

	MAPNODE node = this_map->root;
	MAPNODE save = NULL;

	while (node != NULL)
	{
		if (node->children[LEFT] == NULL)
		{
			//destroy and move to right
			save = node->children[RIGHT];
			Delete(ENTRY, node->entry);
			free(node);
			node = NULL;
		}
		else
		{
			//rotate to right
			save = node->children[LEFT];
			node->children[LEFT] = save->children[RIGHT];
			save->children[RIGHT] = node;
		}

		node = save;
	}
	this_map->root = NULL;
}

bool CAT(MapRemove, CAT(K, V))(void* this, ENTRY entry)
{
	CHECK_NULL(this, false);

	MAP this_map = (MAP)this;

	if (this_map->root == NULL)
	{
		return false;
	}

	//imaginary parent's root
	struct CAT(_MapNode, CAT(K, V)) parent_root = { .entry = NULL, .children = { NULL, NULL }, .color = BLACK };
	parent_root.children[RIGHT] = this_map->root;

	MAPNODE grandparent = NULL;
	MAPNODE parent = NULL;
	MAPNODE current_node = &parent_root;
	MAPNODE found_node = NULL;

	int direction = RIGHT;
	int last_direction = 0;

	while (current_node->children[direction] != NULL)
	{
		//update
		last_direction = direction;

		grandparent = parent;
		parent = current_node;
		current_node = current_node->children[direction];
		
		direction = Call(ENTRY, compareTo, current_node->entry, entry) < 0;

		if (Call(ENTRY, equals, current_node->entry, entry))
		{
			found_node = current_node;
		}

		if (!IsRed(current_node) && !IsRed(current_node->children[direction]))
		{
			if (IsRed(current_node->children[!direction]))
			{
				parent = parent->children[last_direction] = SingleRotate(current_node, direction);
			}
			else if (!IsRed(current_node->children[!direction]))
			{
				MAPNODE other = parent->children[!last_direction];

				if (other != NULL)
				{
					if (!IsRed(other->children[!last_direction]) && !IsRed(other->children[last_direction]))
					{
						parent->color = BLACK;
						other->color = RED;
						current_node->color = RED;
					}
					else
					{
						int is_violation_on_right = grandparent->children[RIGHT] == parent;

						if (IsRed(other->children[last_direction]))
						{
							grandparent->children[is_violation_on_right] = DoubleRotate(parent, last_direction);
						}
						else if (IsRed(other->children[!last_direction]))
						{
							grandparent->children[is_violation_on_right] = SingleRotate(parent, last_direction);
						}

						current_node->color = grandparent->children[is_violation_on_right]->color = RED;
						grandparent->children[is_violation_on_right]->children[LEFT]->color = BLACK;
						grandparent->children[is_violation_on_right]->children[RIGHT]->color = BLACK;
					}
				}
			}
		}
	}

	if (found_node != NULL)
	{
		Delete(ENTRY, found_node->entry);
		found_node->entry = current_node->entry;
		parent->children[parent->children[RIGHT] == current_node] = current_node->children[current_node->children[LEFT] == NULL];
		free(current_node);
	}

	this_map->root = parent_root.children[RIGHT];

	if (this_map->root != NULL)
	{
		this_map->root->color = BLACK;
	}

	this_map->size--;

	return true;
}

bool CAT(MapContains, CAT(K, V))(void* this, ENTRY entry)
{
	CHECK_NULL(this, false);

	MAP this_map = (MAP)this;

	if (this_map->root == NULL)
	{
		//empty tree
		return false;
	}
	else
	{
		MAPNODE current_node = this_map->root;
		
		int direction = 0;

		while (current_node != NULL)
		{	
			//if data is equal, then we stop
			if (Call(ENTRY, equals, current_node->entry, entry))
			{
				return true;
			}

			direction = Call(ENTRY, compareTo, current_node->entry, entry) < 0;
			current_node = current_node->children[direction];
		}
	}

	return false;
}

void* CAT(MapCopy, CAT(K, V))(void* this)
{
	CHECK_NULL(this, NULL);

	return CAT(MapCopyConstruct, CAT(K, V))(this);
}

bool CAT(MapIsEmpty, CAT(K, V))(void* this)
{
	CHECK_NULL(this, false);

	//cast to map
	MAP this_map = (MAP)this;

	return this_map->size == 0;
}

size_t CAT(MapSize, CAT(K, V))(void* this)
{
	CHECK_NULL(this, false);

	//cast to map
	MAP this_map = (MAP)this;

	return this_map->size;
}

bool CAT(MapSet, CAT(K, V))(void* this, const ENTRY* entry, size_t num_elements)
{
	CHECK_NULL(this, false);

	//clear the map
	CAT(MapClear, CAT(K, V))(this);

	//insert entrys
	//loop until null
	for (size_t i = 0; i < num_elements; i++)
	{
		CAT(MapMoveInsert, CAT(K, V))(this, entry[i]);
	}
	
	return true;
}

bool CAT(MapMoveInsert, CAT(K, V))(void* this, ENTRY entry)
{
	CHECK_NULL(this, false);

	MAP this_map = (MAP)this;

	//check if we need to update size
	bool inserted_node = false;

	if (this_map->root == NULL)
	{
		//empty tree
		this_map->root = NewMoveNode(entry);

		inserted_node = true;
	}
	else
	{
		//imaginary parent's root
		struct CAT(_MapNode, CAT(K, V)) parent_root = { .entry = NULL, .children = { NULL, NULL }, .color = BLACK };
		parent_root.children[RIGHT] = this_map->root;

		MAPNODE greatgrandparent = &parent_root;
		MAPNODE grandparent = NULL;
		MAPNODE parent = NULL;
		MAPNODE current_node = this_map->root;
		
		int direction = 0;
		int last_direction = 0;

		while (true)
		{
			//case when we reach a NULL, we insert entry
			if (current_node == NULL)
			{
				parent->children[direction] = current_node = NewMoveNode(entry);

				inserted_node = true;
			}

			//color flip parent and children
			if (IsRed(current_node->children[LEFT]) && IsRed(current_node->children[RIGHT]))
			{
				current_node->color = RED;
				current_node->children[LEFT]->color = BLACK;
				current_node->children[RIGHT]->color = BLACK;
			}

			//other red violation
			if (IsRed(parent) && IsRed(current_node))
			{
				//check which side the violation is on
				int is_violiation_on_right = (greatgrandparent->children[RIGHT] == grandparent);

				//check if single or double rotate
				if (parent->children[last_direction] == current_node)
				{
					greatgrandparent->children[is_violiation_on_right] = SingleRotate(grandparent, !last_direction);
				}
				else
				{
					greatgrandparent->children[is_violiation_on_right] = DoubleRotate(grandparent, !last_direction);
				}
			}

			//if data is equal, then we stop
			if (Call(ENTRY, equals, current_node->entry, entry))
			{
				if (!inserted_node)
				{
					//replace node with moved entry
					Delete(ENTRY, current_node->entry);
					current_node->entry = entry;
				}

				break;
			}

			//move on to next node
			last_direction = direction;
			direction = Call(ENTRY, compareTo, current_node->entry, entry) < 0;

			if (grandparent != NULL)
			{
				greatgrandparent = grandparent;
			}

			grandparent = parent;
			parent = current_node;
			current_node = current_node->children[direction];
		}

		//update root
		this_map->root = parent_root.children[RIGHT];
	}

	//make root black
	this_map->root->color = BLACK;
	if (inserted_node)
	{
		this_map->size++;
	}

	return true;
}

bool CAT(MapInsert, CAT(K, V))(void* this, ENTRY entry)
{
	CHECK_NULL(this, false);

	MAP this_map = (MAP)this;

	//check if we need to update size
	bool inserted_node = false;

	if (this_map->root == NULL)
	{
		//empty tree
		this_map->root = NewNode(entry);

		inserted_node = true;
	}
	else
	{
		//imaginary parent's root
		struct CAT(_MapNode, CAT(K, V)) parent_root = { .entry = NULL, .children = { NULL, NULL }, .color = BLACK };
		parent_root.children[RIGHT] = this_map->root;

		MAPNODE greatgrandparent = &parent_root;
		MAPNODE grandparent = NULL;
		MAPNODE parent = NULL;
		MAPNODE current_node = this_map->root;

		int direction = 0;
		int last_direction = 0;

		while (true)
		{
			//case when we reach a NULL, we insert entry
			if (current_node == NULL)
			{
				parent->children[direction] = current_node = NewNode(entry);

				inserted_node = true;
			}

			//color flip parent and children
			if (IsRed(current_node->children[LEFT]) && IsRed(current_node->children[RIGHT]))
			{
				current_node->color = RED;
				current_node->children[LEFT]->color = BLACK;
				current_node->children[RIGHT]->color = BLACK;
			}

			//other red violoation
			if (IsRed(parent) && IsRed(current_node))
			{
				//check which side the violation is on
				int is_violiation_on_right = (greatgrandparent->children[RIGHT] == grandparent);

				//check if single or double rotate
				if (parent->children[last_direction] == current_node)
				{
					greatgrandparent->children[is_violiation_on_right] = SingleRotate(grandparent, !last_direction);
				}
				else
				{
					greatgrandparent->children[is_violiation_on_right] = DoubleRotate(grandparent, !last_direction);
				}
			}

			//if data is equal, then we stop
			if (Call(ENTRY, equals, current_node->entry, entry))
			{
				if (!inserted_node)
				{
					//replace node with moved entry
					current_node->entry = Call(ENTRY, copy, entry);
				}

				break;
			}

			//move on to next node
			last_direction = direction;
			direction = Call(ENTRY, compareTo, current_node->entry, entry) < 0;

			if (grandparent != NULL)
			{
				greatgrandparent = grandparent;
			}

			grandparent = parent;
			parent = current_node;
			current_node = current_node->children[direction];
		}

		//update root
		this_map->root = parent_root.children[RIGHT];
	}

	//make root black
	this_map->root->color = BLACK;
	if (inserted_node)
	{
		this_map->size++;
	}

	return true;
}

ENTRY CAT(MapFind, CAT(K, V)) (void* this, ENTRY entry)
{
	CHECK_NULL(this, NULL);

	MAP this_map = (MAP)this;

	if (this_map->root == NULL)
	{
		//empty tree
		return NULL;
	}
	else
	{
		MAPNODE current_node = this_map->root;

		int direction = 0;

		while (current_node != NULL)
		{
			//if data is equal, then we stop
			if (Call(ENTRY, equals, current_node->entry, entry))
			{
				return current_node->entry;
			}

			direction = Call(ENTRY, compareTo, current_node->entry, entry) < 0;
			current_node = current_node->children[direction];
		}
	}

	return NULL;
}

bool CAT(MapReplace, CAT(K, V))(void* this, ENTRY to_replace, ENTRY replacement)
{
	CHECK_NULL(this, false);

	MAP this_map = (MAP)this;

	if (this_map->root == NULL)
	{
		//empty tree
		return false;
	}
	else
	{
		MAPNODE current_node = this_map->root;

		int direction = 0;

		while (current_node != NULL)
		{
			//if data is equal, then we stop
			if (Call(ENTRY, equals, current_node->entry, to_replace))
			{
				//delete and move the result in place
				Delete(ENTRY, current_node->entry);
				current_node->entry = replacement;
				return true;
			}

			direction = Call(ENTRY, compareTo, current_node->entry, to_replace) < 0;
			current_node = current_node->children[direction];
		}
	}
	return false; 
}

static ENTRY* CAT(GetMapInOrderTraversalByIndex, CAT(K, V))(MAPNODE node, int* current_index, int wanted_index)
{
	if (node != NULL)
	{
		ENTRY* left_data = CAT(GetMapInOrderTraversalByIndex, CAT(K, V))(node->children[LEFT], current_index, wanted_index);
		if (left_data != NULL)
		{
			return left_data;
		}
		if (*current_index == wanted_index)
		{
			return &node->entry;
		}
		(*current_index)++;
		return CAT(GetMapInOrderTraversalByIndex, CAT(K, V))(node->children[RIGHT], current_index, wanted_index);
	}
	return NULL;
}

CAT(CAT(Map, CAT(K, V)), Iterator) CAT(MapBegin, CAT(K, V))(void* this)
{
	CHECK_NULL(this, NULL);

	MAP this_map = (MAP)this;

	//allocate a iterator
	CAT(CAT(Map, CAT(K, V)), Iterator) iterator = check_calloc(sizeof(struct CAT(CAT(_Map, CAT(K, V)), Iterator)));

	iterator->index = 0;

	int start_index = 0;
	iterator->entry = CAT(GetMapInOrderTraversalByIndex, CAT(K, V))(this_map->root, &start_index, iterator->index);

	return iterator;
}

bool CAT(MapNext, CAT(K, V))(void* this, CAT(CAT(Map, CAT(K, V)), Iterator) iterator)
{
	CHECK_NULL(this, false);
	CHECK_NULL(iterator, false);

	MAP this_map = (MAP)this;

	//search for child node that has the value... 
	//(This is inefficient, but it follows how iterators work in the design)

	iterator->index++;

	int start_index = 0;
	iterator->entry = CAT(GetMapInOrderTraversalByIndex, CAT(K, V))(this_map->root, &start_index, iterator->index);

	return true;
}

CAT(CAT(Map, CAT(K, V)), Iterator) CAT(MapEnd, CAT(K, V))(void* this, CAT(CAT(Map, CAT(K, V)), Iterator) iterator)
{
	CHECK_NULL(this, NULL);
	CHECK_NULL(iterator, NULL);

	MAP this_map = (MAP)this;

	//check if iterator is at the end
	if (iterator->index == (int)this_map->size)
	{
		iterator->index = NPOS;
		iterator->entry = NULL;
		free(iterator);
		return NULL;
	}
	return iterator;
}

/*============================================================================
|	Class member definitions
*===========================================================================*/

#undef IsRed
#undef SingleRotate
#undef DoubleRotate
#undef NewMoveNode
#undef NewNode

#undef ENTRY

#undef MAP
#undef MAPNODE

#undef MapVFTable
#undef mapVFTable

#endif
