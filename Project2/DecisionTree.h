/**
*	@file DecisionTree.h
*	@class DecisionTree
*
*	@brief Abstract class that defines the methods of inducing a decision tree
*
*	@section Description
*	Houses the main function of inducing a decision tree
*
*	@section License
*	Copyright belongs to Juan du Preez (15189016)
*
*/

#ifndef DECISION_TREE
#define DECISION_TREE

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Structure.h"
#include "DTreeNode.h"

using namespace std;

class DecisionTree
{
	protected:
		DTreeNode* root;
		DTreeNode* testSet;
		DTreeNode* trainingSet;
		Structure* structure;
		vector<DTreeNode*> displayStack;

		void initializeRoot(string dataFile);	
		virtual bool classify(vector<string> oneCase) = 0;	
		virtual float classificationError(DTreeNode* set) = 0;	
	public:
		DecisionTree(string specFile, string dataFile);
		virtual ~DecisionTree();
		
		virtual void induceNoMissing() = 0;
		virtual void induceWithMissing() = 0;
		virtual void prune() {};

	
		string toString();
		string toString(DTreeNode* node);
		void toFile(string outFile);	
		void toFile(string outFile, bool prune);	
};

#endif