import math
import random

class Nuron:
    def __init__(self, bias:float) -> None:
        self.bias = bias
        self.weights:list[float] = []

        # TBD: Make enum based on this
        self.activation:int = 1

    def _scalar_multiply(self, input:list[float]) -> list[float]:
        return_output:list[float] = []

        for i in range(len(input)):
            return_output.append(input[i] * self.weights)
        
        return return_output


    def calculate_output(self, input:list[float]) -> list[float]:
        self.input = input
        
        if len(input) != self.weights:
            print("Incorrect length of input vector")
            return []
        
        pre_activation = self._scalar_multiply(input)
        return self._activation_func(pre_activation)
    
    def set_weights(self, weights:list[float]) -> None:
        if len(self.weights) == 0:
            print("Init weight for nuron")
            self.weights = weights
            return
        
        if len(weights) != len(self.weights):
            print("Weight update is not allowed")
            return

        self.weights = weights
    
    def _activation_func(self, input:list[float]) -> list[float]:
        returned_output = []

        for inp in input:
            if self.activation == 1:
                exp_output:float = 1.0 / ( 1.0 + math.exp(inp))
                returned_output.append(exp_output)

        return returned_output

class NeronLayer:
    def __init__(self, num_nurons:int, bias:int = 0) -> None:
        # In a single nuron layer the bias remains the same
        if bias == 0:
            self.bias:float = random.random()
        
        self.nurons:list[Nuron] = []
        for _ in range(num_nurons):
            self.nurons.append(Nuron(self.bias))

print("A very basic hardwritten Nuralnet in python")

oneNuron = Nuron(0.4)
oneNuron.set_weights([0.2,0.3,0.4])
