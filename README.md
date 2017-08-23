[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Build Status](https://travis-ci.com/Maknee/OOC.svg?token=awrLzay2NUpTLyLqBpuQ&branch=master)](https://travis-ci.com/Maknee/OOC)
[![Documentation](https://codedocs.xyz/Maknee/OOC.svg)](https://codedocs.xyz/Maknee/OOC/)
[![codecov](https://codecov.io/gh/Maknee/OOC/branch/master/graph/badge.svg)](https://codecov.io/gh/Maknee/OOC)

## What is OOC?

OOC is an acroynm for "Object Oriented C" - I wasn't creative enough to give it another name :(.

The project uses object orient design and implementations to construct a framework consisting of important
data structures (some have templates :)!) that do not exist in the standard C library.

Current data structures implemented

* String
* Templated Vector
* Templated Set
* Templated Map

## How does this work?

![Alt text](docs/OOC_how_it_works.png?raw=true "How OOC works")

OOC works in a similar fashion to how C++ works. Using how structs
are laid out in memory, one can construct a class, a virtual function table
and even runtime information for the class. 

Here is an example of the vector object. It points to the vector class containing
the virtual function table and other necessary information for the class. Since 
the vector inherits from container, which inherits from object, the vector must override
the object and container methods. There is also a CompleteObjectLocator class, which contains
runtime type information for casting between classes and finding out an object's type at runtime.

A Stackoverflow post that inspired this project

https://stackoverflow.com/questions/2181079/object-oriented-programming-in-c

A better explanation of RTTI

http://www.openrce.org/articles/full_view/23

## Who the heck would want to use this?

Sometimes, C does get a bit messy and hard to manage, even though I love writing raw C code :(. 
The standard library can be tricky at times and there are plenty of unsafe functions
that should/are depreciated. Anyone who is annoyed by the standard library or feel limited
by the amount of primitive data structures in C (struct, arrays), should use this framework.


## Why are you reimplementing C++, you dummy?

Yup, I'll admit it. I'm pretty dumb for implementing this framework when C++ exists. 
But... I want to learn. I didn't fully understand the virtual function table concept.
I didn't understand how RTTI works. This project gave me insight as to how higher level languages
such as java are implemented. Plus, I want to use this in my other (future) projects :).

## Example

```C
#include "ooc.h"

int main()
{	
	//allocate a new string
	String s1 = New(String);

	//allocate a new string
	String s2 = New(String);

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

See examples folder for more examples

## Credits

Explanations of implementing object oriented in c

https://stackoverflow.com/questions/2181079/object-oriented-programming-in-c

Great Travis CI testing C example

https://github.com/softwaresaved/build_and_test_examples

RTTI

http://www.openrce.org/articles/full_view/23

https://www.blackhat.com/presentations/bh-dc-07/Sabanal_Yason/Paper/bh-dc-07-Sabanal_Yason-WP.pdf

## To Do

[never done :(] Document specifications

[x] Finish string class 

[x] Test string class

[x] Test on linux and create makefile

[x] Implement Dynamic cast (upcast/downcast)

[ URGENT ] Provide Examples

[ Good ] Explain how OOC works w/ diagrams

[ Unsafe - probably implemented as MoveCall in future ] Move semantics

[x] Iterator

[ dunno ] const Iterator

[ Make neater ] ForEach keyword

[x] Vector class

[x] Test Vector class

[x] Set class

[x] Map class

[ uh ] Change struct names beginning with underscore (nonstandard...)

[ well ] Consider changing microsoft version of "anonymous" structs -> requires --fms-extensions on gcc :( (Less readable and seeing what is inheritence)

## ?Wonderings, pondering, design decisions?

Should constructors just set vftable pointer to super's vftable or should the super's vftable be memcpy'ed into the dervied pointer?

Leaning towards memcpy

Reason:
No point in just setting the pointer if the pointer is just going to be overwritten...

Inefficient setting of variables in vtable, but necessary to call once. Easier to design, less code though...
