#include "template.h"

void* UpcastVFTable(const char* new_type, void* _pVFTable)
{
	ObjectVFTable* pVFTable = (ObjectVFTable*)_pVFTable;
	CHECK_NULL(pVFTable, NULL);

	CompleteObjectLocator* pCompleteObjectLocator = pVFTable->pCompleteObjectLocator;
	CHECK_NULL(pCompleteObjectLocator, NULL);

	ClassHierarchyDescriptor* pClassHierarchyDescriptor = pCompleteObjectLocator->pClassHierarchyDescriptor;
	CHECK_NULL(pClassHierarchyDescriptor, NULL);

	//check if numBaseClasses == 1 (means class only contains itself)
	if (pClassHierarchyDescriptor->numBaseClasses == 1)
	{
		return NULL;
	}

	for (size_t i = 0; i < pClassHierarchyDescriptor->numBaseClasses; i++)
	{
		BaseClassDescriptor* pBaseClassDescriptor = &pClassHierarchyDescriptor->pBaseClassArray[i];

		//check if the name is the same
		if (!strcmp(pBaseClassDescriptor->pTypeDescriptor->name, new_type))
		{
			return (void*)pVFTable;
		}

		//check if the object type if the same as what the current class type is (the baseclass descriptor contains the same class again)
		//if so, we need to stop recursing
		if (!strcmp(pBaseClassDescriptor->pTypeDescriptor->name, pVFTable->pCompleteObjectLocator->pTypeDescriptor->name))
		{
			DEBUG_PRINT("%s\n", "Upcast failed!");
			return NULL;
		}

		//recurse structure to find name
		ObjectVFTable* recurse_result = UpcastVFTable(new_type, pBaseClassDescriptor->pTypeDescriptor->pVFTable);
		if (recurse_result != NULL)
		{
			return recurse_result;
		}
	}
	DEBUG_PRINT("%s\n", "Upcast failed!");
	return NULL;
}
void* UpcastObject(const char* new_type, void* object)
{
	CHECK_NULL(object, NULL);

	void* pVFTable = ((Object*)object)->pVFTable;
	CHECK_NULL(pVFTable, NULL);

	return UpcastVFTable(new_type, pVFTable);
}