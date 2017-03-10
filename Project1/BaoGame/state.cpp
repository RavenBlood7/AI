#include "state.h"

State::State()
{

}


State::State(const Board &other) : Board(other)
{

}

int State::evaluate()
{
    //consider the number of seeds on each side of the board
    //consider the differences of seeds if can capture
        //i.e. 1 seed can take 7 seeds
    //perhaps value the front row more than the back row...weight it
}
