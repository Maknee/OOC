#include "ooc_object_cunit_test.h"

int initialise_suite(void)
{
   return 0;
}

int cleanup_suite(void)
{
    return 0;
}

void TestObjectVFTableCompleteObjectLocator()
{
	CU_ASSERT_PTR_EQUAL(objectVFTable.equals, NULL);
}

void TestObjectVFTableEquals()
{
	CU_ASSERT_PTR_EQUAL(objectVFTable.equals, ObjectEquals);
}

void TestObjectVFTableObjectToString()
{
	CU_ASSERT_PTR_EQUAL(objectVFTable.toString, ObjectToString);
}
