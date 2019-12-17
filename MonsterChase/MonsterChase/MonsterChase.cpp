//01/ MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>      
#include <conio.h>//for getch()
//Because it is unbuffered, getch() returns each character as soon as the key is pressed


#include "Engine.h"
#include "Character.h"
#include "Vector2D.h"
#include "List.h"


struct ListNode
{
	Character* character;
	int testVal;
	ListNode *next;//recursive
};

//Iterating over the list
void print_list(ListNode * head) {
	ListNode * current = head;//current pointer that will keep track of the node we are currently printing
	while (current != NULL) {
		//printf("%d\n", current->testVal);
		if (current->character != NULL) {
			Vector2D vectorTmp = current->character->getPosition();

			printf("position: [%d, %d]\n", vectorTmp.getX(), vectorTmp.getY());
		}
		//std::cout << current->character.getPtrName();
		//std::cout << current->character->getPtrName();
		current = current->next;//setting the current pointer to the next node until we've reached the end of the list (the next node is NULL
	}
}

//adding to the beginning of the list - push (removing: pop)
/*
	Create a new item and set its value
	Link the new item to point to the head of the list
	Set the head of the list to be our new item
*/

/*
void push(ListNode ** head, int test) {//Since we use a function to do this operation, we want to be able to modify the head variable
	//To do this, we must pass a pointer to the pointer variable,so we will be able to modify the pointer itself
	ListNode * new_node = nullptr;
	new_node = (ListNode*)malloc(sizeof(ListNode));
		
	new_node->testVal = test;
	new_node->next = *head;
	*head = new_node;
}
*/
/*
void push(ListNode ** head, char* name) {//Since we use a function to do this operation, we want to be able to modify the head variable
	//To do this, we must pass a pointer to the pointer variable,so we will be able to modify the pointer itself
	ListNode * new_node = nullptr;
	new_node = (ListNode*)malloc(sizeof(ListNode));

	

	//malloc for str
	//new_node->character = nullptr;
	//new_node->character = (Character*)malloc(sizeof(Character));
	//new_node->character->setPtrName(name);
	//new_node->character.setPtrName(name);
	//new_node->character.setPosition();
	new_node->next = *head;
	*head = new_node;
}*/

/*
void push(ListNode ** head, char* name, Vector2D* vector) {//Since we use a function to do this operation, we want to be able to modify the head variable
	//To do this, we must pass a pointer to the pointer variable,so we will be able to modify the pointer itself
	ListNode * new_node = nullptr;
	new_node = (ListNode*)malloc(sizeof(ListNode));
	new_node->character = (Character*)malloc(sizeof(Character));
	new_node->character->setPosition(vector);

	//malloc for str
	//new_node->character = nullptr;
	//new_node->character = (Character*)malloc(sizeof(Character));
	//new_node->character->setPtrName(name);
	//new_node->character.setPtrName(name);
	//new_node->character.setPosition();
	new_node->next = *head;
	*head = new_node;
}
*/

void push(ListNode ** head, char* name, Vector2D vector) {//Since we use a function to do this operation, we want to be able to modify the head variable
	//To do this, we must pass a pointer to the pointer variable,so we will be able to modify the pointer itself
	ListNode * new_node = nullptr;
	new_node = (ListNode*)malloc(sizeof(ListNode));
	new_node->character = (Character*)malloc(sizeof(Character));
	new_node->character->setPosition(vector);
	//new_node->character->printPosition();

	//malloc for str
	//new_node->character = nullptr;
	//new_node->character = (Character*)malloc(sizeof(Character));
	//new_node->character->setPtrName(name);
	//new_node->character.setPtrName(name);
	//new_node->character.setPosition();
	new_node->next = *head;
	*head = new_node;
}

//removing the first
/*
Take the next item that the head points to and save it
Free the head item
Set the head to be the next item that we've stored on the side
*/
int pop(ListNode ** head) {
	int retval = -1;
	ListNode * next_node = NULL;

	if (*head == NULL) {
		return -1;
	}

	next_node = (*head)->next;
	retval = (*head)->testVal;
	free(*head);
	*head = next_node;

	return retval;
}


//removing last item
/*
	Iterate to the node before the node we wish to delete
	Save the node we wish to delete in a temporary pointer
	Set the previous node's next pointer to point to the node after the node we wish to delete
	Delete the node using the temporary pointer
*/

int remove_last(ListNode * head) {
	int retval = 0;
	/* if there is only one item in the list, remove it */
	if (head->next == NULL) {
		retval = head->testVal;
		free(head);
		return retval;
	}

	/* get to the second to last node in the list */
	ListNode * current = head;
	while (current->next->next != NULL) {
		current = current->next;
	}

	/* now current points to the second to last item of the list, so let's remove current->next */
	retval = current->next->testVal;
	free(current->next);
	current->next = NULL;
	return retval;
}

