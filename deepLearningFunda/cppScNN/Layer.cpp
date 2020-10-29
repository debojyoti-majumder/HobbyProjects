#include "headers\NeuronUnit.hpp"
#include "headers\Layer.hpp"

Layer::Layer(vector<float>& input, int outputLength, bool passthrough = false) : 
        _input(input) 
{
    // The passthrough would be set to ture for input or output layer
    if( passthrough ) _output = input;
}

Layer::Layer(const Layer& prevLayer, int outputLength, bool passthrough = false) :
        _input(prevLayer.getOutputValues())
{
    if( passthrough ) _output = _input;
}

const vector<float>& Layer::getOutputValues() const {
    return _output;
}