#ifndef CONTINUOUS_DT
#define CONTINUOUS_DT

#include <iostream>
#include "DecisionTree.h"

using namespace std;

class ContinuousDT : public DecisionTree
{	
	protected:		
		bool classify(vector<string> oneCase);	
		float classificationError(DTreeNode* set);	
	
	public:
		ContinuousDT(string specFile, string dataFile);//calls parent constructor
		
		void induceNoMissing();
		void induceWithMissing();
		void prune();
};

#endif