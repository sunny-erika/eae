#include "Board.h"



Board::Board()
{
}

Board::Board(int row, int col)
{
	this->row = row;
	this->column = col;
}


Board::~Board()
{
}

void Board::printBoard() {

	board = new int*[row];

	for (int row = 1; row < this->row; ++row)
	{
		for (int col = 1; col < this->column; ++col)
		{
			//std::cout << 
		}
	}
}






