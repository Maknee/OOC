#include "ooc.h"

#ifdef _MSC_VER
	#define _CRTDBG_MAP_ALLOC  
	#include <stdlib.h>  
	#include <crtdbg.h> 
#endif
int main()
{
	void* s1 = New(String);

	Call(String, set, s1, "Much w0w");

	ForEach(char* c, String, s1, 
	{
		*c = 'w';
	});

	Iterator(String) s = Call(String, end, s1);
	printf("111 %s 111\n", s.data - 1);

	printf("%s\n", Call(String, c_str, s1));

	Delete(String, s1);

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
