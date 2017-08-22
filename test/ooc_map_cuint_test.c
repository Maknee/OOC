#include "ooc_map_cuint_test.h"

int MapInitializeSuite()
{
	return 0;
}

int MapCleanUpSuite()
{
	return 0;
}

void TestMapStringVFTableUninitializedCompleteObjectLocator()
{
	CU_ASSERT_PTR_EQUAL(MapintStringvfTable.pCompleteObjectLocator, NULL);
}

void TestMapStringNew()
{
	//allocate a new map_string
	void* map_string = NewMapintString();
	
	//map_string should be allocated
	CU_ASSERT_PTR_NOT_EQUAL(map_string, NULL);

	//free the map_string's resources
	DeleteMapintString(map_string);

	//manual delete map_string call does not map map_string to null :(
	CU_ASSERT_PTR_NOT_EQUAL(map_string, NULL);
}

void TestMapStringDelete()
{
	//allocate a new map_string
	void* map_string = NewMapintString();

	//map_string should be allocated
	CU_ASSERT_PTR_NOT_EQUAL(map_string, NULL);

	//free the map_string's resources
	Delete(MapintString, map_string);

	//macro delete map_string maps map_string to null :)
	CU_ASSERT_PTR_EQUAL(map_string, NULL);
}

void TestMapStringCopyConstructor()
{
	//allocate a new map_string
	void* s1 = New(MapintString);

	//map_string copy
	void* s2 = Call(MapintString, copy, s1);

	//check that the objects are allocated in different regions
	CU_ASSERT_PTR_NOT_EQUAL(s1, s2);

	//free the map_string's resources
	Delete(MapintString, s2);
	Delete(MapintString, s1);
	
	//check that the pointers are freed
	CU_ASSERT_PTR_EQUAL(s1, NULL);
	CU_ASSERT_PTR_EQUAL(s2, NULL);
}

void TestMapStringVFTableEquals()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Allocate a new map of strings
	Map(int, String) map2 = New(Map(int, String));

	//Check if two maps are equal
	CU_ASSERT_TRUE(Call(Map(int, String), equals, map1, map2));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 1);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	Call(Map(int, String), move_insert, map2, entry2);

	//Check if two maps are equal
	CU_ASSERT_TRUE(Call(Map(int, String), equals, map1, map2));

	//Delete map of strings
	Delete(Map(int, String), map2);

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableNotSameSizeEquals()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Allocate a new map of strings
	Map(int, String) map2 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 1);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	Call(Map(int, String), move_insert, map2, entry2);

	//Add a new string to map 3
	Entry(int, String) entry3 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry3, 2);

	String random_string3 = New(String);
	Call(String, set, random_string3, "Testing");
	Call(Entry(int, String), move_set_value, entry3, random_string3);

	Call(Map(int, String), move_insert, map2, entry3);

	//Check if two maps are equal
	CU_ASSERT_FALSE(Call(Map(int, String), equals, map1, map2));

	//Delete map of strings
	Delete(Map(int, String), map2);

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableNotEquals()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Allocate a new map of strings
	Map(int, String) map2 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 1);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Tesssssting");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	Call(Map(int, String), move_insert, map2, entry2);

	//Check if two maps are equal
	CU_ASSERT_FALSE(Call(Map(int, String), equals, map1, map2));

	//Delete map of strings
	Delete(Map(int, String), map2);

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableCompareTo()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Allocate a new map of strings
	Map(int, String) map2 = New(Map(int, String));

	//Check if two maps are equal
	CU_ASSERT_EQUAL(Call(Map(int, String), compareTo, map1, map2), 0);

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 1);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	Call(Map(int, String), move_insert, map2, entry2);

	//Check if two maps are equal
	CU_ASSERT_EQUAL(Call(Map(int, String), compareTo, map1, map2), 0);

	//Delete map of strings
	Delete(Map(int, String), map2);

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableNotSameSizeCompareTo()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Allocate a new map of strings
	Map(int, String) map2 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 1);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	Call(Map(int, String), move_insert, map2, entry2);

	//Add a new string to map 3
	Entry(int, String) entry3 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry3, 2);

	String random_string3 = New(String);
	Call(String, set, random_string3, "Testing");
	Call(Entry(int, String), move_set_value, entry3, random_string3);

	Call(Map(int, String), move_insert, map2, entry3);

	//Check if two maps are equal
	CU_ASSERT_NOT_EQUAL(Call(Map(int, String), compareTo, map1, map2), 0);

	//Delete map of strings
	Delete(Map(int, String), map2);

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableNotCompareTo()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Allocate a new map of strings
	Map(int, String) map2 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 1);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Tesssssting");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	Call(Map(int, String), move_insert, map2, entry2);

	//Check if two maps are equal
	CU_ASSERT_NOT_EQUAL(Call(Map(int, String), compareTo, map1, map2), 0);

	//Delete map of strings
	Delete(Map(int, String), map2);

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableToString()
{
	//Allocate a new map of strings
	Map(int, String) map = New(Map(int, String));

	//Check if toString works
	CU_ASSERT_STRING_EQUAL(Call(Map(int, String), toString, map), "MapintString");

	//Delete map of strings
	Delete(Map(int, String), map);
}

