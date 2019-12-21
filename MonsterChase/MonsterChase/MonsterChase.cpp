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
#include "Point2D.h"
#include "List.h"



struct ListNode
{
	Character* character;
	int testVal;
	ListNode *next;//recursive
};

int gotName = 0;
//Iterating over the list
void print_list(ListNode * head) {
	ListNode * current = head;//current pointer that will keep track of the node we are currently printing
	while (current != NULL) {
		//printf("%d\n", current->testVal);
		if (current->character != NULL) {
			Point2D vectorTmp = current->character->getPosition();

			//printf("position of monster: [%d, %d]\n", vectorTmp.getX(), vectorTmp.getY());
			std::cout << "\n position of monster " << current->character->getPtrName() << ": is [" << vectorTmp.getX() << "," <<vectorTmp.getY() << "]";
			//std::cout << "position of monster: " << current->character->getPtrName();
		}
		//std::cout << current->character.getPtrName();
		//std::cout << current->character->getPtrName();
		current = current->next;//setting the current pointer to the next node until we've reached the end of the list (the next node is NULL
	}
}

void moveMonsters(ListNode * head, Point2D vector) {
	ListNode * current = head;
	
	while (current != NULL) {
	
		if (current->character != NULL) {
			current->character->move(vector);
			
		}

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
void push(ListNode ** head, char* name, Point2D* vector) {//Since we use a function to do this operation, we want to be able to modify the head variable
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

void push(ListNode ** head, char* name, Point2D vector) {//Since we use a function to do this operation, we want to be able to modify the head variable
	//To do this, we must pass a pointer to the pointer variable,so we will be able to modify the pointer itself
	
	ListNode * new_node = (ListNode*)malloc(sizeof(ListNode));
	//ListNode * new_node = nullptr;
	//new_node = (ListNode*)malloc(sizeof(ListNode));
	if (new_node != NULL) {
		//printf("No memory\n");
		//exit;
		new_node->character = (Character*)malloc(sizeof(Character));
	new_node->character->setPosition(vector);
	new_node->character->setPtrName(name);
	new_node->next = *head;
	*head = new_node;
	}
	
	//new_node->character->printPosition();

	//malloc for str
	//new_node->character = nullptr;
	//new_node->character = (Character*)malloc(sizeof(Character));
	
	//new_node->character.setPtrName(name);
	//new_node->character.setPosition();
	
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
	gotName++;
	//int c, i = 0;
	//char name[255];
	const size_t lenName = 255;
	char name[lenName];
	//char *p;
	char *error = (char*)malloc(2);
	//std::cout << "\nEnter a name for the " << type << " : ";//player or monster
	(void)getchar();
	printf("\n Enter a name for the %s: ", type);
	/*
	fgets(name, sizeof name, stdin);
	if ((p = strchr(name, '\n')) != NULL)
		*p = '\0';
	printf("You typed \"%s\"\n", name);
	*/
															//if (gotName >= 1) {
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//}
	//std::cin.ignore(200, '\n');
	//scanf_s("%s", name);
	//scanf_s("%[^\n]s", name);
	//fgets(name, 100, stdin);
	//sscanf_s("%[^\n]s", name);
	//std::cin >> name;//abc = 3 letters -> +1 for delimiter
	
	//getchar();
	/*
	for (int i = 0; i < 256; i++)
	{
		char ch = getchar();
		//while (ch != '\n' && ch != EOF) {
		//while (ch != '\n') {
			while (ch != EOF) {
			name[i] = ch;
			i++;
			ch = getchar();
		}
		name[i] = '\0';
	}
	*/
	//printf("Entered string is: %s", name);
	std::cin.getline(name, sizeof(name)); 
	//fgets(name, 20, stdin);
//	scanf_s("%[^\n]%*c", name);
	//gets_s(name, 255);

	int length = (int) strlen(name);
	char* playerName = (char*)malloc(strlen(name) + 1);

	if (playerName != NULL) {
		/*
	for (int i = 0; i < length; i++) {
		playerName[i] = name[i];
	}
	playerName[length] = '\0';//" " for string literals 
		*/
		int index = 0;

		while (name[index] != '\0') {
			playerName[index] = name[index];
			index++;
		}
		playerName[index] = '\0';

    return playerName;

	}
	else {
		
		if (error != NULL) {
		error[1] = 1;
		exit(1);
		return error;
		
		
		}
		
	}

	
	/*
	do
	{
	c = getchar();
	name[i] = c;
	i++;
	} while (c != '\0');

	*/
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
		srand((int)time(NULL)); //seeding for the first time only!
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}

Point2D createRandomVector(int min, int max) {
	return Point2D((float)random(0, 10), (float)random(0, 10));
}
void Point2D_UnitTest()
{
	Point2D P1(0.0f, 0.0f);
	Point2D P2(0.0f, 0.0f);

	Point2D P3 = P1 + P2;
	P3 = P1 - P2;

	Point2D P4 = P1 * 0.5f;

	Point2D P5 = P1 / 2.0f;

	Point2D P6 = -P4;

	P6 *= 2.0f;
	P5 /= 4.0f;

	P2 += P1;
	P3 -= P1;

	Point2D P7 = (((P1 + P2) * 2.0f) - -P3) / 2.0f;

	bool bArentEqual = P6 != P4;
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
	srand((int)time(NULL));
	/* generate secret number between 1 and 10: */
	lowerRange = rand() % 10 + 1;
	upperRange = rand() % 10 + 1;
	//std::cout << "Hello World!\n";
	//testing input
	//buffer only on the stack, no malloc needed

	//linked list nodes are dynamically allocated
	//advantages over vectors: insertion/deletion speed
	//vector req all other elements to be moved
	
	//Engine::Init();
	//char* player = {'p', ;
	

	std::cout << "Enter the number of monsters: ";
	std::cin >> numberOfMonsters;
	/*
	if (numberOfMonsters == 0)
		printf("Bad input. Please enter an integer greater than 0.");
		*/

	//_LinkNode<Character>* ptr_monsterList = NULL;
	//_LinkNode<Character>* ptr_monsterList = (_LinkNode<Character>*)malloc(sizeof(_LinkNode<Character>));
	
	/*
	Point2D* ptrVector1 = (Point2D*)malloc(sizeof(Point2D));//preferred
	ptrVector1->setX(11);
	ptrVector1->setY(11);

	Point2D* ptrVector2 = (Point2D*)malloc(sizeof(int) * 2);//that's what new does
	ptrVector2->setX(22);

	Point2D vector3(5, 6);
	Point2D vector4(7, 8);
	//Point2D randomVector(lowerRange, upperRange);
	//Point2D randomVector(rand() % 10 + 1 , rand() % 10 + 1);
	*/
	//Character player(Point2D(0, 0));
	Character player;
	player.setPosition(Point2D(0, 0));

	//Character player(ptrVector1);
	//enter a player
	//char* buffer = getName("player");
	//player.setPtrName(buffer);
	//std::cout << "\nBelow you will be asked to enter names: ";
		
	player.setPtrName(getName("player"));//mem for name reserved in getName() with malloc - free in Character
	/*
	const size_t	lenInput = 128;
	char			Input[lenInput];

	while (1)
	{
		printf("Enter a name for the player: ");
		gets_s(Input, lenInput);

		if (strlen(Input))
		{
			player.setPtrName(Input);
			std::cout << player.getPtrName();
			break;
		}
		else
		{

			printf("Empty name not allowed.");
		}
	}
	*/
	/*
	if (player.getPtrName() == NULL) {
		char name[255];
		std::cin.getline(name, 255);
		player.setPtrName(name);
	}
	*/
	//player.setPtrName(getPlayerName());
	std::cout << "\nThe Player's name is " << player.getPtrName();//player or monster
	

	//std::cout << player.getPtrName();
	
	ListNode *ptrHead = nullptr;
	//ptrHead = (ListNode*) malloc(sizeof(ListNode));
	//if (ptrHead == NULL) {//if ptrHead is null then memory not sufficient
	//	return 1;
	//}
	////ptrHead->testVal = 0;
	//ptrHead->next = nullptr;
	
	for (int i = 0; i < numberOfMonsters; i++) {
		char* name = getName("monster");
		//char* name = getMonsterName();

		//push(&ptrHead, 2);
		//push(&ptrHead, name, ptrector2);
		//push(&ptrHead, name, vector3);
		//push(&ptrHead, name, randomVector);
		push(&ptrHead, name, createRandomVector(rand() % 10 + 1, rand() % 10 + 1));
		std::cout << "\nThe name of monster number "<<i+1 << " is " << name;
		//push(&ptrHead, name, Point2D(0, 1));//for testing		
	}
	player.printPosition();
	print_list(ptrHead);
	//player.printPosition();
	//player.move(Point2D(0, 1));
	//player.printPosition();
	//remove_by_index(&ptrHead, 1);//2nd monster //could be randomly range 0 - numberOfMonsters-1

	
	
	bool running = true;
	while (running) 
	{
		int monsterindex = 1;
		std::cout << "\n Press A to move left, D to move right, W to move up, S to move down, M to add a monster, R to remove a monster or Q to quit";
		//std::cin >> input;
		char input = _getch();
		////bool valid = true;
		//user input
		switch (input)
		{
		case 'a':
		case 'A':
			player.move(Point2D(-1, 0));
			player.printPosition();
			moveMonsters(ptrHead, Point2D(-1, 0));

			print_list(ptrHead);//position of monster 
			break;
		case 'd':
		case 'D':
			player.move(Point2D(1, 0));
			player.printPosition();
			moveMonsters(ptrHead, Point2D(1, 0));
			print_list(ptrHead);

			break;
		case 'w':
		case 'W':
			player.move(Point2D(0, 1));
			player.printPosition();
			moveMonsters(ptrHead, Point2D(0, 1));
			print_list(ptrHead);
			break;
		case 's':
		case 'S':
			player.move(Point2D(0, -1));
			player.printPosition();
			moveMonsters(ptrHead, Point2D(0, -1));
			print_list(ptrHead);
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

		case 'r':
		case 'R':
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

	//Point2D vector1 = new Point2D v1(1,2);
	//Engine::Point2D vector1(1, 2);
	//Point2D vector1 = new Point2D (1, 2);//new nur wenn man ptr hat
	Point2D vector1(1, 2);
	Point2D vector2(3, 4);

	//std::cout << "Vector1 = " << vector1;
	//std::cout << "Vector2 = " << vector2;

	//std::cout << "Vector1 + Vector2 = " << (vector1 + vector2);

	//

#ifdef _DEBUG	
	_CrtDumpMemoryLeaks();
#endif // _DEBUG	


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

