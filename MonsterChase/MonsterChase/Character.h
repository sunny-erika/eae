#pragma once

#include <stdlib.h>
#include <Point2D.h>


class Character
	//a character can have a position
	//a character can mark its position with a specific letter;
	//a character can move from its current position to a new Position within the matrix (Board)
	//a character can print its position

{

private:
	Point2D position;
	//char positionMark;
	char * ptrName;

public:
	Character();
	//Character(Point2D newPosition);
	~Character();

	//getter setter
	void setPosition(Point2D position);
	Point2D getPosition();

	void setPtrName( char * ptrName);
	char* getPtrName();
	void printName(char * ptrName); 

	

	//bool move(Position newPosition, Board board);

	void printPosition();
	void move(Point2D);
};

