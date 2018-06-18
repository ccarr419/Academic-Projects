/*
Author:     Christian Carreras
Date:       12/04/17
Due Date:   12/12/17
File:       wrp.cpp
Assignment: #5
Course:     CSC510 Advanced Operating Systems
Professor:  Dr. Parson
University: Kutztown University of Pennsylvania
About:      This file defines the code for the weak reader prefence solution to 
            the readers writers problem. Once compiled this project will also 
            be able to simulate the WRP solution. The WRP solution allows for
            (same amongst the others) concurrent readers in the critical
            section. If a reader is in the critical section, waiting readers
            can keep entering the critical section. Writers can only enter the
            critical section once there is no readers left in the critical
            section and the aquire the mutex lock to do so. Because of the
            concurrent nature of this algorithm and the preference for readers,
            there is a noticeable speed-up compared to other solutions.
            However, there can be a small problem with starvation. If there
            are more readers than writers, writers will starve.
*/
#include <iostream>
#include <functional> //ref() function to wrap atomic variable parameters
#include "readWriteSTM.h"
using namespace std;

/*
Function Name:  wrp
Function Type:  mutator
Parameters:     thread - the calling thread and all its information
Returns:        int - the status of the state machine
About:          Evaluates weak reader preference solution to the readers writers
                problem. This solution states that when a reader is in the
                critical section, writers must wait until all readers exit.
*/
int readWriteSTM::wrp(thread evalThread) {
    switch (currentStates[evalThread.tid]) {
        case STATE_INIT: //Initial state where freshly created threads start
            logMsg("init, ARRIVE", evalThread);
            currentStates[evalThread.tid] = STATE_WAIT; //Go wait to get in cs
            logMsg("init, DEPART", evalThread);
            return(KEEP_GOING);
        
        //This state makes writers wait until all readers exit the critical
        //section and lets the waiting readers enter the critical section if
        //there is a reader in the critical section already
        case STATE_WAIT: //Wait here for the critical section to open
            logMsg("wait, ARRIVE", evalThread);
            logMsg("trying lock on mutex", evalThread, 1);
            if(evalThread.rw == READER) { //Readers Only
                lockMutex(rMtx, rCon, ref(rOpen));
                // BEGIN READER COUNT CRITICAL SECTION
                if(++readersCount == 1) { //Increment the active reader count
                    //Lock or wait for the cs lock if the first reader
                    lockMutex(csMtx, csCon, ref(csOpen));
                }
                // END READER COUNT CRITICAL SECTION
                unlockMutex(rMtx, rCon, ref(rOpen)); //Let other readers come in
                logMsg("acquired the mutex", evalThread, 1);
                currentStates[evalThread.tid] = STATE_CRITSECT;
            }

            else { //(evalThread.rw == WRITER) Writers Only
                lockMutex(csMtx, csCon, ref(csOpen)); //Lock or wait for the cs lock
                logMsg("acquired the mutex", evalThread, 1);
                currentStates[evalThread.tid] = STATE_CRITSECT;
            }
            logMsg("wait, DEPART", evalThread);
            return(KEEP_GOING);
        
        //The critical section can concurrently hold multiple readers or
        //only one writer at a time
        case STATE_CRITSECT:
            logMsg("critSec, ARRIVE", evalThread);
            //If a reader is in the critical section, the critical section will
            //remained locked until all readers exit
            if(evalThread.rw == READER) {
                logMsg("reader in critical section, sleeping...", evalThread, 1);
                usleep(SLEEP_READER); //Sleep to represent doing something
                lockMutex(rMtx, rCon, ref(rOpen)); 
                // BEGIN READER COUNT CRITICAL SECTION
                if(--readersCount == 0) { //Unlock the cs mutex if no more readers
                    unlockMutex(csMtx, csCon, ref(csOpen)); 
                }
                unlockMutex(rMtx, rCon, ref(rOpen)); //Let other readers in
                // END READER COUNT CRITICAL SECTION
            }
            //Writers are non-concurrent and must have exclusive access
            else { //(evalThread.rw == WRITER) 
                logMsg("writer in critical section, sleeping...", evalThread, 1);
                usleep(SLEEP_WRITER); //Sleep to represent doing something
                unlockMutex(csMtx, csCon, ref(csOpen)); //Unlock the cs
            }
            //The task is done go to the terminate state
            currentStates[evalThread.tid] = STATE_TERMINATE;
            logMsg("critSec, DEPART", evalThread);
            return(KEEP_GOING);

        case STATE_TERMINATE: //End the current task for the thread
            logMsg("terminate, ARRIVE", evalThread);
            return(STOP_GOING); //Reached the accept state

        default: //Should never reach this state but for good measure
            logMsg("error: illegal state", evalThread);
            //I do no know how you got here but I am putting a stop to it!
            return(STOP_GOING);
    }
}

//Put other solution function declarations here so readWriteSTM.cpp can know 
//they exist when it selects which algorithm to use. Otherwise the program
//will not compile because these functions will not be defined.
int readWriteSTM::fair(thread evalThread) {}
int readWriteSTM::srp(thread evalThread) {}
int readWriteSTM::wwp(thread evalThread) {}
int readWriteSTM::swp(thread evalThread) {}
int readWriteSTM::fcfs(thread evalThread) {}

int main(int argc, char **argv) {
    readWriteSTM * stm = new readWriteSTM();
    cout << "Weak Reader Preference" << endl;
    stm->makingThreads(STM_WRP); //Start the STM with WRP Preference
    return 0;
}
