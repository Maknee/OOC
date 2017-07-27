#pragma once

#include "object.h"

typedef struct _ContainerVFTable
{
	ObjectVFTable objectVFTable;
	bool (*add)(void* item);
	void (*clear)();
	bool (*remove)(void* item);
	bool (*contains)(void* item);

	bool (*isEmpty)();
	int (*size)();
} ContainerVFTable;

static const ContainerVFTable containerVFTable =
{
	.objectVFTable = 
	{
		.pCompleteObjectLocator = NULL,
		.equals = NULL,
		.toString = NULL
	},
	.add = NULL,
	.clear = NULL,
	.remove = NULL,
	.contains = NULL,
	.isEmpty = NULL,
	.size = NULL
};

typedef struct _Container
{
	Object object;
} Container;

