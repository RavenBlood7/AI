#include "DTreeNode.h"

DTreeNode::DTreeNode()
{
	children = NULL;
}

DTreeNode::~DTreeNode()
{
	//delete children
	if (children != NULL)
	{
		for (vector<DTreeNode*>::iterator it = children->begin(); it != children->end(); it++)
		{
			delete *it;
		}	
		delete children;
	}
}

vector<DTreeNode*>* DTreeNode::getChildren()
{
	return children;
}

void DTreeNode::split(string attr, int index, vector<string> attributeValues)
{
/////////////////////////////
//cout << "\t--in Node split: " << attr << endl;		
//cout << "\t\t index: " << index << endl;	
	splitAttr = attr;
	//create new children according to attributeValues
	children = new vector<DTreeNode*>();
	int size = attributeValues.size();
	for (int i = 0; i < size; i++)
	{
		children->push_back(new DTreeNode());
		children->at(i)->attr = attr;
		children->at(i)->relop = '=';
		children->at(i)->value = attributeValues.at(i);
	}		

	//divide up set	
	//for (list<vector<string> >::iterator it = set.begin(); it != set.end(); it++)
	int setSize = set.size();
	for (int i = 0; i < setSize; i++)
	{	
		for (int j = 0; j < size; j++)
		{				
			if (!set.empty() && set.front().at(index) == attributeValues.at(j))
			{				
				children->at(j)->addCase(set.front());	
				set.pop_front();
				break;
			}
		}
	}	
/////////////////////////////
//cout << "\t--out Node split: " << attr << endl;			
}

void DTreeNode::addCase(vector<string> newCase)
{
	set.push_back(newCase);
}

vector<string> DTreeNode::popCase()
{
	vector <string> tempVec = set.front();
	set.pop_front();
	return tempVec;
}

void DTreeNode::randomize()
{
	//convert list to vector
	vector < vector<string> > tempVec;			
	int size = set.size();
	for (int i = 0; i < size; i++)
	{
		tempVec.push_back(set.front());
		set.pop_front();
	}		
	
	//randomize vector
	random_shuffle(tempVec.begin(), tempVec.end());
	//conver vector to list
	for (int i = 0; i < size; i++)
	{
		set.push_front(tempVec.back());
		tempVec.pop_back();
	}		
}

bool DTreeNode::isLeaf()
{
	return (children == NULL);
}

int DTreeNode::getSize()
{
	return set.size();
}

void DTreeNode::setValue(string value)
{
	this->value = value;
}

string DTreeNode::getValue()
{
	return value;
}

string DTreeNode::getClass(int index)
{
	if (!set.empty())
		return set.front().at(index);
	else return "Unknown class";
}

bool DTreeNode::multipleClasses()
{
	bool multiple = false;
	string tempClass = set.front().back(); 	//the class value of the first case
	for (list<vector<string> >::iterator it = set.begin(); it != set.end(); it++)
	{
		if (it->back() != tempClass)
		{
			multiple = true;
			break;
		}
	}	
	return multiple;
}

int DTreeNode::frequency(int index, string value)
{

/////////////////////////////
//cout << "in freq: " << index << endl;		
//cout << "in freq: " << value << endl;		
	int total = 0;
	for (list<vector<string> >::iterator it = set.begin(); it != set.end(); it++)
	{
/////////////////////////////
//cout << "in freq: in fo" << index << endl;				
		if (it->at(index) == value)
			total++;
	}	
/////////////////////////////
//cout << "out freq: " << total << endl;			
	return total;
}

DTreeNode* DTreeNode::subset(int index, string value)
{
	DTreeNode* subset = new DTreeNode();
	vector<string> tempVec;
	for (list<vector<string> >::iterator it = set.begin(); it != set.end(); it++)
	{
		if (it->at(index) == value)
		{
			tempVec = *it;	//might be shallow copy
			subset->addCase(tempVec);
		}
	}		
	return subset;
}

string DTreeNode::toString()
{
	return "( " + attr + " " + relop + " " + value + " )";
	string ret;// = "The data:\n";
	if (!set.empty())
		for (list<vector<string> >::iterator it = set.begin(); it != set.end(); it++)
		{
			for (int j = 0; j < it->size(); j++)
				ret += it->at(j) + " ";
			ret += "\n";
		}
	ret += "children:\n-----------------\n"; 
	if (children != NULL)
		for (int j = 0; j < children->size(); j++)
		{
			ret += "\tChild: " + children->at(j)->attr;
			ret += children->at(j)->toString();
			ret += "\n\n";
		}
	ret += "-----------------\n"; 			
	return ret;
}