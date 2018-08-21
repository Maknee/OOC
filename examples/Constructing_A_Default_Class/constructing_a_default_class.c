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

	DefaultExampleStruct copy_struct = Call(default_example_struct, copy);

	assert(Call(copy_struct, equals, default_example_struct) == true);
	assert(Call(copy_struct, compareTo, default_example_struct) == 0);
	assert(!strcmp(Call(copy_struct, toString), "DefaultExampleStruct"));

	Delete(copy_struct);
	Delete(default_example_struct);
	return 0;
}
