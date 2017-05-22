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
		cout << "inducing tree" << endl;
		cout << "\t\t---" << endl;
		tree->induceNoMissing();
		cout << "\t\t---" << endl;		
		cout << "writing to file..." << endl;
		cout << "\t\t---" << endl;
		tree->toFile("data.out");
		cout << tree->toString();
	}
	else if (option == "-c")
	{
		tree = new ContinuousDT(specFile, dataFile);
		cout << "inducing tree" << endl;
		cout << "\t\t---" << endl;
		tree->induceNoMissing();		
		cout << tree->toString();
		cout << "\t\t---" << endl;
		cout << "writing to file..." << endl;
		cout << "\t\t---" << endl;
		tree->toFile("data.out");		
		cout << tree->toString();
	}
	else if (option == "-md")
	{
		tree = new DiscreteDT(specFile, dataFile);
		cout << "inducing tree" << endl;
		cout << "\t\t---" << endl;
		tree->induceWithMissing();				
		cout << tree->toString();
		cout << "\t\t---" << endl;
		cout << "writing to file..." << endl;
		cout << "\t\t---" << endl;
		tree->toFile("data.out");		
		cout << tree->toString();
	}
	else if (option == "-mc")
	{
		tree = new ContinuousDT(specFile, dataFile);
		cout << "inducing tree" << endl;
		cout << "\t\t---" << endl;
		tree->induceWithMissing();				
		cout << tree->toString();
		cout << "\t\t---" << endl;
		cout << "writing to file..." << endl;
		cout << "\t\t---" << endl;
		tree->toFile("data.out");		
		cout << tree->toString();
	}
	else if (option == "-pd")
	{
		tree = new DiscreteDT(specFile, dataFile);
		cout << "inducing tree" << endl;
		cout << "\t\t---" << endl;
		tree->induceNoMissing();	
		cout << tree->toString();	
		tree->toFile("data.out", true);
		cout << "\t\t---" << endl;
		cout << "pruning tree" << endl;
		cout << "\t\t---" << endl;
		tree->prune();		
		cout << tree->toString();
		cout << "\t\t---" << endl;
		cout << "writing to file..." << endl;
		cout << "\t\t---" << endl;
	}
	else if (option == "-pc")
	{
		tree = new ContinuousDT(specFile, dataFile);
		cout << "inducing tree" << endl;
		cout << "\t\t---" << endl;
		tree->induceNoMissing();
		cout << tree->toString();
		tree->toFile("data.out", true);		
		cout << "\t\t---" << endl;
		cout << "pruning tree" << endl;		
		cout << "\t\t---" << endl;
		tree->prune();			
		cout << tree->toString();	
		cout << "\t\t---" << endl;
		cout << "writing to file..." << endl;
		cout << "\t\t---" << endl;
	}
	else
	{
		cout << "Error: no such option: " << option << endl;
		usage();
		return 1;
	}
	
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