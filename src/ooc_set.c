#if defined(T) && defined(T_EQUALS)

#include "template.h"

//can't define this as Set since name collision
#define SET CAT(Set, T)
#define SETNODE CAT(SetNode, T)

#define SetVFTable CAT(SET, VFTable)
#define setVFTable CAT(CAT(Set, T), vfTable)

SetVFTable setVFTable =
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

TypeDescriptor CAT(setTypeDescriptor, T) =
{
	.pVFTable = &setVFTable,
	//necessary for checking type Upcast macro (can't print pretty)
	.name = STRINGIFY(SET)
	//print pretty vvvv
	//.name = STRINGIFY(Set(T))
};

BaseClassDescriptor CAT(setBaseClassArray, T)[] =
{
	ContainerBaseClassDescriptor,
	SetBaseClassDescriptor(T)
};

ClassHierarchyDescriptor CAT(setClassHierarchyDescriptor, T) =
{
	.attributes = CLASS_HIERARCHY_VIRTUAL_INHERITENCE,
	.numBaseClasses = 2,
	.pBaseClassArray = CAT(setBaseClassArray, T)
};

CompleteObjectLocator CAT(setCompleteObjectLocator, T) =
{
	.signature = 0x48454845,
	.pTypeDescriptor = &CAT(setTypeDescriptor, T),
	.pClassHierarchyDescriptor = &CAT(setClassHierarchyDescriptor, T)
};


/*============================================================================
|	Helper functions
*===========================================================================*/

static int CAT(SetIsRed, T)(SETNODE node)
{
	return (node != NULL && node->color) ? (RED) : (BLACK);
}

#define IsRed(node) CAT(SetIsRed, T)(node)

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

static SETNODE CAT(SetSingleRotate, T)(SETNODE root, int direction)
{
	//get the opposite node
	SETNODE new_root = root->children[!direction];

	//switch over opposite node's child as old root's child
	root->children[!direction] = new_root->children[direction];

	//update the new root to set the old root as its child
	new_root->children[direction] = root;

	//update the colors, so the tree is valid
	root->color = RED;
	new_root->color = BLACK;

	return new_root;
}

#define SingleRotate(root, direction) CAT(SetSingleRotate, T)(root, direction)

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
|	                     5 <---old root sets new current root to be its child
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

static SETNODE CAT(SetDoubleRotate, T)(SETNODE root, int direction)
{
	//opposite rotate child?
	root->children[!direction] = SingleRotate(root->children[!direction], !direction);

	//rotate root
	return SingleRotate(root, direction);
}

#define DoubleRotate(root, direction) CAT(SetDoubleRotate, T)(root, direction)

static SETNODE CAT(SetNewMoveNode, T)(T* data_ptr)
{
	SETNODE new_node = check_calloc(sizeof(struct CAT(_SetNode, T)));

	new_node->data = *data_ptr;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	new_node->color = RED;

	return new_node;
}

#define NewMoveNode(data_ptr) CAT(SetNewMoveNode, T)(data_ptr)

static SETNODE CAT(SetNewNode, T)(T* data_ptr)
{
	SETNODE new_node = check_calloc(sizeof(struct CAT(_SetNode, T)));

	new_node->data = T_COPY(data_ptr);
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	new_node->color = RED;

	return new_node;
}

#define NewNode(data_ptr) CAT(SetNewNode, T)(data_ptr)

static SETNODE CAT(SetCopyNode, T)(SETNODE node)
{
	SETNODE new_node = check_calloc(sizeof(struct CAT(_SetNode, T)));

	new_node->data = T_COPY(&node->data);
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	new_node->color = node->color;

	return new_node;
}

#define CopyNode(node) CAT(SetCopyNode, T)(node)

/*
int CAT(SetTest, T)(CAT(SetNode, T) root, int indent)
{
	if (root == NULL)
	{
		return 1;
	}
	else
	{
		SETNODE left = root->children[LEFT];
		SETNODE right = root->children[RIGHT];

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

		int right_height = CAT(SetTest, T)(right, indent + 4);

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

		int left_height = CAT(SetTest, T)(left, indent + 4);

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

void* CAT(NewSet, T)()
{
	//allocate a new set
	void* this = check_calloc(sizeof(struct CAT(_Set, T)));

	//cast to set
	SET this_set = (SET)this;

	//allocate vftable
	this_set->container.object.pVFTable = check_calloc(sizeof(SetVFTable));

	//call constructor to set up string
	CAT(SetConstruct, T)(this);

	return this;
}

/*============================================================================
|	Delete Operator
*===========================================================================*/

