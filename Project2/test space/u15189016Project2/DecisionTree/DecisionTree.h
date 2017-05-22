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
		Structure* structure; /**< contains the problem structure according to spec file*/
		vector<DTreeNode*> displayStack; /**< stack used in recursive toString() to keep track of path traveled*/

		void initializeRoot(string dataFile);	/**< puts data within the root and splits testSet and trainingSet*/
		virtual bool classify(vector<string> oneCase) = 0;	/**< for a single pattern, sees whether it is correctly classified by the tree*/
		virtual float classificationError(DTreeNode* set) = 0;	/**< determines how many cases in a set are incorrectly classified*/
	public:
		DecisionTree(string specFile, string dataFile); /**< creation of structure from spec file*/
		virtual ~DecisionTree();
		
		virtual void induceNoMissing() = 0;	 /**< abstract function for inducing a normal tree with no missing values in data*/
		virtual void induceWithMissing() = 0; 	 /**< induces tree accounting for missing values*/
		virtual void prune() {};				/**< abstract function for pruning nodes*/

	
		string toString(); /**< used for displaying and writing to file*/
		string toString(DTreeNode* node); /**< recursively finds path to each leaf and prints respective rule*/
		void toFile(string outFile);	
		void toFile(string outFile, bool prune);	/**< writes both normal and pruned trees to file*/
};

#endif