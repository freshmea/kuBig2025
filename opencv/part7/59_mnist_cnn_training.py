import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
from tensorflow.python.framework import graph_util
from tensorflow.python.platform import gfile

tf.logging.set_verbosity(tf.logging.INFO)

mnist = input_data.read_data_sets("./mnist_data/", one_hot=True)
