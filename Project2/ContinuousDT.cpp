#include "ContinuousDT.h"

ContinuousDT::ContinuousDT(string specFile, string dataFile) : DecisionTree(specFile, dataFile)
{
	
}

void ContinuousDT::induceNoMissing()
{
	
}

void ContinuousDT::induceWithMissing()
{
	
}

void ContinuousDT::prune()
{
	
}


bool ContinuousDT::classify(vector<string> oneCase)
{
	return false;
}

float ContinuousDT::classificationError(DTreeNode* set)
{
	return 0;
}