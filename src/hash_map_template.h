#pragma once

#include "template.h"

#ifdef K
#undef K
#endif

#ifdef V
#undef V
#endif

typedef char* String;

#define K String
#define V int
#include "hash_map.h"
#undef V
#undef K
