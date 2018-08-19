#pragma once

#include <string.h>
#include <stdlib.h>

typedef struct ExampleStruct
{
	int a;
	int b;
	int c;
} ExampleStruct, *pExampleStruct;

#define T pExampleStruct
#include "ooc_vector.h"
#undef T
