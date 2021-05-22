#ifndef _INPUT_LAYER_H
#define _INPUT_LAYER_H

#include <vector>

class InputLayer {
private:
    std::vector<double> _input;

public:
    InputLayer(const std::vector<double>& input);
    const std::vector<double>& getInputs() const;
};

#endif