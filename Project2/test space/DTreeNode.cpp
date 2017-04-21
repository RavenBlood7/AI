#include "DTreeNode.h"

DTreeNode::DTreeNode()
{
	
}

DTreeNode::~DTreeNode()
{
	//delete children
}

vector<DTreeNode>* DTreeNode::getChildren()
{
	
}

void DTreeNode::split(string attribute)
{
	
}

void DTreeNode::addCase(vector<string> newCase)
{
	set.push_back(newCase);
}

bool DTreeNode::isLeaf()
{
	
}

string DTreeNode::toString()
{
	string ret = "The data:\n";
	for (int i = 0; i < set.size(); i++)
	{
		for (int j = 0; j < set.at(i).size(); j++)
			ret += set.at(i).at(j) + " ";
		ret += "\n";
	}
	return ret;
}