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
		!CU_add_test(stringSuite, "TestStringVFTableStringIsEmpty", TestStringVFTableStringIsEmpty) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringSize", TestStringVFTableStringSize) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringSet", TestStringVFTableStringSet) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringSetAllocated", TestStringVFTableStringSetAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringSetAlreadyAllocated", TestStringVFTableStringSetAlreadyAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringC_Str", TestStringVFTableStringC_Str) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringAppend", TestStringVFTableStringAppend) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringAppendAllocated", TestStringVFTableStringAppendAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringAppendAlreadyAllocated", TestStringVFTableStringAppendAlreadyAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringFind", TestStringVFTableStringFind) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringFindHayStackAllocated", TestStringVFTableStringFindHayStackAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringFindNeedleAllocated", TestStringVFTableStringFindNeedleAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringFindHayStackAllocatedNeedleAllocated", TestStringVFTableStringFindHayStackAllocatedNeedleAllocated) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringFindNull", TestStringVFTableStringFindNull) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringSubString", TestStringVFTableStringSubString) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringSubStringLessThanZero", TestStringVFTableStringSubStringLessThanZero) ||
		!CU_add_test(stringSuite, "TestStringVFTableStringSubStringOutOfBounds", TestStringVFTableStringSubStringOutOfBounds) ||
		!CU_add_test(stringSuite, "TestStringNew", TestStringNew))
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
