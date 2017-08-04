#include "ooc_object_cunit_test.h"

int ObjectInitializeSuite()
{
   return 0;
}

int ObjectCleanUpSuite()
{
    return 0;
}

void TestObjectVFTableUninitializedCompleteObjectLocator()
{
	CU_ASSERT_PTR_EQUAL(objectVFTable.pCompleteObjectLocator, NULL);
}

void TestObjectVFTableInitializedCompleteObjectLocator()
{
	//manually allocates and deallocates an object
	//this should __NOT__ be done in a real program
	//since object is an abstract object
	
	//allocate a new object
	void* object = calloc(1, sizeof(Object));

	//allocate vftable
	((Object*)object)->pVFTable = calloc(1, sizeof(Object));

	//call constructor to set up object
	ObjectConstruct(object);

	CU_ASSERT_PTR_EQUAL(objectVFTable.pCompleteObjectLocator, &objectCompleteObjectLocator);

	//call destructor
	ObjectDestruct(object);

	//free vftable
	free(((Object*)object)->pVFTable);

	//free the string's resources
	free(object);

	//NULL the pointer, so we don't have use after free vulns
	object = NULL;
}

void TestObjectNew()
{
	void* object = NewObject();
	CU_ASSERT_PTR_EQUAL(object, NULL);
}

void TestObjectDelete()
{
	//pointer value could be random
	void* object;
	DeleteObject(object);
	CU_ASSERT_PTR_EQUAL(object, NULL);
}

void TestObjectConstructor()
{
	//manually allocates and deallocates an object
	//this should __NOT__ be done in a real program
	//since object is an abstract object

	//allocate a new object
	void* object = calloc(1, sizeof(Object));

	//allocate vftable
	((Object*)object)->pVFTable = calloc(1, sizeof(Object));

	//call constructor to set up object
	ObjectConstruct(object);

	//verify that the vftable is pointing in a different memory location
	CU_ASSERT_PTR_NOT_EQUAL(((Object*)object)->pVFTable, &objectVFTable);

	//call destructor
	ObjectDestruct(object);

	//free vftable
	free(((Object*)object)->pVFTable);

	//free the string's resources
	free(object);

	//NULL the pointer, so we don't have use after free vulns
	object = NULL;
}

void TestObjectCopyConstructor()
{
	//pointer value could be random
	void* object;
	void* other_object = ObjectCopyConstruct(object);
	//tests that the object isn't allocated and thus, equals NULL
	CU_ASSERT_PTR_EQUAL(other_object, NULL);
}

void TestObjectDestructor()
{
	//manually allocates and deallocates an object
	//this should __NOT__ be done in a real program
	//since object is an abstract object

	//allocate a new object
	void* object = calloc(1, sizeof(Object));

	//allocate vftable
	((Object*)object)->pVFTable = calloc(1, sizeof(Object));

	//call constructor to set up object
	ObjectConstruct(object);

	//call destructor
	ObjectDestruct(object);

	//Show that nothing happens after destructor is called since the destructor does not do anything
	CU_ASSERT_PTR_NOT_EQUAL(((Object*)object)->pVFTable, &objectVFTable);

	//free vftable
	free(((Object*)object)->pVFTable);

	//free the string's resources
	free(object);

	//NULL the pointer, so we don't have use after free vulns
	object = NULL;
}

void TestObjectVFTableEquals()
{
	CU_ASSERT_PTR_EQUAL(objectVFTable.equals, ObjectEquals);
}

void TestObjectVFTableObjectToString()
{
	CU_ASSERT_PTR_EQUAL(objectVFTable.toString, ObjectToString);
}
