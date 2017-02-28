#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

class Player
{
protected:
    int playerNumber;

public:

    Player();
    Player(int playerNumber);
    virtual bool takeTurn(Board *) = 0; //returns false if the player loses
    virtual bool play(int row, int col, bool direction, Board *board); //0 for left and 1 for right
};

#endif // PLAYER_H
