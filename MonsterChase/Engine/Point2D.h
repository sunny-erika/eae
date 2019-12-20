#pragma once

//or
//#ifndef __VECTOR2_H
//#define __VECTOR2_H

class Point2D
{

private:
	double x, y;

public:
	Point2D();
	//Point2D(int x, int y);// for the future: use i_ for input vars and o_ for output	Point2D(int i_x, int i_y);
	Point2D(float x, float y);
	//Point2D(double x, double y);
	~Point2D();

	/*
	void setX(int x);
	int getX();

	void setY(int y);
	int getY();
	*/
	void setX(float x);
	float getX();

	void setY(float y);
	float getY();

	//
	//Addition - vector addition, each vector component are individually added to the corresponding component in the second vector
	//implement vector addition by overloading C++ operators
	Point2D & operator+(const Point2D & vector2);
	Point2D & operator-(const Point2D & vector2);
	Point2D & operator*(const Point2D & vector2);
	Point2D & operator+=(const Point2D & vector2);
	Point2D & operator-=(const Point2D & vector2);
	Point2D & operator*=(const Point2D & vector2);
	Point2D & operator*=(const double & scalar);
	Point2D & operator*(const double & scalar);
	Point2D & operator/(const Point2D & vector2);
	Point2D & operator/=(const Point2D & vector2);
	Point2D & operator/=(const double & scalar);
	Point2D & operator/(const double & scalar);
	Point2D & operator-();//negate
	double operator% (const Point2D & vector2);//cross product
	double operator^(const Point2D vector2);//dot operator
	bool operator==(Point2D & vector2)const;
	bool operator!=(Point2D & vector2)const;

	
	
	
	
	//void Point2D::Normalize();

	static const Point2D Zero;

};

