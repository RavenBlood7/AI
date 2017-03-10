/**
*	@file game.h
*	@class Game
*
*	@brief facade to interact with outside world
*
*	@section Description
*   A combination of all other functionality, providing a single point for the external interface to interact with
*
*	@section License
*	Copyright belongs to Juan du Preez (15189016)
*
*/

#ifndef GAME_H
#define GAME_H

#include "aiplayer.h"
#include "user.h"
#include "guiboard.h"
#include <QWidget>

class Game
{
private:
    Player* player1;
    Player* player2;
    Player* curPlayer;  /**< the player whose turn it is*/
    Board* board;       /**< the board shared between players*/
    int curRow, curCol; /**< the current row and column being accessed before sent to the player for processing*/

public:
    Game();
    ~Game();

    void initialize(QWidget *w); /**< Sets the game to it's initial state*/
    void playGame();

    void setCurData(int curRow, int curCol);    /**< a means of setting current row and col*/
    /**
    * sends current row, column, and direction to a player for processing
    * @param direction 0 for left and 1 for right as indicated in Board's constants
    */
    void sendData(bool direction);
};

#endif // GAME_H
