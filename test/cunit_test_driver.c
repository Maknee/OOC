/**
* @file cunit_test_driver.c
* @brief Main testing file
*
* @date	8/4/2017
*/

#include <stdio.h>
#include <string.h>
#include "ooc_object_cunit_test.h"
#include "ooc_container_cunit_test.h"
#include "ooc_string_cunit_test.h"
#include "ooc_vector_cuint_test.h"
#include "ooc_casts_cuint_test.h"
#include "ooc_set_cuint_test.h"
#include "ooc_map_cuint_test.h"

/*
 * Set up and run tests.
 *
 * @return CUE_SUCCESS if successful, else a CUnit error code if
 * any problems arise.
 */

int main()
{
    if (CUE_SUCCESS != CU_initialize_registry())
    {
    	printf("%s\n", CU_get_error_msg());
        return CU_get_error();
    }

	//test object class

    CU_pSuite objectSuite = CU_add_suite("Object Testing Suite", 
										 ObjectInitializeSuite, 
										 ObjectCleanUpSuite);

    if (objectSuite == NULL)
    {
    	printf("%s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(objectSuite, "TestObjectVFTableUninitializedCompleteObjectLocator", TestObjectVFTableUninitializedCompleteObjectLocator) ||
		!CU_add_test(objectSuite, "TestObjectVFTableInitializedCompleteObjectLocator", TestObjectVFTableInitializedCompleteObjectLocator) ||
		!CU_add_test(objectSuite, "TestObjectNew", TestObjectNew) ||
		!CU_add_test(objectSuite, "TestObjectDelete", TestObjectDelete) ||
		!CU_add_test(objectSuite, "TestObjectConstructor", TestObjectConstructor) ||
		!CU_add_test(objectSuite, "TestObjectCopyConstructor", TestObjectCopyConstructor) ||
		!CU_add_test(objectSuite, "TestObjectDestructor", TestObjectDestructor) ||
		!CU_add_test(objectSuite, "TestObjectVFTableEquals", TestObjectVFTableEquals) ||
		!CU_add_test(objectSuite, "TestObjectVFTableCompareTo", TestObjectVFTableCompareTo) ||
		!CU_add_test(objectSuite, "TestObjectVFTableObjectToString", TestObjectVFTableObjectToString))
    {
    	printf("%s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return CU_get_error();
    }
    
	//test container class

	CU_pSuite containerSuite = CU_add_suite("Container Testing Suite",
											ContainerInitializeSuite,
											ContainerCleanUpSuite);

	if (containerSuite == NULL)
	{
		printf("%s\n", CU_get_error_msg());
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (!CU_add_test(containerSuite, "TestContainerVFTableUninitializedCompleteObjectLocator", TestContainerVFTableUninitializedCompleteObjectLocator) ||
		!CU_add_test(containerSuite, "TestContainerVFTableInitializedCompleteObjectLocator", TestContainerVFTableInitializedCompleteObjectLocator) ||
		!CU_add_test(containerSuite, "TestContainerNew", TestContainerNew) ||
		!CU_add_test(containerSuite, "TestContainerDelete", TestContainerDelete) ||
		!CU_add_test(containerSuite, "TestContainerConstructor", TestContainerConstructor) ||
		!CU_add_test(containerSuite, "TestContainerCopyConstructor", TestContainerCopyConstructor) ||
		!CU_add_test(containerSuite, "TestContainerDestructor", TestContainerDestructor) ||
		!CU_add_test(containerSuite, "TestContainerVFTableEquals", TestContainerVFTableEquals) ||
		!CU_add_test(containerSuite, "TestContainerVFTableCompareTo", TestContainerVFTableCompareTo) ||
		!CU_add_test(containerSuite, "TestContainerVFTableContainerToString", TestContainerVFTableContainerToString))
	{
		printf("%s\n", CU_get_error_msg());
		CU_cleanup_registry();
		return CU_get_error();
	}

	//test string class

	CU_pSuite stringSuite = CU_add_suite("String Testing Suite",
		StringInitializeSuite,
		StringCleanUpSuite);

	if (stringSuite == NULL)
	{
		printf("%s\n", CU_get_error_msg());
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (!CU_add_test(stringSuite, "TestStringVFTableUninitializedCompleteObjectLocator", TestStringVFTableUninitializedCompleteObjectLocator) ||
		!CU_add_test(stringSuite, "TestStringVFTableInitializedCompleteObjectLocator", TestStringVFTableInitializedCompleteObjectLocator) ||
		!CU_add_test(stringSuite, "TestStringNew", TestStringNew) ||
		!CU_add_test(stringSuite, "TestStringDelete", TestStringDelete) ||
		!CU_add_test(stringSuite, "TestStringConstructor", TestStringConstructor) ||
		!CU_add_test(stringSuite, "TestStringCopyConstructor", TestStringCopyConstructor) ||
		!CU_add_test(stringSuite, "TestStringDestructor", TestStringDestructor) ||
		!CU_add_test(stringSuite, "TestStringVFTableEquals", TestStringVFTableEquals) ||
		!CU_add_test(stringSuite, "TestStringVFTableCompareTo", TestStringVFTableCompareTo) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringToString", TestStringVFTableStringToString) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringAddFirstAllocatedSecondNot", TestStringVFTableStringAddFirstAllocatedSecondNot) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringAddSecondAllocatedFirstNot", TestStringVFTableStringAddSecondAllocatedFirstNot) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringAdd", TestStringVFTableStringAdd) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringAddAllocated", TestStringVFTableStringAddAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringAddAlreadyAllocated", TestStringVFTableStringAddAlreadyAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringClear", TestStringVFTableStringClear) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringClearAllocated", TestStringVFTableStringClearAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringRemove", TestStringVFTableStringRemove) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringRemoveAllocated", TestStringVFTableStringRemoveAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringRemoveNPOS", TestStringVFTableStringRemoveNPOS) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringContains", TestStringVFTableStringContains) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringCopy", TestStringVFTableStringCopy) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringCopyAllocated", TestStringVFTableStringCopyAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringIsEmpty", TestStringVFTableStringIsEmpty) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringSize", TestStringVFTableStringSize) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringSet", TestStringVFTableStringSet) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringSetAllocated", TestStringVFTableStringSetAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringSetAlreadyAllocated", TestStringVFTableStringSetAlreadyAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringC_Str", TestStringVFTableStringC_Str) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringAppend", TestStringVFTableStringAppend) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringAppendAllocated", TestStringVFTableStringAppendAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringAppendAlreadyAllocated", TestStringVFTableStringAppendAlreadyAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringInsert", TestStringVFTableStringInsert) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringInsertAllocated", TestStringVFTableStringInsertAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringInsertOtherStringAllocated", TestStringVFTableStringInsertOtherStringAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringInsertOtherStringAllocatedNewlyAllocated", TestStringVFTableStringInsertOtherStringAllocatedNewlyAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringInsertAlreadyAllocated", TestStringVFTableStringInsertAlreadyAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringInsertAlreadyAllocatedInsertionStringAllocated", TestStringVFTableStringInsertAlreadyAllocatedInsertionStringAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringInsertOutOfBounds", TestStringVFTableStringInsertOutOfBounds) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringInsertNPOS", TestStringVFTableStringInsertNPOS) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringReplace", TestStringVFTableStringReplace) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringReplaceAllocated", TestStringVFTableStringReplaceAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringFind", TestStringVFTableStringFind) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringFindHayStackAllocated", TestStringVFTableStringFindHayStackAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringFindNeedleAllocated", TestStringVFTableStringFindNeedleAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringFindHayStackAllocatedNeedleAllocated", TestStringVFTableStringFindHayStackAllocatedNeedleAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringFindNull", TestStringVFTableStringFindNull) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringSubString", TestStringVFTableStringSubString) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringSubStringAllocated", TestStringVFTableStringSubStringAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringSubStringLessThanZero", TestStringVFTableStringSubStringLessThanZero) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringSubStringOutOfBounds", TestStringVFTableStringSubStringOutOfBounds) ||
		!CU_add_test(stringSuite, "TestStringIterator", TestStringIterator) ||
		!CU_add_test(stringSuite, "TestStringIteratorAllocated", TestStringIteratorAllocated))
	{
		printf("%s\n", CU_get_error_msg());
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_pSuite vectorSuite = CU_add_suite("Vector Testing Suite",
		VectorInitializeSuite,
		VectorCleanUpSuite);

	if (vectorSuite == NULL)
	{
		printf("%s\n", CU_get_error_msg());
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (!CU_add_test(vectorSuite, "TestVectorStringVFTableUninitializedCompleteObjectLocator", TestVectorStringVFTableUninitializedCompleteObjectLocator) ||
		!CU_add_test(vectorSuite, "TestVectorStringNew", TestVectorStringNew) ||
		!CU_add_test(vectorSuite, "TestVectorStringDelete", TestVectorStringDelete) ||
		!CU_add_test(vectorSuite, "TestVectorStringCopyConstructor", TestVectorStringCopyConstructor) ||
		!CU_add_test(vectorSuite, "TestVectorStringRealloc", TestVectorStringRealloc) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableEquals", TestVectorStringVFTableEquals) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableNotSameSizeEquals", TestVectorStringVFTableNotSameSizeEquals) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableNotEquals", TestVectorStringVFTableNotEquals) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableCompareTo", TestVectorStringVFTableCompareTo) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableNotSameSizeCompareTo", TestVectorStringVFTableNotSameSizeCompareTo) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableNotCompareTo", TestVectorStringVFTableNotCompareTo) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableToString", TestVectorStringVFTableToString) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableAdd", TestVectorStringVFTableAdd) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableClear", TestVectorStringVFTableClear) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableRemove", TestVectorStringVFTableRemove) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableContains", TestVectorStringVFTableContains) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableNotContains", TestVectorStringVFTableNotContains) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableCopy", TestVectorStringVFTableCopy) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableIsEmpty", TestVectorStringVFTableIsEmpty) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableSize", TestVectorStringVFTableSize) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableSet", TestVectorStringVFTableSet) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableGet", TestVectorStringVFTableGet) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableOutOfBoundsGet", TestVectorStringVFTableOutOfBoundsGet) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableMovePushFront", TestVectorStringVFTableMovePushFront) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTablePushFront", TestVectorStringVFTablePushFront) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableMovePushBack", TestVectorStringVFTableMovePushBack) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTablePushBack", TestVectorStringVFTablePushBack) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableMoveInsert", TestVectorStringVFTableMoveInsert) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableMoveInsertOutOfBounds", TestVectorStringVFTableMoveInsertOutOfBounds) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableInsert", TestVectorStringVFTableInsert) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableInsertOutOfBounds", TestVectorStringVFTableInsertOutOfBounds) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableFind", TestVectorStringVFTableFind) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableNPOSFind", TestVectorStringVFTableNPOSFind) ||
		!CU_add_test(vectorSuite, "TestVectorStringVFTableReplace", TestVectorStringVFTableReplace) ||
		!CU_add_test(vectorSuite, "TestVectorIterator", TestVectorIterator))
	{
		printf("%s\n", CU_get_error_msg());
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_pSuite castsSuite = CU_add_suite("Casting Testing Suite",
		CastsInitializeSuite,
		CastsCleanUpSuite);

	if (castsSuite == NULL)
	{
		printf("%s\n", CU_get_error_msg());
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (!CU_add_test(castsSuite, "TestValidUpcast", TestValidUpcast) ||
		!CU_add_test(castsSuite, "TestValidDowncast", TestValidDowncast) ||
		!CU_add_test(castsSuite, "TestMoveSemantics", TestMoveSemantics) ||
		!CU_add_test(castsSuite, "TestInvalidDowncast", TestInvalidDowncast))
	{
		printf("%s\n", CU_get_error_msg());
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_pSuite setSuite = CU_add_suite("Set Testing Suite",
		SetInitializeSuite,
		SetCleanUpSuite);

	if (setSuite == NULL)
	{
		printf("%s\n", CU_get_error_msg());
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (!CU_add_test(setSuite, "TestSetStringVFTableUninitializedCompleteObjectLocator", TestSetStringVFTableUninitializedCompleteObjectLocator) ||
		!CU_add_test(setSuite, "TestSetStringNew", TestSetStringNew) ||
		!CU_add_test(setSuite, "TestSetStringDelete", TestSetStringDelete) ||
		!CU_add_test(setSuite, "TestSetStringCopyConstructor", TestSetStringCopyConstructor) ||
		!CU_add_test(setSuite, "TestSetStringVFTableEquals", TestSetStringVFTableEquals) ||
		!CU_add_test(setSuite, "TestSetStringVFTableNotSameSizeEquals", TestSetStringVFTableNotSameSizeEquals) ||
		!CU_add_test(setSuite, "TestSetStringVFTableNotEquals", TestSetStringVFTableNotEquals) ||
		!CU_add_test(setSuite, "TestSetStringVFTableCompareTo", TestSetStringVFTableCompareTo) ||
		!CU_add_test(setSuite, "TestSetStringVFTableNotSameSizeCompareTo", TestSetStringVFTableNotSameSizeCompareTo) ||
		!CU_add_test(setSuite, "TestSetStringVFTableNotCompareTo", TestSetStringVFTableNotCompareTo) ||
		!CU_add_test(setSuite, "TestSetStringVFTableToString", TestSetStringVFTableToString) ||
		!CU_add_test(setSuite, "TestSetStringVFTableAdd", TestSetStringVFTableAdd) ||
		!CU_add_test(setSuite, "TestSetStringVFTableClear", TestSetStringVFTableClear) ||
		!CU_add_test(setSuite, "TestSetStringVFTableRemove", TestSetStringVFTableRemove) ||
		!CU_add_test(setSuite, "TestSetStringVFTableRemoveLots", TestSetStringVFTableRemoveLots) ||
		!CU_add_test(setSuite, "TestSetStringVFTableContains", TestSetStringVFTableContains) ||
		!CU_add_test(setSuite, "TestSetStringVFTableNotContains", TestSetStringVFTableNotContains) ||
		!CU_add_test(setSuite, "TestSetStringVFTableCopy", TestSetStringVFTableCopy) ||
		!CU_add_test(setSuite, "TestSetStringVFTableIsEmpty", TestSetStringVFTableIsEmpty) ||
		!CU_add_test(setSuite, "TestSetStringVFTableSize", TestSetStringVFTableSize) ||
		!CU_add_test(setSuite, "TestSetStringVFTableSet", TestSetStringVFTableSet) ||
		!CU_add_test(setSuite, "TestSetStringVFTableMoveInsert", TestSetStringVFTableMoveInsert) ||
		!CU_add_test(setSuite, "TestSetStringVFTableMoveInsertLots", TestSetStringVFTableMoveInsertLots) ||
		!CU_add_test(setSuite, "TestSetStringVFTableInsert", TestSetStringVFTableInsert) ||
		!CU_add_test(setSuite, "TestSetStringVFTableInsertLots", TestSetStringVFTableInsertLots) ||
		!CU_add_test(setSuite, "TestSetStringVFTableFind", TestSetStringVFTableFind) ||
		!CU_add_test(setSuite, "TestSetStringVFTableNPOSFind", TestSetStringVFTableNPOSFind) ||
		!CU_add_test(setSuite, "TestSetStringVFTableReplace", TestSetStringVFTableReplace) ||
		!CU_add_test(setSuite, "TestSetIterator", TestSetIterator))
	{
		printf("%s\n", CU_get_error_msg());
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_pSuite mapSuite = CU_add_suite("Map Testing Suite",
		SetInitializeSuite,
		SetCleanUpSuite);

	if (mapSuite == NULL)
	{
		printf("%s\n", CU_get_error_msg());
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (!CU_add_test(mapSuite, "TestMapStringVFTableUninitializedCompleteObjectLocator", TestMapStringVFTableUninitializedCompleteObjectLocator) ||
		!CU_add_test(mapSuite, "TestMapStringNew", TestMapStringNew) ||
		!CU_add_test(mapSuite, "TestMapStringDelete", TestMapStringDelete) ||
		!CU_add_test(mapSuite, "TestMapStringCopyConstructor", TestMapStringCopyConstructor) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableEquals", TestMapStringVFTableEquals) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableNotSameSizeEquals", TestMapStringVFTableNotSameSizeEquals) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableNotEquals", TestMapStringVFTableNotEquals) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableCompareTo", TestMapStringVFTableCompareTo) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableNotSameSizeCompareTo", TestMapStringVFTableNotSameSizeCompareTo) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableNotCompareTo", TestMapStringVFTableNotCompareTo) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableToString", TestMapStringVFTableToString) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableAdd", TestMapStringVFTableAdd) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableClear", TestMapStringVFTableClear) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableRemove", TestMapStringVFTableRemove) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableRemoveLots", TestMapStringVFTableRemoveLots) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableContains", TestMapStringVFTableContains) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableNotContains", TestMapStringVFTableNotContains) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableCopy", TestMapStringVFTableCopy) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableIsEmpty", TestMapStringVFTableIsEmpty) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableSize", TestMapStringVFTableSize) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableSet", TestMapStringVFTableSet) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableMoveInsert", TestMapStringVFTableMoveInsert) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableMoveInsertLots", TestMapStringVFTableMoveInsertLots) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableInsert", TestMapStringVFTableInsert) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableInsertLots", TestMapStringVFTableInsertLots) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableFind", TestMapStringVFTableFind) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableNPOSFind", TestMapStringVFTableNPOSFind) ||
		!CU_add_test(mapSuite, "TestMapStringVFTableReplace", TestMapStringVFTableReplace) ||
		!CU_add_test(mapSuite, "TestMapIterator", TestMapIterator))
	{
		printf("%s\n", CU_get_error_msg());
		CU_cleanup_registry();
		return CU_get_error();
	}

    // Run all tests using CUnit Basic interface which outputs
    // results to command-line.
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // Run all tests using CUnit Automated interface which outputs
    // results to a file, default name CUnitAutomated-Results.xml.
    // DTD CUnit-Run.dtd and and XSL stylesheet CUnit-Run.xsl in Share/
    // Uncomment this line to override default output file prefix.
    // CU_set_output_filename("Test");
    CU_list_tests_to_file();

    // Output listing of tests in suites to a file, default name
    // CUnitAutomated-Listing.xml
    // DTD CUnit-List.dtd and and XSL stylesheet CUnit-List.xsl in Share/
    CU_automated_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}
