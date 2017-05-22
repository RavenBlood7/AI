#include "patternset.h"

PatternSet::PatternSet(string fileName)
{
    ifstream inFile(fileName.c_str());
    set = new vector< vector<float> >();
    if (inFile.is_open())
    {
        stringstream tempStream;
        string line;
        float tempFloat;
        vector<float> tempVec;
        for (int i = 0; getline(inFile, line); i++)
        {
            set->push_back(tempVec);
            tempStream.clear();
            tempStream << line;

            while (tempStream >> tempFloat)
            {
                set->at(i).push_back(tempFloat);
            }
        }
        inFile.close();
    }
    else
    {
        cout << "Error opening file: " << fileName << endl;
    }
}

PatternSet::~PatternSet()
{
    delete set;
}

int myrandom (int i) { return std::rand()%i;}
void PatternSet::randomize()
{
    std::srand ( unsigned ( std::time(0) ) );
    random_shuffle(set->begin(), set->end(), myrandom);
}

int PatternSet::numInputs()
{
    if (set->size() > 0)
        return set->at(0).size();
    return -1;
}

vector<float> PatternSet::getPatternAt(int index)
{
    return set->at(index);
}
