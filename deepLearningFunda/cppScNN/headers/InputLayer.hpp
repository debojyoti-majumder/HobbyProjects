#ifndef _INPUT_LAYER_H
#define _INPUT_LAYER_H

#include <vector>

class InputLayer {
private:
    std::vector<double> _input;

public:
    InputLayer() = default;
    InputLayer(const InputLayer& ) = default;

    InputLayer(std::vector<double>& input);

    std::vector<double> getInputs() const;
};

#endif