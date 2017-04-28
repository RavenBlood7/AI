#include "DTreeNode.h"

DTreeNode::DTreeNode()
{
	children = NULL;
}

DTreeNode::~DTreeNode()
{
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
}
void DTreeNode::splitMissing(string attr, int index, vector<string> attributeValues)
{
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
	int setSize = set.size();
	float probWeight;
	DTreeNode * known = this->subsetNoMissing(index);
	DTreeNode * numerator;
	int sumWeights;
	int knownSize = known->getSize();
	//for each case
	for (int i = 0; i < setSize; i++)
	{	
		//if the value is missing
		if (!set.empty() && set.front().at(index)  == "?")
		{
			//for each attribute
			for (int j = 0; j < size; j++)
			{
				
				//find ratio
				sumWeights = 0;
				numerator = known->subset(index, attributeValues.at(j));
				for (int k = 0; k < numerator->getSize(); k++)
				{
					sumWeights += numerator->probabilities.at(k);
				}
				probWeight = sumWeights / knownSize;
				delete numerator;
				
				//put case and probWeight in attribute
				children->at(j)->addCase(set.front());
				set.pop_front();
				children->at(j)->probabilities.pop_back();
				children->at(j)->probabilities.push_back(probWeight);
				probabilities.erase(probabilities.begin());
			}
		} 
		else
		//for each attribute
		for (int j = 0; j < size; j++)
		{	
			if (!set.empty() && set.front().at(index) == attributeValues.at(j))
			{				
				children->at(j)->addCase(set.front());	
				set.pop_front();
				probabilities.erase(probabilities.begin());
				break;
			}
		}
	}	
	
	delete known;
}

void DTreeNode::unsplit()
{
	//find maximum
	int size;
	int maxSize = children->at(0)->getSize();
	for (int i = 1; i < children->size(); i++)
	{
		size = children->at(i)->set.size();
		if (maxSize < size)
			maxSize = size;
	}
	int counter;
	for (counter = 0; counter < children->size(); counter++)
	{
		size = children->at(counter)->set.size();
		if (maxSize == size)
			break;		
	}
	//update this node's class
	splitAttr = children->at(counter)->getClass();
	attr = children->at(counter)->attr;
	relop = children->at(counter)->relop;
	value = children->at(counter)->value;
	
	//delete children
	for (int i = 0; i < children->size(); i++)
	{
		//note: copying cases back to parent!
		for (int j = 0; j < children->at(i)->set.size(); j++)
		{
			addCase(children->at(i)->set.front());
			children->at(i)->set.pop_front();
		}
		delete (children->at(i));
	}
	delete children;
	children = NULL;
}

void DTreeNode::addCase(vector<string> newCase)
{
	set.push_back(newCase);
	probabilities.push_back(1);
}

void DTreeNode::addProbCase(vector<string> newCase)
{
	set.push_back(newCase);
	probabilities.push_back(1);
}

float DTreeNode::sumProb()
{
	float sum = 0;
	for (int j = 0; j < probabilities.size(); j++)
	{	
		sum += probabilities.at(j);
	}	
	return sum;
}

vector<string> DTreeNode::popCase()
{
	vector <string> tempVec = set.front();
	set.pop_front();
	if (!probabilities.empty())
		probabilities.erase(probabilities.begin());
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

void DTreeNode::setSplitAttr(string split)
{
	splitAttr = split;
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
	else return splitAttr;
}

string DTreeNode::getClass()
{
	if (!set.empty())
		return set.front().at(set.front().size() - 1);
	else return splitAttr;	
}

string DTreeNode::getAttr()
{
	return attr;
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
	int total = 0;
	for (list<vector<string> >::iterator it = set.begin(); it != set.end(); it++)
	{
		if (it->at(index) == value)
			total++;
	}	
	return total;
}

DTreeNode* DTreeNode::subset(int index, string value)
{
	DTreeNode* subset = new DTreeNode();
	vector<string> tempVec;
	int i = 0;
	for (list<vector<string> >::iterator it = set.begin(); it != set.end(); it++)
	{
		if (it->at(index) == value)
		{
			tempVec = *it;	//might be shallow copy
			subset->addCase(tempVec);
			if (!probabilities.empty())
				subset->probabilities.push_back(probabilities.at(i));
		}
		i++;
	}		
	return subset;
}

DTreeNode* DTreeNode::subsetNoMissing(int index)
{
	DTreeNode* subset = new DTreeNode();
	vector<string> tempVec;
	int i = 0;
	for (list<vector<string> >::iterator it = set.begin(); it != set.end(); it++)
	{
		if (it->at(index) != "?")
		{
			tempVec = *it;	//might be shallow copy
			subset->addCase(tempVec);
			if (!probabilities.empty())
				subset->probabilities.push_back(probabilities.at(i));
		}
		i++;
	}		
	return subset;	
}

bool DTreeNode::onlyLeafChildren()
{
	bool onlyChildren = true;
	for (int i = 0; i < children->size(); i++)
	{
		if (!children->at(i)->isLeaf())
		{
			onlyChildren = false;
			break;
		}
	}
	return onlyChildren;
	
}
DTreeNode* DTreeNode::clone()
{
	DTreeNode *newNode = new DTreeNode();
	if (!isLeaf())
	{
		newNode->children = new vector<DTreeNode*>();
		for (int i = 0; i < children->size(); i++)
		{
			newNode->children->push_back(children->at(i)->clone());
		}
	}
	else
	{
		newNode->children = NULL;
	}
	
	newNode->set = set;
	newNode->splitAttr = splitAttr;
	newNode->attr = attr;
	newNode->relop = relop;
	newNode->value = value;
	newNode->probabilities = probabilities;
	
	return newNode;
	
}

string DTreeNode::toString()
{
	return "( " + attr + " " + relop + " " + value + " )";
	string ret = "\n";// = "The data:\n";
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