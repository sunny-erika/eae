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

bool Character::move(Position position, Board board) {

	this->position = position;//TODO if it is within the board
	return true;
}

//getters, setters

void Character::setPosition(Position position) {
	Character::position = position;
}

Position Character::getPosition() {
	return Character::position;
}
