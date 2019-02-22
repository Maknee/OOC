#if defined(K) && defined(V)

#define OOC_V1

#include "ooc_template.h"

//can't define this as Entry since name collision
#define ENTRY CAT(Entry, CAT(K, V))

#define EntryVFTable CAT(ENTRY, VFTable)
#define entryVFTable CAT(CAT(Entry, CAT(K, V)), vfTable)

EntryVFTable entryVFTable =
{
	NULL_OBJECT_VFTABLE,
	.copy = NULL,
	.move_set_key = NULL,
	.set_key = NULL,
	.get_key = NULL,
	.move_set_value = NULL,
	.set_value = NULL,
	.get_value = NULL
};

TypeDescriptor CAT(entryTypeDescriptor, CAT(K, V)) =
{
	.pVFTable = &entryVFTable,
	.name = STRINGIFY(ENTRY)
};

BaseClassDescriptor CAT(entryBaseClassArray, CAT(K, V))[] =
{
	ObjectBaseClassDescriptor,
	EntryBaseClassDescriptor(CAT(K, V))
};

ClassHierarchyDescriptor CAT(entryClassHierarchyDescriptor, CAT(K, V)) =
{
	.attributes = CLASS_HIERARCHY_VIRTUAL_INHERITENCE,
	.numBaseClasses = 2,
	.pBaseClassArray = CAT(entryBaseClassArray, CAT(K, V))
};

CompleteObjectLocator CAT(entryCompleteObjectLocator, CAT(K, V)) =
{
	.signature = 0x48454845,
	.pTypeDescriptor = &CAT(entryTypeDescriptor, CAT(K, V)),
	.pClassHierarchyDescriptor = &CAT(entryClassHierarchyDescriptor, CAT(K, V))
};

/*============================================================================
|	New Operator
*===========================================================================*/

ENTRY CAT(NewEntry, CAT(K, V))()
{
	//allocate a new entry
	ENTRY this = check_calloc(sizeof(struct CAT(Entry_, CAT(K, V))));

	//cast to entry
	ENTRY this_entry = (ENTRY)this;

	//allocate vftable
	this_entry->object.pVFTable = check_calloc(sizeof(EntryVFTable));

	//call constructor to setup entry
	CAT(EntryConstruct, CAT(K, V))(this);

	return this;
}

/*============================================================================
|	Delete Operator
*===========================================================================*/

void CAT(DeleteEntry, CAT(K, V))(ENTRY this)
{
	CHECK_NULL_NO_RET(this);

	//cast to entry
	ENTRY this_entry = (ENTRY)this;

	//call destructor
	CAT(EntryDestruct, CAT(K, V))(this);

	//null the (casted) vftable
	this_entry->object.pVFTable = NULL;

	//free vftable
	free(this_entry->object.objectpVFTable);

	//free the string's resources
	free(this);
}

/*============================================================================
|	Constructor
*===========================================================================*/

void CAT(EntryConstruct, CAT(K, V))(ENTRY this)
{
	CHECK_NULL_NO_RET(this);

	//call super class's constructor (ObjectConstruct)
	ContainerConstruct(this);

	//Override Object's methods
	//=========================

	//Entry the vtable's complete object locator to complete the RTTI circle
	entryVFTable.pCompleteObjectLocator = &CAT(entryCompleteObjectLocator, CAT(K, V));
	entryVFTable.copy = &CAT(EntryCopy, CAT(K, V));
	entryVFTable.delete = &CAT(DeleteEntry, CAT(K, V));
	entryVFTable.equals = &CAT(EntryEquals, CAT(K, V));
	entryVFTable.compareTo = &CAT(EntryCompareTo, CAT(K, V));
	entryVFTable.toString = &CAT(EntryToString, CAT(K, V));
	
	//Initialize class member methods
	//==========================

	entryVFTable.move_set_key = &CAT(EntryMoveSetKey, CAT(K, V));
	entryVFTable.set_key = &CAT(EntrySetKey, CAT(K, V));
	entryVFTable.get_key = &CAT(EntryGetKey, CAT(K, V));
	entryVFTable.move_set_value = &CAT(EntryMoveSetValue, CAT(K, V));
	entryVFTable.set_value = &CAT(EntrySetValue, CAT(K, V));
	entryVFTable.get_value = &CAT(EntryGetValue, CAT(K, V));

	//cast to entry
	ENTRY this_entry = (ENTRY)this;

	//Initialize the vtable to a copy of this object's vtable
	memcpy(this_entry->object.pVFTable, &entryVFTable, sizeof(EntryVFTable));

	//Make the objectpVFTable point to the same table initially
	this_entry->object.objectpVFTable = this_entry->object.pVFTable;

	//Initialize member variables
}

