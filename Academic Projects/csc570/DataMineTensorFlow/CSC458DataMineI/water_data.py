import pandas as pd
import tensorflow as tf

TRAIN_FILE = 'csc458water_training49k_e.csv'
TEST_FILE = 'csc458water_testing491k_e.csv'

CSV_COLUMN_NAMES = [
    'pH', 'TempCelsius', 'Conductance', 'GageHt', 'DischargeRate',
    'TimeOfYear', 'TimeOfDay', 'month', 'MinuteOfDay', 'MinuteFromMidnite',
    'MinuteOfYear', 'MinuteFromNewYear', 'OxygenMgPerLiter']
    
CLASSIFICATIONS = 10

LABEL_NAMES = [
    "'\'(-inf-2.27]\''","'\'(2.27-4.44]\''","'\'(4.44-6.61]\''",
    "'\'(6.61-8.78]\''","'\'(8.78-10.95]\''","'\'(10.95-13.12]\''",
    "'\'(13.12-15.29]\''","'\'(15.29-17.46]\''","'\'(17.46-19.63]\''",
    "'\'(19.63-inf)\''"
]

CSV_COLUMN_DEFAULTS = [[0.0], [0.0], [0.0], [0.0], [0.0], [0], [0], [0], [0], [0],
                        [0], [0], [0]]
    
def load_data(y_name='OxygenMgPerLiter'):
    """Returns the iris dataset as (train_x, train_y), (test_x, test_y)."""
    train = pd.read_csv(TRAIN_FILE, names=CSV_COLUMN_NAMES, header=0)
    train = train.fillna(0)
    train_x, train_y = train, train.pop(y_name)

    test = pd.read_csv(TEST_FILE, names=CSV_COLUMN_NAMES, header=0)
    test = test.fillna(0)
    test_x, test_y = test, test.pop(y_name)

    return (train_x, train_y), (test_x, test_y)
    
def train_input_fn(features, labels, batch_size):
    """An input function for training"""
    # Convert the inputs to a Dataset.
    dataset = tf.data.Dataset.from_tensor_slices((dict(features), labels))
    
    # Shuffle, repeat, and batch the examples.
    dataset = dataset.shuffle(1000).repeat().batch(batch_size)
    
    # Return the dataset.
    return dataset
  
def eval_input_fn(features, labels, batch_size):
    """An input function for evaluation or prediction"""
    features = dict(features)
    if labels is None:
        # No labels, use only features.
        inputs = features
    else:
        inputs = (features, labels)
    
    # Convert the inputs to a Dataset.
    dataset = tf.data.Dataset.from_tensor_slices(inputs)
    
    # Batch the examples
    assert batch_size is not None, "batch_size must not be None"
    dataset = dataset.batch(batch_size)
    
    # Return the dataset.
    return dataset

# The remainder of this file contains a simple example of a csv parser,
#     implemented using a the `Dataset` class.

# `tf.parse_csv` sets the types of the outputs to match the examples given in
#     the `record_defaults` argument.
def _parse_line(line):
    # Decode the line into its fields
    fields = tf.decode_csv(line, record_defaults=CSV_COLUMN_DEFAULTS)
    
    # Pack the result into a dictionary
    features = dict(zip(CSV_COLUMN_NAMES, fields))
    
    # Separate the label from the features
    label = features.pop('OxygenMgPerLiter')
    
    return features, label
      
def csv_input_fn(csv_path, batch_size):
    # Create a dataset containing the text lines.
    dataset = tf.data.TextLineDataset(csv_path).skip(1)
    
    # Parse each line.
    dataset = dataset.map(_parse_line)
    
    # Shuffle, repeat, and batch the examples.
    dataset = dataset.shuffle(1000).repeat().batch(batch_size)
    
    # Return the dataset.
    return dataset