void TestMapStringVFTableAdd()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Allocate a new map of strings
	Map(int, String) map2 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), add, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 1);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	Call(Map(int, String), add, map2, entry2);

	//Check if two maps are equal
	CU_ASSERT_TRUE(Call(Map(int, String), equals, map1, map2));

	//Have to delete strings since they are copied
	Delete(Entry(int, String), entry1);
	Delete(Entry(int, String), entry2);

	//Delete map of strings
	Delete(Map(int, String), map2);

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableClear()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Clear map
	Call(Map(int, String), clear, map1);

	//Check if map is empty
	CU_ASSERT_TRUE(Call(Map(int, String), isEmpty, map1));

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableRemove()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 1);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	CU_ASSERT_TRUE(Call(Map(int, String), remove, map1, entry2));

	//Check if map is empty
	CU_ASSERT_TRUE(Call(Map(int, String), isEmpty, map1));

	//try to remove again
	CU_ASSERT_FALSE(Call(Map(int, String), remove, map1, entry2));

	Delete(Entry(int, String), entry2);

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableRemoveLots()
{
	//Allocate a new map of int
	Map(int, String) map1 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 1
	Entry(int, String) entry123 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry123, 123);

	Call(Entry(int, String), set_value, entry123, random_string1);

	Call(Map(int, String), move_insert, map1, entry123);

	//Add a new string to map 1
	Entry(int, String) entry512 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry512, 512);

	Call(Entry(int, String), set_value, entry512, random_string1);

	Call(Map(int, String), move_insert, map1, entry512);

	//Add a new string to map 1
	Entry(int, String) entry55 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry55, 55);

	Call(Entry(int, String), set_value, entry55, random_string1);

	Call(Map(int, String), move_insert, map1, entry55);

	//Add a new string to map 1
	Entry(int, String) entry43 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry43, 43);

	Call(Entry(int, String), set_value, entry43, random_string1);

	Call(Map(int, String), move_insert, map1, entry43);

	//Add a new string to map 1
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 2);

	Call(Entry(int, String), set_value, entry2, random_string1);

	Call(Map(int, String), move_insert, map1, entry2);

	//Add a new string to map 1
	Entry(int, String) entry65 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry65, 65);

	Call(Entry(int, String), set_value, entry65, random_string1);

	Call(Map(int, String), move_insert, map1, entry65);

	//Add a new string to map 1
	Entry(int, String) entry12 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry12, -12);

	Call(Entry(int, String), set_value, entry12, random_string1);

	Call(Map(int, String), move_insert, map1, entry12);

	//Add a new string to map 1
	Entry(int, String) entry32 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry32, 32);

	Call(Entry(int, String), set_value, entry32, random_string1);

	Call(Map(int, String), move_insert, map1, entry32);

	//Add a new string to map 1
	Entry(int, String) entry532 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry532, 532);

	Call(Entry(int, String), set_value, entry532, random_string1);

	Call(Map(int, String), move_insert, map1, entry532);

	//Add a new string to map 1
	Entry(int, String) entry231 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry231, 231);

	Call(Entry(int, String), set_value, entry231, random_string1);

	Call(Map(int, String), move_insert, map1, entry231);

	//Add a new string to map 1
	Entry(int, String) entry36234 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry36234, 36234);

	Call(Entry(int, String), set_value, entry36234, random_string1);

	Call(Map(int, String), move_insert, map1, entry36234);

	//Add a new string to map 1
	Entry(int, String) entry6345 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry6345, 6345);

	Call(Entry(int, String), set_value, entry6345, random_string1);

	Call(Map(int, String), move_insert, map1, entry6345);

	CU_ASSERT_TRUE(Call(Map(int, String), remove, map1, entry1));
	CU_ASSERT_TRUE(Call(Map(int, String), remove, map1, entry123));
	CU_ASSERT_TRUE(Call(Map(int, String), remove, map1, entry512));
	CU_ASSERT_TRUE(Call(Map(int, String), remove, map1, entry55));
	CU_ASSERT_TRUE(Call(Map(int, String), remove, map1, entry43));
	CU_ASSERT_TRUE(Call(Map(int, String), remove, map1, entry2));
	CU_ASSERT_TRUE(Call(Map(int, String), remove, map1, entry65));
	CU_ASSERT_TRUE(Call(Map(int, String), remove, map1, entry12));
	CU_ASSERT_TRUE(Call(Map(int, String), remove, map1, entry32));
	CU_ASSERT_TRUE(Call(Map(int, String), remove, map1, entry532));
	CU_ASSERT_TRUE(Call(Map(int, String), remove, map1, entry231));
	CU_ASSERT_TRUE(Call(Map(int, String), remove, map1, entry36234));
	CU_ASSERT_TRUE(Call(Map(int, String), remove, map1, entry6345));

	//Delete map of int
	Delete(Map(int, String), map1);
}


