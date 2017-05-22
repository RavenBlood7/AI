#ifndef LVQI_H
#define LVQI_H

#include <iostream>
#include "patternset.h"
#include "network.h"

using namespace std;
class LVQI
{
protected:
    int numIterations;
    PatternSet* trainSet;
    PatternSet* testSet;
    Network* nn;

public:
    LVQI(string dataFileName, int numClusters, string testFileName, int numIterations);
    ~LVQI();

    virtual void train();
    string toString();
    void toFile(string outputFile);
};

#endif // LVQI_H
