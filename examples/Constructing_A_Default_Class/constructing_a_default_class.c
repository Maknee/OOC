#undef OOC_V1
#define OOC_V2

#include "ooc.h"
#include "default_example_struct.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	DefaultExampleStruct default_example_struct = New(DefaultExampleStruct);

	

	Delete(default_example_struct);
	return 0;
}
