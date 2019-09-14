#pragma once
#include "Position.h"
#include "Board.h"
#include <stdlib.h>

class Character
	//a character can have a position
	//a character can mark its position with a specific letter;
	//a character can move from its current position to a new Position within the matrix (Board)
	//a character can print its position

{

private:
	Position position;
	//char positionMark;
	char * ptrName;

public:
	Character();
	Character(Position newPosition);
	~Character();

	//getter setter
	void setPosition(Position position);
	Position getPosition();

	void setPtrName( char * ptrName);
	char* getPtrName();

	

	//bool move(Position newPosition, Board board);

	Position printPosition(Board board) {

	}

	void markPositionOnBoard() {
		
	}
};

