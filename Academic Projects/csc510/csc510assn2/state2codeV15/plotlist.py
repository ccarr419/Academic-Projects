# Halloween to get curves for fcfs rr sjf

# Ignored
DIFFMAP = {
    'SUM_produceProduct'        :       (.20, 10),
    'MEAN_produceProduct'       :       (.20, 5),
    'SUM_spinProducer'          :       (.7, 10),
    'MEAN_spinProducer'         :       (.4, 5),
    'MAX_spinProducer'          :       (.4, 5),
    'SUM_consumeProduct'        :       (.20, 10),
    'MEAN_consumeProduct'       :       (.20, 5),
    'SUM_spinConsumer'          :       (.7, 10),
    'MEAN_spinConsumer'         :       (.4, 5),
    'MAX_spinConsumer'          :       (.4, 5),
    'MEAN_TURNAROUNDTIME'       :       (.4, 10),
    'MAX_TURNAROUNDTIME'        :       (.4, 10),

}

# Make a separate plot for each crunch file.
PLOTLIST = (
	'SUM_TURNAROUNDTIME',
	'MEAN_TURNAROUNDTIME',
	'MAX_TURNAROUNDTIME',
    'SUM_ready',
    'MEAN_ready',
    'SUM_running',
    'MEAN_running',
)
