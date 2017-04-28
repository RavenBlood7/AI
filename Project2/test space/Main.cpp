#include <iostream>
#include "DiscreteDT.h"

using namespace std;


int main(int argc, char *argv[])
{
	//DecisionTree *dt = new DiscreteDT("example.spec", "example.data");
	DecisionTree *dt = new DiscreteDT("tic-tac-toe.spec", "tic-tac-toe.data");
	//DecisionTree *dt = new DiscreteDT("krkopt.spec", "krkopt.data");
	cout << dt->toString() << endl;
	///////////////
	cout << "inducing -d\n\n          \t-----\t\n\n" << endl;
	dt->induceNoMissing();	
	//dt->induceWithMissing();	
	///////////////
	cout << "done inducing -d\n\n          \t-----\t\n\n" << endl;
	cout << dt->toString() << endl;
	///////////////
	cout << "done pruning -d\n\n          \t-----\t\n\n" << endl;
	dt->prune();
	cout << dt->toString() << endl;
	////////////
	cout << "writing to file..." << endl;
	dt->toFile("data.out");
	delete dt;
	
	return 0;
}
