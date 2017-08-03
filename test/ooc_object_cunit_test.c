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
	//needs a malloc'd pointer to call constructor
	//this should __NOT__ be done in a real program
	//since object is an abstract object
	void* object = malloc(sizeof(Object));
	ObjectConstruct(object);
	CU_ASSERT_PTR_EQUAL(objectVFTable.pCompleteObjectLocator, &objectCompleteObjectLocator);
	free(object);
}

void TestObjectVFTableEquals()
{
	CU_ASSERT_PTR_EQUAL(objectVFTable.equals, ObjectEquals);
}

void TestObjectVFTableObjectToString()
{
	CU_ASSERT_PTR_EQUAL(objectVFTable.toString, ObjectToString);
}
