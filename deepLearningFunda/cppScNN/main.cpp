#include <iostream>
#include <vector>

#include "headers\NeuralNetwork.hpp"
#include "headers\RandomVecGenerator.hpp"

int main(int argc, char** argv) {
    RandomVecGenerator generator;
    auto& randomInput { generator.getRandomNumbers(100) };
    
    argc;
    argv;

    NeuralNetwork network(randomInput, 10);
    
    network.addHiddenLayer(10,10);
    network.addHiddenLayer(10,10);

    network.doForwardPass();

    return 0;
}
