#include "hash_map_template.h"

#ifdef K
#undef K
#endif

#ifdef V
#undef V
#endif

//https://stackoverflow.com/questions/7666509/hash-function-for-string
size_t StringHashFunction(char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return (size_t)hash;
}

typedef char* String;

//Key = String
//Value = int
#define K String
#define V int
#define HASH_FUNCTION(element) StringHashFunction(element)
//strcmp (assume that string is null terminated)
#define K_EQUAL(element, other_element) ((!strcmp(element, other_element)) ? (true) : (false))
#define K_DELETE(element) free(element)
#define V_EQUAL(element, other_element) ((element == other_element) ? (true) : (false))
#define V_DELETE(element) element = 0
#include "hash_map.c"
#undef K_EQUALS
#undef K_DELETE
#undef V_EQUALS
#undef V_DELETE
#undef V
#undef K
