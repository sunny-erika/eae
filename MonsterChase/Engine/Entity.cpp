#include "Entity.h"
#include "Vector2D.h"



Entity::Entity()
{
}


Entity::Entity(Vector2D newPosition)
{
	this->position = newPosition;
}


Entity::~Entity()
{
}

bool Entity::move(Vector2D position) {

	this->position = position;//TODO if it is within the board
	return true;
}

//getters, setters

void Entity::setPosition(Vector2D position) {
	Entity::position = position;
}

Vector2D Entity::getPosition() {
	return Entity::position;
}
