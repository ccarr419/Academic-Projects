#!/bin/bash
# runassn2.sh

echo 'Usage: ./runassn2.sh [ Py ] [ Sub ] [ Token ] [ Clean ]' 
echo 'export JVMVMARGS= to valid JVM args before running for Sub or Token'
set -x
# echo "Use symbolic links to save space in student file accounts."
# /bin/rm -f optimize5/*.ref && ln -s /home/KUTZTOWN/parson/OpSys/optimize5/*.ref ./optimize5
export PYTHONPATH=`pwd`
export CLASSPATH=`pwd`:`pwd`/optimize5/stepvmSub/jcip-annotations.jar

if [ $# -gt 0 ]
then
    while [ $# -gt 0 ]
    do
        todo=$1
        shift
        if [ $todo == "Py" ]
        then
            cd ./state2codeV15 && make clean && time make test343SLOW
            echo "PLEASE HIT CARRIAGE RETURN TO EXECUTE NON-SPEED TESTS ON state2codeV15"
            read junk
            make clean test
            make clean
            cd ..
            echo "Py completed, PLEASE HIT CARRIAGE RETURN TO CONTINUE"
            read junk
        fi
        if [ $todo == "Sub" ]
        then
            export STEPVM=Sub
            cd ./optimize5 && time make testpara
            cd ..
            echo "Sub completed, PLEASE HIT CARRIAGE RETURN TO CONTINUE"
            read junk
        fi
        if [ $todo == "Token" ]
        then
            export STEPVM=Token
            cd ./optimize5 && time make testpara
            cd ..
            echo "Token completed, PLEASE HIT CARRIAGE RETURN TO CONTINUE"
            read junk
        fi
        if [ $todo == "Clean" ]
        then
            cd ./state2codeV15 && make clean && cd ..
            cd ./optimize5 && make clean && cd ..
        fi
    done
else
    export STEPVM=Sub
    cd ./optimize5 && time make testpara
    cd ..
    echo "Sub completed, PLEASE HIT CARRIAGE RETURN TO CONTINUE"
    read junk
    
    export STEPVM=Token
    cd ./optimize5 && time make testpara
    cd ..
    echo "Token completed, PLEASE HIT CARRIAGE RETURN TO CONTINUE"
    read junk
    
    cd ./state2codeV15 && make clean && time make test343SLOW
    echo "PLEASE HIT CARRIAGE RETURN TO EXECUTE NON-SPEED TESTS ON state2codeV15"
    read junk
    make clean test
    make clean
    echo "Py completed, PLEASE HIT CARRIAGE RETURN TO CONTINUE"
    read junk
fi
