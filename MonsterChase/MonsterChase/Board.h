#pragma once
class Board
{

private:
	int row;//column, row will become the 2D object
	int column;
	int** board;//a dynamic two-dimensional array is a dynamic one-dimensional array of dynamic one-dimensional arrays
	

public:
	Board();
	Board(int row, int col);
	~Board();
	
	void printBoard();
			
};

