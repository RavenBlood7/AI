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
}

//@todo change this
string DecisionTree::toString()
{
	string ret = "The decision tree:\n";
	ret += "Structure:\n" + structure->toString();
	ret += "Test Set:\n" + testSet->toString();
	ret += "Root:\n" + root->toString();

	return ret;
	
}

string DecisionTree::toFile(string outFile)
{
	return "garbage-for-now";
}