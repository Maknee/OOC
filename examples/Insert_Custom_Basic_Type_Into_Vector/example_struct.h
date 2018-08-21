#pragma once

/*
 * Our example struct
 * We use pExampleStruct because vector internally keeps pointers to objects
 * Vector does not store the struct itself in the buffer.
 */

typedef struct ExampleStruct
{
	int a;
	int b;
	int c;
} ExampleStruct, *pExampleStruct;

/*
 * Have to include the header template
 */

#define T pExampleStruct
#include "ooc_vector.h"
#undef T
