#include "ooc.h"
#include "stdio.h"

int main()
{
	void* string = New(String);
	printf("%s", Call(Object, string, toString, string));
	Delete(String, string);
	system("pause");
	return 0;
}
