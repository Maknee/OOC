/**
* @file template.h
* @brief Template header file
*
* Includes macros for templates
* Credits to:
* https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms
* for preprocesser tricks
*
* @warning
* @date	8/7/2017
*/

#pragma once

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define PRIMITIVE_CAT(a, b) a##b
#define CAT(a, b) PRIMITIVE_CAT(a, b)

#define STRINGIFY_EXPANSION(x) #x
#define STRINGIFY(x) STRINGIFY_EXPANSION(x)

#define ADD_PARERENTHSIS_EXPANSION(x) (x)
#define ADD_PARERENTHSIS(x) ADD_PARERENTHSIS_EXPANSION(x)

#define GET_FIRST_ARG_(arg, ...) arg
#define GET_FIRST_ARG(args) GET_FIRST_ARG_ args

#define GET_SECOND_ARG_(arg, arg2) arg2
#define GET_SECOND_ARG(args) GET_SECOND_ARG_ args
																								//Macros for calling 
#define NewExpansion(type, ...) New ## type(__VA_ARGS__)
#define New(type, ...) NewExpansion(type, __VA_ARGS__)

#define DeleteExpansion(type, object)                         \
		Delete ## type(object);                               \
		object = NULL                                         \

#define Delete(type, object) DeleteExpansion(type, object)

#define CallExpansion(type, function, ...) ((type ## VFTable*)(GET_FIRST_ARG((__VA_ARGS__)))->pVFTable)->function(__VA_ARGS__)
#define Call(type, function, ...) CallExpansion(type, function, __VA_ARGS__)

#define HashMapExpansion(key, value) CAT(HashMap, CAT(key, value))
#define HashMap(key, value) HashMapExpansion(key, value)
