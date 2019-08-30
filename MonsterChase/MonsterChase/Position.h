#pragma once
class Position
{
	int x, y;

public:
	Position();
	Position(int x, int y);
	void setX(int x);
	int getX();
};

Position::Position(int x, int y) {
	Position::x = x;
	Position::y = y;
}

void Position::setX(int x) {
	Position::x = x;
}

int Position::getX() {
	return Position::y;
}
