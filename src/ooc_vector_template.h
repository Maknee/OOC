/**
* @file ooc_vector_template.h
* @brief Vector class header
*
* The vector class is a dynamic array that increases in size 
* as elements are pushed. The vector class ensures that elements
* are contingious in memory.
* 
* @author Henry Zhu (Maknee)
* @bug No know bugs.
* @note 
* @warning <b>NEVER</b> use the same vector more than once in a vector function call.
* @see ooc_vector.c
* @date	8/6/2017
* @todo {}
*/

#pragma once

#define OOC_V1

#include "ooc_template.h"



#define T int
#include "ooc_vector.h"
#undef T

#define T Vectorint
#include "ooc_vector.h"
#undef T

#define T float
#include "ooc_vector.h"
#undef T

#define T String
#include "ooc_vector.h"
#undef T

#define T Container
#include "ooc_vector.h"
#undef T
