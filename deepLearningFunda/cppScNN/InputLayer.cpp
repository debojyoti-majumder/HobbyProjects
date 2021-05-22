#include "headers/InputLayer.hpp"

InputLayer::InputLayer(std::vector<double>& input) : _input(input) {

}

std::vector<double> InputLayer::getInputs() const {
    return _input;
}