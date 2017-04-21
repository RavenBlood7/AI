#include "Structure.h"

Structure::Structure(string specFile)
{
	ifstream inFile(specFile.c_str());
	if (inFile.is_open())
	{
		//set the class name and attributes
		stringstream tempStream;
		string temp;
		getline(inFile, temp);
		
		tempStream << temp;
		tempStream >> temp;
		className = temp.substr(0, temp.length() - 1);
				
		while (tempStream.rdbuf()->in_avail() != 0)
		{
			tempStream >> temp;
			classValues.push_back(temp);
		}
		
		//set the attributes and values
		string line;
		for (int i = 0; getline(inFile, line); i++)
		{						
			tempStream.clear();
			tempStream << line;

			tempStream >> temp;
			attributeList.push_back(temp.substr(0, temp.length() - 1));
			vector<string> emptyVec;
			attributeValueMatrix.push_back(emptyVec);
			for (int j = 0; tempStream.rdbuf()->in_avail() != 0; j++)
			{
				tempStream >> temp;
				if (temp != "{" && temp != "}")
				{
					if (temp.at(temp.length() - 1) == ',')
					{
						temp.erase(temp.length() - 1);
					}
					attributeValueMatrix.at(i).push_back(temp);
				}	
			}			
		}
		inFile.close();
		
		numClassValues = classValues.size();
		numAttributes = attributeList.size();
	}	
	else
	{
		cout << "Error opening file: " << specFile << endl;
	}				
}

int Structure::getNumClassValues()
{
	return numClassValues;
}

int Structure::getNumAttributes()
{
	return numAttributes;
}

int Structure::getNumAttributeValues(string attribute)
{
	for (int i = 0; i < numAttributes; i++)
	{
		if (attributeList.at(i) == attribute)
			return attributeValueMatrix.at(i).size();
	}
	return -1;
}

vector<string> Structure::getClassValues()
{
	return classValues;
}

vector<string> Structure::getAttributes()
{
	return attributeList;
}

vector<string> Structure::getAttributeValues(string attribute)
{
	for (int i = 0; i < numAttributes; i++)
	{
		if (attributeList.at(i) == attribute)
			return attributeValueMatrix.at(i);
	}
}

string Structure::toString()
{	
	string ret = "class name: " + className + "\n";
	ret += "class values:\n";		
	for (int i = 0; i < classValues.size(); i++)
	{
		ret += "\t" + classValues.at(i) + "\n";
	}		
	ret += "attributes:\n";	
	for (int i = 0; i < attributeList.size(); i++)
	{
		ret += "\t" + attributeList.at(i) + " ";	
			for (int j = 0; j < attributeValueMatrix.at(i).size(); j++)
			{
				ret += attributeValueMatrix.at(i).at(j);				
			}		
		ret += "\n";
	}		
	return ret;
	
}