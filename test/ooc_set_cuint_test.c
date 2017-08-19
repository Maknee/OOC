#include "ooc_set_cuint_test.h"

int SetInitializeSuite()
{
	return 0;
}

int SetCleanUpSuite()
{
	return 0;
}

void TestSetStringVFTableUninitializedCompleteObjectLocator()
{
	CU_ASSERT_PTR_EQUAL(SetStringvfTable.pCompleteObjectLocator, NULL);
}

void TestSetStringNew()
{
	//allocate a new set_string
	void* set_string = NewSetString();
	
	//set_string should be allocated
	CU_ASSERT_PTR_NOT_EQUAL(set_string, NULL);

	//free the set_string's resources
	DeleteSetString(set_string);

	//manual delete set_string call does not set set_string to null :(
	CU_ASSERT_PTR_NOT_EQUAL(set_string, NULL);
}

void TestSetStringDelete()
{
	//allocate a new set_string
	void* set_string = NewSetString();

	//set_string should be allocated
	CU_ASSERT_PTR_NOT_EQUAL(set_string, NULL);

	//free the set_string's resources
	Delete(SetString, set_string);

	//macro delete set_string sets set_string to null :)
	CU_ASSERT_PTR_EQUAL(set_string, NULL);
}

void TestSetStringCopyConstructor()
{
	//allocate a new set_string
	void* s1 = New(SetString);

	//set_string copy
	void* s2 = Call(SetString, copy, s1);

	//check that the objects are allocated in different regions
	CU_ASSERT_PTR_NOT_EQUAL(s1, s2);

	//free the set_string's resources
	Delete(SetString, s2);
	Delete(SetString, s1);
	
	//check that the pointers are freed
	CU_ASSERT_PTR_EQUAL(s1, NULL);
	CU_ASSERT_PTR_EQUAL(s2, NULL);
}

void TestSetStringVFTableEquals()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Allocate a new set of strings
	Set(String) set2 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Set(String), move_insert, set1, random_string1);

	//Add a new string to set 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Set(String), move_insert, set2, random_string2);

	//Check if two sets are equal
	CU_ASSERT_TRUE(Call(Set(String), equals, set1, set2));

	//Delete set of strings
	Delete(Set(String), set2);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableNotSameSizeEquals()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Allocate a new set of strings
	Set(String) set2 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Set(String), move_insert, set1, random_string1);

	//Add a new string to set 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Set(String), move_insert, set2, random_string2);

	//Add a new string to set 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "Testing1");
	Call(Set(String), move_insert, set2, random_string3);

	//Check if two sets are equal
	CU_ASSERT_FALSE(Call(Set(String), equals, set1, set2));

	//Delete set of strings
	Delete(Set(String), set2);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableNotEquals()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Allocate a new set of strings
	Set(String) set2 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Set(String), move_insert, set1, random_string1);

	//Add a new string to set 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Tesssssting");
	Call(Set(String), move_insert, set2, random_string2);

	//Check if two sets are equal
	CU_ASSERT_FALSE(Call(Set(String), equals, set1, set2));

	//Delete set of strings
	Delete(Set(String), set2);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableCompareTo()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Allocate a new set of strings
	Set(String) set2 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Set(String), move_insert, set1, random_string1);

	//Add a new string to set 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Set(String), move_insert, set2, random_string2);

	//Check if two sets are equal
	CU_ASSERT_EQUAL(Call(Set(String), compareTo, set1, set2), 0);

	//Delete set of strings
	Delete(Set(String), set2);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableNotSameSizeCompareTo()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Allocate a new set of strings
	Set(String) set2 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Set(String), move_insert, set1, random_string1);

	//Add a new string to set 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Set(String), move_insert, set2, random_string2);

	//Add a new string to set 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "Testing1");
	Call(Set(String), move_insert, set2, random_string3);

	//Check if two sets are equal
	CU_ASSERT_NOT_EQUAL(Call(Set(String), compareTo, set1, set2), 0);

	//Delete set of strings
	Delete(Set(String), set2);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableNotCompareTo()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Allocate a new set of strings
	Set(String) set2 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Set(String), move_insert, set1, random_string1);

	//Add a new string to set 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Tesssssting");
	Call(Set(String), move_insert, set2, random_string2);

	//Check if two sets are equal
	CU_ASSERT_NOT_EQUAL(Call(Set(String), compareTo, set1, set2), 0);

	//Delete set of strings
	Delete(Set(String), set2);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableToString()
{
	//Allocate a new set of strings
	Set(String) set = New(Set(String));

	//Check if toString works
	CU_ASSERT_STRING_EQUAL(Call(Set(String), toString, set), "SetString");

	//Delete set of strings
	Delete(Set(String), set);
}

