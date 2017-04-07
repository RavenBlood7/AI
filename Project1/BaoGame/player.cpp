#include "player.h"

Player::Player()
{
    playerNumber = 1;
}


Player::Player(int playerNumber)
{
    this->playerNumber = playerNumber;
}

bool Player::play(int row, int col, bool direction, Board *board) //returns true if player is done with turn
{
    //if Namua
        //if takasa
        bool clockwise;
        if (playerNumber == 1)
        {
            if (direction == 1)
                clockwise = board->CLOCKWISE;
            else clockwise = board->ANTICLOCKWISE;
        }
        else
        {
            if (direction == 1)
                clockwise = board->ANTICLOCKWISE;
            else clockwise = board->CLOCKWISE;
        }
        if (board->isTakasa())
        {

            board->enterTakasaSeed(row, col, clockwise);
        }
        else
        {
            board->enterSeed(row, col, clockwise);
        }

        bool player;
        if(playerNumber == 1)
            player = board->PLAYER2;
        else player = board->PLAYER1;
        board->possibleMoves(player);
        return !board->isLosingPosition();  //returns true/success if did not lose

        //if takasa and house
    //if Mtaji

}
