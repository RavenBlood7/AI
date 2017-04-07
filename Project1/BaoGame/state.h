/**
*	@file state.h
*	@class State
*
*	@brief Node in Game tree
*
*	@section Description
*   The node in the game tree displaying the current state of the game
*
*	@section License
*	Copyright belongs to Juan du Preez (15189016)
*
*/

#ifndef STATE_H
#define STATE_H

#include "board.h"
#include <vector>
using namespace std;    //for vector

class State : public Board
{
private:
    bool favouredPlayer;  /**< used in evaluation function*/

public:
    vector<State*> children;  /**< reference to further states*/
    int evaluation;  /**< a variable that keeps the evaluated value. Also used as alpha/beta value of node*/
    bool isMaxNode;  /**< shows whether node is min or max node*/

    State();
    State(const Board &other, bool player);
    int evaluate(bool player); /**< evaluates the state of the board with regards to a player*/
    bool getPlayer();  /**< returns the favouredPlayer variable*/

 //   void possibleMoves() {};
};

#endif // STATE_H
