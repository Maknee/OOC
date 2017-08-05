#include "ooc.h"
#include "stdio.h"

int main()
{
	void* s1 = New(String);
	Call(String, append, s1, "HEYYY");
	printf("%s\n", Call(String, c_str, s1));
	Delete(String, s1);
	void* s2 = New(String);
	printf("%d\n", Call(String, equals, s2, s1));
	Delete(String, s2);
	return 0;
}
