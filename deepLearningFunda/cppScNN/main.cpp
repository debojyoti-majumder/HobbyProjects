#include <iostream>
#include <vector>

#include "headers\NeuralNetwork.hpp"
#include "headers\RandomVecGenerator.hpp"

int main(int argc, char** argv) {
    RandomVecGenerator generator;
    auto& randomInput { generator.getRandomNumbers(100) };
    
    argc;
    argv;

    // 10 being the number of calsses
    NeuralNetwork network(randomInput, 10);

    // The input layer output needs to change accordingly    
    network.addHiddenLayer(50,25);

    // The second argument be the same as the number of classes for now
    network.addHiddenLayer(25,10);

    network.doForwardPass();

    return 0;
}
