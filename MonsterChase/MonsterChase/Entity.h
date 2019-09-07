#pragma once
//#include "Position.h"
//#include "Board.h"

class Entity
	//a character can have a position
	//a character can mark its position with a specific letter;
	//a character can move from its current position to a new Position within the matrix (Board)
	//a character can print its position

{

protected:
	//Position position;
	char positionMark;

public:
	Entity();
	//Entity(Position newPosition);
	//~Entity();

	//void setPosition(Position position);
	//Position getPosition();

	//bool move(Position newPosition, Board board);

	//Position printPosition(Board board) {

	//}

	void markPositionOnBoard() {
		
	}
};

