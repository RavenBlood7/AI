#ifndef USER_H
#define USER_H

#include "player.h"
//#include "board.h" ?? because it is in player

class User : public Player
{
public:
    User();
    User(int);

    bool takeTurn(Board *);
    int assessState(Board *);   //whether you must capture or can sow. Also use this to update the widget perhaps
    void sowLeftRight(int);   //x will be 0 for left and 7 for right for player1 and the other way around for player2
    void capture(int);    //or (x, y) if the second row can capture as well
};

#endif // USER_H
