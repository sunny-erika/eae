#pragma once
#include "Vector2D.h"


class Character
{

private:
	Vector2D position;

public:
	Character();
	Character(Vector2D newPosition);
	~Character();

	bool move(Vector2D position);

	//
	void setPosition(Vector2D position);
	Vector2D getPosition();
};

