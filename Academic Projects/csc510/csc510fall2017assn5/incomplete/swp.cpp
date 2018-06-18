/*
Author:     Christian Carreras
Date:       12/04/17
Due Date:   12/12/17
File:       swp.cpp
Assignment: #5
Course:     CSC510 Advanced Operating Systems
Professor:  Dr. Parson
University: Kutztown University of Pennsylvania
About:      
*/
#include <iostream>
#include <functional> //ref() function to wrap atomic variable parameters
#include "readWriteSTM.h"
using namespace std;

//Evaluate Strong Writer Preference (SWP)
int readWriteSTM::swp(thread evalThread) {
    switch (currentStates[evalThread.tid]) {
        case STATE_INIT: //Initial state where freshly created threads start
            logMsg("init, ARRIVE", evalThread);
            currentStates[evalThread.tid] = STATE_WAIT; //Go wait to get in cs
            logMsg("init, DEPART", evalThread);
            return(KEEP_GOING);

        case STATE_WAIT: //Wait here for the critical section to open
            logMsg("wait, ARRIVE", evalThread);
            logMsg("trying lock on mutex", evalThread, 1);
            if(evalThread.rw == READER) {
                lockMutex(csMtx, csCon, ref(csOpen));
                readersWaiting++;
                if(writersWaiting == 0) {
                    readersCount++;
                    unlockMutex(rMtx, rCon, ref(rOpen));
                }
                unlockMutex(csMtx, csCon, ref(csOpen));
                lockMutex(rMtx, rCon, ref(rOpen));   
                lockMutex(csMtx, csCon, ref(csOpen));
                logMsg("acquired the mutex", evalThread, 1);
                currentStates[evalThread.tid] = STATE_CRITSECT;
            }
            
            else { //(evalThread.rw == WRITER)
                lockMutex(csMtx, csCon, ref(csOpen));
                writersWaiting++;
                if(readersCount == 0) {
                    writersCount++;
                    unlockMutex(wMtx, wCon, ref(wOpen));
                }
                unlockMutex(csMtx, csCon, ref(csOpen));
                lockMutex(wMtx, wCon, ref(wOpen));
                lockMutex(csMtx, csCon, ref(csOpen));
                logMsg("acquired the mutex", evalThread, 1);
                currentStates[evalThread.tid] = STATE_CRITSECT;
            }
            logMsg("wait, DEPART", evalThread);
            return(KEEP_GOING);

        //The critical section can concurrently hold multiple readers or
        //only one writer at a time
        case STATE_CRITSECT:
            logMsg("critSec, ARRIVE", evalThread);
            if(evalThread.rw == READER) {
                logMsg("reader in critical section, sleeping...", evalThread, 1);
                usleep(25000);
                readersWaiting--;
                if(--readersCount == 0) {
                    while(writersCount < writersWaiting) {
                        writersCount++;
                    }
                    unlockMutex(wMtx, wCon, ref(wOpen));
                }
                unlockMutex(csMtx, csCon, ref(csOpen));
            }
            else { //(evalThread.rw == WRITER)
                logMsg("writer in critical section, sleeping...", evalThread, 1);
                usleep(32500);
                writersCount--;
                if(--writersWaiting == 0) {
                    while(readersCount < readersWaiting) {
                        readersCount++;
                        unlockMutex(rMtx, rCon, ref(rOpen));
                    }
                }
                unlockMutex(csMtx, csCon, ref(csOpen));
            }
            currentStates[evalThread.tid] = STATE_TERMINATE;
            logMsg("critSec, DEPART", evalThread);
            return(KEEP_GOING);

        case STATE_TERMINATE:  //End the current task for the thread
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
int readWriteSTM::wrp(thread evalThread) {}
int readWriteSTM::srp(thread evalThread) {}
int readWriteSTM::wwp(thread evalThread) {}
int readWriteSTM::fcfs(thread evalThread) {}

int main(int argc, char **argv) {
    readWriteSTM * stm = new readWriteSTM();
    cout << "Strong Writer Preference" << endl;
    stm->makingThreads(STM_SWP);
    return 0;
}
