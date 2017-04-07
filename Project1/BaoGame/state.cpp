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
        else return 0;
	}
	
	//weights
    const float countSeedWeight = 30.0;
    const float frontRowWeight = 20.0;
    const float backRowWeight= 10.0;
    const float frontRowOccWeight = 15.0;
    const float backRowOccWeight= 5.0;
    const float captureWeight = 20.0;
	
	
	//count seeds for each player
    float countSeed;
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
    if (player == PLAYER1) countSeed = 1.0 * (p1 / (p1 + p2));
    else countSeed = 1.0 * (p2 / (p1 + p2));
	
	//count seeds in front rows and back rows respectively
    float frontRow;
    float backRow;
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
        frontRow = 1.0 * (p1 / (p1 + p2));
        if (p1b + p2b != 0) backRow = 1.0 * (p1b / (p1b + p2b));
        else backRow = 0.5;
	}
	else 
	{
        frontRow = 1.0 * (p2 / (p1 + p2));
        if (p1b + p2b != 0) backRow = 1.0 * (p2b / (p1b + p2b));
        else backRow = 0.5;
	}		
	
	//count how many holes are occupied in back row and front rows
    float frontRowOcc;
    float backRowOcc;
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
        frontRowOcc = 1.0 * (p1 / 8);
        backRowOcc =1.0 * (p1b / 8);
	}
	else 
	{
        frontRowOcc = 1.0 * (p2 / 8);
        backRowOcc = 1.0 * (p2b / 8);
	}	
	
	//count the number of seeds each player can capture
    float capture = 0.5;
    if (!isTakasa())
    {
        p1 =0;
        p2 = 0;
        for (int i = 0; i < 8; i++)
        {
            if (board[2][i] != 0 && board[1][i] != 0)
            {
                p1 += board[1][i];
                p2 += board[2][i];
            }
        }
        if (player == PLAYER1) capture = 1.0 * (p1 / (p1 + p2));
        else capture = 1.0 * (p2 / (p1 + p2));
    }
	
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
