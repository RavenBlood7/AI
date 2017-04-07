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
    Player* player1 = NULL;
    Player* player2 = NULL;
    Player* curPlayer = NULL;  /**< the player whose turn it is*/
    GUIBoard* board;       /**< the board shared between players*/
    int curRow, curCol; /**< the current row and column being accessed before sent to the player for processing*/
    bool PvsAI;/**< boolean of whether game is Player vs AI. A special case*/

public:
    Game();
    ~Game();

    void initialize(QWidget *w); /**< Sets the game to it's initial state*/
    void initPvsP(QWidget *w); /**< Sets up the game for Player vs Player*/
    void initPvsAI(QWidget *w, int plyDepth); /**< Sets up the game for Player vs AI*/
    void initAIvsAI(QWidget *w, int plyDepth1, int plyDepth2); /**< Sets up the game for AI vs AI*/

    void playAIvAI(); /**< starts the game for AI vs AI*/

    void setCurData(int curRow, int curCol);    /**< a means of setting current row and col*/
    /**
    * sends current row, column, and direction to a player for processing
    * @param direction 0 for left and 1 for right as indicated in Board's constants
    */
    void sendData(bool direction);
    bool isPvAI(); /**< used for AISettings. To display two AIs or just one*/
    void setPvAI(bool x);
};

#endif // GAME_H
