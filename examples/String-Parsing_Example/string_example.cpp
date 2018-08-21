
#include <string>
#include <vector>
#include "../../src/template.h"

std::vector<std::string> SplitByDelimiter(std::string str, std::string delimiter)
{
	//Create a vector containing all the strings
	std::vector<std::string> directories;

	//Parse line 
	int start_index = 0;
	int index_of_slash = 0;

	//Find the index of the next occurence of "/"
	while ((index_of_slash = str.find(delimiter) != std::string::npos)
	{
		//Get the substring between the last occurence and next occurence of "/"
		std::string directory = str.substr(start_index, index_of_slash);

		//Insert the substring into the vector
		directories.push_back(std::move(directory));

		//Update the index to one past the occurence of "/"
		start_index = index_of_slash + 1;
	}

	//There is still one substring after the last occurence of "/"
	std::string directory = str.substr(start_index, index_of_slash);

	directories.push_back(std::move(directory));

	return directories;
}

int main()
{
	//Want program to output
	//C:
	//path
	//to
	//dir

	std::string path;

	//Read data from file...
	path.assign("C:/path/to/dir");

	//Find substrings with "/"
	std::string delimiter;
	delimiter.assign("/");

	//Call our split function
	std::vector<std::string> directories = SplitByDelimiter(path, delimiter);

	//Iterate through each string and print
	for(std::string& directory : directories)
	{
		printf("%s\n", directory.c_str());
	}

	//For c++, we do not have to deallocate, handled by RAII

	return 0;
}
