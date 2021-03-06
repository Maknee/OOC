#include "ooc_vector_template.h"

//Vector(int)
#define T int
#define T_EQUALS(element, other_element) ((element == other_element) ? (true) : (false))
#define T_COMPARE_TO(element, other_element) (element - other_element)
#define T_ALLOC(T_Ptr) *(T_Ptr) = 0 
#define T_COPY(T_Ptr) *(T_Ptr)
#define T_DELETE(T_Ptr) *(T_Ptr) = 0
#include "ooc_vector.c"
#undef T_EQUALS
#undef T_COPY
#undef T_ALLOC
#undef T_COMPARE_TO
#undef T_DELETE
#undef T

//Vector(Vector(int))
#define T Vectorint
#define T_EQUALS(element, other_element) (Call(Vectorint, equals, element, other_element) ? (true) : (false))
#define T_COMPARE_TO(element, other_element) (Call(Vectorint, compareTo, element, other_element))
#define T_ALLOC(T_Ptr) *(T_Ptr) = NewVectorint()
#define T_COPY(T_Ptr) Call(Vectorint, copy, *(T_Ptr))
#define T_DELETE(T_Ptr) Delete(Vectorint, *(T_Ptr))
#include "ooc_vector.c"
#undef T_EQUALS
#undef T_COMPARE_TO
#undef T_COPY
#undef T_ALLOC
#undef T_COMPARE_TO
#undef T_DELETE
#undef T

//Vector(float)
#define FLOAT_EPLISON 0.005

#define T float
#define T_EQUALS(element, other_element) ((fabs((element) - (other_element)) < FLOAT_EPLISON) ? (true) : (false))
#define T_COMPARE_TO(element, other_element) ((fabs((element) - (other_element)) < FLOAT_EPLISON) ? (0) : ((element - other_element > 0) ? (1) : (-1)))
#define T_ALLOC(T_Ptr) *(T_Ptr) = 0.0f
#define T_COPY(T_Ptr) *(T_Ptr)
#define T_DELETE(T_Ptr) *(T_Ptr) = 0.0f
#include "ooc_vector.c"
#undef T_EQUALS
#undef T_COMPARE_TO
#undef T_COPY
#undef T_ALLOC
#undef T_DELETE
#undef T

#undef FLOAT_EPLISON

//Vector(String)
#define T String
#define T_EQUALS(element, other_element) ((Call(String, equals, element, other_element)) ? (true) : (false))
#define T_COMPARE_TO(element, other_element) (Call(String, compareTo, element, other_element))
#define T_ALLOC(T_Ptr) *(T_Ptr) = New(String)
#define T_COPY(T_Ptr) Call(String, copy, *(T_Ptr))
#define T_DELETE(T_Ptr) Delete(String, *(T_Ptr))
#include "ooc_vector.c"
#undef T_EQUALS
#undef T_COMPARE_TO
#undef T_COPY
#undef T_ALLOC
#undef T_DELETE
#undef T

//Vector of containers? Kind of useless, but okay.
//Vector(Container)
#define T Container
#define T_EQUALS(element, other_element) ((Call(Container, equals, element, other_element)) ? (true) : (false))
#define T_COMPARE_TO(element, other_element) (Call(Container, compareTo, element, other_element))
#define T_ALLOC(T_Ptr) *(T_Ptr) = New(Container)
#define T_COPY(T_Ptr) Call(Container, copy, *(T_Ptr))
#define T_DELETE(T_Ptr) Delete(Container, *(T_Ptr))
#include "ooc_vector.c"
#undef T_EQUALS
#undef T_COMPARE_TO
#undef T_COPY
#undef T_ALLOC
#undef T_DELETE
#undef T

