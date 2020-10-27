#ifndef _RANDOMVECGENERATOR_H
#define _RANDOMVECGENERATOR_H

#include <vector>
#include <random>

using namespace std;

class RandomVecGenerator {
    private:
        random_device   _rd;
        mt19937         _gen;

    public:
        RandomVecGenerator();
        vector<float> getRandomNumbers(size_t count);
};

#endif