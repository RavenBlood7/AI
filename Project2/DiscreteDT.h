#ifndef DISCRETE_DT
#define DISCRETE_DT

#include <iostream>
#include <cmath>	//for log2
#include <cstdlib>	//for rand
#include "DecisionTree.h"

using namespace std;

class DiscreteDT : public DecisionTree
{	
	private:		
		void divideAndConquer(DTreeNode *node);
		float informationGain(DTreeNode *node, string attribute);
		float entropy(DTreeNode *node, int index);
		float averageEntropy(DTreeNode* node, string attribute);
		bool classify(vector<string> oneCase);
		float classificationError(DTreeNode* set);
	
		void divideAndConquerMissing(DTreeNode *node);
		float informationGainMissing(DTreeNode *node, string attribute);
	
		DTreeNode* recursivePrune(DTreeNode *node);
	public:
		DiscreteDT(string specFile, string dataFile);//calls parent constructor
		
		void induceNoMissing();	
		void induceWithMissing();
		void prune();
};

#endif