import argparse
import shutil
import sys

import tensorflow as tf
from sklearn import preprocessing # Used in label encoding

_CSV_COLUMNS = [
    'pH', 'TempCelsius', 'Conductance', 'GageHt', 'DischargeRate',
    'TimeOfYear', 'TimeOfDay', 'month', 'MinuteOfDay', 'MinuteFromMidnite',
    'MinuteOfYear', 'MinuteFromNewYear', 'OxygenMgPerLiter'
]

LABEL_NAMES = [
    "'\'(-inf-2.27]\''","'\'(2.27-4.44]\''","'\'(4.44-6.61]\''",
    "'\'(6.61-8.78]\''","'\'(8.78-10.95]\''","'\'(10.95-13.12]\''",
    "'\'(13.12-15.29]\''","'\'(15.29-17.46]\''","'\'(17.46-19.63]\''",
    "'\'(19.63-inf)\''"
]

_CSV_COLUMN_DEFAULTS = [[0.0], [0.0], [0.0], [0.0], [0.0], [0], [0], [0], [0], [0],
                        [0], [0], [0]]
                        
parser = argparse.ArgumentParser()

parser.add_argument(
    '--model_dir', type=str, default='/tmp/DataMining_Model',
    help='Base directory for the model.')

parser.add_argument(
    '--model_type', type=str, default='wide_deep',
    help="Valid model types: {'wide', 'deep', 'wide_deep'}.")

parser.add_argument(
    '--train_epochs', type=int, default=40, help='Number of training epochs.')

parser.add_argument(
    '--epochs_per_eval', type=int, default=2,
    help='The number of training epochs to run between evaluations.')

parser.add_argument(
    '--batch_size', type=int, default=40, help='Number of examples per batch.')

parser.add_argument(
    '--train_data', type=str, default='csc458water_training49k_e.csv',
    help='Path to the training data.')

parser.add_argument(
    '--test_data', type=str, default='csc458water_testing491k_e.csv',
    help='Path to the test data.')
    
_NUM_EXAMPLES = {
    'train': 49189,
    'test': 491891,
}


def build_model_columns():
    pH = tf.feature_column.numeric_column('pH')
    TempCelsius = tf.feature_column.numeric_column('TempCelsius')
    Conductance = tf.feature_column.numeric_column('Conductance')
    GageHt = tf.feature_column.numeric_column('GageHt')
    DischargeRate = tf.feature_column.numeric_column('DischargeRate')
    TimeOfYear = tf.feature_column.numeric_column('TimeOfYear')
    TimeOfDay = tf.feature_column.numeric_column('TimeOfDay')
    month = tf.feature_column.numeric_column('month')
    MinuteOfDay = tf.feature_column.numeric_column('MinuteOfDay')
    MinuteFromMidnite = tf.feature_column.numeric_column('MinuteFromMidnite')
    MinuteOfYear = tf.feature_column.numeric_column('MinuteOfYear')
    MinuteFromNewYear = tf.feature_column.numeric_column('MinuteFromNewYear')
        
    month_buckets = tf.feature_column.bucketized_column(
        month, boundaries=[3,6,9,12])
        
    base_columns = [
        TimeOfYear, TimeOfDay, month_buckets,
    ]
    
    crossed_columns = [
        tf.feature_column.crossed_column(
            ['TimeOfYear', 'TimeOfDay'], hash_bucket_size=1000),
        tf.feature_column.crossed_column(
            [month_buckets, 'TimeOfYear', 'TimeOfDay'], hash_bucket_size=1000),
    ]
    
    wide_columns = base_columns + crossed_columns
    
    deep_columns = [
        pH,
        TempCelsius,
        Conductance,
        GageHt,
        DischargeRate,
        month,
        MinuteOfDay,
        MinuteFromMidnite,
        MinuteOfYear,
        MinuteFromNewYear,
        TimeOfYear,
        TimeOfDay,
    ]

    return wide_columns, deep_columns
    
    
def build_estimator(model_dir, model_type):
    """Build an estimator appropriate for the given model type."""
    wide_columns, deep_columns = build_model_columns()
    hidden_units = [100, 75, 50, 25]

    # Create a tf.estimator.RunConfig to ensure the model is run on CPU, which
    # trains faster than GPU for this model.
    run_config = tf.estimator.RunConfig().replace(
        session_config=tf.ConfigProto(device_count={'GPU': 0}))

    if model_type == 'wide':
        return tf.estimator.LinearClassifier(
            model_dir=model_dir,
            feature_columns=wide_columns,
            n_classes = 10,
            optimizer=tf.train.FtrlOptimizer(
                learning_rate=0.1,
                l1_regularization_strength=1.0,
                l2_regularization_strength=1.0),
                config=run_config)
    elif model_type == 'deep':
        return tf.estimator.DNNClassifier(
            model_dir=model_dir,
            feature_columns=deep_columns,
            n_classes = 10,
            hidden_units=hidden_units,
            config=run_config)
    else:
        return tf.estimator.DNNLinearCombinedClassifier(
            model_dir=model_dir,
            linear_feature_columns=wide_columns,
            dnn_feature_columns=deep_columns,
            n_classes = 10,
            dnn_hidden_units=hidden_units,
            config=run_config)
        
  
def input_fn(data_file, num_epochs, shuffle, batch_size):
    """Generate an input function for the Estimator."""
    assert tf.gfile.Exists(data_file), ('%s not found.' % data_file)

    def parse_csv(value):
        print('Parsing', data_file)
        columns = tf.decode_csv(value, record_defaults=_CSV_COLUMN_DEFAULTS)
        features = dict(zip(_CSV_COLUMNS, columns))
        labels = features.pop('OxygenMgPerLiter')
        sess = tf.Session()
        return features, labels

    # Extract lines from input files using the Dataset API.
    dataset = tf.data.TextLineDataset(data_file)

    if shuffle:
        dataset = dataset.shuffle(buffer_size=_NUM_EXAMPLES['train'])

    dataset = dataset.map(parse_csv, num_parallel_calls=5)

    # We call repeat after shuffling, rather than before, to prevent separate
    # epochs from blending together.
    dataset = dataset.repeat(num_epochs)
    dataset = dataset.batch(batch_size)
    return dataset 
    
def main(unused_argv):
    # Clean up the model directory if present
    shutil.rmtree(FLAGS.model_dir, ignore_errors=True)
    model = build_estimator(FLAGS.model_dir, FLAGS.model_type)

    # Train and evaluate the model every `FLAGS.epochs_per_eval` epochs.
    for n in range(FLAGS.train_epochs // FLAGS.epochs_per_eval):
        model.train(input_fn=lambda: input_fn(
        FLAGS.train_data, FLAGS.epochs_per_eval, True, FLAGS.batch_size))

        results = model.evaluate(input_fn=lambda: input_fn(
            FLAGS.test_data, 1, False, FLAGS.batch_size))

        # Display evaluation metrics
        print('Results at epoch', (n + 1) * FLAGS.epochs_per_eval)
        print('-' * 60)

        for key in sorted(results):
            print('%s: %s' % (key, results[key]))


if __name__ == '__main__':
    tf.logging.set_verbosity(tf.logging.INFO)
    FLAGS, unparsed = parser.parse_known_args()
    tf.app.run(main=main, argv=[sys.argv[0]] + unparsed)
    