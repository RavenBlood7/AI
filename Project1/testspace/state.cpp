#include "state.h"

State::State()
{

}


State::State(const Board &other, bool player) : Board(other)
{
	favouredPlayer = player;
	isMaxNode = true;
}

int State::evaluate(bool player)
{
	//calculate if losing position 100 or -100
	if (isLosingPosition())
	{
		if (favouredPlayer == player)
			return 100;
		else return -100; 
	}
	
	//weights
	const float countSeedWeight = 30.0/100;
	const float frontRowWeight = 20.0/100;
	const float backRowWeight= 10.0/100;
	const float frontRowOccWeight = 15.0/100;
	const float backRowOccWeight= 5.0/100;
	const float captureWeight = 20.0/100;
	
	
	//count seeds for each player
	int countSeed;
	int p1 = 0;
	for (int i = 0; i < 8; i++)
	{
		p1 += board[2][i] + board[3][i];
	}
	int p2 = 0;
	for (int i = 0; i < 8; i++)
	{
		p2 += board[0][i] + board[1][i];
	}
	if (player == PLAYER1) countSeed = (p1 - p2);
	else countSeed = (p2 - p1);
	
	//count seeds in front rows and back rows respectively
	int frontRow;
	int backRow;
	p1 =0;
	int p1b = 0;
	for (int i = 0; i < 8; i++)
	{
		p1 += board[2][i];
		p1b += board[3][i];		
	}
	p2 = 0;
	int p2b = 0;
	for (int i = 0; i < 8; i++)
	{
		p2 += board[1][i];
		p2b += board[0][i];
	}
	if (player == PLAYER1) 
	{
		frontRow = p1 - p2;
		backRow = p1b - p2b;
	}
	else 
	{
		frontRow = p2 - p1;
		backRow = p2b - p1b;
	}		
	
	//count how many holes are occupied in back row and front rows
	int frontRowOcc;
	int backRowOcc;
	p1 =0;
	p1b = 0;
	for (int i = 0; i < 8; i++)
	{
		if (board[2][i] != 0) p1++;
		if (board[3][i] != 0) p1b++;
	}
	p2 = 0;
	p2b = 0;
	for (int i = 0; i < 8; i++)
	{
		if (board[1][i] != 0) p2++;
		if (board[0][i] != 0) p2b++;
	}	
	if (player == PLAYER1) 
	{
		frontRowOcc = p1 - p2;
		backRowOcc = p1b - p2b;
	}
	else 
	{
		frontRowOcc = p2 - p1;
		backRowOcc = p2b - p1b;
	}	
	
	//count the number of seeds each player can capture
	int capture = 0;
	p1 =0;
	p2 = 0;
	for (int i = 0; i < 8; i++)
	{
		if (board[2][i] != 0 && board[1][i])
		{
			p1 += board[1][i];
			p2 += board[2][i];
		}
	}
	if (player == PLAYER1) capture = p1 - p2;
	else capture = p2 - p1;
	
	//return weighted sum
	return countSeedWeight * countSeed
		+ frontRowWeight * frontRow
		+ backRowWeight * backRow		
		+ frontRowOccWeight * frontRowOcc
		+ backRowOccWeight * backRowOcc
		+captureWeight * capture;
}

 bool State::getPlayer()
{
	return favouredPlayer;
}
