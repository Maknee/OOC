#pragma once

#include <string.h>
#include <stdlib.h>

typedef struct ExampleStruct
{
	int a;
	int b;
	int c;
} ExampleStruct, *pExampleStruct;

#ifdef Vector
#undef Vector
#endif

#ifdef T
#undef T
#endif

#define T pExampleStruct
#include "ooc_vector.h"
#undef T

//re-enable what we type in as Vector(type) b/c Vector is used as a different Vector macro in the includes
#define Vector(type) VectorExpansion(type)