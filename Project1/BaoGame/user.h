/**
*	@file user.h
*	@class User
*
*	@brief the human based part of the game
*
*	@section Description
*   In charge of managing user's decisions
*
*	@section License
*	Copyright belongs to Juan du Preez (15189016)
*
*/


#ifndef USER_H
#define USER_H

#include "player.h"

class User : public Player
{
public:
    User();
    User(int);

    bool takeTurn(Board *); /**< currently not in use*/
    int assessState(Board *); /**< currently not in use*/   //whether you must capture or can sow. Also use this to update the widget perhaps
    void sowLeftRight(int); /**< currently not in use*/  //x will be 0 for left and 7 for right for player1 and the other way around for player2
    void capture(int);  /**< currently not in use*/  //or (x, y) if the second row can capture as well
};

#endif // USER_H
