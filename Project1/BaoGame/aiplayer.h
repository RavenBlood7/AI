/**
*	@file aiplayer.h
*	@class AIPlayer
*
*	@brief the player which will think for himself or herslef
*
*	@section Description
*   The AI part of the game that deals with gametrees and interacts with the board based on gametree's decision
*
*	@section License
*	Copyright belongs to Juan du Preez (15189016)
*
*/

#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"
#include "gametree.h"
#include "guiboard.h"

class AIPlayer : public Player
{
private:
    GameTree* tree; /**< the minimax gametree which will provide and execute the best move*/
    int plyDepth; /**< The depth to which this particular AI can search*/
public:
    AIPlayer();
    AIPlayer(int playerNum, int plyDepth);
    bool takeTurn(GUIBoard *board);
};

#endif // AIPLAYER_H
