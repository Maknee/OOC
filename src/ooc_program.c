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

	//allocate a new string
	void* s3 = New(String);

	//set characters of haystack
	Call(String, set, s1, "0123456789aaabbbcccddd");

	//set characters of needle1
	Call(String, set, s2, "4");

	//set characters of needle2
	Call(String, set, s3, "aee");

	//find index of www in s1
	int index1 = Call(String, find, s1, s2);

	//index should be value of 4

	//find index of WWW in s1
	int index2 = Call(String, find, s1, s3);

	//index should be value of 11

	//call substring
	String* substring = Call(String, substring, s1, index1, index2);

	//test if substring == "test"
	printf("%s\n", Call(String, c_str, substring));

	//free the string's resources
	Delete(String, s3);
	Delete(String, s2);
	Delete(String, s1);

	return 0;
}
