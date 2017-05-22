/**
*	@file DiscreteDT.h
*	@class DiscreteDT
*
*	@brief Concrete class that deals with discrete data only
*
*	@section Description
*	Class that induces a decision tree from discrete or categorical data
*
*	@section License
*	Copyright belongs to Juan du Preez (15189016)
*
*/

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
		void divideAndConquer(DTreeNode* node);	/**< induces a decsion tree recursively assuming no data is missing*/
		float informationGain(DTreeNode* node, string attribute); /**< calculation of the information gain*/
		float entropy(DTreeNode *node, int index); 	/**< calculation of the entropy of a set "node" with regards to different classes*/
		float averageEntropy(DTreeNode* node, string attribute); /**< calculates sum of attribute value entorpies and specifies weights*/	
		bool classify(vector<string> oneCase);		/**< for a single pattern, sees whether it is correctly classified by the tree*/
		float classificationError(DTreeNode* set); 	/**< determines how many cases in a set are incorrectly classified*/
	
		void divideAndConquerMissing(DTreeNode *node); /**< same as divideAndConquer() but takes missing values into account*/
		float informationGainMissing(DTreeNode *node, string attribute);/**< special information gain for missing values. With probabilities*/
	
		DTreeNode* recursivePrune(DTreeNode *node); /**< decides which nodes to prune*/
	
	public:
		DiscreteDT(string specFile, string dataFile);	/**< calls parent constructor*/
		
		void induceNoMissing(); 					/**< implementation of parent's pure virtual function*/
		void induceWithMissing(); 				/**< implementation of parent's pure virtual function*/
		void prune(); 							/**< implementation of parent's pure virtual function*/
};

#endif