// MakeSentenceConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string.h>
using namespace std;

/*
int my_strlen(const char * ptr) {
	int len = 0;
	const char * p = ptr;
	while (*p != '\0') {
		len++;
		p++;
	}
	return len;
}

int my_strlen1(const char ** ptr) {
	int len = 0;
	const char * p = *ptr;
	while (*p != '\0') {
		len++;
		p++;
	}
	return len;
}
*/

/*
int sizeOfArray(const char *array) {//not working with pointer to that array, only directly like in main
	int size = *(&array + 1) - array;
	printf("\nSize: %d", size);

	return size;
}
*/

int calculateArraySize(const char *strings[]) {//array length
	int array_size = 0;

	if (strings != NULL) {

		for (int j = 0; strings[j] != 0; j++) {
			array_size++;
		}
		array_size++; //for null terminator
	}
	//std::cout << "Strings_size=" << array_size << std::endl;
	return array_size;
}


int calculateStringLength(const char *strArray) {
	int length = 0;

	if (strArray == NULL) {
		return 0;
	}
	
	while (*strArray != '\0') {
		length++;
		strArray++;
		
	}
	return length;
}



int calculateStringLengthOfSentence(const char *strings[]) {

	std::cout << "strings_address" << strings << std::endl;

	int array_size = 0;

	array_size = calculateArraySize(strings);
	std::cout << "StringsArray_size=" << array_size << std::endl;
	
	int length = 0;
	
	for (int i = 0; i < array_size; i++) {
		if (strings[i] != 0) {
			std::cout << "String=" << strings[i] << std::endl;
			length += calculateStringLength(strings[i]);
			length += 1;//for space -> calculates 1 as space for dot
			std::cout << "length=" << length << std::endl;
		}
		else {
			length++; //for sentinel 
		}
	}
//	length++; //for dot
	
	return length;
}


void copyString(char *sentence, char *word) {

}


const char* MakeSentence(const char** array) {//TODO changing to parameter without const

	int requiredBytes = calculateStringLengthOfSentence(array);

	std::cout << "\n in MakeSentence requiredBytes should be 16 =" << requiredBytes << std::endl;

	char* sentenceString = (char*)malloc(requiredBytes);

	if (sentenceString == NULL) {
		std::cout << " Could not allocate memory" << std::endl;
		exit(!);
	}



	//now concatinate strings from stringarray
	//TODO


	//int length = my_strlen(*array);
	//int length2 = my_strlen2(array);
	/*

	words = (char*)malloc(length + 1);
	if (words == NULL) {
		printf("No memory\n");
		exit;
	}*/

	//	words = *array;//does not copy content
		//free(array);

	//int array_size = *(&array + 1) - array;

	//printf("\n in MakeSentence array_Size: %d", array_size, "\n");


	//for (int i = 0; i < array_size - 1; i++) {
	for (int i = 0; i < 5 - 1; i++) {
		printf("%s", array[i]);
		if (i == 5 - 2) {
			printf(".");
		}
		else {
			printf(" ");
		}

	}


	//printf("Length: %i\n", length);
	//printf("\n in MakeSentence Length2: %i", length2, "\n");
	//printf("%s", words);
	return *array;
	
}

/*
const char* MakeSentence3(const char* array[]) {//passing now one single string

	//int length = my_strlen(*array);
	int length2 = my_strlen2(array);
	/*

	words = (char*)malloc(length + 1);
	if (words == NULL) {
		printf("No memory\n");
		exit;
	}*/

	//	words = *array;//does not copy content
		//free(array);
/*
	int array_size = 5;

	printf("\n in MakeSentence array_Size: %d", array_size, "\n");


	for (int i = 0; i < array_size - 1; i++) {
		printf("%s", array[i]);
		if (i == array_size - 2) {
			printf(".");
		}
		else {
			printf(" ");
		}

	}


	//printf("Length: %i\n", length);
	printf("\n in MakeSentence Length2: %i", length2, "\n");
	//printf("%s", words);
	return *array;

}
*/

/*
static char* MakeSentenceConst1(const char* type) {

	//char name[255];

	
	//int length = strlen(name);
	int length = my_strlen(type);

	printf("Length: %i\n", length);
	char* word = (char*)malloc(strlen(type) + 1);

	//for (i = 0; s[i] != '\0'; ++i);

	for (int i = 0; i < length; i++) {
		word[i] = type[i];
	}
	word[length] = '\0';//" " for string literals

	return word;
}

*/



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

	/*
	const char * strings2[] = {
	"This",
	"is",
	"a",
	"test",
	NULL
	};
	//sentinel characters

	const char * strings1[] = {
	"This",
	"is",
	"the second",
	"test",
	NULL
	};

	*/
	MakeSentence(strings);

	std::cout << "\n Enter a word =" << std::endl;
	std::cout << "\n Enter the next word (please hit enter, if you don't want to enter another word) " << std::endl;
	//storing each word in an array




	//int length;
	//length = my_strlen(strings[0]);
	//printf("Length: %i\n", length);

	//printf("\nWord: %s", strings[0]);//prints first word
	
	/*char *buffer = (char*)malloc(256);
	if (buffer == NULL) {
		printf("No memory\n");
		return 1;
	}*/

	//printf("\n Enter your sentence: ");



	//fgets(buffer, 256, stdin);//this is a single buffer
	//scanf_s("%s", buffer);
	//length = (my_strlen(buffer));
	//printf("Length: %i\n", length);

	//printf("%s", buffer);
	//MakeSentence(&buffer);
	//printf("%s", MakeSentence(&buffer));


	/*causes memory leak too*/
	//char *mywords = (char*)malloc(256);

	//mywords = MakeSentence(&buffer);
	//mywords = MakeSentence(&strings1);
	//MakeSentenceConst1(*strings1);

	//printf("%s", MakeSentenceConst1(*strings1));
	//printf("%s",mywords);

	//free(mywords);

	/*

	int array_size1 = *(&mywords + 1) - mywords;//causes uninitialized
	//printf("\nSize: %d", array_size);
	
	for (int i = 0; i < array_size1 - 1; i++) {
		printf("%s", mywords[i]);
		if (i == array_size1 - 2) {
			printf(".");
		}
		else {
			printf(" ");
		}

	}
	*/


	
	int array_size = *(&strings + 1) - strings;
	//char** array = (char**) strings;

	//int array_size1 = *(&array + 1) - array;
		


	//printf("\nSize: %d", array_size);
	printf("\n in main array_size: %i", array_size, "\n");//5
	printf( "\n");

	//printf("\n in main array_size1: %i", array_size1, "\n");//5
	printf("\n");


	for (int i = 0; i < array_size - 1; i++) {
		printf("%s", strings[i]);
		if (i == array_size - 2) {
			printf(".");
		}
		else {
			printf(" ");
		}

	}
	
	//free(buffer);

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