//remove specific
//looking ahead to find out if we've reached the node before the item we wish to remove. This is because we need to change the location to where the previous node points to as well
int remove_by_index(ListNode ** head, int n) {
	int i = 0;
	int retval = -1;
	ListNode * current = *head;
	ListNode * temp_node = NULL;

	if (n == 0) {
		return pop(head);
	}

	for (i = 0; i < n - 1; i++) {
		if (current->next == NULL) {
			return -1;
		}
		current = current->next;
	}

	temp_node = current->next;
	retval = temp_node->testVal;
	current->next = temp_node->next;
	free(temp_node);

	return retval;

}


static char* getName(const char* type) {

	char name[255];
	std::cout << "Enter a name for the " << type << " : ";//player or monster

	std::cin >> name;//abc = 3 letters -> +1 for delimiter
	int length = strlen(name);
	char* playerName = (char*)malloc(strlen(name) + 1);

	for (int i = 0; i < length; i++) {
		playerName[i] = name[i];
	}
	playerName[length] = '\0';//" " for string literals 
		
    return playerName;
}

/*
void removeOnCollision(ListNode *head, Character player) {
	//iterate thru list
	ListNode * current = head;//current pointer that will keep track of the node we are currently printing
	while (current != NULL) {
		int index = 0;
		if (current->character->getPosition() == player.getPosition()) {
			remove_by_index(&head, index);
		}
		
		current = current->next;//setting the current pointer to the next node until we've reached the end of the list (the next node is NULL
		index++;
	}
}
*/

