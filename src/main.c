/*! 
Take a look at hash_map.h/.c for the implementation and hash_map_template.h/.c for templated types
*/

#include "template.h"
#include "hash_map_template.h"

#include <assert.h>

//helper function to create strings, assuming string_buf is null terminated
String CreateString(const char* string_buf)
{
	String string = calloc(1, (strlen(string_buf) + 1) * sizeof(char*));

	//not safe, but we assume that string_buf is null terminated
	strcpy(string, string_buf);

	return string;
}

#define MAX_SIZE 1024

void PrintHelp()
{
	printf("\n%s\n", "[help] - get commands");
	printf("%s\n", "[set] - insert a key/value pair");
	printf("%s\n", "[get] - get value from key");
	printf("%s\n", "[delete] - delete key/value pair");
	printf("%s\n", "[load] - get load of hash map");
	printf("%s\n\n", "[quit] - exit program");
}

void TestHashMap();

void PrintTable(HashMap(String, int) hashmap)
{
	printf("%c", '\n');

	for (size_t i = 0; i < hashmap->size; i++)
	{
		//get the next node in the table
		HashMapNodeStringint node = hashmap->table[i];

		printf("%d", i);

		if (!node)
		{
			printf("%s\n", " -> [NULL]");
			continue;
		}

		//if not, iterate through the chain and remove every node
		while (node != NULL)
		{
			printf(" -> [%s | %d]", node->key, node->value);
			node = node->next;
		}
		printf("%s\n", " -> [NULL] ");
	}
	printf("%c", '\n');
}

int main()
{
	TestHashMap();

	printf("%s\n", "String/int hashtable");
	printf("%s\n", "Enter size of hash table");

	//get user input of hash table
	char input[1024] = { 0 };
	fgets(input, MAX_SIZE, stdin);
	input[strlen(input) - 1] = '\0';
	size_t size = (size_t)strtol(input, NULL, 10);

	HashMap(String, int) hashmap = New(HashMap(String, int), size);

	PrintHelp();

	while (strncmp(input, "quit", 5))
	{
		PrintTable(hashmap);

		fgets(input, MAX_SIZE, stdin);
		input[strlen(input) - 1] = '\0';
		if (!strncmp(input, "set", 4))
		{
			printf("%s\n", "Type in key you wish to insert:");

			char* user_input = calloc(1, sizeof(char*) * MAX_SIZE);

			fgets(user_input, MAX_SIZE, stdin);
			user_input[strlen(user_input) - 1] = '\0';

			printf("\n%s\n", "Type in value you wish to insert:");

			fgets(input, MAX_SIZE, stdin);
			input[strlen(input) - 1] = '\0';
			int num = (int)strtol(input, NULL, 10);

			if (Call(HashMap(String, int), set, hashmap, user_input, num))
			{
				printf("%s\n", "Inserted key/value pair or replaced old key/value pair");
			}
			else
			{
				printf("%s\n", "You have reached the limit in the hashmap");
			}
		}
		else if (!strncmp(input, "get", 4))
		{
			printf("%s\n", "Type in key you wish to find:");

			fgets(input, MAX_SIZE, stdin);
			input[strlen(input) - 1] = '\0';

			int* value = Call(HashMap(String, int), get, hashmap, input);

			if (value)
			{
				printf("Got value: %d\n", *value);
			}
			else
			{
				printf("%s\n", "The key does not exist in hashmap");
			}
		}
		else if (!strncmp(input, "delete", 7))
		{
			printf("%s\n", "Type in key you wish to delete:");

			fgets(input, MAX_SIZE, stdin);
			input[strlen(input) - 1] = '\0';

			if (Call(HashMap(String, int), delete, hashmap, input))
			{
				printf("%s\n", "Deleted the key/pair successfully");
			}
			else
			{
				printf("%s\n", "The key does not exist in hashmap");
			}
		}
		else if (!strncmp(input, "load", 5))
		{
			float load = Call(HashMap(String, int), load, hashmap, input);
			printf("Load: %lf\n", load);
		}
		else if (!strncmp(input, "help", 5))
		{
			PrintHelp();
		}
	}

	Delete(HashMap(String, int), hashmap);
	return 0;
}

void TestSet()
{
	printf("%s\n", "Testing set...");

	//hashmap of 2 keys
	HashMap(String, int) hashmap = New(HashMap(String, int), 2);

	//add one and two key
	String one = CreateString("1");
	String two = CreateString("2");
	assert(Call(HashMap(String, int), set, hashmap, one, 1));
	assert(Call(HashMap(String, int), set, hashmap, two, 2));

	//attempt to add three key (fails)
	String three = CreateString("3");
	assert(!Call(HashMap(String, int), set, hashmap, three, 3));
	free(three);

	//create a new string one2
	String one2 = CreateString("1");

	//replace the original key (one)
	assert(Call(HashMap(String, int), set, hashmap, one2, 1));

	Delete(HashMap(String, int), hashmap);

	printf("%s\n", "Testing set successful");
}

void TestGet()
{
	printf("%s\n", "Testing get...");

	//hashmap of 2 keys
	HashMap(String, int) hashmap = New(HashMap(String, int), 2);

	//add one and two key
	String one = CreateString("1");
	String two = CreateString("2");
	assert(Call(HashMap(String, int), set, hashmap, one, 1));
	assert(Call(HashMap(String, int), set, hashmap, two, 2));

	//we can get two!
	assert(Call(HashMap(String, int), get, hashmap, two));

	//can't get three
	String three = CreateString("3");
	assert(!Call(HashMap(String, int), get, hashmap, three));
	free(three);

	printf("%s\n", "Testing get successful");
}

void TestDelete()
{
	printf("%s\n", "Testing delete...");

	//hashmap of 2 keys
	HashMap(String, int) hashmap = New(HashMap(String, int), 2);

	//add one and two key
	String one = CreateString("1");
	String two = CreateString("2");
	assert(Call(HashMap(String, int), set, hashmap, one, 1));
	assert(Call(HashMap(String, int), set, hashmap, two, 2));

	//we can delete two!
	assert(Call(HashMap(String, int), delete, hashmap, two));

	//can't delete three sine it doesn't exist
	String three = CreateString("3");
	assert(!Call(HashMap(String, int), delete, hashmap, three));
	free(three);

	printf("%s\n", "Testing delete successful");
}

void TestLoad()
{
	printf("%s\n", "Testing load...");

	//hashmap of 2 keys
	HashMap(String, int) hashmap = New(HashMap(String, int), 2);

	//add one and two key
	String one = CreateString("1");
	String two = CreateString("2");

	//load of 0.0f
	assert(abs(Call(HashMap(String, int), delete, hashmap, two)) < 0.005f);

	assert(Call(HashMap(String, int), set, hashmap, one, 1));

	//load of 0.5f
	assert(abs(0.5f -Call(HashMap(String, int), delete, hashmap, two)) < 0.005f);

	assert(Call(HashMap(String, int), set, hashmap, two, 2));

	//we can see that load has a value of 1
	assert(abs(1.0f - Call(HashMap(String, int), delete, hashmap, two)) < 0.005f);


	printf("%s\n", "Testing load successful");
}

void TestHashMap()
{
	TestSet();
	TestGet();
	TestDelete();
	TestLoad();
}