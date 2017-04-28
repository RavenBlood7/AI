#include <iostream>
#include "DiscreteDT.h"
#include "ContinuousDT.h"

using namespace std;

void usage();

int main(int argc, char *argv[])
{
	//Check arguments and all that
	if (argc != 4)
	{		
		cout << "Error: invalid number of arguments." << endl;
		usage();
		return(1);
	}
	
	//Induce proper decision tree
	DecisionTree* tree;
	string option = argv[1];
	string specFile = argv[2];
	string dataFile = argv[3];
	if (option == "-d")
	{
		tree = new DiscreteDT(specFile, dataFile);
		tree->induceNoMissing();
	}
	else if (option == "-c")
	{
		tree = new ContinuousDT(specFile, dataFile);
		tree->induceNoMissing();
	}
	else if (option == "-md")
	{
		tree = new DiscreteDT(specFile, dataFile);
		tree->induceWithMissing();		
	}
	else if (option == "-mc")
	{
		tree = new ContinuousDT(specFile, dataFile);
		tree->induceWithMissing();		
	}
	else if (option == "-pd")
	{
		tree = new DiscreteDT(specFile, dataFile);
		tree->induceNoMissing();		
		tree->prune();
	}
	else if (option == "-pc")
	{
		tree = new ContinuousDT(specFile, dataFile);
		tree->induceNoMissing();		
		tree->prune();		
	}
	else
	{
		cout << "Error: no such option: " << option << endl;
		usage();
		return 1;
	}
	tree->toFile("data.out");
	cout << tree->toString();
	
	delete tree;
	return 0;
}

void usage()
{
	cout << "Usage: ./DecisionTree <option> <specfile> <datafile>" << endl;
	cout << "\toptions are:" << endl;
	cout << "\t-d" << endl;
	cout << "\t-c" << endl;
	cout << "\t-md" << endl;
	cout << "\t-mc" << endl;
	cout << "\t-pd" << endl;
	cout << "\t-pc" << endl;
}