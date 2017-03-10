#ifndef STATE_H
#define STATE_H

#include "board.h"
#include <vector>
using namespace std;    //for vector

class State : public Board
{
public:
    vector<State*> children;
    int evaluation;
    bool isMaxNode; //if it is not a max node then it is a min node
    int alphaBeta;

    State();
    State(const Board &other);
    int evaluate();
};

#endif // STATE_H
