from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse
import tensorflow as tf
import noise_data

parser = argparse.ArgumentParser()
parser.add_argument('--batch_size', default=100, type=int, help='batch size')
parser.add_argument('--train_steps', default=1000, type=int, 
    help='number of training steps')
    
def main(argv):
    args = parser.parse_args(argv[1:])
    
    # Fetch the data
    (train_x, train_y), (test_x, test_y) = noise_data.load_data()
    
    # Feature columns describe how to use the input.
    feature_columns = []
    for key in train_x.keys():
        feature_columns.append(tf.feature_column.numeric_column(key=key))
    
    # Build 2 hidden layer DNN with 10, 10 units respectively.
    classifier = tf.estimator.DNNClassifier(
        feature_columns = feature_columns,
        # Two hidden layers of 10 nodes each.
        hidden_units = [10,10],
        # The model must choose between 10 classes.
        n_classes = noise_data.CLASSIFICATIONS)
    
    # Train the Model.
    classifier.train(
        input_fn = lambda:
            noise_data.train_input_fn(train_x, train_y, args.batch_size),
        steps = args.train_steps)
    
    # Evaluate the model.
    eval_result = classifier.evaluate(
        input_fn = lambda: 
            noise_data.eval_input_fn(test_x, test_y, args.batch_size))
            
    print('\nTest set accuracy: {accuracy:0.3f}\n'.format(**eval_result))
   
if __name__ == '__main__':
    tf.logging.set_verbosity(tf.logging.INFO)
    tf.app.run(main)   