/*============================================================================
|	Copy Constructor
*===========================================================================*/

ENTRY CAT(EntryCopyConstruct, CAT(K, V))(ENTRY this)
{
	CHECK_NULL(this, NULL);

	//cast to entry
	ENTRY this_entry = (ENTRY)this;

	//allocate a new entry
	ENTRY copy = CAT(NewEntry, CAT(K, V))();

	//cast to entry
	ENTRY copy_entry = (ENTRY)copy;

	//copy key
	copy_entry->key = K_COPY(&this_entry->key);

	//copy value
	copy_entry->value = V_COPY(&this_entry->value);

	return copy;
}

/*============================================================================
|	Destructor
*===========================================================================*/

void CAT(EntryDestruct, CAT(K, V))(ENTRY this)
{
	CHECK_NULL_NO_RET(this);

	//call super destructor
	ContainerDestruct(this);

	ENTRY this_entry = (ENTRY)this;

	//Call K_DELETE and V_DELETE to deallocate key and value
	K_DELETE(&this_entry->key);
	V_DELETE(&this_entry->value);

}

/*============================================================================
|	Overridden member function definitions
*===========================================================================*/

bool CAT(EntryEquals, CAT(K, V))(ENTRY this, ENTRY other)
{
	CHECK_NULL(this, false);
	CHECK_NULL(other, false);
	
	//cast to entry
	ENTRY this_entry = (ENTRY)this;

	//cast to entry
	ENTRY other_entry = (ENTRY)other;

	//Check if the key and value are the same
	if (K_EQUALS(this_entry->key, other_entry->key) && 
		V_EQUALS(this_entry->value, other_entry->value))
	{
		return true;
	}

	return false;
}

int CAT(EntryCompareTo, CAT(K, V))(ENTRY this, ENTRY other)
{
	CHECK_NULL(this, false);
	CHECK_NULL(other, false);

	//cast to entry
	ENTRY this_entry = (ENTRY)this;

	//cast to entry
	ENTRY other_entry = (ENTRY)other;

	int k_comparsion = K_COMPARE_TO(this_entry->key, other_entry->key);
	int v_comparsion = V_COMPARE_TO(this_entry->value, other_entry->value);
	
	return (k_comparsion ? k_comparsion : (v_comparsion ? v_comparsion : 0));
}

char* CAT(EntryToString, CAT(K, V))(ENTRY this)
{
	CHECK_NULL(this, NULL);

	return ContainerToString(this);
}

ENTRY CAT(EntryCopy, CAT(K, V))(ENTRY this)
{
	CHECK_NULL(this, NULL);

	return CAT(EntryCopyConstruct, CAT(K, V))(this);
}

bool CAT(EntryMoveSetKey, CAT(K, V))(ENTRY this, K item)
{
	CHECK_NULL(this, false);

	ENTRY this_entry = (ENTRY)this;

	this_entry->key = item;

	return true;
}

bool CAT(EntrySetKey, CAT(K, V))(ENTRY this, K item)
{
	CHECK_NULL(this, false);

	ENTRY this_entry = (ENTRY)this;

	this_entry->key = K_COPY(&item);

	return true;
}

K* CAT(EntryGetKey, CAT(K, V))(ENTRY this)
{
	CHECK_NULL(this, NULL);

	ENTRY this_entry = (ENTRY)this;

	return &this_entry->key;
}

bool CAT(EntryMoveSetValue, CAT(K, V))(ENTRY this, V item)
{
	CHECK_NULL(this, false);

	ENTRY this_entry = (ENTRY)this;

	this_entry->value = item;

	return true;
}

bool CAT(EntrySetValue, CAT(K, V))(ENTRY this, V item)
{
	CHECK_NULL(this, false);

	ENTRY this_entry = (ENTRY)this;

	this_entry->value = V_COPY(&item);

	return true;
}

V* CAT(EntryGetValue, CAT(K, V))(ENTRY this)
{
	CHECK_NULL(this, NULL);

	ENTRY this_entry = (ENTRY)this;

	return &this_entry->value;
}

#undef EntryVFTable
#undef entryVFTable

#undef ENTRY

#endif