int random(int min, int max) //range : [min, max)
{
	static bool first = true;
	if (first)
	{
		srand(time(NULL)); //seeding for the first time only!
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}

Vector2D createRandomVector(int min, int max) {
	return Vector2D(random(0, 10), random(0, 10));
}

//Game.cpp
int main()
{
	int numberOfMonsters = 0;
	//matrix size 10x10
	int dimension = 100;
	int lowerRange = 0;
	int upperRange = 0;

	/* initialize random seed: */
	srand(time(NULL));
	/* generate secret number between 1 and 10: */
	lowerRange = rand() % 10 + 1;
	upperRange = rand() % 10 + 1;
	//std::cout << "Hello World!\n";
	//testing input
	//buffer only on the stack, no malloc needed

	//linked list nodes are dynamically allocated
	//advantages over vectors: insertion/deletion speed
	//vector req all other elements to be moved
	
	Engine::Init();
	//char* player = {'p', ;
	//std::cout << player.getPtrName();

	std::cout << "Enter the number of monsters: ";
	std::cin >> numberOfMonsters;

	//_LinkNode<Character>* ptr_monsterList = NULL;
	//_LinkNode<Character>* ptr_monsterList = (_LinkNode<Character>*)malloc(sizeof(_LinkNode<Character>));
	
	Vector2D* ptrVector1 = (Vector2D*)malloc(sizeof(Vector2D));//preferred
	ptrVector1->setX(11);
	ptrVector1->setY(11);

	Vector2D* ptrVector2 = (Vector2D*)malloc(sizeof(int) * 2);//that's what new does
	ptrVector2->setX(22);

	Vector2D vector3(5, 6);
	Vector2D vector4(7, 8);
	//Vector2D randomVector(lowerRange, upperRange);
	//Vector2D randomVector(rand() % 10 + 1 , rand() % 10 + 1);
	
	Character player(Vector2D(0, 0));
	//Character player(ptrVector1);
	//enter a player
	player.setPtrName(getName("player"));//mem for name reserved in getName() with malloc - free in Character

	
	ListNode *ptrHead = nullptr;
	//ptrHead = (ListNode*) malloc(sizeof(ListNode));
	//if (ptrHead == NULL) {//if ptrHead is null then memory not sufficient
	//	return 1;
	//}
	////ptrHead->testVal = 0;
	//ptrHead->next = nullptr;
	
	for (int i = 0; i < numberOfMonsters; i++) {
		char* name = getName("monster");
		//push(&ptrHead, 2);
		//push(&ptrHead, name, ptrector2);
		//push(&ptrHead, name, vector3);
		//push(&ptrHead, name, randomVector);
		push(&ptrHead, name, createRandomVector(rand() % 10 + 1, rand() % 10 + 1));
		//push(&ptrHead, name, Vector2D(0, 1));//for testing		
	}
	print_list(ptrHead);
	//player.printPosition();
	//player.move(Vector2D(0, 1));
	//player.printPosition();
	//remove_by_index(&ptrHead, 1);//2nd monster //could be randomly range 0 - numberOfMonsters-1

	
	bool running = true;
	while (running) 
	{
		int monsterindex = 1;
		std::cout << "Press A to move left, D to move right, W to move up, S to move down or Q to quit";
		//std::cin >> input;
		char input = _getch();
		////bool valid = true;
		//user input
		switch (input)
		{
		case 'a':
		case 'A':
			player.move(Vector2D(-1, 0));
			break;
		case 'd':
		case 'D':
			player.move(Vector2D(1, 0));
			break;
		case 'w':
		case 'W':
			player.move(Vector2D(0, 1));
			break;
		case 's':
		case 'S':
			player.move(Vector2D(0, -1));
			break;
		case 'q':
		case 'Q':
			running = false;
			break;
		case 'm':
		case 'M':
			//add monster

			//char * monsterName;
			//monsterName = getName("monster");
		{
			char* monsterName = getName("monster");
			/*
			char monsterName[255];
			std::cout << "Enter a name for the monster " << " : ";//player or monster
			std::cin >> monsterName;
			*/
			push(&ptrHead, monsterName, createRandomVector(rand() % 10 + 1, rand() % 10 + 1));
			print_list(ptrHead);

			break;
		}

		case 'l':
			//add monster

			//char * monsterName;
			//monsterName = getName("monster");
		{
			//* monsterName = getName("monster");
			/*
			char monsterName[255];
			std::cout << "Enter a name for the monster " << " : ";//player or monster
			std::cin >> monsterName;
			*/
			//push(&ptrHead, monsterName, createRandomVector(rand() % 10 + 1, rand() % 10 + 1));
			
			remove_by_index(&ptrHead, 1);
				print_list(ptrHead);

			break;
		}

		default:
			printf("Unknown input.\n");
			//valid = false;
			break;
		}

		/*
		if (valid)
			break;
		*/
	}


	/*
	struct _LinkNode<Character>* ptr_monsterList = nullptr;//head of the list
	ptr_monsterList = (_LinkNode<Character>*)malloc(sizeof(_LinkNode<Character>));

	if (ptr_monsterList == NULL) {//if ptr_monsterList is null then memory not sufficient
		return 1;
	}

	for (int i = 0; i < numberOfMonsters; i++) {
		getName("monster");
				
		if (ptr_monsterList == NULL) {//if ptr_monsterList is null then memory not sufficient
			return 1;
		}

		ptr_monsterList->pNext = nullptr;


	}
	*/


	/*
	int n, m;

	std::cout << "Enter No. of rows: ";
	std::cin >> n;
	std::cout << "Enter No. of columns: ";
	std::cin >> m;

	//enter a name
	std::cout << "Enter a name for the player: ";
	//using getch()
	char ch;
	char ch_monster;

	ch = _getch();

	std::cout << "Name: " << ch;

	std::cout << "Enter a name for the monster: ";
	ch_monster = _getch();
	std::cout << "Name: " << ch_monster;
	/*
	std::cout << "Enter a name for the monster: ";

	while ((ch = _getch()) != '\r')

		putchar(ch);
	std::cout << "Name: " << ch;//output is 13
	*/

	//count characters +1 - size of char
	
	
	
	/*
	while ((ch1 = _getch()) != '\r') {
		i++;//9 chars = 8 iterations
		putchar(ch1);
	}
	*/

	//std::cout << "iterations: " << i;
	//std::cout << "char: " << ch1;

	//Vector2D vector1 = new Vector2D v1(1,2);
	//Engine::Vector2D vector1(1, 2);
	//Vector2D vector1 = new Vector2D (1, 2);//new nur wenn man ptr hat
	Vector2D vector1(1, 2);
	Vector2D vector2(3, 4);

	//std::cout << "Vector1 = " << vector1;
	//std::cout << "Vector2 = " << vector2;

	//std::cout << "Vector1 + Vector2 = " << (vector1 + vector2);

	//

}

/*

//Position
class Position {
	int x, y;

public:
	Position();
	Position(int x, int y);
	void setX(int x);
	int getX();

};

Position::Position() {
}

Position::Position(int x, int y) {
	Position::x = x;
	Position::y = y;
}

void Position::setX(int x) {
	Position::x = x;
}

int Position::getX() {
	return Position::y;
}

*/

/*

//Player
class Player {
	Position position;

public:
	Player();
	Player(Position position);
	void setPosition(int x, int y);
	Position getPosition();

};

*/

/*

Player::Player() {
	
}
Player::Player(Position position) {
	Player::position = position;
}

void Player::setPosition(int x, int y) {
	Player::position.setX(x);
	
}

Position Player::getPosition() {
	return position;

}
*/



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

