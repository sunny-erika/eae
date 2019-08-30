#pragma once
#include "Player.h"
#include "Position.h"


class Player
{
private:
	Position position;
public:
	Player();
	Player(Position position);
	~Player();

	void setPosition(int x, int y);
	Position getPosition();
};

