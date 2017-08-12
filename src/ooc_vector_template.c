#include "ooc_vector_template.h"

/*
#ifdef T
#undef T
#endif
#define T int
#define T_EQUALS(element, other_element) ((element == other_element) ? (true) : (false))
#define T_ALLOC(element_ptr) *element_ptr
#define T_DELETE(element_ptr) *element_ptr = 0
#include "ooc_vector.c"
#undef T_EQUALS
#undef T_ALLOC
#undef T_DELETE
#undef T

#define FLOAT_EPLISON 0.0000005

#define T float
#define T_EQUALS(element, other_element) ((abs((element) - (other_element)) < FLOAT_EPLISON) ? (true) : (false))
#define T_ALLOC(element_ptr) *element_ptr
#define T_DELETE(element_ptr) *element_ptr = 0.0f
#include "ooc_vector.c"
#undef T_EQUALS
#undef T_ALLOC
#undef T_DELETE
#undef T

#undef FLOAT_EPLISON

#define T StringPtr
#define T_EQUALS(element, other_element) ((!Call(String, equals, element, other_element)) ? (true) : (false))
#define T_ALLOC(element_ptr) New(String)
#define T_DELETE(element_ptr) Delete(String, element_ptr)
#include "ooc_vector.c"
#undef T_EQUALS
#undef T_ALLOC
#undef T_DELETE
#undef T


*/