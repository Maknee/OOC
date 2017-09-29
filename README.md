This project focuses on implementing a templated fixed size (chained) hashmap.
Currently, the key can be only a string (char*), but can be
replaced with another key datatype with its own hash function
I wanted to make the project modular and easy to use in C.

Setup:
	make
	./hashmap

Runtimes
set - Expected O(1) if no collision occurs
get - Expected O(1) if there is no chain at the index produced by the hash function
delete - Expected O(1) if there is no chain at the index produced by the hash function
load - O(1) current size and max size of the hash map is stored in the hashmap struct

/src
	hash_map_template.h/.c - contains the templated key/value pairs
	hash_map.h/.c - implmentation of a fixed hash map
	template.h - contains necessary macros
	main.c - main program (commandline / testing)

How to use it

Everything in the project is constructed using macro expansion, so
for example, we went to construct a hashmap with the key being a string 
and int as the value

```C

//construct a hashmap with String as key and int as value
HashMap(String, int) hashmap = New(HashMap(String, int), 1);

//allocated a string with 1 (helper function)
String one = CreateString("1");

//insert a key/value pair ("1", 1) into the hashmap, so hashmap is now
//at its limit. Only keys can be replaced or removed at this point
Call(HashMap(String, int), set, hashmap, one, 1));

```C

How it works:

HashMap(String, int) hashmap = New(HashMap(String, int), 1);

See template.h for macros

HashMap(String, int) gets expanded to HashMapStringint, which is declared
in hash_map_template.h/.c and gets expanded/defined in hashmap.h/.c

The second part expands to NewHashMapStringint(1)



Call(HashMap(String, int), set, hashmap, one, 1));

Call is an interesting macro. 
Let's first see how the hashmap data structure is defined

HashMap
	pVFTable  -----------> set
	size                   get
	table                  delete
	                       load

The hashmap has a function table that contains the function pointers to the functions to be called, so
Call gets expanded to 

((hashStringintVFTable*)hash_map->pVFTable)->set(one, 1)

Now, this makes a lot more sense :) We access the function table and call set(...) in it

