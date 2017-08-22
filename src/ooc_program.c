#include "ooc.h"

#ifdef _MSC_VER
	#define _CRTDBG_MAP_ALLOC  
	#include <stdlib.h>  
	#include <crtdbg.h> 
#endif
int main()
{
	/*
	//allocate a new string
	void* s1 = New(String);

	//allocate a new string
	void* s2 = New(String);

	//set s1 to "Much w0w"
	Call(String, set, s1, "Much w0w");

	//set s2 to " d0ge"
	Call(String, set, s2, " d0ge");

	//prints "Much w0w"
	printf("%s\n", Call(String, c_str, s1));

	//add s2 to s1
	Call(String, add, s1, s2);

	for (size_t i = 0; i < Call(String, size, s1); i++)
	{
		printf("%c\n", *(Call(String, c_str, s1) + i));
	}

	//prints "Much w0w d0ge"
	printf("%s\n", Call(String, c_str, s1));

	//manually append string literal to s1
	Call(String, append, s1, " gud");

	//prints "Much w0w d0ge gud"
	printf("%s\n", Call(String, c_str, s1));

	//free the string's resources
	Delete(String, s2);
	Delete(String, s1);
	*/
	
	/*
	Vector(Vector(int)) ints = New(Vector(Vector(int)));
	SafeCall(Vector(Vector(int)), push_back, ints, New(Vector(int)));
	Delete(Vector(Vector(int)), ints);

	//Allocate a new vector of strings
	Vector(String) vector = New(Vector(String));

	//Check if toString works
	printf("%s\n", SafeCall(Vector(String), toString, vector));

	//Delete vector of strings
	Delete(Vector(String), vector);
	*/
	/*
	Set(int) s = New(Set(int));

	Call(Set(int), insert, s, 1);
	Call(Set(int), insert, s, 3);
	Call(Set(int), insert, s, 5);
	Call(Set(int), insert, s, 7);
	Call(Set(int), insert, s, 2);
	Call(Set(int), insert, s, 4);
	Call(Set(int), insert, s, 6);
	Call(Set(int), insert, s, 8);

	SetTestint(s->root, 0);

	ForEach(int* string, Set(int), s,
	{
		printf("%d\n", *string);
	})

	Delete(Set(int), s);
	*/
	/*
	//Allocate a new set of strings
	Set(String) set1 = New(Set(String));

	//Allocate a new set of strings
	Set(String) set2 = New(Set(String));

	//Check if two sets are equal
	printf("%d\n", Call(Set(String), equals, set1, set2));

	//Add a new string to set 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "Testing");
	Call(Set(String), move_insert, set1, random_string1);

	//Add a new string to set 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "Testing");
	Call(Set(String), move_insert, set2, random_string2);

	//Check if two sets are equal
	printf("%d\n", Call(Set(String), equals, set1, set2));

	//Delete set of strings
	Delete(Set(String), set2);

	//Delete set of strings
	Delete(Set(String), set1);
	*/

	//Allocate a new map of strings
Map(int, String) map1 = New(Map(int, String));

//Add a new string to map 1
Entry(int, String) entry1 = New(Entry(int, String));

Call(Entry(int, String), move_set_key, entry1, 1);

String random_string1 = New(String);
Call(String, set, random_string1, "Testing");
Call(Entry(int, String), move_set_value, entry1, random_string1);

(Call(Map(int, String), replace, map1, entry1, entry1));

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

Call(Entry(int, String), move_set_key, entry3, 2);

String random_string3 = New(String);
Call(String, set, random_string3, "Testing");
Call(Entry(int, String), move_set_value, entry3, random_string3);

//Add a new string to map 1
Entry(int, String) entry4 = New(Entry(int, String));

Call(Entry(int, String), move_set_key, entry4, 8);

String random_string4 = New(String);
Call(String, set, random_string4, "Testing");
Call(Entry(int, String), move_set_value, entry4, random_string4);

//Add a new string to map 1
Entry(int, String) entry5 = New(Entry(int, String));

Call(Entry(int, String), move_set_key, entry5, 8);

String random_string5 = New(String);
Call(String, set, random_string5, "Testing");
Call(Entry(int, String), move_set_value, entry5, random_string5);


//Find random_string2
(Call(Map(int, String), replace, map1, entry2, entry3));

(Call(Map(int, String), replace, map1, entry5, entry4));

Delete(Entry(int, String), entry4);
Delete(Entry(int, String), entry5);

//Delete map of strings
Delete(Map(int, String), map1);

	/*
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

	//Add a new string to map 1
	Entry(int, String) entry3 = New(Entry(int, String));

	Call(Entry(int, String), move_set_key, entry3, 1);

	String random_string3 = New(String);
	Call(String, set, random_string3, "Testing");
	Call(Entry(int, String), move_set_value, entry3, random_string3);

	ForEach(Entry(int, String)* entry, Map(int, String), map1,
	{
		String* string = Call(Entry(int, String), get_value, *entry);
		Call(String, set, *string, "www");
	})

	Delete(Entry(int, String), entry3);

	Delete(Map(int, String), map1);
	*/
	/*
	//Allocate a new vector of strings
	Vector(String) vector1 = New(Vector(String));

	//Add a new string to vector 1
	String random_string1 = New(String);
	Call(String, set, random_string1, "a");
	Call(Vector(String), add, vector1, random_string1);

	//Add a new string to vector 2
	String random_string2 = New(String);
	Call(String, set, random_string2, "b");
	Call(Vector(String), push_front, vector1, random_string2);

	//Add a new string to vector 3
	String random_string3 = New(String);
	Call(String, set, random_string3, "c");
	Call(Vector(String), insert, vector1, random_string3, 1);

	ForEach(String* s, Vector(String), vector1,
	{
		printf("```` %s ````\n", Call(String, c_str, *s));
	})

	//Get the second index
	//int error = 0;
	//String equal_random_string3 = Call(Vector(String), get, vector1, 1, &error);

	printf("%zu -- \n", Call(Vector(String), size, vector1));

	//Delete vector of strings
	Delete(Vector(String), vector1);
	*/
	
#ifdef _MSC_VER
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}
