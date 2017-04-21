#ifndef DISCRETE_DT
#define DISCRETE_DT

#include <iostream>
#include "DecisionTree.h"

using namespace std;

class DiscreteDT : public DecisionTree
{	
	public:
		DiscreteDT(string specFile, string dataFile);//calls parent constructor
		
		void induceNoMissing();
		void induceWithMissing();
		void prune();
};

#endif