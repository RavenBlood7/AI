#include "game.h"

Game::Game()
{
    initialize();
}


Game::~Game()
{
    delete player1;
    delete player2;
    delete board;
}

void Game::initialize()
{
    //check if AI against AI or person against person or AI against person
    //set AI levels

    player1 = new User(1);
    player2 = new User(2);

    board = new Board();
}

void Game::playGame()
{
    // while (player1->takeTurn(board) && player2->takeTurn(board))
    //{}
}
