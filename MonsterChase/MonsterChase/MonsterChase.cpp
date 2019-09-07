// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <conio.h>//for getch()
//Because it is unbuffered, getch() returns each character as soon as the key is pressed
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

//including classes
//#include "Position.h"
#include "Player.h"
#include "Monster.h"
//#include "Board.h"

#include "Entity.h"


int main()
{
    std::cout << "Hello World!\n"; 
	
	//Player player;
	//Player player2;
	//Position position = new Position(3, 4);
	//Position position;
	//position.setX (3);
	//position.setY (4);

	////Position position2(5, 6);

	////player.setPosition(1, 2);
	//player.setPosition(position);
	//player2.setPosition(position2);

	//
	//std::cout << "position " << player.getPosition().getX();
	//std::cout << "position " << player2.getPosition().getX();

	//testing input

	//Engine::Init();

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
	int i=0;

	while ((ch1 = _getch()) != '\r') {
		i++;//9 chars = 8 iterations
		putchar(ch1);
	}

	std::cout << "iterations: " << i;
	std::cout << "char: " << ch1;
	


	   
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

