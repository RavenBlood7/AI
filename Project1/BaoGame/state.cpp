#include "state.h"

State::State()
{

}


State::State(const Board &other)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 8; j++)
            this->board[i][j] = other.board[i][j];

    this->stack1 = other.stack1;
    this->stack2 = other.stack2;
    this->isNamuaVar = other.isNamuaVar;
}

int State::evaluate()
{
    //consider the number of seeds on each side of the board
    //consider the differences of seeds if can capture
        //i.e. 1 seed can take 7 seeds
    //perhaps value the front row more than the back row...weight it
}
