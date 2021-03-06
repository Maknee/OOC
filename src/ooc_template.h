/**
* @file ooc_template.h
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
#include "ooc_object.h"
#include "ooc_string.h"
#include <math.h>
#include <stdbool.h>

/**********************************************************************************************//**
 * @def		EXPAND(x)
 *
 * @brief	expands a token
 *
 * @param	x	Variable to expand
 * 				
 * @def		CAT(a, b)
 *
 * @brief	appends two token
 *
 * @param	a	Variable to append
 * @param	b	Variable to append
 * 				
 * @def		STRINGIFY(x) 
 *
 * @brief	makes a token a string
 *
 * @param	x	Variable to become a string
 *
 * @def		GET_FIRST_ARG(arg, ...)
 *
 * @brief	Gets the first argument of a macro
 *
 * @param	arg		The first argument
 * @param	args	The arguments
 *
 * @note	bug in VS... https://stackoverflow.com/questions/4750688/how-to-single-out-the-first-parameter-sent-to-a-macro-taking-only-a-variadic-par
 *
 * @def		PP_NARG(...)
 *
 * @brief	Returns the number of arguments
 * 
 * @param	args	The arguments
 * 
 * @def		New(type)
 *
 * @brief	A macro that calls new for a class and returns an object
 * @param	type	The class
 * @return	An object
 *  
 * @def		Delete(type, object)
 *
 * @brief	A macro that calls new for a class and returns an object
 * 			
 * @param	type	The class
 * @param	object	the object to be deleted
 * 
 * @def		Call(type, function, ...)
 *
 * @brief	A macro that calls a function in an object
 * 			
 * @param	type		The class
 * @param	function	The object's member method
 * @param	...			Variable arguments providing additional information.
 * @note    The first parameter in the variable arguments must be the <b>object</b> because every member
 * 			function passes <b>this</b> as the first argument
 * 
 * @def		SafeCall(type, function, ...)
 *
 * @brief	A macro that calls a function in an object and checks the type at runtime
 * 			
 * @param	type		The class
 * @param	function	The object's member method
 * @param	...			Variable arguments providing additional information.
 * @note    The first parameter in the variable arguments must be the <b>object</b> because every member
 * 			function passes <b>this</b> as the first argument
 * 			
 * @def		Initializer_List(type, ...)
 *
 * @brief	A macro that initializes an object
 *
 * @param	type		The class's type
 * @param	...			List of arguements
 * 			
 * @def		Upcast(new_type, object)
 *
 * @brief	Casts an object to a new_object, returns vftable, NULL if failure
 *
 * @param	new_type	The new upcast type
 * @param	object		The object
 *
 *
 **************************************************************************************************/

#define EMPTY(...)
#define DEFER(...) __VA_ARGS__ EMPTY()
#define EXPAND(...) __VA_ARGS__

#define PRIMITIVE_CAT(a, b) a##b
#define CAT(a, b) PRIMITIVE_CAT(a, b)

#define STRINGIFY_EXPANSION(x) #x
#define STRINGIFY(x) STRINGIFY_EXPANSION(x)

#define ADD_PARERENTHSIS_EXPANSION(x) (x)
#define ADD_PARERENTHSIS(x) ADD_PARERENTHSIS_EXPANSION(x)

#define GET_FIRST_ARG_(arg, ...) arg
#define GET_FIRST_ARG(args) GET_FIRST_ARG_ args

#define GET_SECOND_ARG_(arg, arg2, ...) arg2
#define GET_SECOND_ARG(args) GET_SECOND_ARG_ args

//https ://stackoverflow.com/questions/2124339/c-preprocessor-va-args-number-of-arguments
//doesn't work with empty
#define PP_NARG(...) \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())

#define PP_NARG_(...) \
         EXPAND(PP_ARG_N(__VA_ARGS__))

#define PP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N

#define PP_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

//Macros for calling 

#define Initializer_List(type, ...) (const type[]) {__VA_ARGS__, 0}, PP_NARG(__VA_ARGS__)

