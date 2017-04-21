#include <iostream>
#include "DecisionTree.h"

using namespace std;


int main(int argc, char *argv[])
{
	DecisionTree *dt = new DecisionTree("tic-tac-toe.spec", "out.data");
	cout << dt->toString() << endl;
	delete dt;
	
	return 0;
}
