#define OOC_V2

#include "ooc.h"

Vector(String) SplitByDelimiter(String str, String delimiter)
{
	//Create a vector containing all the strings
	Vector(String) directories = New(Vector(String));

	//Parse line 
	int start_index = 0;
	int index_of_slash = 0;

	//Find the index of the next occurence of "/"
	while ((index_of_slash = Call(str, find, delimiter, start_index)) != NPOS)
	{
		//Get the substring between the last occurence and next occurence of "/"
		String directory = Call(str, substring, start_index, index_of_slash);

		//Insert the substring into the vector
		MoveCall(directories, push_back, directory);

		//Update the index to one past the occurence of "/"
		start_index = index_of_slash + 1;
	}

	//There is still one substring after the last occurence of "/"
	String last_directory = Call(str, substring, start_index, index_of_slash);

	MoveCall(directories, push_back, last_directory);

	return directories;
}

int main()
{
	//Want program to output
	//C:
	//path
	//to
	//dir

	String path = New(String);

	//Read data from file...
	Call(path, set, "C:/path/to/dir");

	//Find substrings with "/"
	String delimiter = New(String);
	Call(delimiter, set, "/");

	//Call our split function
	Vector(String) directories = SplitByDelimiter(path, delimiter);

	//Iterate through each string and print
	ForEach(String* directory, Vector(String), directories,
	{
		printf("%s\n", Call(*directory, c_str));
	})

	//Free resources
	Delete(delimiter);

	Delete(path);

	Delete(directories);

	return 0;
}

//Version 1
/*
#define OOC_V1

#include "ooc.h"

int main()
{
	//Want program to output
	//C:
	//path
	//to
	//dir

	String path = New(String);

	//Read data from file...
	Call(String, set, path, "C:/path/to/dir");

	//Parse line 
	int start_index = 0;
	int index_of_slash = 0;

	//Find substrings with "/"
	String to_find = New(String);
	Call(String, set, to_find, "/");

	//Create a vector containing all the strings
	Vector(String) directories = New(Vector(String));

	//Find the index of the next occurence of "/"
	while ((index_of_slash = Call(String, find, path, to_find, start_index)) != NPOS)
	{
		//Get the substring between the last occurence and next occurence of "/"
		String directory = Call(String, substring, path, start_index, index_of_slash);

		//Insert the substring into the vector
		MoveCall(Vector(String), push_back, directories, directory);

		//Update the index to one past the occurence of "/"
		start_index = index_of_slash + 1;
	}

	//There is still one substring after the last occurence of "/"
	String last_directory = Call(String, substring, path, start_index, index_of_slash);

	MoveCall(Vector(String), push_back, directories, last_directory);

	//Iterate through each string and print
	ForEach(String* directory, Vector(String), directories,
	{
		printf("%s\n", Call(String, c_str, *directory));
	})

	//Free resources
	Delete(String, to_find);

	Delete(String, path);

	Delete(Vector(String), directories);

	return 0;
}
 */