//TEMPLATES
#define VectorExpansion(type) CAT(Vector, type)
#define Vector(type) VectorExpansion(type)

#define SetExpansion(type) CAT(Set, type)
#define Set(type) SetExpansion(type)

#define EntryExpansion(key_type, value_type) CAT(Entry, CAT(key_type, value_type))
#define Entry(key_type, value_type) EntryExpansion(key_type, value_type)

#define MapExpansion(key_type, value_type) CAT(Map, CAT(key_type, value_type))
#define Map(key_type, value_type) MapExpansion(key_type, value_type)

#define IteratorExpansion(type) CAT(type, Iterator)
#define Iterator(type) IteratorExpansion(type)

//CASTS

void* SetVFTable(void* object, void* new_vftable);

void* UpcastVFTableRecurse(const char* new_type, void* _pVFTable, void* _basepVFTable);
void* UpcastVFTable(const char* new_type, void* object);

//only casts table
#define UpcastTableExpansion(new_type, object)                 \
		UpcastVFTable(STRINGIFY(new_type), object)             \

#define UpcastTable(new_type, object) UpcastTableExpansion(new_type, object)

//casts object (changes vftable)
#define Upcast(new_type, object) ((UpcastTable(new_type, object)) ? (SetVFTable(object, UpcastTable(new_type, object))) : (NULL))

void* DowncastVFTable(void* _newTypeVFTable, void* object);

//only casts table
#define DowncastTableExpansion(new_type, object)               \
		DowncastVFTable(&CAT(new_type, vfTable), object)       \

#define DowncastTable(new_type, object) DowncastTableExpansion(new_type, object)

#define Downcast(new_type, object) ((DowncastTable(new_type, object)) ? (SetVFTable(object, DowncastTable(new_type, object))) : (NULL))

//used for SafeCall -- we don't want to change the vftable, only checks if cast is allowed
#define CheckDynamicCast(new_type, object) ((UpcastTable(new_type, object)) ? (true) : ((DowncastTable(new_type, object)) ? (true) : (false)))

//converts actual object's vftable
//#define DynamicCast(new_type, object) ((UpcastTable(new_type, object)) ? (Upcast(new_type, object)) : ((DowncastTable(new_type, object)) ? (Downcast(new_type, object)) : (NULL)))

//attempts upcast and downcast vftable (doesn't change vftable)
#define DynamicCast(new_type, object) ((UpcastTable(new_type, object)) ? (object) : ((DowncastTable(new_type, object)) ? (object) : (NULL)))

//Important expansions

#define NewExpansion(type) New ## type()
#define New(type) NewExpansion(type)

//TOTAL UNSAFE... :(
//MOVE SEMANTICS 
// =/ in C LUL?

//ugh not perfect, we convert the macro to a string and check if it is a move
//const char* CheckForMove(const char* macro);

/*
#define Moo(type, function, ...) CheckForMove(GET_FIRST_ARG((#__VA_ARGS__)))

#define CheckMove(...) CheckForMove(GET_FIRST_ARG((#__VA_ARGS__)))

#define MoveCall(type, function, ...)                 \
(CheckForMove(GET_FIRST_ARG((#__VA_ARGS__)))           \
?                                                      \
(Call(type, CAT(move_, function), __VA_ARGS__))        \
:                                                      \
(Call(type, function, __VA_ARGS__))                    \
)                                                      \

#define MoveCall(type, function, ...) MoveCallExpansion(type, function, __VA_ARGS__)
*/


bool MoveSetPointerToNull(bool result, void** object);

/*
#define MoveCallExpansion(type, function, ...) ((type ## VFTable*)((Object)GET_FIRST_ARG((__VA_ARGS__)))->pVFTable)->CAT(move_, function)(__VA_ARGS__)
#define MoveCall(type, function, ...) MoveCallExpansion(type, function, __VA_ARGS__)
*/

//default to V2 if V1 is not defined
#define OOC_V2

