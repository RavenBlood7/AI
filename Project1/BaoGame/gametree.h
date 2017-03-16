/**
*	@file gametree.h
*	@class GameTree
*
*	@brief the "brain" behind the AI functionality
*
*	@section Description
*   This is the tree that the AIPlayer will use to look ahead in the game
*
*	@section License
*	Copyright belongs to Juan du Preez (15189016)
*
*/

#ifndef GAMETREE_H
#define GAMETREE_H

#include "state.h"
#include "board.h"
#include "guiboard.h"
#include "move.h"
#include <vector>

class GameTree
{
    State* root;
    bool player;
    int maxDepth;
    vector<int> alphaValues;
    vector<int> betaValues;
	
    bool compareAlpha(int x);
    bool compareBeta(int x);

public:
    GameTree();
    GameTree(Board* board, bool player, int plyDepth);
    ~GameTree();
    void destroy(State * root);

    //to interact with AIPlayer
    Move makeBestMove(GUIBoard* board);/**< the umbrella function which is the interface to external classes*/

    vector<Move*>*  getPossibleMoves(State* state);/**< generates list of possible moves based on current state*/
    State* getNextState(State* state, Move* move); /**< based on current state and a move, makes next state*/
    int alphaBetaPruning(State* cur, int curDepth);

// for testing purposes
    void print();
};

#endif // GAMETREE_H
