#include "ooc.h"
#include "stdio.h"

int main()
{
	void* s1 = New(String);
	Call(String, set, s1, "0123456789");
	printf("%s\n", Call(String, c_str, s1));
	void* s2 = New(String);
	Call(String, set, s2, "0123456789");
	printf("%d\n", Call(String, add, s2, s1));
	printf("%s\n", Call(String, c_str, s2));
	Delete(String, s2);
	Delete(String, s1);
	return 0;
}
