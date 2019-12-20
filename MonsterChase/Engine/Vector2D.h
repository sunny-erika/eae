#pragma once

//or
//#ifndef __VECTOR2_H
//#define __VECTOR2_H

class Vector2D
{

private:
	int x, y;

public:
	Vector2D();
	Vector2D(int x, int y);// for the future: use i_ for input vars and o_ for output	Vector2D(int i_x, int i_y);
	
	~Vector2D();

	//
	void setX(int x);
	int getX();

	void setY(int y);
	int getY();

	//
	//Addition - vector addition, each vector component are individually added to the corresponding component in the second vector
	//implement vector addition by overloading C++ operators
	Vector2D & operator+=(const Vector2D & vector2);
	Vector2D & operator-=(const Vector2D & vector2);
	Vector2D & operator*=(const Vector2D & vector2);
	Vector2D & operator/=(const Vector2D & vector2);
	Vector2D & operator-(const Vector2D & vector2);//negate
	float operator% (const Vector2D & vector2);//cross product
	float operator^(const Vector2D vector2);//dot operator
	bool operator==(Vector2D & vector2)const;
	bool operator!=(Vector2D & vector2)const;

	
	
	
	
	//void Vector2D::Normalize();

	static const Vector2D Zero;

};

