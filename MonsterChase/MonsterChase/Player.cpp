#include "Player.h"
#include "Position.h"


//constructors
Player::Player()
{
}

Player::Player(Position position) {
	Player::position = position;
}

Player::~Player()
{
}


//setter & getter
void Player::setPosition(int x, int y) {
	Player::position.setX(x);

}

Position Player::getPosition() {
	return position;

}