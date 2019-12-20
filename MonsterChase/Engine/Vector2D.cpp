#include "Vector2D.h"



Vector2D::Vector2D()
{

}

//overloaded constructor
Vector2D::Vector2D(int x, int y)
{
	
	this->x = x;
	this->y = y;
	
}


Vector2D::~Vector2D()
{
}

const Vector2D Vector2D::Zero(0, 0);

Vector2D & Vector2D::operator+=(const Vector2D & vector)
{
	x += vector.x;
	y += vector.y;

	return *this;
}

Vector2D & Vector2D::operator-=(const Vector2D & vector)
{
	x -= vector.x;
	y -= vector.y;

	return *this;
}

Vector2D & Vector2D::operator*=(const Vector2D & vector)//Calculates the componentwise product with the vector v.
{ 
	x *= vector.x;
	y *= vector.y;

	return *this;
}

Vector2D & Vector2D::operator/=(const Vector2D & vector)
{
	x /= vector.x;
	y /= vector.y;

	return *this;
}

float Vector2D::operator%(const Vector2D & vector)//crossproduct
{
	
	return (x * vector.y) - (y *vector.x);;
}

float Vector2D::operator^(const Vector2D vector) {//dot product
	
	return (x * vector.x) + (y * vector.y);
}


bool Vector2D::operator ==(Vector2D& vector)const
{
	//return (isEqual(x, vector.x) && isEqual(y, vector.y));
	return (x == vector.x && y == vector.y);
}

bool Vector2D::operator !=(Vector2D& vector)const
{
	//return !(isEqual(x, vector.x) && isEqual(y, vector.y));
	return !(x == vector.x && y == vector.y);
}


Vector2D & Vector2D::operator-(const Vector2D & vector)
{
	x = -vector.x;
	y = -vector.y;

	return *this;
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

/*
	Vector2D operator+(Vector2D vector2);
	Vector2D operator-(Vector2D vector2);
	Vector2D operator*(Vector2D vector2);//
	Vector2D operator/(Vector2D vector2);//
	Vector2D operator% (Vector2D vector2);//cross product, vector product
	int operator^(Vector2D vector2);//dot operator, scalar product
	bool operator==(Vector2D vector2);
	bool operator!=(Vector2D vector2);
*/

const Vector2D Vector2D::Zero(0, 0);

/*
// Addition 
Vector2D Vector2D::operator+(Vector2D vector2)
{
	int x_result, y_result;
	x_result = x + vector2.getX();
	y_result = y + vector2.getY();
	Vector2D result = Vector2D(x_result, y_result);
	
	return result;
}
*/
