[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build Status](https://travis-ci.com/Maknee/OOC.svg?token=awrLzay2NUpTLyLqBpuQ&branch=master)](https://travis-ci.com/Maknee/OOC)
[![Documentation](https://codedocs.xyz/Maknee/OOC.svg)](https://codedocs.xyz/Maknee/OOC/index.html)
[![codecov](https://codecov.io/gh/Maknee/OOC/branch/master/graph/badge.svg)](https://codecov.io/gh/Maknee/OOC)

## What is OOC?

OOC is an acroynm for "Object Oriented C"

The project uses object orient design and implementations to construct a framework consisting of important
data structures (some have templates :)!) that do not exist in the standard C library.

Current data structures implemented

* String
* Templated Vector
* Templated Set
* Templated Map

## Who the heck would want to use this?

Sometimes, C does get a bit messy and hard to manage. 
The standard library can be tricky at times and there are plenty of unsafe functions
that should/are deprecated. Anyone who is annoyed by the standard library or feel limited
by the amount of primitive data structures in C (struct, arrays), should use this framework.

There also are Object oriented C libraries out there, but they're far too awkward to use (too C heavy-handed)

[https://github.com/shichao-an/ooc](https://github.com/shichao-an/ooc)
[http://ooc-coding.sourceforge.net/](http://ooc-coding.sourceforge.net/)
[https://en.wikipedia.org/wiki/GObject](https://en.wikipedia.org/wiki/GObject)

## Tested compilers

- Microsoft Visual Studio 2015
- Microsoft Visual Studio 2017
- gcc 4.8.4
- gcc 8.0
- clang 3.8
- clang 5.0
- clang 6.0

If clang is used, make sure -Werror is not enabled if clang >= 5.0. This will cause a c extension to fail (-Wmicrosoft-anon-struct).

## Building

The project uses [cmake](https://cmake.org/) to generate the library and examples.

If a microsoft visual studio is used, testing will be disabled since [cuint](http://cunit.sourceforge.net/) is used as the testing framework.

In top level directory of OOC

cmake -Bbuild .

There is also a Makefile in the directory as well (It does not generate a library, however)

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

#### Abstraction

Each object in OOC is abstracted into its own class and implemenation details can be ignored. The same 
calls can be made to different objects such as String and Vector

```C
//returns number of elements in vec
Call(Vector(int), size, vec);

//returns number of characters in str
Call(String, size, str);
```

#### Encapsulation

The user never has to manually "grab" any data fields of an object in OOC.
Therefore, all data fields are "private" and there are getter functions to 
grab the data.

Example with vector (stores data in contigious memory)

```C
//get pointer to data (No need to do this)
vec->data;

//get first element of vector (more obvious that one is trying to get an int)
Call(Vector(int), get, vec, 0);
```

#### Inheritence

![Alt text](docs/OOC_inheritence.png?raw=true "OOC Inheritence")

Inheritence can be done by making use of how structs are laid out in memory.

For example, the string class inherits from a container class by holding the container struct inside string struct.

```C
typedef struct _String
{
	struct _Container container;
	size_t length;
	size_t capacity;
	union
	{
		char buf[DEFAULT_STRING_LENGTH];
		char* pBuf;
	} data;
} *String;
```

#### Polymorphism

![Alt text](docs/OOC_polymorphism.png?raw=true "OOC Polymorphism")

Polymorphism can be done in a similar fashion to how inheritence is implemented in OOC.

For example, the string virtual function table inherits from the container virtual function table
and overrides the original function in the string constructor

String Virtual Function Table

```C
typedef struct _StringVFTable
{
	struct _ContainerVFTable;
	void* (*set)(void* this, const char* item);
	char* (*c_str)(void* this);
	...
	StringIterator (*end)(void* this, StringIterator iterator);
} StringVFTable;
```
String Constructor 

```C
void StringConstruct(void* this)
{
	CHECK_NULL_NO_RET(this);

	//call super class's constructor (ContainerConstruct)
	ContainerConstruct(this);

	//Override Object's methods
	//=========================

	//Set the vtable's complete object locator to complete the RTTI circle
	StringvfTable.pCompleteObjectLocator = &stringCompleteObjectLocator;
	
	//Set the equals function
	StringvfTable.delete = &DeleteString;

	...

	//Override Container's methods
	//==========================

	StringvfTable.add = &StringAdd;
	StringvfTable.clear = &StringClear;

	...

	//Initialize class member methods
	//==========================

	StringvfTable.set = &StringSet;
	StringvfTable.c_str = &StringC_Str;

	...

}
```

## More detailed information on the topic

A Stackoverflow post that inspired this project

https://stackoverflow.com/questions/2181079/object-oriented-programming-in-c

A better explanation of RTTI

http://www.openrce.org/articles/full_view/23

## Limitations

Only one empty constructor can be made for a class

Single inheritence

## Why are you reimplementing C++, you dummy?

Yup. I'm pretty much reinventing the wheel for implementing this framework when C++ exists. 
But..., sometimes one has to use C and I wanted to learn from this project. I didn't fully understand the virtual function table concept.
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

[x] Explain how OOC works w/ diagrams

[x] Iterator

[x] Vector class

[x] Test Vector class

[x] Set class

[x] Map class

[ >:( ] Provide Examples

[sort of working] Move semantics

[ in the far future ] const Iterator

[ Kind of ugly right now ] ForEach keyword

[ really should ] Add do(){ } while(0); to macros...

[ :( ] Change struct names beginning with underscore (nonstandard...)

[ :( ] Consider changing microsoft version of "anonymous" structs -> requires --fms-extensions on gcc :( (Less readable and seeing what is inheritence)

[ Not sure, maybe take a look at how it's done in C++ ] Exceptions/Exception handling

[ should be simple ] Allow one to pass multiple parameters to a constructor. Add __VA_ARGS__ to New

[ ehh ] Replace Delete(type, object) with Delete(object). Can be fixed by below

[ ugh, going to have to figure out how to template this one ] Simplify library calls by templating object.h/container.h. Instead of Call(type, object, method), one can use Call(object, method) or object->Call(...)

[ Probably not ] Allow allocations on the stack and RAII like C++. Take a look at [https://github.com/Snaipe/libcsptr](https://github.com/Snaipe/libcsptr)

[ well ] C++ shared/unique_ptr

## Contributing

Feel free to make a PR and when I have time, I'll take a look into it. :)
