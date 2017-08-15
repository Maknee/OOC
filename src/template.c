#include "template.h"

void* SetVFTable(void* object, void* new_vftable)
{
	((Object*)object)->pVFTable = new_vftable;
	return object;
}

void* UpcastVFTableRecurse(const char* new_type, void* _pVFTable, void* _basepVFTable)
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

	//WRONG WHAT HAPPENS IF THE CURRENT VFTABLE IS OBJECT? THIS WILL RETURN NULL
	//check if numBaseClasses == 1 (means class only contains itself)
	//if (pClassHierarchyDescriptor->numBaseClasses == 1)
	//{
	//	return NULL;
	//}

	for (size_t i = 0; i < pClassHierarchyDescriptor->numBaseClasses; i++)
	{
		BaseClassDescriptor* pBaseClassDescriptor = &pClassHierarchyDescriptor->pBaseClassArray[i];

		//printf("Want type %s - Current object %s - Current iter type - %s - base obj type %s\n", new_type, pCompleteObjectLocator->pTypeDescriptor->name, pBaseClassDescriptor->pTypeDescriptor->name, basepCompleteObjectLocator->pTypeDescriptor->name);

		//case when the object is casted to the same object type
		if (!strcmp(pBaseClassDescriptor->pTypeDescriptor->name, new_type) &&
			!strcmp(pBaseClassDescriptor->pTypeDescriptor->name, basepCompleteObjectLocator->pTypeDescriptor->name))
		{
			//return original vftable
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
			//return the index of the vftable
			return (void*)pBaseClassDescriptor->pTypeDescriptor->pVFTable;
		}

		//recurse structure to find name
		ObjectVFTable* recurse_result = UpcastVFTableRecurse(new_type, pBaseClassDescriptor->pTypeDescriptor->pVFTable, basepVFTable);
		if (recurse_result != NULL)
		{
			printf("Result %s\n", recurse_result->pCompleteObjectLocator->pTypeDescriptor->name);
			return recurse_result;
		}
	}

	//only called if the object could not be casted
	DEBUG_PRINT("%s\n%s%s%s%s\n", "Cast failed!", "Attempted to cast to ", new_type, ", but object type is ", basepCompleteObjectLocator->pTypeDescriptor->name);
	return NULL;
}

void* UpcastVFTable(const char* new_type, void* object)
{
	CHECK_NULL(object, NULL);

	//void* pVFTable = ((Object*)object)->pVFTable;
	//CHECK_NULL(pVFTable, NULL);

	void* objectpVFTable = ((Object*)object)->objectpVFTable;
	CHECK_NULL(objectpVFTable, NULL);

	return UpcastVFTableRecurse(new_type, objectpVFTable, objectpVFTable);
}

void* DowncastVFTable(void* _newTypeVFTable, void* object)
{
	CHECK_NULL(object, NULL);

	ObjectVFTable* objectpVFTable = ((Object*)object)->objectpVFTable;
	CHECK_NULL(objectpVFTable, NULL);

	CompleteObjectLocator* pCompleteObjectLocator = objectpVFTable->pCompleteObjectLocator;
	CHECK_NULL(pCompleteObjectLocator, NULL);

	ObjectVFTable* newTypeVFTable = (ObjectVFTable*)_newTypeVFTable;
	CHECK_NULL(newTypeVFTable, NULL);

	//find the current object type starting from the down casted vftable
	void* castedObject = UpcastVFTableRecurse(pCompleteObjectLocator->pTypeDescriptor->name, newTypeVFTable, newTypeVFTable);

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

char* CheckForMove(char* macro)
{
	printf("%s\n", macro);

	if (strstr(macro, "Move"))
	{
		printf("%s\n", "YUP");
		return macro;
	}
	return NULL;
}