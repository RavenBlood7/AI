#include "game.h"

Game::Game()
{
    //initialize();
}


Game::~Game()
{
    delete player1;
    delete player2;
    delete board;
}

void Game::initialize(QWidget *w)
{
    //check if AI against AI or person against person or AI against person
    //set AI levels

    if (player1 == NULL) delete player1;
    if (player2 == NULL) delete player2;
    if (board == NULL) delete board;

    player1 = new User(1);
    player2 = new User(2);
    curPlayer = player1;

    board = new GUIBoard(w);
    board->print();
}

void Game::playGame()
{
    // while (player1->takeTurn(board) && player2->takeTurn(board))
    //{}
}

void Game::setCurData(int curRow, int curCol)
{
    this->curRow = curRow;
    this->curCol = curCol;
}

void Game::sendData(bool direction) //0 for left and 1 for right
{
    if (curPlayer->play(curRow, curCol, direction, board))
    {
        //change player
        if (curPlayer == player1)
            curPlayer = player2;
        else curPlayer = player1;
    }
}
