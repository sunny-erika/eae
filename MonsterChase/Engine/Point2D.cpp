#include "Point2D.h"



Point2D::Point2D()
{

}

//overloaded constructor
/*
Point2D::Point2D(int x, int y)
{
	
	this->x = x;
	this->y = y;
	
}
*/
Point2D::Point2D(float x, float y)
{

	this->x = x;
	this->y = y;

}
/*
Point2D::Point2D(double x, double y)
{

	this->x = x;
	this->y = y;

}
*/


Point2D::~Point2D()
{
}

const Point2D Point2D::Zero(0, 0);

Point2D & Point2D::operator+(const Point2D & vector)
{
	x += vector.x;
	y += vector.y;

	return *this;
}

Point2D & Point2D::operator+=(const Point2D & vector)
{
	x += vector.x;
	y += vector.y;

	return *this;
}

Point2D & Point2D::operator-(const Point2D & vector)
{
	x -= vector.x;
	y -= vector.y;

	return *this;
}

Point2D & Point2D::operator-=(const Point2D & vector)
{
	x -= vector.x;
	y -= vector.y;

	return *this;
}

Point2D & Point2D::operator*(const Point2D & vector)//Calculates the componentwise product with the vector v.
{ 
	x *= vector.x;
	y *= vector.y;

	return *this;
}

Point2D & Point2D::operator*=(const Point2D & vector)//Calculates the componentwise product with the vector v.
{
	x *= vector.x;
	y *= vector.y;

	return *this;
}
/*
Point2D & Point2D::operator*(const Point2D & vector)//Calculates the componentwise product with the vector v.
{
	x *= vector.x;
	y *= vector.y;

	return *this;
}
*/
Point2D & Point2D::operator*(const double & scalar)//Calculates the componentwise product with the vector v.
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Point2D & Point2D::operator*=(const double & scalar)//Calculates the componentwise product with the vector v.
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Point2D & Point2D::operator/=(const Point2D & vector)
{
	x /= vector.x;
	y /= vector.y;

	return *this;
}

Point2D & Point2D::operator/(const Point2D & vector)
{
	x /= vector.x;
	y /= vector.y;

	return *this;
}

Point2D & Point2D::operator/(const double & scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}
Point2D & Point2D::operator/=(const double & scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}

double Point2D::operator%(const Point2D & vector)//crossproduct
{
	
	return (x * vector.y) - (y *vector.x);;
}

double Point2D::operator^(const Point2D vector) {//dot product
	
	return (x * vector.x) + (y * vector.y);
}


bool Point2D::operator ==(Point2D& vector)const
{
	//return (isEqual(x, vector.x) && isEqual(y, vector.y));
	return (x == vector.x && y == vector.y);
}

bool Point2D::operator !=(Point2D& vector)const
{
	//return !(isEqual(x, vector.x) && isEqual(y, vector.y));
	return !(x == vector.x && y == vector.y);
}


Point2D & Point2D::operator-()
{
	Point2D v;
	v.x = -x;
	v.y = -y;
	return v;

}


//setter & getter
void Point2D::setX(float x) {
	Point2D::x = x;
	//x = x;
}

float Point2D::getX() {
	return (float) Point2D::x;
}

void Point2D::setY(float y) {
	Point2D::y = y;
}

float Point2D::getY() {
	return Point2D::y;
}

/*
	Point2D operator+(Point2D vector2);
	Point2D operator-(Point2D vector2);
	Point2D operator*(Point2D vector2);//
	Point2D operator/(Point2D vector2);//
	Point2D operator% (Point2D vector2);//cross product, vector product
	int operator^(Point2D vector2);//dot operator, scalar product
	bool operator==(Point2D vector2);
	bool operator!=(Point2D vector2);
*/

//const Point2D Point2D::Zero(0, 0);

/*
// Addition 
Point2D Point2D::operator+(Point2D vector2)
{
	int x_result, y_result;
	x_result = x + vector2.getX();
	y_result = y + vector2.getY();
	Point2D result = Point2D(x_result, y_result);
	
	return result;
}
*/
