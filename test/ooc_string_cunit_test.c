#include "ooc_string_cunit_test.h"

int StringInitializeSuite()
{
	return 0;
}

int StringCleanUpSuite()
{
	return 0;
}

void TestStringVFTableUninitializedCompleteObjectLocator()
{
	CU_ASSERT_PTR_EQUAL(stringVFTable.pCompleteObjectLocator, NULL);
}

void TestStringVFTableInitializedCompleteObjectLocator()
{
	//manually allocates and deallocates an string
	//this should __NOT__ be done in a real program
	
	//allocate a new string
	void* string = calloc(1, sizeof(String));

	//allocate vftable
	((String*)string)->container.object.pVFTable = calloc(1, sizeof(StringVFTable));

	//call constructor to set up string
	StringConstruct(string);

	CU_ASSERT_PTR_EQUAL(stringVFTable.pCompleteObjectLocator, &stringCompleteObjectLocator);

	//call destructor
	StringDestruct(string);

	//free vftable
	free(((String*)string)->container.object.pVFTable);

	//free the string's resources
	free(string);

	//NULL the pointer, so we don't have use after free vulns
	string = NULL;
}

void TestStringNew()
{
	//allocate a new string
	void* string = NewString();

	//string should be allocated
	CU_ASSERT_PTR_NOT_EQUAL(string, NULL);

	//free the string's resources
	DeleteString(string);

	//manual delete string call does not set string to null :(
	CU_ASSERT_PTR_NOT_EQUAL(string, NULL);
}

void TestStringDelete()
{
	//allocate a new string
	void* string = NewString();

	//string should be allocated
	CU_ASSERT_PTR_NOT_EQUAL(string, NULL);

	//free the string's resources
	Delete(String, string);

	//macro delete string sets string to null :)
	CU_ASSERT_PTR_EQUAL(string, NULL);
}

void TestStringConstructor()
{
	//manually allocates and deallocates an string
	//this should __NOT__ be done in a real program

	//allocate a new string
	void* string = calloc(1, sizeof(String));

	//allocate vftable
	((String*)string)->container.object.pVFTable = calloc(1, sizeof(StringVFTable));

	//call constructor to set up string
	StringConstruct(string);

	//verify that the vftable is pointing in a different memory location
	CU_ASSERT_PTR_NOT_EQUAL(((String*)string)->container.object.pVFTable, &stringVFTable);
	
	//call destructor
	StringDestruct(string);

	//free vftable
	free(((String*)string)->container.object.pVFTable);

	//free the string's resources
	free(string);

	//NULL the pointer, so we don't have use after free vulns
	string = NULL;
}

void TestStringCopyConstructor()
{
	//allocate a new string
	void* s1 = New(String);

	//string copy
	void* s2 = Call(String, copy, s1);

	//check that the objects are allocated in different regions
	CU_ASSERT_PTR_NOT_EQUAL(s1, s2);
	
	//check if strings' values are the same
	CU_ASSERT_STRING_EQUAL(Call(String, c_str, s1), Call(String, c_str, s2));

	//free the string's resources
	Delete(String, s2);
	Delete(String, s1);
	
	//check that the pointers are freed
	CU_ASSERT_PTR_EQUAL(s1, NULL);
	CU_ASSERT_PTR_EQUAL(s2, NULL);
}

void TestStringDestructor()
{
	//manually allocates and deallocates an string
	//this should __NOT__ be done in a real program
	
	//allocate a new string
	void* string = calloc(1, sizeof(String));

	//allocate vftable
	((String*)string)->container.object.pVFTable = calloc(1, sizeof(StringVFTable));

	//call constructor to set up string
	StringConstruct(string);

	//call destructor
	StringDestruct(string);

	//Show that nothing happens after destructor is called since the destructor does not do anything
	CU_ASSERT_PTR_NOT_EQUAL(((String*)string)->container.object.pVFTable, &stringVFTable);

	//free vftable
	free(((String*)string)->container.object.pVFTable);

	//free the string's resources
	free(string);

	//NULL the pointer, so we don't have use after free vulns
	string = NULL;
}

void TestStringVFTableEquals()
{
	//compile time check
	CU_ASSERT_PTR_EQUAL(stringVFTable.equals, StringEquals);

	//allocate a new string
	void* s1 = New(String);

	//string copy
	void* s2 = New(String);

	//check if strings' values are the same
	CU_ASSERT_STRING_EQUAL(Call(String, c_str, s1), Call(String, c_str, s2));

	//append characters
	Call(String, append, s1, "TEST");

	//not equal
	CU_ASSERT_STRING_NOT_EQUAL(Call(String, c_str, s1), Call(String, c_str, s2));

	//append characters
	Call(String, append, s2, "TEST");

	//equal
	CU_ASSERT_STRING_NOT_EQUAL(Call(String, c_str, s1), Call(String, c_str, s2));

	//free the string's resources
	Delete(String, s2);
	Delete(String, s1);

	//check that the pointers are freed
	CU_ASSERT_PTR_EQUAL(s1, NULL);
	CU_ASSERT_PTR_EQUAL(s2, NULL);
}

