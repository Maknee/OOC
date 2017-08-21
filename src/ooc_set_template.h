/**
* @file ooc_set_template.h
* @brief Set class header
*
* The set class is a dynamic array that increases in size 
* as elements are pushed. The set class ensures that elements
* are contingious in memory.
* 
* @author Henry Zhu (Maknee)
* @bug No know bugs.
* @note 
* @warning <b>NEVER</b> use the same set more than once in a set function call.
* @see ooc_set.c
* @date	8/6/2017
* @todo {}
*/

#pragma once

#include "template.h"

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

#define T int
#include "ooc_set.h"
#undef T

#define T float
#include "ooc_set.h"
#undef T

#define T String
#include "ooc_set.h"
#undef T

#define T Container
#include "ooc_set.h"
#undef T

#undef RED
#undef BLACK
#undef RIGHT
#undef LEFT

#define Set(type) SetExpansion(type)
