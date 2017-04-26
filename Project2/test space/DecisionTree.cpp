#include "DecisionTree.h"

DecisionTree::DecisionTree(string specFile, string dataFile)
{
	structure = new Structure(specFile);
	initializeRoot(dataFile);
}

DecisionTree::~DecisionTree()
{
	delete root;
	delete testSet;
	delete structure;
}

void DecisionTree::initializeRoot(string dataFile)
{
/////////////////////////////
//cout << "in initRoot: " << endl;	
	root = new DTreeNode();
	ifstream inFile(dataFile.c_str());
	stringstream tempStream;
	string line;
	vector<string> tempVec;
	
	if (inFile.is_open())
	{
		//place all data in root set
		while (getline(inFile, line))
		{
			tempStream.clear();
			tempStream << line;			
			while (tempStream.rdbuf()->in_avail() !=0)
			{
				tempStream >> line;		
				tempVec.push_back(line);
			}
			root->addCase(tempVec);
			tempVec.clear();
		}
		
		//randomize data	
		root->randomize();
		
		//place top  30% in test set
		testSet = new DTreeNode();
		int trainNum = 0.3 * root->getSize();
		for (int i = 0; i < trainNum; i++)
		{
			testSet->addCase(root->popCase());
		}
	}
	else
	{
		cout << "Error opening file: " << dataFile << endl;
	}
/////////////////////////////
//cout << "out initRoot: " << endl;		
}

//@todo change this
string DecisionTree::toString()
{
/////////////////////////////
cout << "in toString: " << endl;		
	string ret = "The decision tree:\n";
	ret += "Structure:\n" + structure->toString();
	//ret += "Test Set:\n" + testSet->toString();
	//ret += "Root:\n" + root->toString();

	ret += toString(root);
	return ret;
/////////////////////////////
//cout << "in toString: " << endl;			
}

string DecisionTree::toString(DTreeNode* node)
{
/////////////////////////////
//cout << "in recToString: " << endl;			
	string ret = "";
	if (node != NULL)
	{
		if (node->isLeaf())
		{
			ret = "IF ";
/////////////////////////////
//cout << "in recToString: before for 1 " << (displayStack.size() - 1) << endl;	
			int size = displayStack.size();
			for (int i = 1; i < size ; i++)
			{
				ret += displayStack.at(i)->toString() + " AND ";
			}

/////////////////////////////
//cout << "in recToString: before size - 1 " << endl;			
				ret += node->toString();
/////////////////////////////
//cout << "in recToString: after size - 1 " << endl;							
			ret += " THEN " + structure->getClassName() + " is " + node->getClass(structure->getNumAttributes());
		}
		else
		{	
			displayStack.push_back(node);		
			vector<DTreeNode*>* children = node->getChildren();
/////////////////////////////
//cout << "in recToString: before for " << endl;							
			for (int i = 0; i < children->size(); i++)
			{
				ret += toString(children->at(i)) + "\n";
			}				
/////////////////////////////
//cout << "in recToString: after for " << endl;										
			displayStack.pop_back();
		}
	}
/////////////////////////////
//cout << "out recToString: " << endl;				
	return ret;
}

string DecisionTree::toFile(string outFile)
{
	return "garbage-for-now";
}