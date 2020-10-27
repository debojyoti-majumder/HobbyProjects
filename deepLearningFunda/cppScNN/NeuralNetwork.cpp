#include "headers\NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(vector<float> inputValues, size_t outputLength) :
                inputLayer(inputValues, inputValues.size() ),  
                outputLayer(inputLayer, outputLength) 
{

}

// TODO: To add actual impelementation, should be retruning a layer instead
bool NeuralNetwork::addHiddenLayer(size_t inputLength, size_t outputLength) {
    return true;
}

// TODO: Add actual impl
vector<float> NeuralNetwork::doForwardPass() {
    return vector<float> {};
}