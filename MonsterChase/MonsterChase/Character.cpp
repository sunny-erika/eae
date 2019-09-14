#include "Character.h"


Character::Character()
{
}

Character::Character(Position newPosition)
{
}


Character::~Character()
{
	free (ptrName);
}

/*
bool Character::move(Position position) {

	this->position = position;//TODO if it is within the board
	return true;
}
*/

//getters, setters

void Character::setPosition(Position position) {
	Character::position = position;
}

Position Character::getPosition() {
	return Character::position;
}

void Character::setPtrName(char *ptrName) {
	Character::ptrName = ptrName;
}

char * Character::getPtrName() {
	return Character::ptrName;
}
