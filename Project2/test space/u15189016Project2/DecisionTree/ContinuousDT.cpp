#include "ContinuousDT.h"

ContinuousDT::ContinuousDT(string specFile, string dataFile) : DecisionTree(specFile, dataFile)
{
	
}

void ContinuousDT::induceNoMissing()
{
	this->divideAndConquer(root);
}

void ContinuousDT::induceWithMissing()
{
	
}

void ContinuousDT::prune()
{
	recursivePrune(root);	
}
////////////////////////NO MISSING VALUES///////////////////////////////////////
void ContinuousDT::divideAndConquer(DTreeNode* node)
{
	cout << "Considering node: " << node->toString() << endl;	
	//check if T is empty
	if (node->getSize() == 0)
	{
		node->setSplitAttr(structure->getClassValues().at(rand() % structure->getNumClassValues()));
		//assign class
		return;
	}
	//check if T contains only a single class
	if (!node->multipleClasses())
	{
		//assign class to node
		//node->setDescription();
		return;
	}
	//check if T has different cases
	else
	{		
		//calulate information gain on each attribute
		vector<string> attributes = structure->getAttributes();
		vector<string> attributeValues;
		vector<float> infoGain;
		float gain;
		int size = attributes.size();
		vector<float> values;
		//for each attribute:
		for (int i = 0; i < size; i++)
		{
			//add information gain	
			
			gain = informationGain(node, structure->getAttribute(i));	
			cout << "\tCalculated information gain: " << gain << endl;
			if (structure->getAttributeValues(structure->getAttribute(i)).at(0) == "Real")
			{
				values.push_back(curValue);
			} else values.push_back(0);
			infoGain.push_back(gain);
			
		}	

		//find highest information gain
		float max = infoGain.at(0);
		for (int i = 1; i < size; i++)
		{
			if (infoGain.at(i) > max)
				max = infoGain.at(i);
		}	
		if (max == -100) return;
		int index = 0;
		for (int i = 0; i < size; i++)
		{
			if (infoGain.at(i) == max)
			{
				index = i;
				break;
			}
		}			
		//split on that attribute		
		if (max == 0) return;
		if (structure->getAttributeValues(structure->getAttribute(index)).at(0) == "Real")
		{		
			node->splitContinuous(structure->getAttribute(index), values.at(index), index);
		}
		else 
		{
			node->split(structure->getAttribute(index), index, structure->getAttributeValues(structure->getAttribute(index)));
		}
	}
	//call recursively
	vector<DTreeNode*>* children = node->getChildren();
	for (int i = 0; i < children->size(); i++)
	{
		divideAndConquer(children->at(i));
	}	
}

float ContinuousDT::informationGain(DTreeNode *node, string attribute)
{
	if (structure->getAttributeValues(attribute).at(0) == "Real")
		return continuousInfoGain(node, attribute);
	else
		return entropy(node, structure->getNumAttributes()) - averageEntropy(node, attribute);	
}

float ContinuousDT::continuousInfoGain(DTreeNode* node, string attribute)
{
	//get vector of all possible values
	vector<float> possibleValues = node->getPossibleValues(structure->getIndex(attribute));
	//sort this vector
	sort(possibleValues.begin(), possibleValues.end());
	
	//create another vector to store test values
	vector<float> testValues;
	for (int i = 0; i < possibleValues.size() - 1; i++)//maybe check for empty set
	{
		testValues.push_back((possibleValues.at(i) + possibleValues.at(i + 1)) / 2);
	}
	if (testValues.size() < 2) return 0;	
	
	//for all values in the second vector
	float currentEntropy = entropy(node, structure->getNumAttributes());
	if (currentEntropy == 0) return 0;
	float maxGain = -100;
	float curGain;
	
	for (int i = 0; i < testValues.size(); i++)
	{
		//evaluate info gain on that single split
		curGain = currentEntropy - entropyCont(node, testValues.at(i), structure->getIndex(attribute));
		//get maximum of currentMax and that attribute
		if (curGain > maxGain) 
		{
			curValue = testValues.at(i);
			maxGain = curGain;
		}
	}
	//return maximum information gain
	return maxGain;
}

float ContinuousDT::entropyCont(DTreeNode* node, float value, int index)
{
	//node would be split into two subsets:
	//those less than or equal to value, and the rest
	//add entropy of both of these multiplied with appropriate fraction
	float sum = 0;
	int freq = node->frequencyLessThanEq(index, value);		
	float P = 1.0 * freq / node->getSize();
	DTreeNode* subset = node->subsetLessThanEq(index, value);
	sum +=  P * entropy(subset, structure->getNumAttributes());
	delete subset;
	
	freq = node->getSize() - freq;
	P = 1.0 * freq / node->getSize();		
	subset = node->subsetGreaterThan(index, value);
	sum +=  P * entropy(subset, structure->getNumAttributes());
	delete subset;		
	return sum;
}

