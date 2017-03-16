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
    bool favouredPlayer;

public:
    vector<State*> children;
    int evaluation;
    bool isMaxNode; //if it is not a max node then it is a min node

    State();
    State(const Board &other, bool player);
    int evaluate(bool player);
    bool getPlayer();

 //   void possibleMoves() {};
};

#endif // STATE_H
