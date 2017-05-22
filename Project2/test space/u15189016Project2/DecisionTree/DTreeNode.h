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
#include <sstream>
#include <algorithm> //for random_shuffle

using namespace std;

class DTreeNode
{
	private:
		string attr;	/**< the attribute to display*/
		char relop; 	/**< relational operator: = > <*/
		string value;	/**< the value on which node is split*/
		string splitAttr;/**< used for classValues in leaf nodes and attribute split on in nonleaves*/
		
		vector<DTreeNode*>* children = NULL; /**< node's sub-nodes*/
		list< vector<string> > set;		/**< the list of data cases or patterns*/
		vector<float> probabilities;		/**< used for missing value datasets: keeps track of the probability of a case*/

	public:
		DTreeNode();
		~DTreeNode();
		
		vector<DTreeNode*>* getChildren();
		
		void split(string attr, int index, vector<string> attributeValues);	/**< divides set cases into subsets*/
		void splitMissing(string attr, int index, vector<string> attributeValues);/**< special splitting based on missing values*/
		void unsplit(); /**< combining children with parent. used when pruning*/
	
		void addCase(vector<string> newCase);	/**< add single data pattern to set*/
		void addProbCase(vector<string> newCase);/**< add data pattern and acompanying probability*/
		float sumProb();			/**< add up all the probabilities*/
	
		vector<string> popCase();	/**< removes and returns top data pattern or case*/
		void randomize();			/**< arranges the set in random order*/
	
		void setSplitAttr(string split);
		bool isLeaf();
		int getSize();
		void setValue(string value);
		string getValue();
		string getClass(int index);
		string getClass();
		string getAttr();	
	
		bool multipleClasses();		/**< checks if the set has only one class*/
	
		int frequency(int index, string value); /**< how many times a value appears in a given set*/
	
		DTreeNode* subset(int index, string value);	/**< creates a subset of cases which have the given value or attribute*/
		DTreeNode* subsetNoMissing(int index); /**< returns a set of all cases that have values*/
		
		bool onlyLeafChildren(); 		/**< used in pruning: checks if children have children*/
		DTreeNode *clone();		/**< returns a deep copy of current node*/
	
		string toString();
		
		/////continuous
		vector<float> getPossibleValues(int index);/**< returns a set of floats that appear in the given attribute index*/
		int frequencyLessThanEq(int index, float value);/**< counts how many cases have a attribute value less than or equal to the given value*/
		DTreeNode* subsetLessThanEq(int index, float value); /**< gets a subset of all the cases with real attribute less than or equal to the value*/
		DTreeNode* subsetGreaterThan(int index, float value);/**< gets a subset of all the cases with real attribute greater than the value*/
		void splitContinuous(string attr, float curValue, int index); /**< special form of splitting which accounts for continuous values*/
		
	

};

#endif