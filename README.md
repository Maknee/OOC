[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Build Status](https://travis-ci.com/Maknee/OOC.svg?token=awrLzay2NUpTLyLqBpuQ&branch=master)](https://travis-ci.com/Maknee/OOC)
[![Documentation](https://codedocs.xyz/Maknee/OOC.svg)](https://codedocs.xyz/Maknee/OOC/)
[![codecov](https://codecov.io/gh/Maknee/OOC/branch/master/graph/badge.svg)](https://codecov.io/gh/Maknee/OOC)

## Credits

Explanations of implementing object oriented in c

https://stackoverflow.com/questions/2181079/object-oriented-programming-in-c

Great Travis CI testing C example

https://github.com/softwaresaved/build_and_test_examples

RTTI

http://www.openrce.org/articles/full_view/23

https://www.blackhat.com/presentations/bh-dc-07/Sabanal_Yason/Paper/bh-dc-07-Sabanal_Yason-WP.pdf

## Example

```C
#include "ooc.h"

int main()
{	
	//allocate a new string
	void* s1 = New(String);

	//allocate a new string
	void* s2 = New(String);

	//set s1 to "Much w0w"
	Call(String, set, s1, "Much w0w");

	//set s2 to " d0ge"
	Call(String, set, s2, " d0ge");

	//prints "Much w0w"
	printf("%s\n", Call(String, c_str, s1));

	//add s2 to s1
	Call(String, add, s1, s2);

	//prints "Much w0w d0ge"
	printf("%s\n", Call(String, c_str, s1));

	//manually append string literal to s1
	Call(String, append, s1, " gud");

	//prints "Much w0w d0ge gud"
	printf("%s\n", Call(String, c_str, s1));

	//free the string's resources
	Delete(String, s2);
	Delete(String, s1);

	return 0;
}
```

## To Do

[never] Document specifications

[x] Finish string class 

[x] Test string class

[x] Test on linux and create makefile

[x] Implement Dynamic cast (upcast/downcast)

[ URGENT ] Provide Examples

[ Not sure ] Move semantics

[80%] Vector class

[60%] Test Vector class

[ :( ] Map class

## ?Wonderings, pondering, design decisions?

Should constructors just set vftable pointer to super's vftable or should the super's vftable be memcpy'ed into the dervied pointer?

Leaning towards memcpy

Reason:
No point in just setting the pointer if the pointer is just going to be overwritten...

Inefficient setting of variables in vtable, but necessary to call once. Easier to design, less code though...