float ContinuousDT::entropy(DTreeNode *node, int index)
{
	if (node->getSize() == 0) return 0;
	vector<string> classNames = structure->getClassValues();
	float sum = 0;
	float P= 0;
	for (int i = 0; i < structure->getNumClassValues(); i++)
	{
		P = node->frequency(index, classNames.at(i));//last column
		P = P / node->getSize();
		if (P != 0)
			sum += P * log2(P);
	}	
	return -1 * sum;	
}
	
float ContinuousDT::averageEntropy(DTreeNode* node, string attribute)
{
	vector<string> attributeValues = structure->getAttributeValues(attribute);	
	DTreeNode *subset;
	float sum = 0;
	float P;	//number of instances of the current attributeValue
			//divided by the total number of cases in set
			//ie gets proportion of set that is of one attributeValue
	for (int i = 0; i < attributeValues.size(); i++)
	{
		P = node->frequency(structure->getIndex(attribute), attributeValues.at(i));
		P = P / node->getSize();
				
		//partition set into a subset of 
		subset = node->subset(structure->getIndex(attribute), attributeValues.at(i));
		sum += P * entropy(subset, structure->getNumAttributes());		
		delete subset;
	}
	return sum;	
}

////////////////Classification/////////////////////////////////

bool ContinuousDT::classify(vector<string> oneCase)
{
/////////////////////////		
cout << "classifying:\n\t";	
	for (int i = 0; i < oneCase.size(); i++)
	{
		cout << oneCase.at(i) << " ";
	}			
	cout << endl;
////////////////////////	
	stringstream tempStream;	
	float tempValue;
	float tempValue2;
	DTreeNode* ptr = root;
	string attr = "";
	char relop;
	vector<string> attrValues;
	if (ptr != NULL)
	while (!ptr->isLeaf())
	{			
		attr = ptr->getChildren()->at(0)->getAttr();
		
		attrValues = structure->getAttributeValues(attr);
		if (attrValues.size() == 0) return false;
		
		if (attrValues.at(0) == "Real")
		{
				tempStream.clear();
				tempStream.str(std::string());
				tempStream << oneCase.at(structure->getIndex(attr));
				tempStream >> tempValue;
				tempStream.clear();
				tempStream.str(std::string());
				tempStream << ptr->getChildren()->at(0)->getValue();
				tempStream >> tempValue2;
				if (tempValue < tempValue2)
				{
					ptr = ptr->getChildren()->at(0);
				}
				else
				{					
					ptr = ptr->getChildren()->at(1);
				}
		}
		else
		{
		attr = ptr->getChildren()->at(0)->getAttr();			
			for (int i=0; i < ptr->getChildren()->size(); i++)
			{
				if (attrValues.at(i) == oneCase.at(structure->getIndex(attr)))
				{
					ptr = ptr->getChildren()->at(i);
					break;
				}
			}
		}
	}

	return ptr->getClass(structure->getNumAttributes()) == oneCase.at(structure->getNumAttributes());
}

float ContinuousDT::classificationError(DTreeNode* set)
{
	DTreeNode *temp = set->clone();
	int size = set->getSize();
	if (size == 0) return 0;
	int count = 0;
	while (temp->getSize() > 0)
	{
		//count errors
		if (!classify(temp->popCase()))
		{
			count++;
		}
	}
	delete temp;
	return 1.0 * count / size;
}

/////////////////////PRUNE/////////////////////////////
DTreeNode* ContinuousDT::recursivePrune(DTreeNode *node)
{
	
///////////////////////////////////////////////////////
cout << "in pruning function: consider to prune: " << node->toString()<< endl;		
	//root
	if (node == root && node->isLeaf())
	{
	///////////////////////////////////////////////////////
cout << "\tcase0: root is leaf " << endl;			
		return NULL;
	}
	if (node->isLeaf())
	{
	///////////////////////////////////////////////////////
cout << "\tcase1: leaf " << endl;					
		return node;
	}
	else if (!node->onlyLeafChildren())
	{		
	///////////////////////////////////////////////////////
cout << "\tcase2: not only leaf children" << endl;			
		//recursive prune all children
		for (int i = 0; i < node->getChildren()->size(); i++)
		{
			node->getChildren()->at(i) = recursivePrune(node->getChildren()->at(i));
		}
		//if change to only leaf children
		if (node->onlyLeafChildren())
			return recursivePrune(node);
	}
	//if only leaf children
	else if (node->onlyLeafChildren())
	{
///////////////////////////////////////////////////////
cout << "\tcase3: only leaf children" << endl;				
		DTreeNode* subtree = node->clone();		
		float before = classificationError(testSet);
		node->unsplit();
		float after = classificationError(testSet);

///////////////////////////////////////////////////////
cout << "\tcase3: error: " << after - before << endl;			
		//if deteriorate > 5%
		if ((after - before) > 0.05)
		{
			delete node;
			node = subtree;
			return node;
		}			
		else
		{
			return node;
		}
	}
}