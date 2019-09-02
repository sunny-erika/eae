#include "Character.h"


Character::Character()
{
}

Character::Character(Position newPosition)
{
}


Character::~Character()
{
}

void Character::move(Position position) {

	this->position = position;
}

//getters, setters

void Character::setPosition(Position position) {
	Character::position = position;
}

Position Character::getPosition() {
	return Character::position;
}
