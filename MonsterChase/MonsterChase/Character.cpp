#include "Character.h"
#include <cstdio>



Character::Character()
{
}

/*
Character::Character(Point2D newPosition)
{
	Character::position = newPosition;
	//this->position = newPosition;
	//Character::position(newPosition.getX(), newPosition.getY());
}*/


Character::~Character()
{
	free (ptrName);//delete() if new is used - distinguish arrays/ptr
	Character::position.setX(0.0f);
	Character::position.setY(0.0f);
}

/*
bool Character::move(Position position) {

	this->position = position;//TODO if it is within the board
	return true;
}
*/

void Character::printPosition() {
	printf("\nposition of player: [%d, %d]\n", (int)position.getX(), (int)position.getY());
	
}

void Character::move(Point2D moveVector) {
	position += moveVector;
	//printf("\nNew position of player: [%d, %d]\n", position.getX(), position.getY());

}

void Character::printName(char * ptrName) {
	
}


//getters, setters

void Character::setPosition(Point2D position) {
	Character::position = position;
}

Point2D Character::getPosition() {
	return Character::position;
}

void Character::setPtrName(char *ptrName) {
	Character::ptrName = ptrName;
}

char * Character::getPtrName() {
	return Character::ptrName;
}
