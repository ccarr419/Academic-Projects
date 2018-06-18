# swapping2016/diffset.py -- set of simulation properties to test after
# a simulation run. See crunchlog.py

# Map the property to be checked against its (TOLERANCE, RAWTOLERANCE),
# where TOLERANCE is a percatage as a fraction, and RAWTOLERANCE
# is the minimum difference between the simulation value and the
# reference value for the property required to trigger an error.
DIFFMAP = {
    'MEAN_running'              :       (.20, 10),
    'MEAN_ready'                :       (.20, 10),
    'MEAN_waiting'              :       (.20, 10),
    'MEAN_waitForMemory'        :       (.20, 10),
    'SUM_waitForMemory'         :       (.20, 10),
    'MEAN_checkIfMemory'        :       (.20, 10),
    'SUM_checkIfMemory'         :       (.20, 10),
    'MEAN_TURNAROUNDTIME'       :       (.20, 10),
    'MAX_running'               :       (.20, 10),
    'MAX_ready'                 :       (.20, 10),
    'MAX_waiting'               :       (.20, 10),
    'MAX_waitForMemory'         :       (.20, 10),
    'MAX_checkIfMemory'         :       (.20, 10),
    'MAX_TURNAROUNDTIME'        :       (.20, 10),
    'MIN_running'               :       (.20, 10),
    'MIN_ready'                 :       (.20, 10),
    'MIN_waiting'               :       (.20, 10),
    'MIN_waitForMemory'         :       (.20, 10),
    'MIN_checkIfMemory'         :       (.20, 10),
    'MIN_TURNAROUNDTIME'        :       (.20, 10),
}

# Make a separate plot for each crunch file.
PLOTLIST = (
    'MIN_ready', 'MEAN_ready', 'MAX_ready',
    'MEAN_running', 'MEAN_waiting',
    'MIN_waitForMemory', 'MEAN_waitForMemory', 'MAX_waitForMemory',
    'MIN_checkIfMemory', 'MEAN_checkIfMemory', 'MAX_checkIfMemory',
    'MEAN_TURNAROUNDTIME',
)
