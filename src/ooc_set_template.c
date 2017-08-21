#include "ooc_set_template.h"

//get rid of Set macro and then redef at end cause Set is a type
#ifdef Set
#undef Set
#endif

#ifdef T
#undef T
#endif

#define RED 1
#define BLACK 0
#define RIGHT 1
#define LEFT 0

//Set(int)
#define T int
#define T_EQUALS(element, other_element) ((element == other_element) ? (true) : (false))
#define T_COMPARE_TO(element, other_element) (element - other_element)
#define T_ALLOC(T_Ptr) *(T_Ptr) = 0 
#define T_COPY(T_Ptr) *(T_Ptr)
#define T_DELETE(T_Ptr) *(T_Ptr) = 0
#include "ooc_set.c"
#undef T_EQUALS
#undef T_COPY
#undef T_ALLOC
#undef T_COMPARE_TO
#undef T_DELETE
#undef T

//Set(float)
#define FLOAT_EPLISON 0.0000005

#define T float
#define T_EQUALS(element, other_element) ((fabs((element) - (other_element)) < FLOAT_EPLISON) ? (true) : (false))
#define T_COMPARE_TO(element, other_element) ((fabs((element) - (other_element)) < FLOAT_EPLISON) ? (0) : ((element - other_element > 0) ? (1) : (-1)))
#define T_ALLOC(T_Ptr) *(T_Ptr) = 0.0f
#define T_COPY(T_Ptr) *(T_Ptr)
#define T_DELETE(T_Ptr) *(T_Ptr) = 0.0f
#include "ooc_set.c"
#undef T_EQUALS
#undef T_COMPARE_TO
#undef T_COPY
#undef T_ALLOC
#undef T_DELETE
#undef T

#undef FLOAT_EPLISON

//Set(String)
#define T String
#define T_EQUALS(element, other_element) ((Call(String, equals, element, other_element)) ? (true) : (false))
#define T_COMPARE_TO(element, other_element) (Call(String, compareTo, element, other_element))
#define T_ALLOC(T_Ptr) *(T_Ptr) = New(String)
#define T_COPY(T_Ptr) Call(String, copy, *(T_Ptr))
#define T_DELETE(T_Ptr) Delete(String, *(T_Ptr))
#include "ooc_set.c"
#undef T_EQUALS
#undef T_COMPARE_TO
#undef T_COPY
#undef T_ALLOC
#undef T_DELETE
#undef T

//Set of containers? Kind of useless, but okay.
//Set(Container)
#define T Container
#define T_EQUALS(element, other_element) ((Call(Container, equals, element, other_element)) ? (true) : (false))
#define T_COMPARE_TO(element, other_element) (Call(Container, compareTo, element, other_element))
#define T_ALLOC(T_Ptr) *(T_Ptr) = New(Container)
#define T_COPY(T_Ptr) Call(Container, copy, *(T_Ptr))
#define T_DELETE(T_Ptr) Delete(Container, *(T_Ptr))
#include "ooc_set.c"
#undef T_EQUALS
#undef T_COMPARE_TO
#undef T_COPY
#undef T_ALLOC
#undef T_DELETE
#undef T

#undef RED
#undef BLACK
#undef RIGHT
#undef LEFT

#define Set(type) SetExpansion(type)
