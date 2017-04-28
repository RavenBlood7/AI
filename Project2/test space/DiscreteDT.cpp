#include "DiscreteDT.h"

DiscreteDT::DiscreteDT(string specFile, string dataFile) : DecisionTree(specFile, dataFile)
{
	
}

void DiscreteDT::induceNoMissing()
{
	divideAndConquer(root);
}

void DiscreteDT::induceWithMissing()
{
	divideAndConquerMissing(root);
}

void DiscreteDT::prune()
{
	recursivePrune(root);
}

void DiscreteDT::divideAndConquer(DTreeNode *node)
{
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
		//for each attribute:
		for (int i = 0; i < size; i++)
		{
			//add information gain	
			gain = informationGain(node, structure->getAttribute(i));			
			infoGain.push_back(gain);
		}	

		//find highest information gain
		float max = infoGain.at(0);
		for (int i = 1; i < size; i++)
		{
			if (infoGain.at(i) > max)
				max = infoGain.at(i);
		}	
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
		node->split(structure->getAttribute(index), index, structure->getAttributeValues(structure->getAttribute(index)));
	}
	//call recursively
	vector<DTreeNode*>* children = node->getChildren();
	for (int i = 0; i < children->size(); i++)
	{
		divideAndConquer(children->at(i));
	}
}

float DiscreteDT::informationGain(DTreeNode *node, string attribute)
{	
	return entropy(node, structure->getNumAttributes()) - averageEntropy(node, attribute);
}

float DiscreteDT::entropy(DTreeNode *node, int index)
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

float DiscreteDT::averageEntropy(DTreeNode* node, string attribute)
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

bool DiscreteDT::classify(vector<string> oneCase)
{
	bool missing = false;
	for (int i = 0; i < oneCase.size(); i++)
	{
		if (oneCase.at(i) == "?")
		{
			missing = true;
			break;
		}
	}			
	
	DTreeNode* ptr;
	//no missing values
	if (!missing)
	{		
		ptr = root;
		string attr = "";
		vector<string> attrValues;
		if (ptr != NULL)
		while (!ptr->isLeaf())
		{			
			attr = ptr->getChildren()->at(0)->getAttr();
			attrValues = structure->getAttributeValues(attr);
			if (attrValues.size() == 0) return false;
			
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
	else
	{
	//missing values
		ptr = root;
		string attr = "";
		vector<string> attrValues;
		if (ptr != NULL)
		while (!ptr->isLeaf())
		{
			attr = ptr->getChildren()->at(0)->getAttr();
			attrValues = structure->getAttributeValues(attr);
			for (int i=0; i < attrValues.size(); i++)
			{
				if (attrValues.at(i) == oneCase.at(structure->getIndex(attr)))
				{
					ptr = ptr->getChildren()->at(i);
					break;
				}
				else if (oneCase.at(structure->getIndex(attr)) == "?")
				{
					//for each attribute / child, check for highest probability
					float max = ptr->getChildren()->at(0)->sumProb();
					for (int j=1; j < attrValues.size(); j++)
					{
						if (max < ptr->getChildren()->at(j)->sumProb())
							max = ptr->getChildren()->at(j)->sumProb();
					
					}
					
					//pick maximum					
					int counter;
					for (counter=0; counter < ptr->getChildren()->size(); counter++)
					{
						if (max == ptr->getChildren()->at(counter)->sumProb())
							break;
					}										
					ptr = ptr->getChildren()->at(counter );				
					break;					
				}
			}
		}		
	}

	return ptr->getClass(structure->getNumAttributes()) == oneCase.at(structure->getNumAttributes());
}

float DiscreteDT::classificationError(DTreeNode* set)
{
	DTreeNode *temp = set->clone();
	int size = set->getSize();
	int count = 0;
	while (temp->getSize() > 0)
	{
		//count errors
		if (!classify(temp->popCase()))
		{
			count++;
		}
	}
	return 1.0 * count / size;
}

/////////////////////MISSING VALUES/////////////////////////////
void DiscreteDT::divideAndConquerMissing(DTreeNode *node)
{
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
		//for each attribute:
		for (int i = 0; i < size; i++)
		{
			//add information gain	
			gain = informationGainMissing(node, structure->getAttribute(i));
			infoGain.push_back(gain);
		}	

		//find highest information gain
		float max = infoGain.at(0);
		for (int i = 1; i < size; i++)
		{
			if (infoGain.at(i) > max)
				max = infoGain.at(i);
		}	
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
		node->splitMissing(structure->getAttribute(index), index, structure->getAttributeValues(structure->getAttribute(index)));
	}
	//call recursively
	vector<DTreeNode*>* children = node->getChildren();
	for (int i = 0; i < children->size(); i++)
	{
		divideAndConquerMissing(children->at(i));
	}
}

float DiscreteDT::informationGainMissing(DTreeNode *node, string attribute)
{	
	DTreeNode* noMissing = node->subsetNoMissing(structure->getIndex(attribute));
	int size = noMissing->getSize() ;
	float gain = informationGain(noMissing, attribute);
	delete noMissing;
	return 1.0 * size / node->getSize() * gain;
}

/////////////////////PRUNE/////////////////////////////
DTreeNode* DiscreteDT::recursivePrune(DTreeNode *node)
{
	//root
	if (node == root && node->isLeaf())
	{
		return NULL;
	}
	if (node->isLeaf())
	{
		return node;
	}
	else if (!node->onlyLeafChildren())
	{
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
		DTreeNode* subtree = node->clone();		
		float before = classificationError(testSet);
		node->unsplit();
		float after = classificationError(testSet);
		
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