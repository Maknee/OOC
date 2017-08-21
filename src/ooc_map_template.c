#include "ooc_map_template.h"

//get rid of Entry macro and then redef at end cause Entry is a type
#ifdef Entry
#undef Entry
#endif

#ifdef K
#undef K
#endif

#ifdef V
#undef V
#endif

#define RED 1
#define BLACK 0
#define RIGHT 1
#define LEFT 0

//Entry(int, int)
#define K int
#define V int
#define K_EQUALS(element, other_element) ((element == other_element) ? (true) : (false))
#define K_COMPARE_TO(element, other_element) (element - other_element)
#define K_ALLOC(T_Ptr) *(T_Ptr) = 0 
#define K_COPY(T_Ptr) *(T_Ptr)
#define K_DELETE(T_Ptr) *(T_Ptr) = 0
#define V_EQUALS(element, other_element) ((element == other_element) ? (true) : (false))
#define V_COMPARE_TO(element, other_element) (element - other_element)
#define V_ALLOC(T_Ptr) *(T_Ptr) = 0 
#define V_COPY(T_Ptr) *(T_Ptr)
#define V_DELETE(T_Ptr) *(T_Ptr) = 0
#include "ooc_entry.c"
#include "ooc_map.c"
#undef K_EQUALS
#undef K_COPY
#undef K_ALLOC
#undef K_COMPARE_TO
#undef K_DELETE
#undef V_EQUALS
#undef V_COPY
#undef V_ALLOC
#undef V_COMPARE_TO
#undef V_DELETE
#undef V
#undef K

#undef RED
#undef BLACK
#undef RIGHT
#undef LEFT

#define Entry(key_type, value_type) EntryExpansion(key_type, value_type)