void TestMapStringVFTableContains()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 1);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	CU_ASSERT_TRUE(Call(Map(int, String), contains, map1, entry2));

	Delete(Entry(int, String), entry2);

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableNotContains()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 23132);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	CU_ASSERT_FALSE(Call(Map(int, String), contains, map1, entry2));

	Delete(Entry(int, String), entry2);

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableCopy()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Copy map
	Map(int, String) map2 = Call(Map(int, String), copy, map1);
	
	//Check if two maps are equal
	CU_ASSERT_TRUE(Call(Map(int, String), equals, map1, map2));

	//Delete map of strings
	Delete(Map(int, String), map2);

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableIsEmpty()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 1);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	Call(Map(int, String), remove, map1, entry2);

	//Check if map is empty
	CU_ASSERT_TRUE(Call(Map(int, String), isEmpty, map1));

	Delete(Entry(int, String), entry2);

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableSize()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 1);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	Call(Map(int, String), move_insert, map1, entry2);

	//Check if two maps are equal
	CU_ASSERT_EQUAL(Call(Map(int, String), size, map1), 1);

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableSet()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 1);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	//Check if two maps are equal
	CU_ASSERT_PTR_NOT_EQUAL(Call(Map(int, String), set, map1, Initializer_List(Entry(int, String), entry1, entry2)), NULL);

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableMoveInsert()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 2);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	CU_ASSERT_TRUE(Call(Map(int, String), move_insert, map1, entry2));

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableMoveInsertLots()
{
	//Allocate a new map of int
	Map(int, String) map1 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 1
	Entry(int, String) entry123 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry123, 123);

	Call(Entry(int, String), set_value, entry123, random_string1);

	Call(Map(int, String), move_insert, map1, entry123);

	//Add a new string to map 1
	Entry(int, String) entry512 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry512, 512);

	Call(Entry(int, String), set_value, entry512, random_string1);

	Call(Map(int, String), move_insert, map1, entry512);

	//Add a new string to map 1
	Entry(int, String) entry55 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry55, 55);

	Call(Entry(int, String), set_value, entry55, random_string1);

	Call(Map(int, String), move_insert, map1, entry55);

	//Add a new string to map 1
	Entry(int, String) entry43 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry43, 43);

	Call(Entry(int, String), set_value, entry43, random_string1);

	Call(Map(int, String), move_insert, map1, entry43);

	//Add a new string to map 1
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 2);

	Call(Entry(int, String), set_value, entry2, random_string1);

	Call(Map(int, String), move_insert, map1, entry2);

	//Add a new string to map 1
	Entry(int, String) entry65 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry65, 65);

	Call(Entry(int, String), set_value, entry65, random_string1);

	Call(Map(int, String), move_insert, map1, entry65);

	//Add a new string to map 1
	Entry(int, String) entry12 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry12, -12);

	Call(Entry(int, String), set_value, entry12, random_string1);

	Call(Map(int, String), move_insert, map1, entry12);

	//Add a new string to map 1
	Entry(int, String) entry32 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry32, 32);

	Call(Entry(int, String), set_value, entry32, random_string1);

	Call(Map(int, String), move_insert, map1, entry32);

	//Add a new string to map 1
	Entry(int, String) entry532 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry532, 532);

	Call(Entry(int, String), set_value, entry532, random_string1);

	Call(Map(int, String), move_insert, map1, entry532);

	//Add a new string to map 1
	Entry(int, String) entry231 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry231, 231);

	Call(Entry(int, String), set_value, entry231, random_string1);

	Call(Map(int, String), move_insert, map1, entry231);

	//Add a new string to map 1
	Entry(int, String) entry36234 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry36234, 36234);

	Call(Entry(int, String), set_value, entry36234, random_string1);

	Call(Map(int, String), move_insert, map1, entry36234);

	//Add a new string to map 1
	Entry(int, String) entry6345 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry6345, 6345);

	Call(Entry(int, String), set_value, entry6345, random_string1);

	Call(Map(int, String), move_insert, map1, entry6345);

	//Delete map of int
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableInsert()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 1);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	Call(Map(int, String), insert, map1, entry2);

	//Add a new string to map 1
	Entry(int, String) entry3 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry3, 1);

	String random_string3 = New(String);
	Call(String, set, random_string3, "Testing");
	Call(Entry(int, String), move_set_value, entry3, random_string3);

	Entry(int, String)* equal_entry2 = Call(Map(int, String), find, map1, entry3);
	
	//Check if they are equal, entry2 is not moved
	CU_ASSERT_PTR_NOT_EQUAL(entry2, *equal_entry2);

	Delete(Entry(int, String), entry2);
	Delete(Entry(int, String), entry3);

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableInsertLots()
{
	//Allocate a new map of int
	Map(int, String) map1 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), insert, map1, entry1);

	//Add a new string to map 1
	Entry(int, String) entry123 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry123, 123);

	Call(Entry(int, String), set_value, entry123, random_string1);

	Call(Map(int, String), insert, map1, entry123);

	//Add a new string to map 1
	Entry(int, String) entry512 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry512, 512);

	Call(Entry(int, String), set_value, entry512, random_string1);

	Call(Map(int, String), insert, map1, entry512);

	//Add a new string to map 1
	Entry(int, String) entry55 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry55, 55);

	Call(Entry(int, String), set_value, entry55, random_string1);

	Call(Map(int, String), insert, map1, entry55);

	//Add a new string to map 1
	Entry(int, String) entry43 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry43, 43);

	Call(Entry(int, String), set_value, entry43, random_string1);

	Call(Map(int, String), insert, map1, entry43);

	//Add a new string to map 1
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 2);

	Call(Entry(int, String), set_value, entry2, random_string1);

	Call(Map(int, String), insert, map1, entry2);

	//Add a new string to map 1
	Entry(int, String) entry65 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry65, 65);

	Call(Entry(int, String), set_value, entry65, random_string1);

	Call(Map(int, String), insert, map1, entry65);

	//Add a new string to map 1
	Entry(int, String) entry12 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry12, -12);

	Call(Entry(int, String), set_value, entry12, random_string1);

	Call(Map(int, String), insert, map1, entry12);

	//Add a new string to map 1
	Entry(int, String) entry32 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry32, 32);

	Call(Entry(int, String), set_value, entry32, random_string1);

	Call(Map(int, String), insert, map1, entry32);

	//Add a new string to map 1
	Entry(int, String) entry532 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry532, 532);

	Call(Entry(int, String), set_value, entry532, random_string1);

	Call(Map(int, String), insert, map1, entry532);

	//Add a new string to map 1
	Entry(int, String) entry231 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry231, 231);

	Call(Entry(int, String), set_value, entry231, random_string1);

	Call(Map(int, String), insert, map1, entry231);

	//Add a new string to map 1
	Entry(int, String) entry36234 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry36234, 36234);

	Call(Entry(int, String), set_value, entry36234, random_string1);

	Call(Map(int, String), insert, map1, entry36234);

	//Add a new string to map 1
	Entry(int, String) entry6345 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry6345, 6345);

	Call(Entry(int, String), set_value, entry6345, random_string1);

	Call(Map(int, String), insert, map1, entry6345);

	Delete(Entry(int, String), entry1);
	Delete(Entry(int, String), entry123);
	Delete(Entry(int, String), entry512);
	Delete(Entry(int, String), entry55);
	Delete(Entry(int, String), entry43);
	Delete(Entry(int, String), entry2);
	Delete(Entry(int, String), entry65);
	Delete(Entry(int, String), entry12);
	Delete(Entry(int, String), entry32);
	Delete(Entry(int, String), entry532);
	Delete(Entry(int, String), entry231);
	Delete(Entry(int, String), entry36234);
	Delete(Entry(int, String), entry6345);

	//Delete map of int
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableFind()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));
		
	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	CU_ASSERT_PTR_EQUAL((Call(Map(int, String), find, map1, entry1)), NULL);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 1);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	Call(Map(int, String), move_insert, map1, entry2);

	//Add a new string to map 1
	Entry(int, String) entry3 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry3, 1);

	String random_string3 = New(String);
	Call(String, set, random_string3, "Testing");
	Call(Entry(int, String), move_set_value, entry3, random_string3);

	//Find random_string2
	CU_ASSERT_TRUE(Call(Entry(int, String), equals, (*(Call(Map(int, String), find, map1, entry3))), entry3));

	Delete(Entry(int, String), entry3);

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableNPOSFind()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	CU_ASSERT_PTR_EQUAL((Call(Map(int, String), find, map1, entry1)), NULL);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 1);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	Call(Map(int, String), move_insert, map1, entry2);

	//Add a new string to map 1
	Entry(int, String) entry3 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry3, 323231);

	String random_string3 = New(String);
	Call(String, set, random_string3, "Testing");
	Call(Entry(int, String), move_set_value, entry3, random_string3);

	Entry(int, String)* entry = Call(Map(int, String), find, map1, entry3);
	CU_ASSERT_PTR_EQUAL(entry, NULL);

	Delete(Entry(int, String), entry3);

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapStringVFTableReplace()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	CU_ASSERT_FALSE(Call(Map(int, String), replace, map1, entry1, entry1));

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 2);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	Call(Map(int, String), move_insert, map1, entry2);

	//Add a new string to map 1
	Entry(int, String) entry3 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry3, 1);

	String random_string3 = New(String);
	Call(String, set, random_string3, "Testing");
	Call(Entry(int, String), move_set_value, entry3, random_string3);

	//Find random_string2
	CU_ASSERT_TRUE(Call(Map(int, String), replace, map1, entry1, entry3));

	//Delete map of strings
	Delete(Map(int, String), map1);
}

