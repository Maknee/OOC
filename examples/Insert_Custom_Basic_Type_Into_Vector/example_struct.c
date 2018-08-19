#include "example_struct.h"

pExampleStruct CopyExampleStruct(pExampleStruct p_example_struct)
{
	pExampleStruct copy_p_example_struct = malloc(sizeof(struct ExampleStruct));
	return memcpy(copy_p_example_struct, p_example_struct, sizeof(struct ExampleStruct));
}

#ifdef Vector
#undef Vector
#endif

#ifdef T
#undef T
#endif

//Vector(pExampleStruct)
#define T pExampleStruct
#define T_EQUALS(element, other_element) (!memcmp(element, other_element, sizeof(ExampleStruct)))
#define T_COMPARE_TO(element, other_element) (memcmp(element, other_element, sizeof(ExampleStruct)))
#define T_ALLOC(T_Ptr) *(T_Ptr) = malloc(sizeof(ExampleStruct))
#define T_COPY(T_Ptr) CopyExampleStruct(*(T_Ptr))
#define T_DELETE(T_Ptr) free(T_Ptr)
#include "ooc_vector.c"
#undef T_EQUALS
#undef T_COMPARE_TO
#undef T_COPY
#undef T_ALLOC
#undef T_COMPARE_TO
#undef T_DELETE
#undef T

//re-enable what we type in as Vector(type) b/c Vector is used as a different Vector macro in the includes
#define Vector(type) VectorExpansion(type)