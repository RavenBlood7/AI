#ifndef GAMETREE_H
#define GAMETREE_H

#include "state.h"
#include "board.h"
#include "move.h"

class GameTree
{
    State* root;
    int plyDepth;

public:
    GameTree();

    //to interact with AIPlayer
    Move makeBestMove(Board* board);

    Move* getPossibleMoves(State* state);//returns a list of Moves
    void expandState(State* state);
    State* getNextState(State* state, Move* move);
};

#endif // GAMETREE_H
