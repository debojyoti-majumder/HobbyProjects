#include "headers\NeuronUnit.hpp"

NeuronUnit::NeuronUnit(const vector<float>& input, float bias) : _input(input) {
    _bias = bias;
}

NeuronUnit::NeuronUnit(const Layer& prevLayer, float bias) : _input(vector<float>{}) {

}

float NeuronUnit::computeOutput() const {
    return 0.0f;
}