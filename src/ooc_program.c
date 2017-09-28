/*! 
* \mainpage OOC Main page
*
* \section intro_sec Introduction
*
* Welcome to OOC documentation
*
* \section string_sec String class
*
*   		String Methods
*
* 			Overridden Object Methods
* 
*			equals - @ref StringEquals
*			compareTo - @ref StringCompareTo
*			toString - @ref StringToString
*
*			Overridden Container Methods
*
*			add - @ref StringAdd
*			clear - @ref StringClear
*			remove - @ref StringRemove
*			contains - @ref StringContains
*			copy - @ref StringCopy
*			isEmpty - @ref StringIsEmpty
*			size - @ref StringSize
* 
*/

#include "template.h"
#include "hash_map_template.h"

//helper function to create strings, assuming string_buf is null terminated
String CreateString(const char* string_buf)
{
	String string = calloc(1, (strlen(string_buf) + 1) * sizeof(char*));

	//not safe, but we assume that string_buf is null terminated
	strcpy(string, string_buf);

	return string;
}

int main()
{
	HashMap(String, int) hashmap = New(HashMap(String, int), 1);

	String one = CreateString("1");
	String two = CreateString("2");

	printf("%d\n", Call(HashMap(String, int), set, hashmap, one, 1));
	printf("%d\n", Call(HashMap(String, int), set, hashmap, one, 1));
	printf("%d\n", Call(HashMap(String, int), set, hashmap, two, 2));

	return 0;
}
