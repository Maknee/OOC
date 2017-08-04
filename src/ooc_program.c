#include "ooc.h"
#include "stdio.h"

int main()
{
	void* string = New(String);
	printf("%s", Call(Object, toString, string));
	printf("%s", Call2(Object, string, toString, string));
	Delete(String, string);
	return 0;
}