void CAT(DeleteSet, T)(void* this)
{
	CHECK_NULL_NO_RET(this);

	//cast to set
	SET this_set = (SET)this;

	//call destructor
	CAT(SetDestruct, T)(this);

	//null the (casted) vftable
	this_set->container.object.pVFTable = NULL;

	//free vftable
	free(this_set->container.object.objectpVFTable);

	//free the string's resources
	free(this);
}

/*============================================================================
|	Constructor
*===========================================================================*/

void CAT(SetConstruct, T)(void* this)
{
	CHECK_NULL_NO_RET(this);

	//call super class's constructor (ObjectConstruct)
	ContainerConstruct(this);

	//Override Object's methods
	//=========================

	//Set the vtable's complete object locator to complete the RTTI circle
	setVFTable.pCompleteObjectLocator = &CAT(setCompleteObjectLocator, T);

	//Set the equals function
	setVFTable.equals = &CAT(SetEquals, T);

	//Set the compareTo function
	setVFTable.compareTo = &CAT(SetCompareTo, T);

	//Set the toString
	setVFTable.toString = &CAT(SetToString, T);

	//Override Container's methods
	//==========================
	
	setVFTable.add = &CAT(SetAdd, T);
	setVFTable.clear = &CAT(SetClear, T);
	setVFTable.remove = &CAT(SetRemove, T);
	setVFTable.contains = &CAT(SetContains, T);
	setVFTable.copy = &CAT(SetCopy, T);
	setVFTable.isEmpty = &CAT(SetIsEmpty, T);
	setVFTable.size = &CAT(SetSize, T);
	
	//Initialize class member methods
	//==========================

	setVFTable.set = &CAT(Set_Set, T);
	setVFTable.move_insert = &CAT(SetMoveInsert, T);
	setVFTable.insert = &CAT(SetInsert, T);
	setVFTable.find = &CAT(SetFind, T);
	setVFTable.replace = &CAT(SetReplace, T);
	setVFTable.begin = &CAT(SetBegin, T);
	setVFTable.next = &CAT(SetNext, T);
	setVFTable.end = &CAT(SetEnd, T);

	//cast to set
	SET this_set = (SET)this;

	//Initialize the vtable to a copy of this object's vtable
	memcpy(this_set->container.object.pVFTable, &setVFTable, sizeof(SetVFTable));

	//Make the objectpVFTable point to the same table initially
	this_set->container.object.objectpVFTable = this_set->container.object.pVFTable;

	//Initialize member variables

	//set size
	this_set->size = 0;

	//set root to NULL
	this_set->root = NULL;
}

/*============================================================================
|	Copy Constructor
*===========================================================================*/

static SETNODE CAT(SetCopyHelper, T)(SETNODE node, SETNODE copy_node)
{
	if (node != NULL)
	{
		copy_node = CopyNode(node);
		copy_node->children[LEFT] = CAT(SetCopyHelper, T)(node->children[LEFT], copy_node->children[LEFT]);
		copy_node->children[RIGHT] = CAT(SetCopyHelper, T)(node->children[RIGHT], copy_node->children[RIGHT]);
		return copy_node;
	}
	return NULL;
}

void* CAT(SetCopyConstruct, T)(void* this)
{
	CHECK_NULL(this, NULL);

	//cast to set
	SET this_set = (SET)this;

	//allocate a new set
	void* copy = CAT(NewSet, T)();

	//cast to set
	SET copy_set = (SET)copy;

	//copy the contents of the string to the copied set except for vftable (which is contained in Container struct inside the String struct)
	copy_set->size = this_set->size;

	//copy tree
	copy_set->root = CAT(SetCopyHelper, T)(this_set->root, copy_set->root);

	return copy;
}

/*============================================================================
|	Destructor
*===========================================================================*/

