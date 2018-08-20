
#define OOC_V1

#include "ooc.h"
#include "example_struct.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	Vector(pExampleStruct) example_structs = New(Vector(pExampleStruct));

	pExampleStruct p_example_struct = malloc(sizeof(ExampleStruct));

	Call(Vector(pExampleStruct), push_back, example_structs, p_example_struct);

	free(p_example_struct);

	Delete(Vector(pExampleStruct), example_structs);

	return 0;
}
