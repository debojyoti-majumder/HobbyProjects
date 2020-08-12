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

def my_network_model(data_input, number_of_features, output_class):
    output_1 = nn_layer(data_input, [number_of_features, output_class], [output_class])

    return output_1

# TODO: This not a good way of using variable have to use some type of object related functionality
train_i, test_i, train_out, test_out = load_data()


def do_training(tf_session, input_batch):
    input_placeholder = tf.placeholder(tf.float32, shape=(None, 4))
    pred = my_network_model(input_placeholder, 4, 3)
    
    init = tf.initialize_all_variables()
    tf_session.run(init)

    session.run(pred, feed_dict={input_placeholder: input_batch})

with tf.Session(config=tf.ConfigProto(log_device_placement=False)) as session:
    start_index = 0  

    with tf.variable_scope("shared_variable") as scope:     
        # TODO: This needs to done based on data size
        for i in range(2) :
            train_data = train_i[start_index:start_index + 10]

            # Does the actual computation
            do_training(session, train_data)

            start_index += 10
            scope.reuse_variables()
