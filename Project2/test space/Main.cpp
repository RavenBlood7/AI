#include <iostream>
#include "DiscreteDT.h"

using namespace std;


int main(int argc, char *argv[])
{
	DecisionTree *dt = new DiscreteDT("tic-tac-toe.spec", "out.data");
	cout << dt->toString() << endl;
	///////////////
	cout << "inducing -d" << endl;
	dt->induceNoMissing();
	cout << dt->toString() << endl;
	delete dt;
	
	return 0;
}
