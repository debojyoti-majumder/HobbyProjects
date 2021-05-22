#include "headers/InputLayer.hpp"

InputLayer::InputLayer(const std::vector<double>& input) : _input(input) {

}

const std::vector<double>& InputLayer::getInputs() const {
    return _input;
}