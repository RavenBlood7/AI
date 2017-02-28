#ifndef GAME_H
#define GAME_H

//#include "AIPlayer.h"
#include "user.h"
#include "board.h"

class Game
{
private:
    Player* player1;
    Player* player2;
    Board* board;
    bool isInNamua;

public:
    Game();
    ~Game();
    void initialize();
    void playGame();
};

#endif // GAME_H
