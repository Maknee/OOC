#include "ooc_vector_template.h"

//get rid of Vector macro and then redef at end cause Vector is a type
#ifdef Vector
#undef Vector
#endif

#ifdef T
#undef T
#endif

//Vector(int)
#define T int
#define T_EQUALS(element, other_element) ((element == other_element) ? (true) : (false))
#define T_ALLOC(T_Ptr) *(T_Ptr) = 0 
#define T_COPY(T_Ptr) *(T_Ptr)
#define T_DELETE(T_Ptr) *(T_Ptr) = 0
#include "ooc_vector.c"
#undef T_EQUALS
#undef T_COPY
#undef T_ALLOC
#undef T_DELETE
#undef T

//Vector(Vector(int))
#define T Vectorint
#define T_EQUALS(element, other_element) (!Call(Vectorint, equals, element, other_element) ? (true) : (false))
#define T_ALLOC(T_Ptr) *(T_Ptr) = NewVectorint()
#define T_COPY(T_Ptr) Call(Vectorint, copy, *(T_Ptr))
#define T_DELETE(T_Ptr) Delete(Vectorint, *(T_Ptr))
#include "ooc_vector.c"
#undef T_EQUALS
#undef T_COPY
#undef T_ALLOC
#undef T_DELETE
#undef T


//Vector(float)
#define FLOAT_EPLISON 0.0000005

#define T float
#define T_EQUALS(element, other_element) ((fabs((element) - (other_element)) < FLOAT_EPLISON) ? (true) : (false))
#define T_ALLOC(T_Ptr) *(T_Ptr) = 0.0f
#define T_COPY(T_Ptr) *(T_Ptr)
#define T_DELETE(T_Ptr) *(T_Ptr) = 0.0f
#include "ooc_vector.c"
#undef T_EQUALS
#undef T_COPY
#undef T_ALLOC
#undef T_DELETE
#undef T

#undef FLOAT_EPLISON

//Vector(String)
#define T String
#define T_EQUALS(element, other_element) ((Call(String, equals, element, other_element)) ? (true) : (false))
#define T_ALLOC(T_Ptr) *(T_Ptr) = New(String)
#define T_COPY(T_Ptr) Call(String, copy, *(T_Ptr))
#define T_DELETE(T_Ptr) Delete(String, *(T_Ptr))
#include "ooc_vector.c"
#undef T_EQUALS
#undef T_COPY
#undef T_ALLOC
#undef T_DELETE
#undef T

#define Vector(type) VectorExpansion(type)
