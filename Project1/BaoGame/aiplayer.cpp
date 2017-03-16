#include "aiplayer.h"
#include <QApplication>

AIPlayer::AIPlayer()
{
    plyDepth = 3;
}

AIPlayer::AIPlayer(int playerNum,int plyDepth) : Player(playerNum)
{
    this->plyDepth = plyDepth;
}

bool AIPlayer::takeTurn(GUIBoard *board)
{
    qApp->processEvents();
    bool player;
    if (playerNumber == 1) player = 0;
    else player = 1;
    tree = new GameTree(board, player, plyDepth);
    tree->makeBestMove(board);
    delete tree;
    return !board->isLosingPosition();
}
