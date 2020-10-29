#include "headers\NeuralNetwork.hpp"

// Both the input and output layer would be passthrough
NeuralNetwork::NeuralNetwork(vector<float> inputValues, size_t outputLength) :
                _inputLayer(inputValues, inputValues.size() , true),  
                _outputLayer(_inputLayer, outputLength, true),

{

}

// TODO: Should get added to the current layer and update the current layer
// The output player also needs to be changed based on it's side
bool NeuralNetwork::addHiddenLayer(size_t inputLength, size_t outputLength) {
    return true;
}

// TODO: Add actual impl
vector<float> NeuralNetwork::doForwardPass() {
    return vector<float> {};
}