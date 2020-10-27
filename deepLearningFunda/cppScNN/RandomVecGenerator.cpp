#include "headers/RandomVecGenerator.hpp"

RandomVecGenerator::RandomVecGenerator() : _gen(_rd()) {

}

vector<float> RandomVecGenerator::getRandomNumbers(size_t count) {
    vector<float> randomNumbers;

    std::uniform_real_distribution<> dist(0, 1000);

    for( size_t i=0; i<=count; i++ ) {
        int num = dist(_gen);
        randomNumbers.emplace_back(num / 1000.0f);    
    }

    return randomNumbers;
}