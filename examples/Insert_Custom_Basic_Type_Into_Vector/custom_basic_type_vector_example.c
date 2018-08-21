#define OOC_V2

#include "ooc.h"
#include "example_struct.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	Vector(pExampleStruct) example_structs = New(Vector(pExampleStruct));

	pExampleStruct p_example_struct = malloc(sizeof(ExampleStruct));

	Call(example_structs, push_back, p_example_struct);

	free(p_example_struct);

	Delete(example_structs);

	return 0;
}
