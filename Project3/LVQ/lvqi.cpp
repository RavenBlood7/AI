#include "lvqi.h"

LVQI::LVQI(string dataFileName, int numClusters, string testFileName, int numIterations)
{
    this->numIterations = numIterations;
    trainSet = new PatternSet(dataFileName);
    trainSet->randomize();
    testSet = new PatternSet(testFileName);
    nn = new Network(trainSet->numInputs(), numClusters);
}

LVQI::~LVQI()
{
    delete trainSet;
    delete testSet;
    delete nn;
}


void LVQI::train()
{

}

string LVQI::toString()\
{

}

void LVQI::toFile(string outputFile)
{

}
