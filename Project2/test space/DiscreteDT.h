#ifndef DISCRETE_DT
#define DISCRETE_DT

#include <iostream>
#include <cmath>	//for log2
#include "DecisionTree.h"

using namespace std;

class DiscreteDT : public DecisionTree
{	
	private:	
		void divideAndConquer(DTreeNode *node);
		float informationGain(DTreeNode *node, string attribute);
		float entropy(DTreeNode *node, int index);
		float averageEntropy(DTreeNode* node, string attribute);
	public:
		DiscreteDT(string specFile, string dataFile);//calls parent constructor
		
		void induceNoMissing();	
		void induceWithMissing();
		void prune();
};

#endif