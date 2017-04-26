#include <iostream>
#include "DiscreteDT.h"

using namespace std;


int main(int argc, char *argv[])
{
	DecisionTree *dt = new DiscreteDT("krkopt.spec", "krkopt.data");
	cout << dt->toString() << endl;
	///////////////
	cout << "inducing -d\n\n          \t-----\t\n\n" << endl;
	dt->induceNoMissing();	
	///////////////
	cout << "done inducing -d\n\n          \t-----\t\n\n" << endl;
	cout << dt->toString() << endl;
	delete dt;
	
	return 0;
}
