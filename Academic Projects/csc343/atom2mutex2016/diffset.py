# swapping2016/diffset.py -- set of simulation properties to test after
# a simulation run. See crunchlog.py

# Map the property to be checked against its (TOLERANCE, RAWTOLERANCE),
# where TOLERANCE is a percatage as a fraction, and RAWTOLERANCE
# is the minimum difference between the simulation value and the
# reference value for the property required to trigger an error.
DIFFMAP = {
    'SUM_TURNAROUNDTIME'                :   (.20, 10),
    'MEAN_TURNAROUNDTIME'               :   (.20, 10),
    'STDDEV_TURNAROUNDTIME'             :   (.20, 10),
    'SUM_lockSum'                       :   (.20, 10),
    'MEAN_lockSum'                      :   (.20, 10),
    'STDDEV_lockSum'                    :   (.20, 10),
    'SUM_lockDifference'                :   (.20, 10),
    'MEAN_lockDifference'               :   (.20, 10),
    'STDDEV_lockDifference'             :   (.20, 10),
}

# Make a separate plot for each crunch file.
PLOTLIST = (
    'SUM_TURNAROUNDTIME',
    'MEAN_TURNAROUNDTIME',
    'STDDEV_TURNAROUNDTIME',
    'SUM_lockSum',
    'MEAN_lockSum',
    'STDDEV_lockSum',
    'SUM_lockDifference',
    'MEAN_lockDifference',
    'STDDEV_lockDifference',
)
