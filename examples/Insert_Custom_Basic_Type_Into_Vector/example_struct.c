#include "example_struct.h"

pExampleStruct CopyExampleStruct(pExampleStruct p_example_struct)
{
	pExampleStruct copy_p_example_struct = malloc(sizeof(struct ExampleStruct));
	return memcpy(copy_p_example_struct, p_example_struct, sizeof(struct ExampleStruct));
}

	//Vector(pExampleStruct)
#define T pExampleStruct
#define T_EQUALS(element, other_element) (!memcmp(element, other_element, sizeof(ExampleStruct)))
#define T_COMPARE_TO(element, other_element) (memcmp(element, other_element, sizeof(ExampleStruct)))
#define T_COPY(T_Ptr) CopyExampleStruct(*(T_Ptr))
#define T_DELETE(T_Ptr) free(*T_Ptr)
#include "ooc_vector.c"
#undef T_EQUALS
#undef T_COMPARE_TO
#undef T_COPY
#undef T_ALLOC
#undef T_COMPARE_TO
#undef T_DELETE
#undef T
