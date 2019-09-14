#include "Vector2D.h"



Vector2D::Vector2D()
{
}

//overloaded constructor
Vector2D::Vector2D(int x, int y)
{
	setX(x);
	setY(y);
}


Vector2D::~Vector2D()
{
}

//setter & getter
void Vector2D::setX(int x) {
	Vector2D::x = x;
	//x = x;
}

int Vector2D::getX() {
	return Vector2D::x;
}

void Vector2D::setY(int y) {
	Vector2D::y = y;
}

int Vector2D::getY() {
	return Vector2D::y;
}