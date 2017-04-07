/**
*	@file move.h
*	@class Move
*
*	@brief a single move that can be made on a current board state
*
*	@section Description
*   This class is used to create the edges of the game tree. One stated leads to another state through a move.
*
*	@section License
*	Copyright belongs to Juan du Preez (15189016)
*
*/
#ifndef MOVE_H
#define MOVE_H

class Move
{
public:
    int row; /**< the current row which is chosen in the move*/
    int col;/**< the current column which is chosen in the move*/
    bool direction; /**< the direction row which is chosen in the move*/

    bool isTakasaHouse; /**< true if the move ends in a takas house situation*/
    bool isNamuaStop; /**< true if the one chooses to stop at the house*/
    Move();
};

#endif // MOVE_H
