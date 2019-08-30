// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>


int main()
{
    std::cout << "Hello World!\n"; 
}


class Position {
	int x, y;

public:
	Position(int x, int y);
	void setX(int x);
	int getX();

};

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




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