#if defined(OOC_V1)

#define Delete(type, object) DeleteExpansion(type, object)

#define CallExpansion(type, function, ...) ((type ## VFTable*)((Object)GET_FIRST_ARG((__VA_ARGS__)))->pVFTable)->function(__VA_ARGS__)
#define Call(type, function, ...) CallExpansion(type, function, __VA_ARGS__)

#define MoveCallExpansion(type, function, ...) MoveSetPointerToNull(((type ## VFTable*)((Object)GET_FIRST_ARG((__VA_ARGS__)))->pVFTable)->CAT(move_, function)(__VA_ARGS__), (void**)&GET_SECOND_ARG((__VA_ARGS__)))
#define MoveCall(type, function, ...) MoveCallExpansion(type, function, __VA_ARGS__)

#define SafeCallExpansion(type, function, ...) (CheckDynamicCast(type, GET_FIRST_ARG((__VA_ARGS__))) ? (((type ## VFTable*)((Object)GET_FIRST_ARG((__VA_ARGS__)))->pVFTable)->function(__VA_ARGS__)) : 0)
#define SafeCall(type, function, ...) SafeCallExpansion(type, function, __VA_ARGS__)

#define DeleteExpansion(type, object)                         \
		Delete ## type(object);                               \
		object = NULL                                         \

//Iterators

#define ForEach(element, container_type, container, ...)      \
		for(                                                  \
			Iterator(container_type) CAT(container, Iterator) = Call(container_type, begin, container); \
			Call(container_type, end, container, CAT(container, Iterator)) != NULL;                     \
			Call(container_type, next, container, CAT(container, Iterator))                             \
		   )                                                  \
        {                                                     \
			element = CAT(container, Iterator)->data;         \
			__VA_ARGS__                                       \
		}                                                     \

#elif defined(OOC_V2)

//Iterators
#define ForEach(element, container_type, container, ...)                                \
		for(                                                                            \
			Iterator(container_type) CAT(container, Iterator) = Call(container, begin); \
			Call(container, end, CAT(container, Iterator)) != NULL;                     \
			Call(container, next, CAT(container, Iterator))                             \
		   )                                                                            \
        {                                                                               \
			element = CAT(container, Iterator)->data;                                   \
			__VA_ARGS__                                                                 \
		}                                                                               \

#define MoveCallExpansion(object, function, ...) MoveSetPointerToNull((object)->pVFTable->CAT(move_, function)(object, __VA_ARGS__), (void**)&GET_FIRST_ARG((__VA_ARGS__)))
#define MoveCall(object, function, ...) MoveCallExpansion(object, function, __VA_ARGS__)

#ifdef _MSC_VER //microsoft (nonstandard) zero arguments erases comma

#define CallExpansion(object, function, ...) ((object)->pVFTable->function(object, __VA_ARGS__))
#define Call(object, function, ...) CallExpansion(object, function, __VA_ARGS__)

#define SafeCallExpansion(type, object, function, ...) ((CheckDynamicCast(type, object)) ? (Call(type, object, function, __VA_ARGS__)) : (0))
#define SafeCall(type, object, function, ...) do { SafeCallExpansion(type, object, function, __VA_ARGS__) } while(0);

#else //assume gcc/clang (nonstandard) zero arguments passed to __VA_ARGS__ doesn't erase the comma

#define CallExpansion(object, function, ...) ((object)->pVFTable->function(object, ##__VA_ARGS__))
#define Call(object, function, ...) CallExpansion(object, function, ##__VA_ARGS__)

#define SafeCallExpansion(type, object, function, ...) ((CheckDynamicCast(type, object)) ? (Call(type, object, function, ##__VA_ARGS__)) : (0))
#define SafeCall(type, object, function, ...) do { SafeCallExpansion(type, object, function, ##__VA_ARGS__) } while(0);

#endif

#define DeleteExpansion(object)                         \
          Call(object, delete);                         \
		  object = NULL;                                \

