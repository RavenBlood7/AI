#include "gametree.h"
#include "board.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	Board b;
	GameTree* gt = new GameTree(&b, b.PLAYER1, 3);
	gt->makeBestMove(&b);
	cout << "==========================" << endl;
	gt->print();
	
	delete gt;
	
}
