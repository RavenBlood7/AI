#include "board.h"
#include <iostream>

using namespace std;


Board::Board()
{
	stack1 = stack2 = 22;
    isNamuaVar = true;
	
	for (int i = 0; i < 4; i++)
        for (int j = 0; j < 8; j++)
            board[i][j] = 0;

	board[1][3] = 6;
	board[2][4] = 6;	
	board[1][1] = 2;
	board[1][2] = 2;
	board[2][5] = 2;
	board[2][6] = 2;	
}


Board::Board(const Board &other)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 8; j++)
            this->board[i][j] = other.board[i][j];

    this->stack1 = other.stack1;
    this->stack2 = other.stack2;
    this->isNamuaVar = other.isNamuaVar;
}

bool Board::sow(int & row, int & col, bool clockwise, int hand)
{
	int topRow;
	if (row > 1) 
		topRow = 2; 
	else topRow = 0;
	
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
    return board[row][col] == 1;    
}

int Board::take(int row, int col)
{
	int temp = board[row][col];
	board[row][col] = 0;
	return temp;	
}

int Board::capture(int row, int col)
{	int oppRow;	
	row == 1? oppRow = 2 : oppRow = 1;
	if (board[oppRow][col] == 0 || (row == 0) || (row == 3))
		return -1;	//cannot capture

	return take(oppRow, col);
}

bool Board::enterSeed(int row, int col, bool clockwise)
{	
	int hand = capture(row, col);
	if (hand == -1) return false;
	
	board[row][col]++;
	row > 1? stack1-- : stack2--;
	if (stack1 == 0 && stack2 == 0)
        isNamuaVar = false;
	//if stack is zero go into mtaji
	bool endMove = false;
	while (!endMove)
	{
		
		if (hand == -1)
		{
            hand = take(row, col);
			if (row % 2 == 0)	//top row
			{
				if (clockwise)
					col++;
				else col--;				
			}
			else			//bottom row
			{
				if (clockwise)
					col--;
				else col++;				
			}
			if (col == 8)
			{
				if (clockwise)
					row++;
				else row--;
				col = 7;
			}
			else if (col == -1)
			{
				if (clockwise)
					row--;
				else row++;
				col = 0;				
            }
            endMove = sow(row, col, clockwise, hand);
		}
		else
		{
			if (col > 1 && col < 6)
			{
				if (row > 1)	//player 1
					clockwise? col = 0 : col = 7;
                else clockwise? col = 7 : col = 0;
			}
			else if (col <= 1)
			{
				col = 0;
				row > 1? clockwise = CLOCKWISE : clockwise = ANTICLOCKWISE;
			}
			else if (col >= 6)
			{
				col = 7;
				row > 1? clockwise = ANTICLOCKWISE : clockwise = CLOCKWISE;				
			}
			endMove = sow(row, col, clockwise, hand);
			

		}
		if (!endMove) hand = capture(row, col);
	}
	return true;
}

bool Board::isTakasa()
{
	for (int i = 0; i < 8; i++)
	{
		if (board[1][i] != 0 && board[2][i] != 0)
			return false;
	}
	return true;
}

bool Board::isTakasaNyumba()
{
    if (!isTakasa()) return false;
	//have to make it for both players
	//for (int i = 0; i < 8; i++)
	//{
	//	if (board[][])
	//		return false;
	//}
	return true;
}

bool Board::enterTakasaSeed(int row, int col, bool clockwise)
{
	if (board[row][col] < 2) return false;
    row > 1? stack1-- : stack2--;

	//enter in row, col
	board[row][col]++;
	bool emptyHole = false;
	int hand = 0;
	
	//while not in empty hole	
	while (!emptyHole)
	{
		//pick up in row, col
		hand = take(row, col);
		//get next hole
		if (row % 2 == 0)	//top row
		{
			if (clockwise)
				col++;
			else col--;				
		}
		else			//bottom row
		{
			if (clockwise)
				col--;
			else col++;				
		}
		if (col == 8)
		{
			if (clockwise)
				row++;
			else row--;
			col = 7;
		}
		else if (col == -1)
		{
			if (clockwise)
				row--;
			else row++;
			col = 0;				
		}		
		//sow in correct direction
		emptyHole = sow(row,col, clockwise, hand);
	}
	return true;
}

bool Board::isNamua()
{
    return !((stack1 == 0)&&(stack2 == 0));
}

bool Board::isLosingPosition()
{
    bool lost1 = true;
   for (int i = 0; i < 8; i++)
       if (board[1][i] != 0)
           lost1 = false;

   bool lost2 = true;
   for (int i = 0; i < 8; i++)
       if (board[2][i] != 0)
           lost2 = false;

   return lost1 || lost2;
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

