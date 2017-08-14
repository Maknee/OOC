#include "template.h"

void* UpcastVFTable(const char* new_type, void* _pVFTable, void* _basepVFTable)
{
	ObjectVFTable* pVFTable = (ObjectVFTable*)_pVFTable;
	CHECK_NULL(pVFTable, NULL);

	CompleteObjectLocator* pCompleteObjectLocator = pVFTable->pCompleteObjectLocator;
	CHECK_NULL(pCompleteObjectLocator, NULL);

	ClassHierarchyDescriptor* pClassHierarchyDescriptor = pCompleteObjectLocator->pClassHierarchyDescriptor;
	CHECK_NULL(pClassHierarchyDescriptor, NULL);

	ObjectVFTable* basepVFTable = (ObjectVFTable*)_basepVFTable;
	CHECK_NULL(basepVFTable, NULL);

	CompleteObjectLocator* basepCompleteObjectLocator = basepVFTable->pCompleteObjectLocator;
	CHECK_NULL(basepCompleteObjectLocator, NULL);

	ClassHierarchyDescriptor* basepClassHierarchyDescriptor = basepCompleteObjectLocator->pClassHierarchyDescriptor;
	CHECK_NULL(basepClassHierarchyDescriptor, NULL);

	//check if numBaseClasses == 1 (means class only contains itself)
	if (pClassHierarchyDescriptor->numBaseClasses == 1)
	{
		return NULL;
	}

	for (size_t i = 0; i < pClassHierarchyDescriptor->numBaseClasses; i++)
	{
		BaseClassDescriptor* pBaseClassDescriptor = &pClassHierarchyDescriptor->pBaseClassArray[i];

		//printf("Want type %s - Current iter type - %s - base obj type %s\n", new_type, pBaseClassDescriptor->pTypeDescriptor->name, basepCompleteObjectLocator->pTypeDescriptor->name);

		//case when the object is casted to the same object type
		if (!strcmp(pBaseClassDescriptor->pTypeDescriptor->name, new_type) &&
			!strcmp(pBaseClassDescriptor->pTypeDescriptor->name, basepCompleteObjectLocator->pTypeDescriptor->name))
		{
			return (void*)pVFTable;
		}

		//check if the current iteration is at the end (same object type as current object)
		if (!strcmp(pBaseClassDescriptor->pTypeDescriptor->name, pCompleteObjectLocator->pTypeDescriptor->name))
		{
			//check if there was not a cast to be found (same object type as base object)
			if (!strcmp(basepCompleteObjectLocator->pTypeDescriptor->name, pCompleteObjectLocator->pTypeDescriptor->name))
			{
				break;
			}
			return NULL;
		}

		//check if the name is the same
		if (!strcmp(pBaseClassDescriptor->pTypeDescriptor->name, new_type))
		{
			return (void*)pVFTable;
		}

		//recurse structure to find name
		ObjectVFTable* recurse_result = UpcastVFTable(new_type, pBaseClassDescriptor->pTypeDescriptor->pVFTable, basepVFTable);
		if (recurse_result != NULL)
		{
			return recurse_result;
		}

	}

	//only called if the object could not be casted
	DEBUG_PRINT("%s\n%s%s%s%s\n", "Cast failed!", "Attempted to cast to ", new_type, ", but object type is ", basepCompleteObjectLocator->pTypeDescriptor->name);
	return NULL;
}

void* UpcastObject(const char* new_type, void* object)
{
	CHECK_NULL(object, NULL);

	void* pVFTable = ((Object*)object)->pVFTable;
	CHECK_NULL(pVFTable, NULL);

	return UpcastVFTable(new_type, pVFTable, pVFTable);
}

void* DowncastObject(void* _newTypeVFTable, void* object)
{
	CHECK_NULL(object, NULL);

	ObjectVFTable* pVFTable = ((Object*)object)->pVFTable;
	CHECK_NULL(pVFTable, NULL);

	CompleteObjectLocator* pCompleteObjectLocator = pVFTable->pCompleteObjectLocator;
	CHECK_NULL(pCompleteObjectLocator, NULL);

	ObjectVFTable* newTypeVFTable = (ObjectVFTable*)_newTypeVFTable;
	CHECK_NULL(newTypeVFTable, NULL);

	//find the current object type starting from the down casted vftable
	void* castedObject = UpcastVFTable(pCompleteObjectLocator->pTypeDescriptor->name, newTypeVFTable, newTypeVFTable);

	//if we find the result, we want to return the casted vftable
	if (castedObject)
	{
		return _newTypeVFTable;
	}
	else
	{
		return NULL;
	}
}