void CAT(SetDestruct, T)(void* this)
{
	CHECK_NULL_NO_RET(this);

	//call super destructor
	ContainerDestruct(this);

	//call clear
	CAT(SetClear, T)(this);
}

/*============================================================================
|	Overridden member function definitions
*===========================================================================*/

static bool CAT(SetEqualsHelper, T)(SETNODE node1, SETNODE node2)
{
	//if either are null, quit
	if (node1 == NULL && node2 == NULL)
	{
		return true;
	}

	return (T_EQUALS(node1->data, node2->data) &&
		CAT(SetEqualsHelper, T)(node1->children[LEFT], node2->children[LEFT]) &&
		CAT(SetEqualsHelper, T)(node1->children[RIGHT], node2->children[RIGHT]);
}

bool CAT(SetEquals, T)(void* this, void* other)
{
	CHECK_NULL(this, false);
	CHECK_NULL(other, false);
	
	//cast to set
	SET this_set = (SET)this;

	//cast to set
	SET other_set = (SET)other;

	//Check if the sizes are the same
	if (this_set->size != other_set->size)
	{
		return false;
	}

	return CAT(SetEqualsHelper, T)(this_set->root, other_set->root);
}

static int CAT(SetCompareToHelper, T)(SETNODE node1, SETNODE node2)
{
	//if either are null, quit
	if (node1 == NULL && node2 == NULL)
	{
		return 0;
	}

	return (T_COMPARE_TO(node1->data, node2->data) &&
		CAT(SetEqualsHelper, T)(node1->children[LEFT], node2->children[LEFT]) &&
		CAT(SetEqualsHelper, T)(node1->children[RIGHT], node2->children[RIGHT]));
}

int CAT(SetCompareTo, T)(void* this, void* other)
{
	CHECK_NULL(this, false);
	CHECK_NULL(other, false);

	//cast to set
	SET this_set = (SET)this;

	//cast to set
	SET other_set = (SET)other;

	//Check if the sizes are the same
	if (this_set->size != other_set->size)
	{
		//should work?
		return (int)this_set->size - (int)other_set->size;
	}

	return CAT(SetCompareToHelper, T)(this_set->root, other_set->root);
}

char* CAT(SetToString, T)(void* this)
{
	CHECK_NULL(this, NULL);

	return ContainerToString(this);
}

bool CAT(SetAdd, T)(void* this, T item)
{
	return CAT(SetInsert, T)(this, item);
}

void CAT(SetClear, T)(void* this)
{
	CHECK_NULL_NO_RET(this);

	//cast to set
	SET this_set = (SET)this;
	this_set->size = 0;

	SETNODE node = this_set->root;
	SETNODE save = NULL;

	while (node != NULL)
	{
		if (node->children[LEFT] == NULL)
		{
			//destroy and move to right
			save = node->children[RIGHT];
			T_DELETE(&node->data);
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
	this_set->root = NULL;
}

bool CAT(SetRemove, T)(void* this, T item)
{
	CHECK_NULL(this, false);

	SET this_set = (SET)this;

	if (this_set->root == NULL)
	{
		return false;
	}

	//imaginary parent's root
	struct CAT(_SetNode, T) parent_root = { .data = 0, .children = { NULL, NULL }, .color = BLACK };
	parent_root.children[RIGHT] = this_set->root;

	SETNODE grandparent = NULL;
	SETNODE parent = NULL;
	SETNODE current_node = &parent_root;
	SETNODE found_node = NULL;

	int direction = RIGHT;
	int last_direction = 0;

	while (current_node->children[direction] != NULL)
	{
		//update
		last_direction = direction;

		grandparent = parent;
		parent = current_node;
		current_node = current_node->children[direction];
		
		direction = T_COMPARE_TO(current_node->data, item) < 0;

		if (T_EQUALS(current_node->data, item))
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
				SETNODE other = parent->children[!last_direction];

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
		T_DELETE(&found_node->data);
		found_node->data = current_node->data;
		parent->children[parent->children[RIGHT] == current_node] = current_node->children[current_node->children[LEFT] == NULL];
		free(current_node);
	}

	this_set->root = parent_root.children[RIGHT];

	if (this_set->root != NULL)
	{
		this_set->root->color = BLACK;
	}

	this_set->size--;

	return true;
}

bool CAT(SetContains, T)(void* this, T item)
{
	CHECK_NULL(this, false);

	SET this_set = (SET)this;

	if (this_set->root == NULL)
	{
		//empty tree
		return false;
	}
	else
	{
		SETNODE current_node = this_set->root;
		
		int direction = 0;

		while (current_node != NULL)
		{	
			//if data is equal, then we stop
			if (T_EQUALS(current_node->data, item))
			{
				return true;
			}

			direction = T_COMPARE_TO(current_node->data, item) < 0;
			current_node = current_node->children[direction];
		}
	}

	return false;
}

void* CAT(SetCopy, T)(void* this)
{
	CHECK_NULL(this, NULL);

	return CAT(SetCopyConstruct, T)(this);
}

bool CAT(SetIsEmpty, T)(void* this)
{
	CHECK_NULL(this, false);

	//cast to set
	SET this_set = (SET)this;

	return this_set->size == 0;
}

size_t CAT(SetSize, T)(void* this)
{
	CHECK_NULL(this, false);

	//cast to set
	SET this_set = (SET)this;

	return this_set->size;
}

bool CAT(Set_Set, T)(void* this, const T* item, size_t num_elements)
{
	CHECK_NULL(this, false);

	//clear the set
	CAT(SetClear, T)(this);

	//insert items
	//loop until null
	for (size_t i = 0; i < num_elements; i++)
	{
		CAT(SetMoveInsert, T)(this, item[i]);
	}
	
	return true;
}

bool CAT(SetMoveInsert, T)(void* this, T item)
{
	CHECK_NULL(this, false);

	SET this_set = (SET)this;

	//check if we need to update size
	bool inserted_node = false;

	if (this_set->root == NULL)
	{
		//empty tree
		this_set->root = NewMoveNode(&item);

		inserted_node = true;
	}
	else
	{
		//imaginary parent's root
		struct CAT(_SetNode, T) parent_root = { .data = 0, .children = { NULL, NULL }, .color = BLACK };
		parent_root.children[RIGHT] = this_set->root;

		SETNODE greatgrandparent = &parent_root;
		SETNODE grandparent = NULL;
		SETNODE parent = NULL;
		SETNODE current_node = this_set->root;
		
		int direction = 0;
		int last_direction = 0;

		while (true)
		{
			//case when we reach a NULL, we insert item
			if (current_node == NULL)
			{
				parent->children[direction] = current_node = NewMoveNode(&item);

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
			if (T_EQUALS(current_node->data, item))
			{
				if (!inserted_node)
				{
					//replace node with moved item
					T_DELETE(&current_node->data);
					current_node->data = item;
				}

				break;
			}

			//move on to next node
			last_direction = direction;
			direction = T_COMPARE_TO(current_node->data, item) < 0;

			if (grandparent != NULL)
			{
				greatgrandparent = grandparent;
			}

			grandparent = parent;
			parent = current_node;
			current_node = current_node->children[direction];
		}

		//update root
		this_set->root = parent_root.children[RIGHT];
	}

	//make root black
	this_set->root->color = BLACK;
	if (inserted_node)
	{
		this_set->size++;
	}

	return true;
}

bool CAT(SetInsert, T)(void* this, T item)
{
	CHECK_NULL(this, false);

	SET this_set = (SET)this;

	//check if we need to update size
	bool inserted_node = false;

	if (this_set->root == NULL)
	{
		//empty tree
		this_set->root = NewNode(&item);

		inserted_node = true;
	}
	else
	{
		//imaginary parent's root
		struct CAT(_SetNode, T) parent_root = { .data = 0, .children = { NULL, NULL }, .color = BLACK };
		parent_root.children[RIGHT] = this_set->root;

		SETNODE greatgrandparent = &parent_root;
		SETNODE grandparent = NULL;
		SETNODE parent = NULL;
		SETNODE current_node = this_set->root;

		int direction = 0;
		int last_direction = 0;

		while (true)
		{
			//case when we reach a NULL, we insert item
			if (current_node == NULL)
			{
				parent->children[direction] = current_node = NewNode(&item);

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
			if (T_EQUALS(current_node->data, item))
			{
				if (!inserted_node)
				{
					//replace node with moved item
					current_node->data = T_COPY(&item);
				}

				break;
			}

			//move on to next node
			last_direction = direction;
			direction = T_COMPARE_TO(current_node->data, item) < 0;

			if (grandparent != NULL)
			{
				greatgrandparent = grandparent;
			}

			grandparent = parent;
			parent = current_node;
			current_node = current_node->children[direction];
		}

		//update root
		this_set->root = parent_root.children[RIGHT];
	}

	//make root black
	this_set->root->color = BLACK;
	if (inserted_node)
	{
		this_set->size++;
	}

	return true;
}

T* CAT(SetFind, T) (void* this, T item)
{
	CHECK_NULL(this, NULL);

	SET this_set = (SET)this;

	if (this_set->root == NULL)
	{
		//empty tree
		return NULL;
	}
	else
	{
		SETNODE current_node = this_set->root;

		int direction = 0;

		while (current_node != NULL)
		{
			//if data is equal, then we stop
			if (T_EQUALS(current_node->data, item))
			{
				return &current_node->data;
			}

			direction = T_COMPARE_TO(current_node->data, item) < 0;
			current_node = current_node->children[direction];
		}
	}

	return NULL;
}

bool CAT(SetReplace, T)(void* this, T to_replace, T replacement)
{
	CHECK_NULL(this, false);

	SET this_set = (SET)this;

	if (this_set->root == NULL)
	{
		//empty tree
		return false;
	}
	else
	{
		SETNODE current_node = this_set->root;

		int direction = 0;

		while (current_node != NULL)
		{
			//if data is equal, then we stop
			if (T_EQUALS(current_node->data, to_replace))
			{
				//delete and move the result in place
				T_DELETE(&current_node->data);
				current_node->data = replacement;
				return true;
			}

			direction = T_COMPARE_TO(current_node->data, to_replace) < 0;
			current_node = current_node->children[direction];
		}
	}
	return false; 
}

static T* CAT(GetSetInOrderTraversalByIndex, T)(SETNODE node, int* current_index, int wanted_index)
{
	if (node != NULL)
	{
		T* left_data = CAT(GetSetInOrderTraversalByIndex, T)(node->children[LEFT], current_index, wanted_index);
		if (left_data != NULL)
		{
			return left_data;
		}
		if (*current_index == wanted_index)
		{
			return &node->data;
		}
		(*current_index)++;
		return CAT(GetSetInOrderTraversalByIndex, T)(node->children[RIGHT], current_index, wanted_index);
	}
	return NULL;
}

CAT(CAT(Set, T), Iterator) CAT(SetBegin, T)(void* this)
{
	CHECK_NULL(this, NULL);

	SET this_set = (SET)this;

	//allocate a iterator
	CAT(CAT(Set, T), Iterator) iterator = check_calloc(sizeof(struct CAT(CAT(_Set, T), Iterator)));

	iterator->index = 0;

	int start_index = 0;
	iterator->data = CAT(GetSetInOrderTraversalByIndex, T)(this_set->root, &start_index, iterator->index);

	return iterator;
}

bool CAT(SetNext, T)(void* this, CAT(CAT(Set, T), Iterator) iterator)
{
	CHECK_NULL(this, false);
	CHECK_NULL(iterator, false);

	SET this_set = (SET)this;

	//search for child node that has the value... 
	//(This is inefficient, but it follows how iterators work in the design)

	iterator->index++;

	int start_index = 0;
	iterator->data = CAT(GetSetInOrderTraversalByIndex, T)(this_set->root, &start_index, iterator->index);

	return true;
}

CAT(CAT(Set, T), Iterator) CAT(SetEnd, T)(void* this, CAT(CAT(Set, T), Iterator) iterator)
{
	CHECK_NULL(this, NULL);
	CHECK_NULL(iterator, NULL);

	SET this_set = (SET)this;

	//check if iterator is at the end
	if (iterator->index == (int)this_set->size)
	{
		iterator->index = NPOS;
		iterator->data = NULL;
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

#undef SET
#undef SETNODE

#undef SetVFTable
#undef setVFTable

#endif