#define Delete(object) do { DeleteExpansion(object) } while(0)

#endif

#ifdef OOC_V1
#undef OOC_V1
#endif

#ifdef OOC_V2
#undef OOC_V2
#endif

//GLOBAL DEFINES
#define NPOS -1

#define OOC_CLASS(type, ...)                                      \
	typedef struct CAT(type, VFTable_) CAT(type, VFTable);        \
	typedef struct CAT(type, _)                                   \
	{                                                             \
		CAT(type, VFTable)* pVFTable;                             \
		CAT(type, VFTable)* objectpVFTable;                       \
		struct                                                    \
			GET_FIRST_ARG((__VA_ARGS__))                          \
		;                                                         \
	} *type;                                                      \
	                                                              \
	typedef struct CAT(type, VFTable_)                            \
	{                                                             \
		CompleteObjectLocator* pCompleteObjectLocator;            \
		void (*delete)(type this);                                \
		type (*copy)(type this);                                  \
		bool (*equals)(type this, type other);                    \
		int (*compareTo)(type this, type other);                  \
		char* (*toString)(type this);                             \
		struct                                                    \
			GET_SECOND_ARG((__VA_ARGS__))                         \
		;                                                         \
	} CAT(type, VFTable);                                         \
	                                                              \
	type CAT(New, type)();                                        \
	void Delete##type(type this);                                 \
	type CAT(type, copy)(type this);                              \
	bool CAT(type, equals)(type this, type other);                \
	int CAT(type, compareTo)(type this, type other);              \
	char* CAT(type, toString)(type this);                         \
	                                                              \
	TypeDescriptor CAT(type, TypeDescriptor);                     \
	BaseClassDescriptor CAT(type, BaseClassArray)[2];             \
	ClassHierarchyDescriptor CAT(type, ClassHierarchyDescriptor); \
	CompleteObjectLocator CAT(type, CompleteObjectLocator);       \
	                                                              \

