#ifndef GAME_H
#define GAME_H

//#include "AIPlayer.h"
#include "user.h"
#include "guiboard.h"
#include <QWidget>

class Game
{
private:
    Player* player1;
    Player* player2;
    Player* curPlayer;
    Board* board;
    bool isInNamua;
    int curRow, curCol;

public:
    Game();
    ~Game();
    void initialize(QWidget *w);
    void playGame();

    void setCurData(int curRow, int curCol);
    void sendData(bool direction); //0for left and 1 for right
};

#endif // GAME_H
