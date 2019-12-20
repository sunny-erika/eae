#include "Character.h"
#include <cstdio>



Character::Character()
{
}

Character::Character(Vector2D newPosition)
{
	Character::position = newPosition;
	//this->position = newPosition;
	//Character::position(newPosition.getX(), newPosition.getY());
}


Character::~Character()
{
	//free (ptrName);//delete() if new is used - distinguish arrays/ptr
	//free (position);
}

/*
bool Character::move(Position position) {

	this->position = position;//TODO if it is within the board
	return true;
}
*/

void Character::printPosition() {
	printf("\nposition of player: [%d, %d]\n", position.getX(), position.getY());
	
}

void Character::move(Vector2D moveVector) {
	position += moveVector;
	//printf("\nNew position of player: [%d, %d]\n", position.getX(), position.getY());

}

void Character::printName(char * ptrName) {
	
}


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