#define OOC_DEFAULT_CLASS_IMPL(type)                                                                                                                                                   \
	CAT(type, VFTable) CAT(type, vfTable) = { 0 };                                                                                                                                     \
	type CAT(New, type)()																														                                       \
	{                                                                                                                                                                                  \
		type this = check_calloc(sizeof(struct CAT(type, _)));                                                                                                                         \
		this->pVFTable = check_calloc(sizeof(CAT(type, VFTable)));                                                                                                                     \
		ObjectConstruct(this);                                                                                                                                                         \
		                                                                                                                                                                               \
	    CAT(type, vfTable).pCompleteObjectLocator = &CAT(type, CompleteObjectLocator);                                                                                                 \
	    CAT(type, vfTable).delete = &Delete##type;                                                                                                                                     \
	    CAT(type, vfTable).copy = &CAT(type, copy);                                                                                                                                    \
	    CAT(type, vfTable).equals = &CAT(type, equals);                                                                                                                                \
	    CAT(type, vfTable).compareTo = &CAT(type, compareTo);                                                                                                                          \
	    CAT(type, vfTable).toString = &CAT(type, toString);                                                                                                                            \
	                                                                                                                                                                                   \
	    memcpy(this->pVFTable, &CAT(type, vfTable), sizeof(struct CAT(type, _)));                                                                                                      \
	                                                                                                                                                                                   \
	    return this;                                                                                                                                                                   \
	}                                                                                                                                                                                  \
	                                                                                                                                                                                   \
	void Delete##type(type this)                                                                                                                                                       \
	{                                                                                                                                                                                  \
		ObjectDestruct(this);	                                                                                                                                                       \
	    this->pVFTable = NULL;                                                                                                                                                         \
	    free(this->objectpVFTable);                                                                                                                                                    \
	    free(this);                                                                                                                                                                    \
	}                                                                                                                                                                                  \
	                                                                                                                                                                                   \
	type CAT(type, copy)(type this)                                                                                                                                                    \
	{                                                                                                                                                                                  \
		type copy_object = CAT(New, type)(this);	                                                                                                                                   \
		memcpy((char*)copy_object + 2 * sizeof(CAT(type, VFTable)*), (char*)this + 2 * sizeof(CAT(type, VFTable)*), sizeof(struct CAT(type, _)) - 2 * sizeof(CAT(type, VFTable)*));    \
	    return copy_object;                                                                                                                                                            \
	}                                                                                                                                                                                  \
	                                                                                                                                                                                   \
	bool CAT(type, equals)(type this, type other)                                                                                                                                      \
	{                                                                                                                                                                                  \
	    return !memcmp((char*)this + 2 * sizeof(CAT(type, VFTable)*), (char*)other + 2 * sizeof(CAT(type, VFTable)*), sizeof(struct CAT(type, _)) - 2 * sizeof(CAT(type, VFTable)*));  \
	}	                                                                                                                                                                               \
	                                                                                                                                                                                   \
	int CAT(type, compareTo)(type this, type other)                                                                                                                                    \
	{                                                                                                                                                                                  \
	    return memcmp((char*)this + 2 * sizeof(CAT(type, VFTable)*), (char*)other + 2 * sizeof(CAT(type, VFTable)*), sizeof(struct CAT(type, _)) - 2 * sizeof(CAT(type, VFTable)*));   \
	}	  	                                                                                                                                                                           \
	                                                                                                                                                                                   \
	char* CAT(type, toString)(type this)                                                                                                                                               \
	{                                                                                                                                                                                  \
	    return ObjectToString(this);                                                                                                                                                   \
	}	  	                                                                                                                                                                           \
	                                                                                                                                                                                   \
	TypeDescriptor CAT(type, TypeDescriptor) =                                                                                                                                         \
	{                                                                                                                                                                                  \
		.pVFTable = &CAT(type, vfTable),                                                                                                                                               \
		.name = STRINGIFY(type)                                                                                                                                                        \
	};                                                                                                                                                                                 \
                                                                                                                                                                                       \
	BaseClassDescriptor CAT(type, BaseClassArray)[] =                                                                                                                                  \
	{                                                                                                                                                                                  \
		ObjectBaseClassDescriptor,                                                                                                                                                     \
		{                                                                                                                                                                              \
			.numContainedClasses = 2,                                                                                                                                                  \
			.pTypeDescriptor = &CAT(type, TypeDescriptor)                                                                                                                              \
		}                                                                                                                                                                              \
	};                                                                                                                                                                                 \
                                                                                                                                                                                       \
	ClassHierarchyDescriptor CAT(type, ClassHierarchyDescriptor) =                                                                                                                     \
	{                                                                                                                                                                                  \
		.attributes = CLASS_HIERARCHY_VIRTUAL_INHERITENCE,                                                                                                                             \
		.numBaseClasses = 2,                                                                                                                                                           \
		.pBaseClassArray = CAT(type, BaseClassArray)                                                                                                                                   \
	};                                                                                                                                                                                 \
                                                                                                                                                                                       \
	CompleteObjectLocator CAT(type, CompleteObjectLocator) =                                                                                                                           \
	{                                                                                                                                                                                  \
		.signature = 0x48454845,                                                                                                                                                       \
		.pTypeDescriptor = &CAT(type, TypeDescriptor),                                                                                                                                 \
		.pClassHierarchyDescriptor = &CAT(type, ClassHierarchyDescriptor)                                                                                                              \
	};                                                                                                                                                                                 \
                                                                                                                                                                                       \


//GCC

#define GCC_VERSION (__GNUC__ * 10000 \
                               + __GNUC_MINOR__ * 100 \
                               + __GNUC_PATCHLEVEL__)

 /* Test for GCC > 4.9.0 */
#if GCC_VERSION > 40900
//implement _Generic
#define GCC_New()

void free_object(void* obj);

//https://snai.pe/c/c-smart-pointers/
#define unique __attribute__((cleanup(free_object)))

#endif

