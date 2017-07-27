#include "libstring.h"
#include "stdio.h"

int main()
{
	printf("%s", (*objectCompleteObjectLocator.pClassHierarchyDescriptor->pBaseClassArray)[0].pTypeDescriptor->name);
	system("pause");
	return 0;
}