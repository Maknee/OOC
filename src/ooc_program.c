#include "ooc.h"
#include "stdio.h"

int main()
{
	void* string = New(String);
	printf("%s", Call(String, toString, string));
	Delete(String, string);
	return 0;
}
