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
#include <list>
#include <iostream>
#include <algorithm> //for random_shuffle

using namespace std;

class DTreeNode
{
	private:
		string value;
		char relop;
		string attr;
		string splitAttr;
		
		vector<DTreeNode*>* children = NULL;
		list< vector<string> > set;

	public:
		DTreeNode();
		~DTreeNode();
		
		vector<DTreeNode*>* getChildren();
		
		void split(string attr, int index, vector<string> attributeValues);
	
		void addCase(vector<string> newCase);
	
		vector<string> popCase();
		void randomize();
	
		void setSplitAttr(string split);
		bool isLeaf();
		int getSize();
		void setValue(string value);
		string getValue();
		string getClass(int index);
	
		bool multipleClasses();
	
		int frequency(int index, string value);
	
		DTreeNode* subset(int index, string value);
	
		string toString();
	

};

#endif