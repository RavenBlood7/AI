/**
*	@file DTreeNode.h
*	@class DTreeNode
*
*	@brief Houses the sets of data or cases
*
*	@section Description
*	An individual node in a tree: has a set of cases and could be a leaf, i.e. class, or an attribute
*
*	@section License
*	Copyright belongs to Juan du Preez (15189016)
*
*/

#ifndef DTREE_NODE
#define DTREE_NODE

#include <vector>
#include <iostream>

using namespace std;

class DTreeNode
{
	private:
		string description;
		vector<DTreeNode*>* children;
		vector< vector<string> > set;

	public:
		DTreeNode();
		~DTreeNode();
		
		vector<DTreeNode>* getChildren();
		
		void split(string attribute);
	
		void addCase(vector<string> newCase);
	
		bool isLeaf();
	
		string toString();
};

#endif