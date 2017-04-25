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
		Structure* structure;

		void initializeRoot(string dataFile);	
	public:
		DecisionTree(string specFile, string dataFile);
		virtual ~DecisionTree();
		
	//	virtual void induceNoMissing() = 0;
	//	virtual void induceWithMissing() = 0;
	//	virtual void prune() = 0;
	
		string toString();
		string toFile(string outFile);	
};

#endif