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
	free (ptrName);//delete() if new is used - distinguish arrays/ptr
}

/*
bool Character::move(Position position) {

	this->position = position;//TODO if it is within the board
	return true;
}
*/

//getters, setters

void Character::setPosition(Vector2D position) {
	Character::position = position;
}

Vector2D Character::getPosition() {
	return Character::position;
}

void Character::setPtrName(char *ptrName) {
	Character::ptrName = ptrName;
}

char * Character::getPtrName() {
	return Character::ptrName;
}
