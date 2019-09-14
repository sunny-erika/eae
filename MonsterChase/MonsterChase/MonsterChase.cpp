// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <conio.h>//for getch()
//Because it is unbuffered, getch() returns each character as soon as the key is pressed
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

//including classes
#include "Position.h"
#include "Character.h"
#include "Board.h"

/*
typedef struct userInput {
	int numberOfMonsters;
	char * ptrPlayerName;
}USERINPUT;
*/

struct UserInput {
	int numberOfMonsters;
	char * ptrPlayerName;
};

UserInput *ptr_userInput;

void start();
void getInput(UserInput * ptr_userInput);


int main()
{

	start();
	free(ptr_userInput);

	   
}

void start() {

	ptr_userInput = new UserInput;
	getInput(ptr_userInput);

	std::cout << "Hello World!\n";

	//Character player;
	//Character monsterArray;
	

	Position position;
	position.setX(3);
	position.setY(4);

	Position position2(5, 6);

	//player.setPosition(position);
	   
	//std::cout << "position " << player.getPosition().getX();
	//std::cout << "position " << player2.getPosition().getX();

	//testing input
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

	char ch1;
	int i = 0;

	while ((ch1 = _getch()) != '\r') {
		i++;//9 chars = 8 iterations
		putchar(ch1);
	}

	std::cout << "iterations: " << i;
	std::cout << "char: " << ch1;


}



void getInput(UserInput *ptr_userInput) {

	//cout << "How many monsters to start (max 5): " << index.name << '\n';
	std::cout << "How many monsters to start(max 5) :" ;
	std::cin >> ptr_userInput->numberOfMonsters;
	std::cout << "\nnumber of monsters :" << ptr_userInput->numberOfMonsters << '\n';
	_getch(); //keeps it open



}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

