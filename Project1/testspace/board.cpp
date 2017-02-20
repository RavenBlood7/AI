#include "board.h"
#include <iostream>

using namespace std;


Board::Board()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = 0;
		}
	}
}

bool Board::sow(bool player1,int row, int col, bool clockwise, int hand)
{
	int topRow;
	if (player1) 
		topRow = 2; 
	else topRow = 0;
	//consider getting rid of player:
		//	if ((row == 2) || (row == 3)) 
		//		topRow = 2; 
		//	else topRow = 0;
	//also make row and column passed by reference not value so that
		//the final row and column can be returned
	
	
	board[row][col]++;
	hand--;		
	while (hand)
	{		    
		if (row == topRow)
			clockwise ? col++ : col--;
		else
			clockwise ? col-- : col++;
		if (col > 7)
		{
			col = 7;
			clockwise? row = topRow + 1 : row = topRow;
		}
		else if (col < 0)
		{
			col = 0;
			clockwise? row = topRow : row = topRow + 1;
		}		
		board[row][col]++;
		hand--;	
	}
///////////////////remove this	
	cout << "last row: " << row << endl;
	cout << "last col: " << col << endl;  
	cout << "in function : " << board[row][col] << endl;  
    return board[row][col] == 1;
    
}

void Board::print()
{
	cout << "The Board:" << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << "\n";
	}	
	cout << "\n";
}