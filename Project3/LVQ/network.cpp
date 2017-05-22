#include "network.h"


Network::Network(int numInputs, int numClusters)
{
    this->numInputs = numInputs;
    this->numClusters = numClusters;
}

float Network::getWeight(int input, int cluster)
{
    return weights[input][cluster];
}

float Network::setWeight(int input, int cluster, float weight)
{

}
