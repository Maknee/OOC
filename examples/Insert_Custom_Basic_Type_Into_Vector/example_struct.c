#include "example_struct.h"

#include <string.h>
#include <stdlib.h>

pExampleStruct CopyExampleStruct(pExampleStruct p_example_struct)
{
	pExampleStruct copy_p_example_struct = malloc(sizeof(struct ExampleStruct));
	return memcpy(copy_p_example_struct, p_example_struct, sizeof(struct ExampleStruct));
}

/*
 * Define all the macros necessary to construct a vector template
 * element is pExampleStruct
 * element_ptr is pExampleStruct*
 */

//Vector(pExampleStruct)
#define T pExampleStruct
#define T_EQUALS(element, other_element) (!memcmp(element, other_element, sizeof(ExampleStruct)))
#define T_COMPARE_TO(element, other_element) (memcmp(element, other_element, sizeof(ExampleStruct)))
#define T_COPY(element_ptr) CopyExampleStruct(*(element_ptr)) //Return a copy
#define T_DELETE(element_ptr) free(*(element_ptr)) //Free the element
#include "ooc_vector.c"
#undef T_EQUALS
#undef T_COPY
#undef T_COMPARE_TO
#undef T_DELETE
#undef T
