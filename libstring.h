#pragma once

#include "container.h"

typedef struct _StringVFTable
{
	ContainerVFTable containerVFTable;
	char* (*c_str)(void* this);
	char* (*append)(void* this, char* value);
	int (*find) (void* this, char* value);
	String* (*substring)(void* this, int start, int end);

} StringVFTable;

bool StringEquals(void* object)
{
	
};

typedef struct _String
{
	Container container;
	int length;
	char* pString;
} String;
