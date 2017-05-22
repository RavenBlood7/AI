#ifndef PATTERNSET_H
#define PATTERNSET_H

#include <iostream>
#include <list>
#include <vector>

#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

class PatternSet
{
private:
    vector< vector<float> >* set;

public:
    PatternSet(string fileName);
    ~PatternSet();

    void randomize();
    int numInputs();

    vector<float> getPatternAt(int index);
};

#endif // PATTERNSET_H
