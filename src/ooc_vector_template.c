#include "ooc_vector_template.h"

#ifdef T
#undef T
#endif
#define T int
#define T_EQUALS(element, other_element) ((element == other_element) ? (true) : (false))
#include "ooc_vector.c"
#undef T_EQUALS
#undef T
