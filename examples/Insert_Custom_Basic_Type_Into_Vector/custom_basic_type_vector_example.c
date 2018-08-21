#define OOC_V2

#include "ooc.h"
#include "example_struct.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	//Create a vector
	Vector(pExampleStruct) example_structs = New(Vector(pExampleStruct));

	//Have to manually allocate since we did not create a class
	pExampleStruct p_example_struct = malloc(sizeof(ExampleStruct));

	//push a copy back
	Call(example_structs, push_back, p_example_struct);

	//free the struct
	free(p_example_struct);

	//delete the vector (will internally free the copy)
	Delete(example_structs);

	return 0;
}
