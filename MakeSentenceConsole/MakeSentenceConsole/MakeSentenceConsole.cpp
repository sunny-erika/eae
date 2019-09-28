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

	//printf("\nWord: %s", strings[0]);

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
