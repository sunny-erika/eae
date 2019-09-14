#pragma once
class Vector2D
{

private:
	int x, y;

public:
	Vector2D();
	Vector2D(int x, int y);
	~Vector2D();

	void setX(int x);
	int getX();

	void setY(int y);
	int getY();
};

