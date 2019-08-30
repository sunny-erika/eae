#include "Position.h" 
//header files include the membervar declarations & all function prototypes incl constructors
//cpp files include the function definitions

//constructors & deconstructor
Position::Position()
{
}

Position::Position(int x, int y) {
	Position::x = x;
	Position::y = y;
}

Position::~Position()
{
}

//setter & getter
void Position::setX(int x) {
	Position::x = x;
}

int Position::getX() {
	return Position::y;
}