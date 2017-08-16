#include "ooc_vector_cuint_test.h"

int VectorInitializeSuite()
{
	return 0;
}

int VectorCleanUpSuite()
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

void TestVectorStringRealloc()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	for (size_t i = 0; i < 30; i++)
	{
		String random_string1 = New(String);
		Call(String, set, random_string1, "Testing");
		Call(Vector(String), move_push_back, vector1, random_string1);
	}

	//Check if vector has a size of 30
	CU_ASSERT_EQUAL(Call(Vector(String), size, vector1), 30);

	//Delete vector of strings
	Delete(Vector(String), vector1);
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
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Vector(String), move_push_back, vector2, random_string2);

	//Check if two vectors are equal
	CU_ASSERT_TRUE(Call(Vector(String), equals, vector1, vector2));

	//Delete vector of strings
	Delete(Vector(String), vector2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableNotSameSizeEquals()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Allocate a new vector of strings
	Vector(String) vector2 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Vector(String), move_push_back, vector2, random_string2);

	//Add a new string to vector 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "Testing");
	Call(Vector(String), move_push_back, vector2, random_string3);

	//Check if two vectors are equal
	CU_ASSERT_FALSE(Call(Vector(String), equals, vector1, vector2));

	//Delete vector of strings
	Delete(Vector(String), vector2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableNotEquals()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Allocate a new vector of strings
	Vector(String) vector2 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Tesssssting");
	Call(Vector(String), move_push_back, vector2, random_string2);

	//Check if two vectors are equal
	CU_ASSERT_FALSE(Call(Vector(String), equals, vector1, vector2));

	//Delete vector of strings
	Delete(Vector(String), vector2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableCompareTo()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Allocate a new vector of strings
	Vector(String) vector2 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Vector(String), move_push_back, vector2, random_string2);

	//Check if two vectors are equal
	CU_ASSERT(Call(Vector(String), compareTo, vector1, vector2), 0);

	//Delete vector of strings
	Delete(Vector(String), vector2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableNotSameSizeCompareTo()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Allocate a new vector of strings
	Vector(String) vector2 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Vector(String), move_push_back, vector2, random_string2);

	//Add a new string to vector 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "Testing");
	Call(Vector(String), move_push_back, vector2, random_string3);

	//Check if two vectors are equal
	CU_ASSERT_NOT_EQUAL(Call(Vector(String), compareTo, vector1, vector2), 0);

	//Delete vector of strings
	Delete(Vector(String), vector2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableNotCompareTo()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Allocate a new vector of strings
	Vector(String) vector2 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Tesssssting");
	Call(Vector(String), move_push_back, vector2, random_string2);

	//Check if two vectors are equal
	CU_ASSERT_NOT_EQUAL(Call(Vector(String), compareTo, vector1, vector2), 0);

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
	CU_ASSERT_STRING_EQUAL(Call(Vector(String), toString, vector), "VectorString");

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
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Vector(String), add, vector2, random_string2);

	//Check if two vectors are equal
	CU_ASSERT_TRUE(Call(Vector(String), equals, vector1, vector2));

	//Have to delete strings since they are copied
	Delete(String, random_string1);
	Delete(String, random_string2);

	//Delete vector of strings
	Delete(Vector(String), vector2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableClear()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Clear vector
	Call(Vector(String), clear, vector1);

	//Check if vector is empty
	CU_ASSERT_TRUE(Call(Vector(String), isEmpty, vector1));

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableRemove()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Test if thie string exists in vector and remove
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Vector(String), remove, vector1, random_string2);

	//Check if vector is empty
	CU_ASSERT_TRUE(Call(Vector(String), isEmpty, vector1));

	Delete(String, random_string2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableContains()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Test if thie string exists in vector and remove
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	CU_ASSERT_TRUE(Call(Vector(String), contains, vector1, random_string2));

	Delete(String, random_string2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableNotContains()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Test if thie string exists in vector and remove
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testinwwwwwwwwg");
	CU_ASSERT_FALSE(Call(Vector(String), contains, vector1, random_string2));

	Delete(String, random_string2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableCopy()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Copy vector
	Vector(String) vector2 = Call(Vector(String), copy, vector1);
	
	//Check if two vectors are equal
	CU_ASSERT_TRUE(Call(Vector(String), equals, vector1, vector2));

	//Delete vector of strings
	Delete(Vector(String), vector2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableIsEmpty()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Test if thie string exists in vector and remove
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Vector(String), remove, vector1, random_string2);

	//Check if vector is empty
	CU_ASSERT_TRUE(Call(Vector(String), isEmpty, vector1));

	Delete(String, random_string2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableSize()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string2);

	//Check if two vectors are equal
	CU_ASSERT_EQUAL(Call(Vector(String), size, vector1), 2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableSet()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");

	//Check if two vectors are equal
	CU_ASSERT_TRUE(Call(Vector(String), set, vector1, INITIALIZER_LIST(String, random_string1, random_string2)));

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableGet()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string2);

	//Get the second index
	int error = 0;
	String equal_random_string2 = Call(Vector(String), get, vector1, 1, &error);

	//Check if they are equal
	CU_ASSERT_EQUAL(error, 0);
	CU_ASSERT_PTR_EQUAL(random_string2, equal_random_string2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableOutOfBoundsGet()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string2);

	//Get the second index
	int error = 0;
	String equal_random_string2 = Call(Vector(String), get, vector1, 80, &error);

	//Check if they are equal
	CU_ASSERT_EQUAL(error, 1);
	CU_ASSERT_PTR_EQUAL(NULL, equal_random_string2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableMovePushFront()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Vector(String), move_push_front, vector1, random_string2);

	//Get the first index
	int error = 0;
	String equal_random_string2 = Call(Vector(String), get, vector1, 0, &error);
	//Check if they are equal
	CU_ASSERT_EQUAL(error, 0);
	CU_ASSERT_PTR_EQUAL(random_string2, equal_random_string2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTablePushFront()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Vector(String), push_front, vector1, random_string2);

	//Get the first index
	int error = 0;
	String equal_random_string2 = Call(Vector(String), get, vector1, 0, &error);
	//Check if they are equal
	CU_ASSERT_EQUAL(error, 0);
	CU_ASSERT_PTR_NOT_EQUAL(random_string2, equal_random_string2);

	//Delete strings
	Delete(String, random_string1);
	Delete(String, random_string2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableMovePushBack()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Vector(String), move_push_back, vector1, random_string2);

	//Get the second index
	int error = 0;
	String equal_random_string2 = Call(Vector(String), get, vector1, 1, &error);

	//Check if they are equal
	CU_ASSERT_EQUAL(error, 0);
	CU_ASSERT_PTR_EQUAL(random_string2, equal_random_string2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTablePushBack()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Vector(String), push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Vector(String), push_back, vector1, random_string2);

	//Get the second index
	int error = 0;
	String equal_random_string2 = Call(Vector(String), get, vector1, 1, &error);

	//Check if they are equal
	CU_ASSERT_EQUAL(error, 0);
	CU_ASSERT_PTR_NOT_EQUAL(random_string2, equal_random_string2);

	//Delete strings
	Delete(String, random_string1);
	Delete(String, random_string2);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableMoveInsert()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "a");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "b");
	Call(Vector(String), move_push_back, vector1, random_string2);

	//Add a new string to vector 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "c");
	Call(Vector(String), move_insert, vector1, random_string3, 1);

	//Get the second index
	int error = 0;
	String equal_random_string3 = Call(Vector(String), get, vector1, 1, &error);

	//Check if they are equal
	CU_ASSERT_EQUAL(error, 0);
	CU_ASSERT_PTR_EQUAL(random_string3, equal_random_string3);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableInsert()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "a");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "b");
	Call(Vector(String), move_push_back, vector1, random_string2);

	//Add a new string to vector 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "c");
	Call(Vector(String), insert, vector1, random_string3, 1);

	//Get the second index
	int error = 0;
	String equal_random_string3 = Call(Vector(String), get, vector1, 1, &error);

	//Check if they are equal
	CU_ASSERT_EQUAL(error, 0);
	CU_ASSERT_PTR_NOT_EQUAL(random_string3, equal_random_string3);

	//Delete String
	Delete(String, random_string3);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableMoveInsertOutOfBounds()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "a");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "b");
	Call(Vector(String), move_push_back, vector1, random_string2);

	//Add a new string to vector 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "c");
	CU_ASSERT_FALSE(Call(Vector(String), move_insert, vector1, random_string3, 1000));

	//failed to move_insert, so we have to handle
	Delete(String, random_string3);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableInsertOutOfBounds()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "a");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "b");
	Call(Vector(String), move_push_back, vector1, random_string2);

	//Add a new string to vector 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "c");
	CU_ASSERT_FALSE(Call(Vector(String), insert, vector1, random_string3, 1000));

	//failed to insert, so we have to handle
	Delete(String, random_string3);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableFind()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "a");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "b");
	Call(Vector(String), move_push_back, vector1, random_string2);

	//Add a new string to vector 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "b");

	//Find random_string2
	CU_ASSERT_EQUAL(Call(Vector(String), find, vector1, random_string3), 1);

	Delete(String, random_string3);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableNPOSFind()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "a");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "b");
	Call(Vector(String), move_push_back, vector1, random_string2);

	//Add a new string to vector 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "wwww");

	//Find random_string2
	CU_ASSERT_EQUAL(Call(Vector(String), find, vector1, random_string3), NPOS);

	Delete(String, random_string3);

	//Delete vector of strings
	Delete(Vector(String), vector1);
}

void TestVectorStringVFTableReplace()
{
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "a");
	Call(Vector(String), move_push_back, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "b");
	Call(Vector(String), move_push_back, vector1, random_string2);

	//Add a new string to vector 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "c");

	//replace random_string2
	CU_ASSERT_TRUE(Call(Vector(String), replace, vector1, random_string2, random_string3));

	int error = 0;
	String tmp = Call(Vector(String), get, vector1, 1, &error);
	
	CU_ASSERT_EQUAL(error, 0);

	//see that it is now 3
	CU_ASSERT_STRING_EQUAL(Call(String, c_str, tmp), Call(String, c_str, random_string3));

	//Delete vector of strings
	Delete(Vector(String), vector1);
}
