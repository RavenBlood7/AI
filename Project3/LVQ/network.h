#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <vector>

using namespace std;

class Network
{
private:
    int numInputs;
    int numClusters;
    vector< vector<float> > weights;

public:
    Network(int numInputs, int numClusters);
    float getWeight(int input, int cluster);
    float setWeight(int input, int cluster, float weight);
};

#endif // NETWORK_H
