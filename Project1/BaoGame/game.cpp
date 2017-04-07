#include "game.h"

Game::Game()
{
    //initialize();
    curCol = 0;
    curRow = 0;
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
    board->possibleMoves(board->PLAYER1);
}

void Game::initPvsP(QWidget *w)
{
    PvsAI = false;
    if (player1 != NULL) delete player1;
    if (player2 != NULL) delete player2;
    if (board != NULL) delete board;

    player1 = new User(1);
    player2 = new User(2);
    curPlayer = player1;

    board = new GUIBoard(w);
    board->print();
    board->possibleMoves(board->PLAYER1);
}

void Game::initPvsAI(QWidget *w, int plyDepth)
{
    PvsAI = true;
    if (player1 == NULL) delete player1;
    if (player2 == NULL) delete player2;
    if (board == NULL) delete board;

    //get plydepth of each AI player

    player1 = new User(1);
    player2 = new AIPlayer(2, plyDepth);
    curPlayer = player1;

    board = new GUIBoard(w);
    board->print();
    board->possibleMoves(board->PLAYER1);
}

void Game::initAIvsAI(QWidget *w, int plyDepth1, int plyDepth2)
{
    PvsAI = false;
    if (player1 == NULL) delete player1;
    if (player2 == NULL) delete player2;
    if (board == NULL) delete board;

    //get plydepth of each AI player

    player1 = new AIPlayer(1, plyDepth1);
    player2 = new AIPlayer(2, plyDepth2);
    curPlayer = player1;

    board = new GUIBoard(w);
    board->print();
    (board)->disableAll();
    playAIvAI();
}

void Game::playAIvAI()
{
    while (true)
    {
        if (!((AIPlayer*) player1)->takeTurn(board)) break;
        if (!((AIPlayer*) player2)->takeTurn(board)) break;
    }
}

void Game::setCurData(int curRow, int curCol)
{
    this->curRow = curRow;
    this->curCol = curCol;
}

void Game::sendData(bool direction) //0 for left and 1 for right
{
    if (!PvsAI)
    {
        if (curPlayer->play(curRow, curCol, direction, board))
        {
            //change player
            if (curPlayer == player1)
                curPlayer = player2;
            else curPlayer = player1;
        }
    }
    else //player vs AI
    {
        if (player1->play(curRow, curCol, direction, board))
        {
            //let AI play
            ((AIPlayer*)player2)->takeTurn(board);
            board->possibleMoves(board->PLAYER1);
        }
    }
}

bool Game::isPvAI()
{
    return PvsAI;
}

void Game::setPvAI(bool x)
{
    PvsAI = x;
}
