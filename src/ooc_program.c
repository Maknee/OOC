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
	
	Set(String) s = New(Set(String));

	Call(Set(String), move_insert, s, Call(String, set, New(String), "a"));
	Call(Set(String), move_insert, s, Call(String, set, New(String), "b"));
	Call(Set(String), move_insert, s, Call(String, set, New(String), "c"));
	Call(Set(String), move_insert, s, New(String));

	printf("%zu\n", s->size);
	//SetTestString(s->root, 0);

	ForEach(String* string, Set(String), s,
	{
		printf("%s\n", Call(String, c_str, *string));
	})

	//String* found = Call(Set(String), find, s, New(String));

	Delete(Set(String), s);
	
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
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}