void TestStringVFTableStringToString()
{
	//compile time check
	CU_ASSERT_PTR_EQUAL(stringVFTable.toString, StringToString);

	//manually allocates and deallocates an string
	//this should __NOT__ be done in a real program
	//since string is an abstract string

	//allocate a new string
	void* string = calloc(1, sizeof(String));

	//allocate vftable
	((String*)string)->container.object.pVFTable = calloc(1, sizeof(StringVFTable));

	//call constructor to set up string
	StringConstruct(string);

	CU_ASSERT_STRING_EQUAL(((StringVFTable*)((String*)string)->container.object.pVFTable)->toString(string), "String");
	CU_ASSERT_STRING_EQUAL(StringToString(string), "String");

	//call destructor
	StringDestruct(string);

	//free vftable
	free(((String*)string)->container.object.pVFTable);

	//free the string's resources
	free(string);

	//NULL the pointer, so we don't have use after free vulns
	string = NULL;
}

void TestStringVFTableStringSet()
{
	//allocate a new string
	void* string = New(String);

	//append a char array > 16
	Call(String, set, string, "Test this test because testing is good!");

	//check if strings' values are the same
	CU_ASSERT_STRING_EQUAL(Call(String, c_str, string), "Test this test because testing is good!");

	//free the string's resources
	Delete(String, string);

	//check that the pointers are freed
	CU_ASSERT_PTR_EQUAL(string, NULL);
}


void TestStringVFTableStringC_Str()
{
	//allocate a new string
	void* string = New(String);

	//append a char array > 16
	Call(String, append, string, "Test this test because testing is good!");

	//check if strings' values are the same
	CU_ASSERT_STRING_EQUAL(Call(String, c_str, string), "Test this test because testing is good!");

	//free the string's resources
	Delete(String, string);

	//check that the pointers are freed
	CU_ASSERT_PTR_EQUAL(string, NULL);
}

void TestStringVFTableStringAppend()
{
	//allocate a new string
	void* string = New(String);

	//append a char array > 16
	Call(String, append, string, "Test this test because testing is good!");

	//check if strings' values are the same
	CU_ASSERT_STRING_EQUAL(Call(String, c_str, string), "Test this test because testing is good!");

	//free the string's resources
	Delete(String, string);

	//check that the pointers are freed
	CU_ASSERT_PTR_EQUAL(string, NULL);
}

void TestStringVFTableStringFind()
{
	//allocate a new string
	void* s1 = New(String);

	//allocate a new string
	void* s2 = New(String);
	
	//append characters to haystack
	Call(String, set, s1, "TESTwwwTESTWWW");

	//append characters to needle
	Call(String, set, s2, "www");

	//find index of www in s1
	int index = Call(String, find, s1, s2);
	
	//index should be value of 4
	CU_ASSERT_EQUAL(index, 4);

	//free the string's resources
	Delete(String, s2);
	Delete(String, s1);

	//check that the pointers are freed
	CU_ASSERT_PTR_EQUAL(s1, NULL);
	CU_ASSERT_PTR_EQUAL(s2, NULL);
}

void TestStringVFTableStringSubString()
{
	//allocate a new string
	void* s1 = New(String);

	//allocate a new string
	void* s2 = New(String);

	//allocate a new string
	void* s3 = New(String);

	//set characters of haystack
	Call(String, set, s1, "TESTwwwtestWWW");

	//set characters of needle1
	Call(String, set, s2, "www");

	//set characters of needle2
	Call(String, set, s2, "WWW");

	//find index of www in s1
	int index1 = Call(String, find, s1, s2);

	//index should be value of 4
	CU_ASSERT_EQUAL(index1, 4);

	//find index of WWW in s1
	int index2 = Call(String, find, s1, s3);

	//index should be value of 11
	CU_ASSERT_EQUAL(index2, 11);

	//call substring
	void* substring = Call(String, substring, s1, index1, index2);

	//test if substring == "test"
	CU_ASSERT_STRING_EQUAL(Call(String, c_str, substring), "test");

	//free the string's resources
	Delete(String, s3);
	Delete(String, s2);
	Delete(String, s1);

	//check that the pointers are freed
	CU_ASSERT_PTR_EQUAL(s3, NULL);
	CU_ASSERT_PTR_EQUAL(s2, NULL);
	CU_ASSERT_PTR_EQUAL(s1, NULL);
}

