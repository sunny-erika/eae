#pragma once
#include "Position.h"
#include "Board.h"

class Character
	//a character can be at a certain position
	//a character can move from its current position to a new Position - vector distance

{

protected:
	Position position;

public:
	Character();
	Character(Position newPosition);
	~Character();

	void setPosition(Position position);
	Position getPosition();

	void move(Position newPosition);
};

