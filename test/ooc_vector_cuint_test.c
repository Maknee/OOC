#include "ooc_vector_cuint_test.h"

int VectorStringInitializeSuite()
{
	return 0;
}

int VectorStringCleanUpSuite()
{
	return 0;
}

void TestVectorStringVFTableUninitializedCompleteObjectLocator()
{
	CU_ASSERT_PTR_EQUAL(VectorStringvfTable.pCompleteObjectLocator, NULL);
}

void TestVectorStringNew()
{
	//allocate a new vector_string
	void* vector_string = NewVectorString();
	
	//vector_string should be allocated
	CU_ASSERT_PTR_NOT_EQUAL(vector_string, NULL);

	//free the vector_string's resources
	DeleteVectorString(vector_string);

	//manual delete vector_string call does not set vector_string to null :(
	CU_ASSERT_PTR_NOT_EQUAL(vector_string, NULL);
}

void TestVectorStringDelete()
{
	//allocate a new vector_string
	void* vector_string = NewVectorString();

	//vector_string should be allocated
	CU_ASSERT_PTR_NOT_EQUAL(vector_string, NULL);

	//free the vector_string's resources
	Delete(VectorString, vector_string);

	//macro delete vector_string sets vector_string to null :)
	CU_ASSERT_PTR_EQUAL(vector_string, NULL);
}

void TestVectorStringCopyConstructor()
{
	//allocate a new vector_string
	void* s1 = New(VectorString);

	//vector_string copy
	void* s2 = Call(VectorString, copy, s1);

	//check that the objects are allocated in different regions
	CU_ASSERT_PTR_NOT_EQUAL(s1, s2);

	//free the vector_string's resources
	Delete(VectorString, s2);
	Delete(VectorString, s1);
	
	//check that the pointers are freed
	CU_ASSERT_PTR_EQUAL(s1, NULL);
	CU_ASSERT_PTR_EQUAL(s2, NULL);
}

void TestVectorStringVFTableEquals()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Allocate a new vector of strings
	Vector(String) vector2 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), push_back, vector2, random_string1);

	//Check if two vectors are equal
	Call(Vector(String), equals, vector1, vector2);

	//Delete vector of strings
	Delete(Vector(String), vector2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableToString()
{
	//Allocate a new vector of strings
	Vector(String) vector = New(Vector(String));

	//Check if toString works
	CU_ASSERT_STRING_EQUAL(SafeCall(Vector(String), toString, vector), "VectorString");

	//Delete vector of strings
	Delete(Vector(String), vector);
}

void TestVectorStringVFTableAdd()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Allocate a new vector of strings
	Vector(String) vector2 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), add, vector1, random_string1);

	//Add a new string to vector 2
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), add, vector2, random_string1);

	//Check if two vectors are equal
	Call(Vector(String), equals, vector1, vector2);

	//Delete vector of strings
	Delete(Vector(String), vector2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}