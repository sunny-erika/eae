#pragma once
class Entity
{
private:
	Vector2D position;

public:
	Entity();
	Entity(Vector2D newPosition);
	~Entity();

	bool move(Vector2D position);

	//
	void setPosition(Vector2D position);
	Vector2D getPosition();

};