void TestSetStringVFTableAdd()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Allocate a new set of strings
	Set(String) set2 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Set(String), add, set1, random_string1);

	//Add a new string to set 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Set(String), add, set2, random_string2);

	//Check if two sets are equal
	CU_ASSERT_TRUE(Call(Set(String), equals, set1, set2));

	//Have to delete strings since they are copied
	Delete(String, random_string1);
	Delete(String, random_string2);

	//Delete set of strings
	Delete(Set(String), set2);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableClear()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Set(String), move_insert, set1, random_string1);

	//Clear set
	Call(Set(String), clear, set1);

	//Check if set is empty
	CU_ASSERT_TRUE(Call(Set(String), isEmpty, set1));

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableRemove()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Set(String), move_insert, set1, random_string1);

	//Test if thie string exists in set and remove
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Set(String), remove, set1, random_string2);

	//Check if set is empty
	CU_ASSERT_TRUE(Call(Set(String), isEmpty, set1));

	//try to remove again
	CU_ASSERT_FALSE(Call(Set(String), remove, set1, random_string2));

	Delete(String, random_string2);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableRemoveLots()
{
	//Allocate a new set of int
	Set(int) set1 = New(Set(int));

	Call(Set(int), insert, set1, 1);
	Call(Set(int), insert, set1, 123);
	Call(Set(int), insert, set1, 512);
	Call(Set(int), insert, set1, 55);
	Call(Set(int), insert, set1, 43);
	Call(Set(int), insert, set1, 2);
	Call(Set(int), insert, set1, 65);
	Call(Set(int), insert, set1, -12);
	Call(Set(int), insert, set1, 32);
	Call(Set(int), insert, set1, 532);
	Call(Set(int), insert, set1, 231);
	Call(Set(int), insert, set1, 36234);
	Call(Set(int), insert, set1, 6345);

	CU_ASSERT_TRUE(Call(Set(int), remove, set1, 1));
	CU_ASSERT_TRUE(Call(Set(int), remove, set1, 123));
	CU_ASSERT_TRUE(Call(Set(int), remove, set1, 512));
	CU_ASSERT_TRUE(Call(Set(int), remove, set1, 55));
	CU_ASSERT_TRUE(Call(Set(int), remove, set1, 43));
	CU_ASSERT_TRUE(Call(Set(int), remove, set1, 2));
	CU_ASSERT_TRUE(Call(Set(int), remove, set1, 65));
	CU_ASSERT_TRUE(Call(Set(int), remove, set1, -12));
	CU_ASSERT_TRUE(Call(Set(int), remove, set1, 32));
	CU_ASSERT_TRUE(Call(Set(int), remove, set1, 532));
	CU_ASSERT_TRUE(Call(Set(int), remove, set1, 231));
	CU_ASSERT_TRUE(Call(Set(int), remove, set1, 36234));
	CU_ASSERT_TRUE(Call(Set(int), remove, set1, 6345));

	//Delete set of int
	Delete(Set(int), set1);
}


void TestSetStringVFTableContains()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");

	CU_ASSERT_FALSE(Call(Set(String), contains, set1, random_string2));

	Call(Set(String), move_insert, set1, random_string1);

	//Test if thie string exists in set and remove
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	CU_ASSERT_TRUE(Call(Set(String), contains, set1, random_string2));

	Delete(String, random_string2);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableNotContains()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Set(String), move_insert, set1, random_string1);

	//Test if thie string exists in set and remove
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testinwwwwwwwwg");
	CU_ASSERT_FALSE(Call(Set(String), contains, set1, random_string2));

	Delete(String, random_string2);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableCopy()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Set(String), move_insert, set1, random_string1);

	//Copy set
	Set(String) set2 = Call(Set(String), copy, set1);
	
	//Check if two sets are equal
	CU_ASSERT_TRUE(Call(Set(String), equals, set1, set2));

	//Delete set of strings
	Delete(Set(String), set2);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableIsEmpty()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Set(String), move_insert, set1, random_string1);

	//Test if thie string exists in set and remove
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Set(String), remove, set1, random_string2);

	//Check if set is empty
	CU_ASSERT_TRUE(Call(Set(String), isEmpty, set1));

	Delete(String, random_string2);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableSize()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Set(String), move_insert, set1, random_string1);

	//Add a new string to set 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Set(String), move_insert, set1, random_string2);

	//Check if two sets are equal
	CU_ASSERT_EQUAL(Call(Set(String), size, set1), 1);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableSet()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");

	//Add a new string to set 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");

	//Check if two sets are equal
	CU_ASSERT_PTR_NOT_EQUAL(Call(Set(String), set, set1, Initializer_List(String, random_string1, random_string2)), NULL);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableMoveInsert()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "a");
	Call(Set(String), move_insert, set1, random_string1);

	//Add a new string to set 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "b");
	Call(Set(String), move_insert, set1, random_string2);

	//Add a new string to set 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "c");
	Call(Set(String), move_insert, set1, random_string3);

	String* equal_random_string3 = Call(Set(String), find, set1, random_string3);

	//Check if they are equal
	CU_ASSERT_PTR_EQUAL(random_string3, *equal_random_string3);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableMoveInsertLots()
{
	//Allocate a new set of int
	Set(int) set1 = New(Set(int));

	Call(Set(int), move_insert, set1, 13213);
	Call(Set(int), move_insert, set1, 1123);
	Call(Set(int), move_insert, set1, 5212);
	Call(Set(int), move_insert, set1, 525);
	Call(Set(int), move_insert, set1, 435);
	Call(Set(int), move_insert, set1, 2);
	Call(Set(int), move_insert, set1, 652);
	Call(Set(int), move_insert, set1, -12);
	Call(Set(int), move_insert, set1, 32);
	Call(Set(int), move_insert, set1, 532);
	Call(Set(int), move_insert, set1, 231);
	Call(Set(int), move_insert, set1, 36234);
	Call(Set(int), move_insert, set1, 6345);
	Call(Set(int), move_insert, set1, 23);
	Call(Set(int), move_insert, set1, 532);
	Call(Set(int), move_insert, set1, 56);
	Call(Set(int), move_insert, set1, 221);
	Call(Set(int), move_insert, set1, 31234);
	Call(Set(int), move_insert, set1, 6345);

	//Delete set of int
	Delete(Set(int), set1);
}

