/**
*	@file player.h
*	@class Player
*
*	@brief base class for User and AIPlayer
*
*	@section Description
*   Base class which can be used to implement either the user's or the computer's part in the game
*
*	@section License
*	Copyright belongs to Juan du Preez (15189016)
*
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

class Player
{
protected:
    int playerNumber;   /**< 1 or 2 based on where one sits with regards to facing the board*/

public:

    Player();
    Player(int playerNumber);
    virtual ~Player() {};
    //virtual bool takeTurn(Board *) {}; //returns false if the player loses
    virtual bool play(int row, int col, bool direction, Board *board); //0 for left and 1 for right
};

#endif // PLAYER_H
