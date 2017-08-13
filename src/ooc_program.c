#include "ooc.h"

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
	Vector(int)* vector = New(Vector(int));
	printf("%s\n", Call(Vector(int), toString, vector));

	Call(Vector(int), set, vector, INITIALIZER_LIST(int, 5, 5, 5, 5, 6));

	Call(Vector(int), set, vector, INITIALIZER_LIST(int, 1));

	printf("%zu\n", Call(Vector(int), size, vector));
	
	int error_no;
	for (size_t i = 0; i < Call(Vector(int), size, vector); i++)
	{
		int v = Call(Vector(int), get, vector, (int)i, &error_no);

		printf("ww - %d - %d\n", v, error_no);
	}

	Delete(Vector(int), vector);
	*/
	
	
	Vector(String)* vector = New(Vector(String));
	printf("%s\n", Call(Vector(String), toString, vector));

	Call(Vector(String), set, vector, INITIALIZER_LIST(String, New(String)));

	printf("%zu\n", Call(Vector(String), size, vector));

	int error_no;
	for (size_t i = 0; i < Call(Vector(String), size, vector); i++)
	{
		String v = Call(Vector(String), get, vector, (int)i, &error_no);

		printf("ww - %s - %d\n", Call(String, c_str, v), error_no);
	}

	Delete(Vector(String), vector);
	
	return 0;
}
