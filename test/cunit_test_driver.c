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

/*
 * Set up and run tests.
 *
 * @return CUE_SUCCESS if successful, else a CUnit error code if
 * any problems arise.
 */
 * 
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
