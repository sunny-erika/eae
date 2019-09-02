#pragma once
#include "Player.h"
#include "Position.h"
#include "Character.h"


class Player: public Character
{
private:
	//Position position;
public:
	Player();
	Player(Position position);
	~Player();

	//void setPosition(int x, int y);
	//Position getPosition();
};

