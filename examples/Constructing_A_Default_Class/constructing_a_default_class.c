#undef OOC_V1
#define OOC_V2 //make sure we are using version 2

#include "ooc.h"
#include "default_example_struct.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main()
{
	DefaultExampleStruct default_example_struct = New(DefaultExampleStruct);

	//set the values
	default_example_struct->a = 1;
	default_example_struct->b = 2;
	default_example_struct->c = 3;

	//copy the struct
	DefaultExampleStruct copy_struct = Call(default_example_struct, copy);

	//make sure that copied struct is the same
	assert(default_example_struct->a == default_example_struct->a);
	assert(default_example_struct->b == default_example_struct->b);
	assert(default_example_struct->c == default_example_struct->c);

	//copy struct calls are valid
	assert(Call(copy_struct, equals, default_example_struct) == true);
	assert(Call(copy_struct, compareTo, default_example_struct) == 0);
	assert(!strcmp(Call(copy_struct, toString), "DefaultExampleStruct"));

	//delete the object
	Delete(copy_struct);
	Delete(default_example_struct);
	return 0;
}
