#include "ooc_container_cunit_test.h"

int ContainerInitializeSuite()
{
   return 0;
}

int ContainerCleanUpSuite()
{
    return 0;
}

void TestContainerVFTableUninitializedCompleteContainerLocator()
{
	CU_ASSERT_PTR_EQUAL(containerVFTable.pCompleteContainerLocator, NULL);
}

void TestContainerVFTableInitializedCompleteContainerLocator()
{
	//manually allocates and deallocates an container
	//this should __NOT__ be done in a real program
	//since container is an abstract container
	
	//allocate a new container
	void* container = calloc(1, sizeof(Container));

	//allocate vftable
	((Container*)container)->pVFTable = calloc(1, sizeof(Container));

	//call constructor to set up container
	ContainerConstruct(container);

	CU_ASSERT_PTR_EQUAL(containerVFTable.pCompleteContainerLocator, &containerCompleteContainerLocator);

	//call destructor
	ContainerDestruct(container);

	//free vftable
	free(((Container*)container)->pVFTable);

	//free the string's resources
	free(container);

	//NULL the pointer, so we don't have use after free vulns
	container = NULL;
}

void TestContainerNew()
{
	void* container = NewContainer();
	CU_ASSERT_PTR_EQUAL(container, NULL);
}

void TestContainerDelete()
{
	//pointer value could be random
	void* container = NULL;
	DeleteContainer(container);
	CU_ASSERT_PTR_EQUAL(container, NULL);
}

void TestContainerConstructor()
{
	//manually allocates and deallocates an container
	//this should __NOT__ be done in a real program
	//since container is an abstract container

	//allocate a new container
	void* container = calloc(1, sizeof(Container));

	//allocate vftable
	((Container*)container)->pVFTable = calloc(1, sizeof(Container));

	//call constructor to set up container
	ContainerConstruct(container);

	//verify that the vftable is pointing in a different memory location
	CU_ASSERT_PTR_NOT_EQUAL(((Container*)container)->pVFTable, &containerVFTable);

	//call destructor
	ContainerDestruct(container);

	//free vftable
	free(((Container*)container)->pVFTable);

	//free the string's resources
	free(container);

	//NULL the pointer, so we don't have use after free vulns
	container = NULL;
}

void TestContainerCopyConstructor()
{
	//pointer value could be random
	void* container = NULL;
	void* other_container = ContainerCopyConstruct(container);
	//tests that the container isn't allocated and thus, equals NULL
	CU_ASSERT_PTR_EQUAL(other_container, NULL);
}

void TestContainerDestructor()
{
	//manually allocates and deallocates an container
	//this should __NOT__ be done in a real program
	//since container is an abstract container

	//allocate a new container
	void* container = calloc(1, sizeof(Container));

	//allocate vftable
	((Container*)container)->pVFTable = calloc(1, sizeof(Container));

	//call constructor to set up container
	ContainerConstruct(container);

	//call destructor
	ContainerDestruct(container);

	//Show that nothing happens after destructor is called since the destructor does not do anything
	CU_ASSERT_PTR_NOT_EQUAL(((Container*)container)->pVFTable, &containerVFTable);

	//free vftable
	free(((Container*)container)->pVFTable);

	//free the string's resources
	free(container);

	//NULL the pointer, so we don't have use after free vulns
	container = NULL;
}

void TestContainerVFTableEquals()
{
	//compile time check
	CU_ASSERT_PTR_EQUAL(containerVFTable.equals, ContainerEquals);

	//manually allocates and deallocates an container
	//this should __NOT__ be done in a real program
	//since container is an abstract container

	//allocate a new container
	void* container = calloc(1, sizeof(Container));

	//allocate vftable
	((Container*)container)->pVFTable = calloc(1, sizeof(Container));

	//call constructor to set up container
	ContainerConstruct(container);

	//allocate a new container
	void* other_container = calloc(1, sizeof(Container));

	//allocate vftable
	((Container*)other_container)->pVFTable = calloc(1, sizeof(Container));

	//call constructor to set up container
	ContainerConstruct(other_container);

	//test for equals
	CU_ASSERT_TRUE(((ContainerVFTable*)((Container*)container)->pVFTable)->equals(container, other_container));
	CU_ASSERT_TRUE(((ContainerVFTable*)((Container*)other_container)->pVFTable)->equals(other_container, container));
	CU_ASSERT_TRUE(ContainerEquals(other_container, container));

	//call destructor
	ContainerDestruct(other_container);

	//free vftable
	free(((Container*)other_container)->pVFTable);

	//free the string's resources
	free(other_container);

	//call destructor
	ContainerDestruct(container);

	//free vftable
	free(((Container*)container)->pVFTable);

	//free the string's resources
	free(container);

	//NULL the pointer, so we don't have use after free vulns
	container = NULL;
}

void TestContainerVFTableContainerToString()
{
	//compile time check
	CU_ASSERT_PTR_EQUAL(containerVFTable.toString, ContainerToString);

	//manually allocates and deallocates an container
	//this should __NOT__ be done in a real program
	//since container is an abstract container

	//allocate a new container
	void* container = calloc(1, sizeof(Container));

	//allocate vftable
	((Container*)container)->pVFTable = calloc(1, sizeof(Container));

	//call constructor to set up container
	ContainerConstruct(container);

	CU_ASSERT_STRING_EQUAL(((ContainerVFTable*)((Container*)container)->pVFTable)->toString(container), "Container");
	CU_ASSERT_STRING_EQUAL(ContainerToString(container), "Container");

	//call destructor
	ContainerDestruct(container);

	//free vftable
	free(((Container*)container)->pVFTable);

	//free the string's resources
	free(container);

	//NULL the pointer, so we don't have use after free vulns
	container = NULL;
}