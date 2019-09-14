#pragma once
#include "Position.h"

class Position
{
private:
	int x, y;

public:
	
	Position();
	Position(int x, int y);
	~Position();

	void setX(int x);
	int getX();

	void setY(int y);
	int getY();
};
	