void TestSetStringVFTableInsert()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "a");
	Call(Set(String), move_insert, set1, random_string1);

	//Add a new string to set 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "b");
	Call(Set(String), move_insert, set1, random_string2);

	//Add a new string to set 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "b");

	String* equal_random_string2 = Call(Set(String), find, set1, random_string3);

	Delete(String, random_string3);
	
	//Check if they are equal
	CU_ASSERT_PTR_EQUAL(random_string2, *equal_random_string2);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableInsertLots()
{
	//Allocate a new set of int
	Set(int) set1 = New(Set(int));

	Call(Set(int), insert, set1, 13213);
	Call(Set(int), insert, set1, 1123);
	Call(Set(int), insert, set1, 5212);
	Call(Set(int), insert, set1, 525);
	Call(Set(int), insert, set1, 435);
	Call(Set(int), insert, set1, 2);
	Call(Set(int), insert, set1, 652);
	Call(Set(int), insert, set1, -12);
	Call(Set(int), insert, set1, 32);
	Call(Set(int), insert, set1, 532);
	Call(Set(int), insert, set1, 231);
	Call(Set(int), insert, set1, 36234);
	Call(Set(int), insert, set1, 6345);
	Call(Set(int), insert, set1, 23);
	Call(Set(int), insert, set1, 532);
	Call(Set(int), insert, set1, 56);
	Call(Set(int), insert, set1, 221);
	Call(Set(int), insert, set1, 31234);
	Call(Set(int), insert, set1, 6345);

	//Delete set of int
	Delete(Set(int), set1);
}

void TestSetStringVFTableFind()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "a");
	
	CU_ASSERT_PTR_EQUAL(*(Call(Set(String), find, set1, random_string1)), NULL);
	
	Call(Set(String), move_insert, set1, random_string1);

	//Add a new string to set 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "b");
	Call(Set(String), move_insert, set1, random_string2);

	//Add a new string to set 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "b");

	//Find random_string2
	CU_ASSERT_TRUE(Call(String, equals, *(Call(Set(String), find, set1, random_string3)), random_string2));

	Delete(String, random_string3);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableNPOSFind()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "a");
	Call(Set(String), move_insert, set1, random_string1);

	//Add a new string to set 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "b");
	Call(Set(String), move_insert, set1, random_string2);

	//Add a new string to set 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "wwww");

	//Find random_string2
	CU_ASSERT_EQUAL(Call(Set(String), find, set1, random_string3), NULL);

	Delete(String, random_string3);

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetStringVFTableReplace()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "a");

	CU_ASSERT_FALSE(Call(Set(String), replace, set1, random_string1, random_string1));

	Call(Set(String), move_insert, set1, random_string1);

	//Add a new string to set 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "b");

	CU_ASSERT_FALSE(Call(Set(String), replace, set1, random_string2, random_string1));

	Call(Set(String), move_insert, set1, random_string2);

	//Add a new string to set 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "c");

	//replace random_string2
	CU_ASSERT_TRUE(Call(Set(String), replace, set1, random_string2, random_string3));

	String* tmp = Call(Set(String), find, set1, random_string3);
	
	//see that it is now 3
	CU_ASSERT_STRING_EQUAL(Call(String, c_str, *tmp), Call(String, c_str, random_string3));

	//Delete set of strings
	Delete(Set(String), set1);
}

void TestSetIterator()
{
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "a");
	Call(Set(String), move_insert, set1, random_string1);

	//Add a new string to set 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "b");
	Call(Set(String), move_insert, set1, random_string2);

	//Add a new string to set 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "c");
	Call(Set(String), move_insert, set1, random_string3);

	ForEach(String* s, Set(String), set1,
	{
		Call(String, set, *s, "l");
	})

	//see that it is now l
	CU_ASSERT_STRING_EQUAL(Call(String, c_str, random_string1), "l");
	CU_ASSERT_STRING_EQUAL(Call(String, c_str, random_string2), "l");
	CU_ASSERT_STRING_EQUAL(Call(String, c_str, random_string3), "l");

	//Delete set of strings
	Delete(Set(String), set1);
}
