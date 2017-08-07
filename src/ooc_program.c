#include "ooc.h"
#include "stdio.h"

int main()
{	
	//allocate a new string
	void* s1 = New(String);

	//allocate a new string
	void* s2 = New(String);

	//allocate a new string
	void* s3 = New(String);

	//append characters to s1
	Call(String, set, s1, "this test this");

	//append characters to insertion string
	Call(String, set, s2, "this");

	//insert the string into s1 at index 
	Call(String, replace, s1, s2, s3);

	//Call(String, remove, s1, s2);

	//test if substring == "test"
	printf("%s\n", Call(String, c_str, s1));

	//free the string's resources
	Delete(String, s3);
	Delete(String, s2);
	Delete(String, s1);

	return 0;
}
