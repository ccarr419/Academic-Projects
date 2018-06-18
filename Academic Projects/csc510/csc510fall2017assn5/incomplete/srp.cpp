/*
Author:     Christian Carreras
Date:       12/04/17
Due Date:   12/12/17
File:       srp.cpp
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

//Evaluate Strong Reader Preference (SRP)
int readWriteSTM::srp(thread evalThread) {
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
                if(!free2read) {
                    lockMutex(rMtx, rCon, ref(rOpen));
                    readersWaiting++;
                    unlockMutex(rMtx, rCon, ref(rOpen));
                    while(!free2read) {}
                }
                // BEGIN READER COUNT CRITICAL SECTION
                lockMutex(rMtx, rCon, ref(rOpen));
                if(++readersCount == 1) {
                    lockMutex(csMtx, csCon, ref(csOpen));
                }
                if(readersWaiting >= 1) {
                    if(--readersWaiting == 0) {
                        free2write = true;
                    }
                }
                else { free2read = true; }
                // END READER COUNT CRITICAL SECTION
                unlockMutex(rMtx, rCon, ref(rOpen));
                logMsg("acquired the mutex", evalThread, 1);
                currentStates[evalThread.tid] = STATE_CRITSECT;
            }

            else { //(evalThread.rw == WRITER)
                lockMutex(wMtx, wCon, ref(wOpen));
                // BEGIN WRITER COUNT CRITICAL SECTION
                writersCount++; //Let other threads know there is an active writer
                // END WRITER COUNT CRITICAL SECTION
                unlockMutex(wMtx, wCon, ref(wOpen));
                if(writersCount > 1) {
                    while(!free2write) {} //Wait until there are no active writers
                }
                while(readersCount > 0) {}
                lockMutex(csMtx, csCon, ref(csOpen));
                free2read = false; //No readers allowed until writer is done
                free2write = false; //Only one writer allowed in cs at a time
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
                // BEGIN READER COUNT CRITICAL SECTION
                lockMutex(rMtx, rCon, ref(rOpen));
                if(--readersCount == 0) {
                    free2write = true;
                    unlockMutex(csMtx, csCon, ref(csOpen));
                }
                unlockMutex(rMtx, rCon, ref(rOpen));
                // END READER COUNT CRITICAL SECTION
            }
            //Writers are non-concurrent and must have exclusive access
            else { //(evalThread.rw == WRITER)
                logMsg("writer in critical section, sleeping...", evalThread, 1);
                usleep(32500);
                lockMutex(wMtx, wCon, ref(wOpen));
                // BEGIN WRITER COUNT CRITICAL SECTION
                writersCount--;
                if(readersWaiting > 0) {
                    free2read = true;
                    free2write = false;
                }
                else {
                    free2write = true;
                }
                // END WRITER COUNT CRITICAL SECTION
                unlockMutex(wMtx, wCon, ref(wOpen));
                unlockMutex(csMtx, csCon, ref(csOpen));
            }
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
int readWriteSTM::wrp(thread evalThread) {}
int readWriteSTM::wwp(thread evalThread) {}
int readWriteSTM::swp(thread evalThread) {}
int readWriteSTM::fcfs(thread evalThread) {}

int main(int argc, char **argv) {
    readWriteSTM * stm = new readWriteSTM();
    cout << "Strong Reader Preference" << endl;
    stm->makingThreads(STM_SRP);
    return 0;
}