void TestMapIterator()
{
	//Allocate a new map of strings
	Map(int, String) map1 = New(Map(int, String));

	//Add a new string to map 1
	Entry(int, String) entry1 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry1, 1);

	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Entry(int, String), move_set_value, entry1, random_string1);

	Call(Map(int, String), move_insert, map1, entry1);

	//Add a new string to map 2
	Entry(int, String) entry2 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry2, 2);

	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Entry(int, String), move_set_value, entry2, random_string2);

	Call(Map(int, String), move_insert, map1, entry2);

	//Add a new string to map 1
	Entry(int, String) entry3 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry3, 3);

	String random_string3 = New(String);
	Call(String, set, random_string3, "Testing");
	Call(Entry(int, String), move_set_value, entry3, random_string3);

	Call(Map(int, String), move_insert, map1, entry3);
	
	ForEach(Entry(int, String)* entry, Map(int, String), map1,
	{
		String* string = Call(Entry(int, String), get_value, *entry);
		Call(String, set, *string, "www");
	})

	String* string1 = Call(Entry(int, String), get_value, entry1);
	CU_ASSERT_STRING_EQUAL(Call(String, c_str, *string1), "www");
	String* string2 = Call(Entry(int, String), get_value, entry2);
	CU_ASSERT_STRING_EQUAL(Call(String, c_str, *string2), "www");
	String* string3 = Call(Entry(int, String), get_value, entry3);
	CU_ASSERT_STRING_EQUAL(Call(String, c_str, *string3), "www");

	//Delete map of strings
	Delete(Map(int, String), map1);
}
