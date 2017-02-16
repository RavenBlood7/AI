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
};

#endif // PLAYER_H
