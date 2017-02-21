#include "board.h"
#include <iostream>
/**@class Board
*/
using namespace std;


Board::Board()
{
	stack1 = stack2 = 22;
	isNamua = true;
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = 0;
		}
	}
	
	board[2][4] = 5;
	board[2][3] = 17;
	board[1][4] = 1;
	board[1][3] = 1;
}

bool Board::sow(int & row, int & col, bool clockwise, int hand)
{
	int topRow;
	if (row > 1) 
		topRow = 2; 
	else topRow = 0;
	
	board[row][col]++;
	hand--;	

///////////////////remove this	
	cout << "just sowed: " << row << "," << col << endl;	
	cout << "\thand is: " << hand << endl;	
	cout << "\tboard[row][col] is: " << board[row][col] << endl;	
	print();
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
///////////////////remove this	
	cout << "just sowed: " << row << "," << col << endl;	
	cout << "\thand is: " << hand << endl;	
	cout << "\tboard[row][col] is: " << board[row][col] << endl;
	print();
	}
///////////////////remove this	
	//cout << "last row: " << row << endl;
//	cout << "last col: " << col << endl;  
	cout << "in sow : " << board[row][col] << endl;  
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
		isNamua = false;
	//if stack is zero go into mtaji
	bool endMove = false;
	while (!endMove)
	{
		
		if (hand == -1)
		{
			hand = take(row, col);
			/*
			//get the next hole
			if (col == 0 && row % 2 == 1)//in bottom row
				clockwise? row-- : row++;
			else if (col == 7 && row % 2 == 0)
				clockwise? row++ : row--;
			else if (row % 2 == 0) 	//then it is in top row				
				clockwise ? col++ : col--;
			else clockwise ? col-- : col++;//it is in the bottom row
			*/
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
				
///////////////////remove this	
//	cout << "here0: " << row << col << endl;				
			endMove = sow(row, col, clockwise, hand);
			//if (!endMove) hand = capture(row, col);			
		}
		else
		{
			if (col > 1 && col < 6)
			{
				if (row > 1)	//player 1
					clockwise? col = 0 : col = 7;
				else clockwise? col = 7 : col = 0;	
///////////////////remove this	
//	cout << "here1: " << row << col << endl;				
			}
			else if (col <= 1)
			{
				col = 0;
				row > 1? clockwise = CLOCKWISE : clockwise = ANTICLOCKWISE;

///////////////////remove this	
//	cout << "here2: " << row << endl;								
			}
			else if (col >= 6)
			{
				col = 7;
				row > 1? clockwise = ANTICLOCKWISE : clockwise = CLOCKWISE;				

///////////////////remove this	
//	cout << "here3: " << row << endl;								
			}
			endMove = sow(row, col, clockwise, hand);
			

		}
		if (!endMove) hand = capture(row, col);
	}
	return true;
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