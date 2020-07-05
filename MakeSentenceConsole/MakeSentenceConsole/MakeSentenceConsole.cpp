// MakeSentenceConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string.h>

int my_strlen(const char * ptr) {
	int len = 0;
	const char * p = ptr;
	while (*p != '\0') {
		len++;
		p++;
	}
	return len;
}

int sizeOfArray(const char *array) {
	int size = *(&array + 1) - array;
	printf("\nSize: %d", size);

	return size;
}

static char* MakeSentenceConst(const char* type) {

	char name[255];

	int length = strlen(name);
	char* word = (char*)malloc(strlen(name) + 1);

	//for (i = 0; s[i] != '\0'; ++i);

	for (int i = 0; i < length; i++) {
		word[i] = name[i];
	}
	word[length] = '\0';//" " for string literals

	return word;
}

char* MakeSentence(char** array) {
	
	int length = my_strlen(*array);
	char* words = (char*)malloc(length + 1);
	if (words == NULL) {
		printf("No memory\n");
		exit;
	}

	words = *array;
	//free(array);
	printf("Length: %i\n", length);
	//printf("%s", words);
	return words;
}



int main()
{
    std::cout << "Hello World!\n"; 

	const char * strings[] = {
		"This",
		"is",
		"a",
		"test",
		NULL
	};
	//sentinel characters

	int length;
	length = my_strlen(strings[0]);
	printf("Length: %i\n", length);

	//printf("\nWord: %s", strings[0]);//prints first word
	
	char *buffer = (char*)malloc(256);
	if (buffer == NULL) {
		printf("No memory\n");
		return 1;
	}

	printf("Enter your sentence: ");
	fgets(buffer, 1000, stdin);
	//scanf_s("%s", buffer);
	//length = (my_strlen(buffer));
	//printf("Length: %i\n", length);

	//printf("%s", buffer);
	//MakeSentence(&buffer);
	printf("%s", MakeSentence(&buffer));


	int array_size = *(&strings + 1) - strings;
	//printf("\nSize: %d", array_size);

	for (int i = 0; i < array_size - 1; i++) {
		printf("%s", strings[i]);
		if (i == array_size - 2) {
			printf(".");
		}
		else {
			printf(" ");
		}

	}

	free(buffer);

	getchar();

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
