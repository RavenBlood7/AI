/**
*	@file ContinuousDT.h
*	@class ContinuousDT
*
*	@brief Concrete class that deals with discrete data as well as continuous data
*
*	@section Description
*	Class that induces a decision tree from continuous or numerical data
*
*	@section License
*	Copyright belongs to Juan du Preez (15189016)
*
*/

#ifndef CONTINUOUS_DT
#define CONTINUOUS_DT

#include <iostream>
#include <sstream>
#include <cmath>		//for log
#include <algorithm>	//for sort
#include "DecisionTree.h"

using namespace std;

class ContinuousDT : public DecisionTree
{	
	protected:		
		float curValue;						/**< captures which value has highest information gain*/
	
		void divideAndConquer(DTreeNode* node);	/**< induces a decsion tree recursively assuming no data is missing*/
		float informationGain(DTreeNode* node, string attribute); /**< calculation of the information gain*/
		float entropy(DTreeNode *node, int index); 	/**< calculation of the entropy of a set "node" with regards to different classes*/
		float averageEntropy(DTreeNode* node, string attribute); /**< calculates sum of attribute value entorpies and specifies weights*/	
		bool classify(vector<string> oneCase);		/**< for a single pattern, sees whether it is correctly classified by the tree*/
		float classificationError(DTreeNode* set); 	/**< determines how many cases in a set are incorrectly classified*/
	
		//new
		float continuousInfoGain(DTreeNode* node, string attribute); /**< calculates information gain specifically for continuos data*/
		float entropyCont(DTreeNode* node, float value, int index); /**< similarly entropy for a continuous attribute*/
		DTreeNode* recursivePrune(DTreeNode *node); /**< decides which nodes to prune*/
	
	
	public:
		ContinuousDT(string specFile, string dataFile);/**< calls parent constructor*/
		
		void induceNoMissing(); 					/**< implementation of parent's pure virtual function*/
		void induceWithMissing(); 				/**< implementation of parent's pure virtual function*/
		void prune(); 							/**< implementation of parent's pure virtual function*/
};

#endif