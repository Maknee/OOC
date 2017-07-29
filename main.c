#include "libstring.h"
#include "stdio.h"

int main()
{
	printf("%s", (*objectCompleteObjectLocator.pClassHierarchyDescriptor->pBaseClassArray).pTypeDescriptor->name);
	return 0;
}