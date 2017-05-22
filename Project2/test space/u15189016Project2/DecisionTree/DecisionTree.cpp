#include "DecisionTree.h"

DecisionTree::DecisionTree(string specFile, string dataFile)
{
	structure = new Structure(specFile);
	initializeRoot(dataFile);
}

DecisionTree::~DecisionTree()
{
	delete root;
	delete trainingSet;
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
			root->addProbCase(tempVec);
			tempVec.clear();
		}
		
		//randomize data	
		root->randomize();
		trainingSet = root->clone();
		
		//place top  30% in test set
		testSet = new DTreeNode();
		int trainNum = 0.3 * root->getSize();
		for (int i = 0; i < trainNum; i++)
		{
			testSet->addProbCase(root->popCase());
			trainingSet->popCase();
		}
	}
	else
	{
		cout << "Error opening file: " << dataFile << endl;
	}
}

string DecisionTree::toString()
{
	stringstream tempStream;
	string ret = "The decision tree:\n";
	ret += "problem structure:\n" + structure->toString();
	
	//classification errors on training set and test set
	tempStream << classificationError(trainingSet);
	ret += "\n\nTraining set classification error: " + tempStream.str() + "\n";
	tempStream.str("");
	tempStream << classificationError(testSet);
	ret += "Test set classification error: " + tempStream.str() + "\n";
	
	//rules
	ret += "\n\nRules:\n\n";
//	ret += "root: \n" + root->toString();
//	ret += "testSet: \n" + testSet->toString();
//	ret += "trainingSet: \n" + trainingSet->toString();

	if (root == NULL || root->getChildren() == NULL ||root->getChildren()->size() == 0) 
		return ret + "nothing to show\n";		
	ret += toString(root);

	//classification errors on training set and test set
	tempStream << classificationError(trainingSet);
	ret += "\n\nTraining set classification error: " + tempStream.str() + "\n";
	tempStream.str("");
	tempStream << classificationError(testSet);
	ret += "Test set classification error: " + tempStream.str() + "\n";	

	return ret;
}

string DecisionTree::toString(DTreeNode* node)
{		
	string ret = "";
	if (root->isLeaf()) return "root is leaf";
	if (node != NULL)
	{
		if (node->isLeaf())
		{
			//the actual rule
			ret += "IF ";
			int size = displayStack.size();
			for (int i = 1; i < size ; i++)
			{
				ret += displayStack.at(i)->toString() + " AND ";
			}
			ret += node->toString();
			ret += " THEN " + structure->getClassName() + " is " + node->getClass(structure->getNumAttributes()) + "\n";
			
			//classification error on test set
			stringstream tempStream;			
			tempStream << classificationError(node);
			ret += "\tclassification error on training set: " + tempStream.str() + "\n";
								
			//classification error on test set
			DTreeNode* tempSet = testSet->clone();
			DTreeNode* tempSet2 = new DTreeNode();
			vector<string> tempCase ;
			int count = 0;
			bool mustAdd;			
			while (tempSet->getSize() != 0)
			{
				tempCase = tempSet->popCase();
				mustAdd = true;
				for (int i = 1; i < displayStack.size(); i++)
				{
					if (displayStack.at(i)->getValue() == tempCase.at(i))
					{
						count++;
						mustAdd = false;
						break;
					}
				}				
				if (mustAdd)
				{	
					tempSet2->addCase(tempCase);
				}
			}
			tempStream.str("");
			tempStream << classificationError(tempSet2);
			ret += "\tclassification error on test set: " + tempStream.str() + "\n";
			delete tempSet;
			delete tempSet2;
								
			//number of data patterns associated with this rule
			tempStream.str("");
			tempStream << node->getSize();
			ret += "\tnumber of data patterns: " + tempStream.str() + "\n";			
			
			//for each class: number of patterns associated with that class
			vector<string> classValues = structure->getClassValues();
			ret += "\tnumber of patterns for each class: \n";			
			for (int i = 0; i < structure->getNumClassValues(); i++)
			{
				tempSet = node->subset(structure->getNumAttributes(), classValues.at(i));								
				tempStream.str("");
				tempStream << (count + tempSet->getSize());
				ret += "\t\t" + classValues.at(i) + ": " + tempStream.str() + "\n";			
				delete tempSet;
			}
		}
		else
		{	
			displayStack.push_back(node);		
			vector<DTreeNode*>* children = node->getChildren();
			for (int i = 0; i < children->size(); i++)
			{
				ret += toString(children->at(i)) + "\n";
			}				
			displayStack.pop_back();
		}
	}
	return ret;
}

void DecisionTree::toFile(string outFile)
{
	ofstream out(outFile.c_str());
	
	if (out.is_open())
	{
		out << toString();
		out.close();
	}
	else
	{
		cout << "Error writing to file: " << outFile << endl;
	}
}


void DecisionTree::toFile(string outFile, bool prune)
{
	ofstream out(outFile.c_str());
	
	if (out.is_open())
	{
		out << "Original Tree:" << endl;
		out << "______________" << endl;
		out << toString();
		DecisionTree::prune();
		out << "______________" << endl;
		out << "Pruned Tree:" << endl;
		out << "______________" << endl;
		out << toString();
		out.close();
	}
	else
	{
		cout << "Error writing to file: " << outFile << endl;
	}	
}