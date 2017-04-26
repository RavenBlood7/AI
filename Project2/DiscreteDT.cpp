#include "DiscreteDT.h"

DiscreteDT::DiscreteDT(string specFile, string dataFile) : DecisionTree(specFile, dataFile)
{
	
}

void DiscreteDT::induceNoMissing()
{
/////////////////////////////
//cout << "in DT induceNoMissing: " << endl;	
	divideAndConquer(root);
/////////////////////////////
//cout << "out DT induceNoMissing: " << endl;	
}

void DiscreteDT::induceWithMissing()
{
	
}

void DiscreteDT::prune()
{
	
}

//private recursive functions
void DiscreteDT::divideAndConquer(DTreeNode *node)
{
/////////////////////////////
//cout << "in DT divAndC: " << endl;		
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
/////////////////////////////
//cout << "\t\tinfo gain on: "<< structure->getAttribute(i) << endl;							
//cout << "\t\t#info gain: "<< gain << endl;				
			
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
/////////////////////////////
cout << "split on: " << structure->getAttribute(index) << endl;			
cout << "\tbecause of maximum info gain: " << max << endl;			
cout << "\tnode: " << node->toString() << endl;	
		if (max == 0) return;
		node->split(structure->getAttribute(index), index, structure->getAttributeValues(structure->getAttribute(index)));
	}
	//call recursively
	vector<DTreeNode*>* children = node->getChildren();
	for (int i = 0; i < children->size(); i++)
	{
		divideAndConquer(children->at(i));
	}
/////////////////////////////
//divideAndConquer(children->at(0));	
//cout << "##################calling root child one " << endl;
//divideAndConquer(root->getChildren()->at(0));	
//cout << "##################calling root child child one "<< root->getChildren()->at(0)->getChildren()->at(0)->toString()<< endl;
//divideAndConquer(root->getChildren()->at(0)->getChildren()->at(0));	
	
//cout << "out DT divAndC: " << endl;			
}

float DiscreteDT::informationGain(DTreeNode *node, string attribute)
{
/////////////////////////////
//cout << "in informationGain" << endl;
	return entropy(node, structure->getNumAttributes()) - averageEntropy(node, attribute);
/////////////////////////////
//cout << "out informationGain" << endl;	
}

float DiscreteDT::entropy(DTreeNode *node, int index)
{
/////////////////////////////
//cout << "in entropy: " << index << endl;
	if (node->getSize() == 0) return 0;
	vector<string> classNames = structure->getClassValues();
	float sum = 0;
	float P= 0;
	for (int i = 0; i < structure->getNumClassValues(); i++)
	{
/////////////////////////////
//cout << "\tin entropy for: " << index << endl;		
		P = node->frequency(index, classNames.at(i));//last column
/////////////////////////////
//cout << "\tin entropy for: " << classNames.at(i) << endl;		
		P = P / node->getSize();
		if (P != 0)
			sum += P * log2(P);
	}	
/////////////////////////////
//cout << "out entropy: " << (-1 * sum) << endl;	
	return -1 * sum;
}

float DiscreteDT::averageEntropy(DTreeNode* node, string attribute)
{
/////////////////////////////
//cout << "in averageEntropy: " << attribute << endl;
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
		
/////////////////////////////
//cout << "/////////////////////////////////////////////////////////////" << endl;		
//cout << "subset: " << subset->toString() << endl;	
//cout << "/////////////////////////////////////////////////////////////" << endl;			
		sum += P * entropy(subset, structure->getNumAttributes());		
		delete subset;
	}
/////////////////////////////
//cout << "out averageEntropy: " << attribute << endl;	
//cout << "\t--: " << sum << endl;	
	return sum;
}