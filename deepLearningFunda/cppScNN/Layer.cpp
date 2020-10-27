#include "headers\NeuronUnit.hpp"
#include "headers\Layer.hpp"

Layer::Layer(vector<float>& input, int outputLength) {

}

Layer::Layer(const Layer& prevLayer, int outputLength) {

}

const vector<float>& Layer::getOutputValues() const {
    return _output;
}