#include "DecisionTree.h"

DecisionTree::DecisionTree(string specFile, string dataFile)
{
	structure = new Structure(specFile);
	initializeRoot(dataFile);
}

DecisionTree::~DecisionTree()
{
	delete root;
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
	ret += root->toString();
	return ret;
	
}

string DecisionTree::toFile(string outFile)
{
	
}