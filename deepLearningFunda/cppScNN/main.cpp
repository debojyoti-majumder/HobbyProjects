#include <iostream>
#include <vector>

using namespace std;

class Layer;

class NeuronUnit {
    private:
        vector<float>   _input;
        vector<float>   _weight;
        float           _bias;

    public:
        NeuronUnit(const vector<float>& input, float bias) {

        }

        NeuronUnit(const Layer& prevLayer, float bias) {

        }
};

class Layer {

};

class NeuralNetwork {

};

int main(int, char**) {
    cout << "This is test nural network item\n";
}
