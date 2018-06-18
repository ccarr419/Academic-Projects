#!/bin/bash
# checkfiles.sh checks csc458 'make turnitin' fo correct files
# D. Parson, Fall 2017

set -x

if [ ! -f readme.txt ]
then
    echo "Your project is missing file readme.txt"
    exit 1
fi

if [ ! -f USGS_PA_STREAM_2012_SMALL.arff ]
then
    echo "Your project is missing file USGS_PA_STREAM_2012_SMALL.arff"
    exit 1
else
    bytes=`/bin/ls -l USGS_PA_STREAM_2012_SMALL.arff | cut -d" " -f5`
    if [ $bytes -eq 5549228 ]
    then
        echo "File USGS_PA_STREAM_2012_SMALL.arff has not been updated!"
        exit 1
    fi
fi
