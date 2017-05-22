#ifndef COMPETATIVE_LVQI_H
#define COMPETATIVE_LVQI_H


#include "lvqi.h"

class Competative_LVQI : public LVQI
{
public:
    Competative_LVQI(string dataFileName, int numClusters, string testFileName, int numIterations);
    void train();
};

#endif // COMPETATIVE_LVQI_H
