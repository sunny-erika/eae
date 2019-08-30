#pragma once
class Player
{
	Position position;
public:
	Player();
	Player(Position position);
	~Player();

	void setPosition(int x, int y);
	Position getPosition();
};

