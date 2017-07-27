#pragma once

#include <stdint.h>
#include <stdbool.h>

#define MAX_CLASS_NAME_LENGTH                80

#define CLASS_HIERARCHY_VIRTUAL_INHERITENCE  0x1
#define CLASS_HIERARCHY_MULTIPLE_INHERTIENCE 0x3

typedef struct _String String;
typedef struct _TypeDescriptor TypeDescriptor;
typedef struct _ClassHierarchyDescriptor ClassHierarchyDescriptor;
typedef struct _BaseClassDescriptor BaseClassDescriptor;

typedef struct _CompleteObjectLocator
{
	uint32_t signature;
	struct _TypeDescriptor* pTypeDescriptor;
	struct _ClassHierarchyDescriptor* pClassHierarchyDescriptor;
} CompleteObjectLocator;

//Contains the classes details and names
typedef struct _TypeDescriptor
{
	void* pVFTable;
	char name[MAX_CLASS_NAME_LENGTH];
} TypeDescriptor;


typedef struct _ClassHierarchyDescriptor
{
	uint32_t attributes;
	uint32_t numBaseClasses;
	struct _BaseClassDescriptor (*pBaseClassArray)[]; //pointer to array
} ClassHierarchyDescriptor;

typedef struct _BaseClassDescriptor
{
	uint32_t numContainedClasses;
	struct _TypeDescriptor* pTypeDescriptor;
} BaseClassDescriptor;

