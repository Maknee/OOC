/**
* @file ooc_entry_template.h
* @brief Entry class header
*
* The entry class is a dynamic array that increases in size 
* as elements are pushed. The entry class ensures that elements
* are contingious in memory.
* 
* @author Henry Zhu (Maknee)
* @bug No know bugs.
* @note 
* @warning <b>NEVER</b> use the same entry more than once in a entry function call.
* @see ooc_entry.c
* @date	8/6/2017
* @todo {}
*/

#pragma once

#include "template.h"

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

#define K int
#define V int
#include "ooc_entry.h"
#include "ooc_map.h"
#undef V
#undef K

#define K int
#define V String
#include "ooc_entry.h"
#include "ooc_map.h"
#undef V
#undef K

#undef RED
#undef BLACK
#undef RIGHT
#undef LEFT

#define Entry(key_type, value_type) EntryExpansion(key_type, value_type)
