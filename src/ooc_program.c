#include "ooc.h"
#include "stdio.h"

int main()
{
	/*
	void* s1 = New(String);
	Call(String, set, s1, "0123456789");
	printf("%s\n", Call(String, c_str, s1));
	void* s2 = New(String);
	Call(String, set, s2, "0123456789");
	printf("%d\n", Call(String, add, s2, s1));
	printf("%s\n", Call(String, c_str, s2));
	Delete(String, s2);
	Delete(String, s1);
	*/
	
	//allocate a new string
	void* s1 = New(String);

	//allocate a new string
	void* s2 = New(String);

	//append characters to s1
	Call(String, set, s1, "Test this test");

	//append characters to insertion string
	Call(String, set, s2, " Test this test");

	//insert the string into s1 at index 
	Call(String, insert, s1, s2, 14);

	//test if substring == "test"
	printf("%s\n", Call(String, c_str, s1));

	//free the string's resources
	Delete(String, s2);
	Delete(String, s1);

	return 0;
}
