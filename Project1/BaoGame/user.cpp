#include "user.h"

User::User()
{

}

User::User(int playerNumber) : Player(playerNumber)
{

}

bool User::takeTurn(Board * board)
{
    //state = assessState
    //board->update(playerNumber, state)

    //wait for input x
    //this could take the form of connecting a function slot to a   //this function could be makeChoice(state)
        //widget on click signal

    //if state == sowing
    //sowLeftRight(x)

    //else if state == mustCapture
    //capture(x)
}

int User::assessState(Board * board)
{
    //return board->currentState(playerNumber)
}

void User::sowLeftRight(int x)  //perhaps pass the board as well
{
    //if (player number == 1)
        //if (x == 0) board->sowLeft()
        //else if (x == 7) board->sowRight()
    //else if (player number == 2)
        //if (x == 0) board->sowRight()
        //else if (x == 7) board->sowLeft()
}

void User::capture(int x)
{

}
