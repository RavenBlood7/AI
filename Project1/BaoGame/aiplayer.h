#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"
#include "gametree.h"

class AIPlayer : public Player
{
private:
    GameTree* tree;
public:
    AIPlayer();
};

#endif // AIPLAYER_H
