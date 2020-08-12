import tensorflow.compat.v1 as tf
import pandas as pd
import numpy as np

tf.disable_v2_behavior()


# Data source: https://www.kaggle.com/uciml/iris
# TODO: Make this a class with constructor so there are reusable
# methods for other common task
def load_data():
    data = pd.read_csv('data/Iris.csv')
    data_shape = data.shape

    # the ID field is not required
    del data['Id']

    # Species is categorical variable let's change to int
    data['Species'], mapping_index = pd.Series(data['Species']).factorize()
    print(data.head())
    print(mapping_index)

    # Splitting the training and testing data
    mask = np.random.rand(data_shape[0]) < 0.8
    train_set = data[mask]
    test_set = data[~mask]

    # For debugging
    train_input = train_set[['SepalLengthCm', 'SepalWidthCm', 'PetalLengthCm', 'PetalWidthCm']]
    train_output = train_set['Species']

    test_input = test_set[['SepalLengthCm', 'SepalWidthCm', 'PetalLengthCm', 'PetalWidthCm']]
    test_output = test_set['Species']

    return train_input, test_input, train_output, test_output


def nn_layer(layer_input, weight_shape, bias_shape):
    weight_init = tf.random_uniform_initializer(minval=-1, maxval=1)
    bias_init = tf.constant_initializer(value=0)

    W = tf.get_variable('Weight', weight_shape, initializer=weight_init, dtype=tf.float32)
    b = tf.get_variable('bias', bias_shape, initializer=bias_init, dtype=tf.float32)

    return tf.matmul(layer_input, W) + b


print("Stating the training model")

# TODO: This not a good way of using variable have to use some type of object related functionality
train_i, test_i, train_out, test_out = load_data()


with tf.Session() as session:
    # Let pass 10 items
    start_index = 0    
    
    # TODO This is to be done in a loop
    inp_1 = train_i[start_index:start_index + 10]

    # TODO Fixing this error Op has type float32 that does not match type float64 of argument 'a'
    # 3 because there are 3 types of output, 4 becuase there are 4 features
    input_placeholder = tf.placeholder(tf.float32, shape=(None, 4))
    comp = nn_layer(input_placeholder, [4, 3], [3])
    
    init = tf.initialize_all_variables()
    session.run(init)
    
    # This is where the actual computation happens
    session.run(comp, feed_dict={input_placeholder: inp_1})
