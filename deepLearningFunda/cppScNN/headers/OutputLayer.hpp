#ifndef _OUTPUT_LAYER_H
#define _OUTPUT_LAYER_H

#include <vector>

enum class OutputLayerLossType {
    Log,
    SquareRoot
};

class OutputLayer {
    private:
        const std::vector<double>& _output;

    public:
        OutputLayer(const std::vector<double>& output);

        const std::vector<double> getOutput() const;
        double getLoss( const std::vector<double>& actualOutput, 
                        const OutputLayerLossType& lossType = OutputLayerLossType::SquareRoot) const;
};

#endif