#include "Character.h"



Character::Character()
{
}

Character::Character(Vector2D newPosition)
{
	this->position = newPosition;
}


Character::~Character()
{
}

bool Character::move(Vector2D position) {

	this->position = position;//TODO if it is within the board
	return true;
}

//getters, setters

void Character::setPosition(Vector2D position) {
	Character::position = position;
}

Vector2D Character::getPosition() {
	return Character::position;
}