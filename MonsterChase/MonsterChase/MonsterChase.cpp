// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <conio.h>//for getch()
//Because it is unbuffered, getch() returns each character as soon as the key is pressed
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "Engine.h"
#include "Character.h"
#include "Vector2D.h"
#include "List.h"


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


//Game.cpp
int main()
{
	int numberOfMonsters = 0;

	Vector2D* ptrVector1 = (Vector2D*)malloc(sizeof(Vector2D));//preferred
	ptrVector1->setX(11);

	Vector2D* ptrVector2 = (Vector2D*)malloc(sizeof(int)*2);//that's what new does
	ptrVector2->setX(22);


	std::cout << "Hello World!\n";


	//testing input
	//buffer only on the stack, no malloc needed

	Character player(Vector2D(0,0));
	_LinkNode<Character>* monsterList = (_LinkNode<Character>*)malloc(sizeof(_LinkNode<Character>));

	
	Engine::Init();
	//char* player = {'p', ;
	
	//enter a player
	player.setPtrName(getName("player"));//mem for name reserved in getName() with malloc - free in Character
	//std::cout << player.getPtrName();

	std::cout << "/n Enter the number of monsters: ";
	std::cin >> numberOfMonsters;

	for (int i = 0; i < numberOfMonsters; i++) {
		getName("monster");
	}

	   	 

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
	
	
	char ch1;
	int i = 0;

	while ((ch1 = _getch()) != '\r') {
		i++;//9 chars = 8 iterations
		putchar(ch1);
	}

	std::cout << "iterations: " << i;
	std::cout << "char: " << ch1;

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

