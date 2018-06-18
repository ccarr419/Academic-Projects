/**
 *  stepvmSubroutineInC.c is the subroutine-threaded code rewrite of stepvmTokenInC.c
 *  Dale Parson Summer & Fall 2017. It uses pointers to functions for opcodes.
 *  stepvmTokenInC.c is a token-threaded VM example that we will use in
 *  assignment 1 of CSC510 Advanced Operating Systems, Fall 2017.
 *  stepvmSubroutineInC.c is D. Parson's solution to assignment 1.
 *  See stepvmInC.h for the primary documentation comments.
 *  Updated 11/12/2017 to get real & CPU times via times() function.
**/
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <unistd.h>
#include <string.h>
#include "stepvmInC.h"
#ifndef DEBUGVM
#define NDEBUG 1
#endif
/* NDEBUG disables assert checks */

/* Every time a new program gets loaded into the VM,
 * reset codePointers to NULL. This happens in stepvmInC_constructor.
 * See usage in stepvmInC_constructor and run_stepvmInC.
 * @param vm is the VM being run.
 * @param dumpOnTermination is true if an opcode that terminates the VM should
 * dump its state to stderr.
 * @return value is true (non-0) if run_stepvmInC should return, thus
 * terminating the VM; a return value of 0 from an opcodeFunctionPtr
 * indicates continuation of running.
*/
typedef int (*opcodeFunctionPtr)(struct stepvmInC *vm, int dumpOnTermination);
static opcodeFunctionPtr *codePointers = NULL ;

/* C non-encapsulated alternatives to C++ member functions: */
/* Initialize the data fields and arrays per docs in stepvmInC.h. */
void stepvmInC_constructor(struct stepvmInC *addressOfVM,
    stepdata_t *dataStackParam, int32_t topdsParam,
    stepdata_t *staticMemoryParam, int32_t staticMemoryParamElems,
    stepaddr_t *callStackParam, int32_t topcsParam,
    stepcode_t *codeMemoryParam, int32_t codeMemoryParamSize,
    int8_t isSupervisorModeParam) {
    memset(addressOfVM, 0, sizeof(struct stepvmInC)); /* zero all data */
    addressOfVM->topds = (topdsParam > 0) ? topdsParam : 0 ;
    addressOfVM->topcs = (topcsParam > 0) ? topcsParam : 0 ;
    addressOfVM->isSupervisorMode = (isSupervisorModeParam != 0) ;
    if (dataStackParam != NULL && topdsParam > 0) {
        memcpy(addressOfVM->dataStack, dataStackParam,
            topdsParam * sizeof(addressOfVM->dataStack[0]));
    }
    if (staticMemoryParam != NULL && staticMemoryParamElems > 0) {
        memcpy(addressOfVM->staticMemory, staticMemoryParam,
            staticMemoryParamElems * sizeof(addressOfVM->staticMemory[0]));
    }
    if (callStackParam != NULL && topcsParam > 0) {
        memcpy(addressOfVM->callStack, callStackParam,
            topcsParam * sizeof(addressOfVM->callStack[0]));
    }
    if (codeMemoryParam != NULL && codeMemoryParamSize > 0) {
        memcpy(addressOfVM->codeMemory, codeMemoryParam,
            codeMemoryParamSize * sizeof(addressOfVM->codeMemory[0]));
    }
    if (codePointers != NULL) {
        free(codePointers);
        codePointers = NULL ; /* Used to compile pointers to labels. */
    }
}

void dump_stepvmInC(struct stepvmInC *vm) {
    int i ;
    fprintf(stderr,"DUMP OF VM:\n");
    fprintf(stderr,"\tip = %d, isSupervisorMode = %d, topds = %d, topcs = %d\n",
        (int)(vm->ip),
        (int)(vm->isSupervisorMode),(int)(vm->topds),(int)(vm->topcs));
    fprintf(stderr,"\tlower_user_ip = %d, upper_user_ip = %d\n",
        (int)(vm->lower_user_ip),(int)(vm->upper_user_ip));
    fprintf(stderr,"\tlower_user_static = %d, upper_user_static = %d\n",
        (int)(vm->lower_user_static),(int)(vm->upper_user_static));
    for (i = vm->topds-1 ; i >= 0 ; i--) {
        fprintf(stderr,"\t\tdataStack[%d] = %ld\n",i,(long)(vm->dataStack[i]));
    }
    for (i = vm->topcs-1 ; i >= 0 ; i--) {
        fprintf(stderr,"\t\tcallStack[%d] = %d\n",i,(int)(vm->callStack[i]));
    }
    for (i = 0 ; i <= ((int)(vm->upper_user_static)) ; i++) {
        fprintf(stderr,"\t\tstaticMemory[%d] = %ld\n",i,(long)(vm->staticMemory[i]));
    }
    for (i = 0 ; i <= ((int)(vm->upper_user_ip)) ; i++) {
        fprintf(stderr,"\t\tcodeMemory[%d] = %d\n",i,(int)(vm->codeMemory[i]));
    }
    fflush(stderr);
}
static int FUNCTION_STEP_LADD(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds-2]
        = vm->dataStack[vm->topds-2] + vm->dataStack[vm->topds-1];
    vm->topds -= 1 ;
    return(0);
}
static int FUNCTION_STEP_LSUB(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds-2]
        = vm->dataStack[vm->topds-2] - vm->dataStack[vm->topds-1];
    vm->topds -= 1 ;
    return(0);
}
static int FUNCTION_STEP_LMULT(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds-2]
        = vm->dataStack[vm->topds-2] * vm->dataStack[vm->topds-1];
    vm->topds -= 1 ;
    return(0);
}
static int FUNCTION_STEP_LDIV(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds-2]
        = vm->dataStack[vm->topds-2] / vm->dataStack[vm->topds-1];
    vm->topds -= 1 ;
    return(0);
}
static int FUNCTION_STEP_LMOD(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds-2]
        = vm->dataStack[vm->topds-2] % vm->dataStack[vm->topds-1];
    vm->topds -= 1 ;
    return(0);
}
static int FUNCTION_STEP_LSHL(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds-2]
        = vm->dataStack[vm->topds-2] << vm->dataStack[vm->topds-1];
    vm->topds -= 1 ;
    return(0);
}
static int FUNCTION_STEP_LSHR(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds-2]
        = vm->dataStack[vm->topds-2] >> vm->dataStack[vm->topds-1];
    vm->topds -= 1 ;
    return(0);
}
static int FUNCTION_STEP_LBITAND(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds-2]
        = vm->dataStack[vm->topds-2] & vm->dataStack[vm->topds-1];
    vm->topds -= 1 ;
    return(0);
}
static int FUNCTION_STEP_LBITOR(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds-2]
        = vm->dataStack[vm->topds-2] | vm->dataStack[vm->topds-1];
    vm->topds -= 1 ;
    return(0);
}
static int FUNCTION_STEP_LBITXOR(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds-2]
        = vm->dataStack[vm->topds-2] ^ vm->dataStack[vm->topds-1];
    vm->topds -= 1 ;
    return(0);
}
static int FUNCTION_STEP_LCOMPLEMENT(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds-1] = ~vm->dataStack[vm->topds-2] ;
    return(0);
}
static int FUNCTION_STEP_LLOGAND(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds-2]
        = vm->dataStack[vm->topds-2] && vm->dataStack[vm->topds-1];
    vm->topds -= 1 ;
    return(0);
}
static int FUNCTION_STEP_LLOGOR(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds-2]
        = vm->dataStack[vm->topds-2] || vm->dataStack[vm->topds-1];
    vm->topds -= 1 ;
    return(0);
}
static int FUNCTION_STEP_LLOGNOT(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds-1] = !vm->dataStack[vm->topds-2] ;
    return(0);
}
static int FUNCTION_STEP_DUP(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds] = vm->dataStack[vm->topds-1] ;
    vm->topds += 1 ;
    return(0);
}
static int FUNCTION_STEP_DUP2(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds] = vm->dataStack[vm->topds-1] ;
    vm->dataStack[vm->topds+1] = vm->dataStack[vm->topds-1] ;
    vm->topds += 2 ;
    return(0);
}
static int FUNCTION_STEP_OVER(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds] = vm->dataStack[vm->topds-2] ;
    vm->topds += 1 ;
    return(0);
}
static int FUNCTION_STEP_OVER2(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds] = vm->dataStack[vm->topds-3] ;
    vm->topds += 1 ;
    return(0);
}
static int FUNCTION_STEP_SWAP(struct stepvmInC *vm,
            int dumpOnTermination) {
    stepdata_t accum ;
    accum = vm->dataStack[vm->topds-1];
    vm->dataStack[vm->topds-1] = vm->dataStack[vm->topds-2];
    vm->dataStack[vm->topds-2] = accum ;
    return(0);
}
static int FUNCTION_STEP_SWAP2(struct stepvmInC *vm,
            int dumpOnTermination) {
    stepdata_t accum ;
    accum = vm->dataStack[vm->topds-1];
    vm->dataStack[vm->topds-1] = vm->dataStack[vm->topds-3];
    vm->dataStack[vm->topds-3] = accum ;
    return(0);
}
static int FUNCTION_STEP_LFETCH(struct stepvmInC *vm,
            int dumpOnTermination) {
    stepdata_t accum ;
    accum = vm->dataStack[vm->topds-1];
    assert(accum >= vm->lower_user_static
        && accum <= vm->upper_user_static);
    /* assert stands in for an MMU check */
    vm->dataStack[vm->topds-1]
        = vm->staticMemory[accum];
    return(0);
}
static int FUNCTION_STEP_LSTORE(struct stepvmInC *vm,
            int dumpOnTermination) {
    stepdata_t accum ;
    accum = vm->dataStack[vm->topds-1];
    assert(accum >= vm->lower_user_static
        && accum <= vm->upper_user_static);
    /* assert stands in for an MMU check */
    vm->staticMemory[accum] = vm->dataStack[vm->topds-2];
    vm->topds -= 2 ;
    return(0);
}
static int FUNCTION_STEP_GOTO(struct stepvmInC *vm,
            int dumpOnTermination) {
    stepdata_t accum ;
    accum = vm->codeMemory[vm->ip];
    /* vm->ip += 1 ; */
    assert(accum >= vm->lower_user_ip
        && accum <= vm->upper_user_ip);
    vm->ip = accum ;
    return(0);
}
static int FUNCTION_STEP_GOTO0(struct stepvmInC *vm,
            int dumpOnTermination) {
    stepdata_t accum ;
    accum = vm->codeMemory[vm->ip];
    vm->ip += 1 ;
    if (vm->dataStack[vm->topds-1] == 0) {
        vm->ip = accum ;
        assert(accum >= vm->lower_user_ip
            && accum <= vm->upper_user_ip);
    }
    vm->topds -= 1 ;
    return(0);
}
static int FUNCTION_STEP_CALL(struct stepvmInC *vm,
            int dumpOnTermination) {
    stepdata_t accum ;
    accum = vm->codeMemory[vm->ip];
    vm->callStack[vm->topcs] = vm->ip + 1 ; /* next instruction */
    vm->topcs += 1 ;
    assert(accum >= vm->lower_user_ip
        && accum <= vm->upper_user_ip);
    vm->ip = accum ;
    return(0);
}
static int FUNCTION_STEP_RETURN(struct stepvmInC *vm,
            int dumpOnTermination) {
    stepdata_t accum ;
    vm->topcs -= 1 ;
    accum = vm->callStack[vm->topcs] ;
    vm->ip = accum ;
    assert(accum >= vm->lower_user_ip
        && accum <= vm->upper_user_ip);
    return(0);
}
static int FUNCTION_STEP_SYSCALL(struct stepvmInC *vm,
            int dumpOnTermination) {
    /* Implementation note - instead of running emulated code,
     * we'll just do the valid syscalls here.
    */
    stepdata_t accum ;
    vm->isSupervisorMode = 1 ;
    accum = vm->dataStack[vm->topds-1];
    if (accum == 0) {
        int buf ;
        buf = 0 ;
#ifdef DEBUGVM
        fprintf(stderr, "INPUTTING STDIN\n");
        fflush(stderr);
#endif
        (void) fscanf(stdin, "%d", &buf);
        vm->dataStack[vm->topds-1] = buf ;
    } else if (accum == 1) {
        fprintf(stdout, "%ld\n",
            (long)(vm->dataStack[vm->topds-2]));
        vm->topds -= 2 ;
    } else if (accum == 2) {
        vm->topds -= 1 ;
        if (dumpOnTermination) {
            dump_stepvmInC(vm);
            fprintf(stderr,"SYSCALL(2) termination.\n");
        }
        return(1) ;
    } else {
        dump_stepvmInC(vm);
        fprintf(stderr,"INVALID SYSCALL(%ld)\n",(long)accum);
        return(1) ;
    }
    return(0);
}
static int FUNCTION_STEP_CONST(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->dataStack[vm->topds] = vm->codeMemory[vm->ip];
    vm->topds += 1 ;
    vm->ip += 1 ;
    return(0);
}
static int FUNCTION_STEP_DROP(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->topds -= 1 ;
    return(0);
}
static int FUNCTION_STEP_DROP2(struct stepvmInC *vm,
            int dumpOnTermination) {
    vm->topds -= 2 ;
    return(0);
}
/* PRIVILEGED INSTRUCTIONS */
static int FUNCTION_STEP_SYSRETURN(struct stepvmInC *vm,
            int dumpOnTermination) {
    stepdata_t accum ;
    if (! vm->isSupervisorMode) {
        dump_stepvmInC(vm);
        fprintf(stderr,"ILLEGAL STEP_SYSRETURN from User mode.\n");
        return(1) ;
    }
    vm->isSupervisorMode = 0 ;
    vm->topcs -= 1 ;
    accum = vm->callStack[vm->topcs] ;
    vm->ip = accum ;
    assert(accum >= vm->lower_user_ip
        && accum <= vm->upper_user_ip);
    return(0);
}
static int FUNCTION_STEP_LINPUT(struct stepvmInC *vm,
            int dumpOnTermination) {
    int scanbuf ;
    if (! vm->isSupervisorMode) {
        dump_stepvmInC(vm);
        fprintf(stderr,"ILLEGAL STEP_LINPUT from User mode.\n");
        return(1) ;
    }
#ifdef DEBUGVM
    fprintf(stderr, "INPUTTING STDIN\n");
    fflush(stderr);
#endif
    scanbuf = 0 ;
    (void) fscanf(stdin, "%d", &scanbuf);
    vm->dataStack[vm->topds] = scanbuf ;
    vm->topds += 1 ;
    return(0);
}
static int FUNCTION_STEP_LOUTPUT(struct stepvmInC *vm,
            int dumpOnTermination) {
    if (! vm->isSupervisorMode) {
        dump_stepvmInC(vm);
        fprintf(stderr,"ILLEGAL STEP_LOUTPUT from User mode.\n");
        return(1) ;
    }
    fprintf(stdout, "%ld\n",
            (long)(vm->dataStack[vm->topds-1]));
    vm->topds -= 1 ;
    return(0);
}
static int FUNCTION_STEP_LDATAMEM(struct stepvmInC *vm,
            int dumpOnTermination) {
    if (! vm->isSupervisorMode) {
        dump_stepvmInC(vm);
        fprintf(stderr,"ILLEGAL STEP_LDATAMEM from User mode.\n");
        return(1) ;
    } else if (! (vm->dataStack[vm->topds-2]
            <= vm->dataStack[vm->topds-1])) {
        dump_stepvmInC(vm);
        fprintf(stderr,"STEP_LDATAMEM invalid args: %ld %ld\n",
            (long)(vm->dataStack[vm->topds-2]),
            (long)(vm->dataStack[vm->topds-1]));
        return(1) ;
    }
    vm->lower_user_static = vm->dataStack[vm->topds-2] ;
    vm->upper_user_static = vm->dataStack[vm->topds-1];
    vm->topds -= 2 ;
    return(0);
}
static int FUNCTION_STEP_LCODEMEM(struct stepvmInC *vm,
            int dumpOnTermination) {
    if (! vm->isSupervisorMode) {
        dump_stepvmInC(vm);
        fprintf(stderr,"ILLEGAL STEP_LCODEMEM from User mode.\n");
        return(1) ;
    } else if (! (vm->dataStack[vm->topds-2]
            <= vm->dataStack[vm->topds-1])) {
        dump_stepvmInC(vm);
        fprintf(stderr,"STEP_LCODEMEM invalid args: %ld %ld\n",
            (long)(vm->dataStack[vm->topds-2]),
            (long)(vm->dataStack[vm->topds-1]));
        return(1) ;
    }
    vm->lower_user_ip = vm->dataStack[vm->topds-2] ;
    vm->upper_user_ip = vm->dataStack[vm->topds-1];
    vm->topds -= 2 ;
    return(0);
}
static int FUNCTION_STEP_STARTUSER(struct stepvmInC *vm,
            int dumpOnTermination) {
    if (! vm->isSupervisorMode) {
        dump_stepvmInC(vm);
        fprintf(stderr,"ILLEGAL STEP_STARTUSER from User mode.\n");
        return(1) ;
    }
    vm->ip = vm->lower_user_ip ;
    vm->isSupervisorMode = 0 ;
    return(0);
}
static int FUNCTION_STEP_TERMINATE_VM(struct stepvmInC *vm,
            int dumpOnTermination) {
    if (! vm->isSupervisorMode) {
        dump_stepvmInC(vm);
        fprintf(stderr,"ILLEGAL STEP_TERMINATE_VM from User mode.\n");
        return(1) ;
    }
    if (dumpOnTermination) {
        dump_stepvmInC(vm);
        fprintf(stderr,"VM terminated via STEP_TERMINATE_VM\n");
    }
    return(1) ;
}

void run_stepvmInC(struct stepvmInC *vm, int dumpOnTermination) {
    int opix ;
    static opcodeFunctionPtr opcodeFunctionTable[] = {
        &FUNCTION_STEP_LADD, &FUNCTION_STEP_LSUB, &FUNCTION_STEP_LMULT,
        &FUNCTION_STEP_LDIV, &FUNCTION_STEP_LMOD, &FUNCTION_STEP_LSHL,
        &FUNCTION_STEP_LSHR, &FUNCTION_STEP_LBITAND, &FUNCTION_STEP_LBITOR,
        &FUNCTION_STEP_LBITXOR, &FUNCTION_STEP_LCOMPLEMENT, &FUNCTION_STEP_LLOGAND,
        &FUNCTION_STEP_LLOGOR, &FUNCTION_STEP_LLOGNOT, &FUNCTION_STEP_DUP,
        &FUNCTION_STEP_DUP2, &FUNCTION_STEP_OVER, &FUNCTION_STEP_OVER2,
        &FUNCTION_STEP_SWAP, &FUNCTION_STEP_SWAP2, &FUNCTION_STEP_LFETCH,
        &FUNCTION_STEP_LSTORE, &FUNCTION_STEP_GOTO, &FUNCTION_STEP_GOTO0,
        &FUNCTION_STEP_CALL, &FUNCTION_STEP_RETURN, &FUNCTION_STEP_SYSCALL,
        &FUNCTION_STEP_CONST, &FUNCTION_STEP_DROP, &FUNCTION_STEP_DROP2,
        NULL, NULL, /* There is a gap in the opcode space here. */
        &FUNCTION_STEP_SYSRETURN, &FUNCTION_STEP_LINPUT, &FUNCTION_STEP_LOUTPUT,
        &FUNCTION_STEP_LDATAMEM, &FUNCTION_STEP_LCODEMEM, &FUNCTION_STEP_STARTUSER,
        &FUNCTION_STEP_TERMINATE_VM
    };
    if (codePointers == NULL) {
        codePointers = calloc(sizeof(vm->codeMemory)/sizeof(vm->codeMemory[0]),
                sizeof(opcodeFunctionPtr));
        int codeix ;
        for (codeix = 0
                ; codeix < sizeof(vm->codeMemory)/sizeof(vm->codeMemory[0])
                ; codeix++) {
            stepcode_t opcode = vm->codeMemory[codeix];
            if (opcode >= 0 && opcode <= STEP_TERMINATE_VM) {
                codePointers[codeix] = opcodeFunctionTable[opcode];
            } else { /* in-line data in the instruction stream is NULL */
                codePointers[codeix] = NULL ;
            }
        }
    }
    vm->ip = 0 ;
    while (1) {
#ifdef DEBUGVM
        dump_stepvmInC(vm);
        stepcode_t opcode = vm->codeMemory[vm->ip];
        if (opcode < 0 || opcode > STEP_TERMINATE_VM) {
            fprintf(stderr,"ILLEGAL OPCODE AT LOCATION %d: %d\n",
                (int)(vm->ip), (int) opcode);
            fflush(stderr);
            exit(1);
        }
#endif
        opcodeFunctionPtr jumpcode = codePointers[vm->ip];
#ifdef DEBUGVM
        fprintf(stderr,"DEBUG value of jumpcode = %lx, opcode = %d\n",
            (long)jumpcode, (int)(vm->codeMemory[vm->ip]));
#endif
        vm->ip += 1 ;   /* point to in-line data or next instruction */
        /** USER MODE INSTRUCTIONS, see stepvmInC.h **/
        if ((*jumpcode)(vm,dumpOnTermination)) {
            return ;    /* Return if opcode function says to return. */
        }
    }
}

/** TEST PROGRAMS FOR THE VM:
 *  Rather than write a loader in C or write one in Python coupled
 *  here, we will just hard code a series of test cases in arrays,
 *  then load and run them as they appear on main's command line.
 *  Cheap and fast.
 *  STEP_SYSCALL(0) does a STEP_LINPUT.
 *  STEP_SYSCALL(1) does a STEP_LOUTPUT.
 *  STEP_SYSCALL(2) terminates the VM program.
 *  STEP_LDATAMEM gets set at entry and is never modified in the first test.
 *  STEP_LCODEMEM gets set at entry and is never modified in the first test.
**/

/* Start BASIC test: */
static stepcode_t BASIC_codeMemory[] = {
    /* STARTUP CODE IN SUPERVISOR MODE: */
    STEP_CONST, 0, STEP_CONST, (STATIC_MEMORY_SIZE-1), STEP_LDATAMEM,
    STEP_CONST, 17 /* see start of user code below */,
    STEP_CONST, 57 /* see end of user code below */,
    STEP_LCODEMEM,
    STEP_STARTUSER, /* just in case: */ STEP_TERMINATE_VM,
    /* We are now at location [12] in code for syscall(0). */
    STEP_LINPUT, STEP_SYSRETURN,
    /* We are now at location [14] in code for syscall(1). */
    STEP_LINPUT, STEP_SYSRETURN,
    /* We are now at location [16] in code for syscall(2). */
    STEP_TERMINATE_VM,
    /* USER PROGRAM starts at location [17], see STEP_LCODEMEM above. */
    /* USER PROGRAM computes BASE**POWER, hard code long-running values. */
    /* USER PROGRAM prints resulting value (BASE**POWER) via SYSCALL(1),
    /* [17] */ STEP_CONST, 2, STEP_CONST, 3, STEP_CALL, 38, /* 2**3 */
                STEP_CONST, 1, STEP_SYSCALL, /* output the result of call */
    /* [26] */ STEP_CONST, 2, STEP_CONST, 62, STEP_CALL, 38, /* 2**62 */
                STEP_CONST, 1, STEP_SYSCALL, /* output the result of call */
    /* [35] */ STEP_CONST, 2, STEP_SYSCALL, /* exit() system call */
    /* [38] is start of the subroutine that computes v1**v2 from stack */
    /* [38] */ STEP_CONST, 1, /* data stack is BASE, POWER, 1 at THIS POINT,
        iterate until power hits 0, then jump to function exit at bottom,
        which cleans up data stack and returns the value. accumulator on top.
    */
    /* [40] */ STEP_OVER /* POWER */, STEP_GOTO0, 53, /* to bottom on done */
    /* [43] */ STEP_OVER2, STEP_LMULT,  /* multiply BASE into accumulator */
    /* [45] */ STEP_OVER, STEP_CONST, 1, STEP_LSUB, STEP_SWAP2, STEP_DROP,
    /* [51] at this point we have updated BASE, POWER, ACCUM, goto loop top */
    /* [51] */ STEP_GOTO, 40, /* 40 is the top of loop */
    /* [53] */ STEP_SWAP, STEP_DROP, STEP_SWAP, STEP_DROP, /* drop POWER BASE */
    /* [57] ACCUM is on stack */
    /* [57] */ STEP_RETURN /* 57 is the last valid user code address */
};
/* End BASIC test: */

int main(int argc, char **argv) {
    static char *USAGE =
    "stepvmSubroutineInC DUMPONTERMINATION? TEST(e.g.BASIC) REPCOUNT\n";
    int isdump = 1 ;
    int i ;
    struct stepvmInC *vm = (struct stepvmInC *)
        malloc(sizeof(struct stepvmInC));
    stepvmInC_constructor(vm,NULL,0,NULL,0,NULL,0,NULL,0,1);
    if (argc < 4 || ((argc & 1) != 0)) {
        fprintf(stderr, "INVALID COMMAND LINE: ");
        for (i = 0 ; i < argc ; i++) {
            fprintf(stderr, "%s ", argv[i]);
        }
        fprintf(stderr, "\n");
        fprintf(stderr, "%s", USAGE);
        exit(1);
    }
    isdump = atoi(argv[1]);
    for (i = 2 ; i < argc ; i+= 2) {
        int reps = 0 ;
        reps = atoi(argv[i+1]);
        if (reps < 1) {
            fprintf(stderr,"Invalid reps count of %d for %s\n",
                reps, argv[i]);
            exit(1);
        }
        if (strcmp(argv[i], "BASIC") == 0) {
            int j ;
            struct tms before, after ;
            double utime, stime ;
            struct timeval tvbefore, tvafter ;
            time_t tbefore = (time_t)0, tafter = (time_t)0 ;
            memset(&before, 0, sizeof(before));
            memset(&after, 0, sizeof(after));
            memset(&tvbefore, 0, sizeof(tvbefore));
            memset(&tvafter, 0, sizeof(tvafter));
            stepvmInC_constructor(vm,
                NULL,0, /* data stack */
                NULL,0, /* static memory */
                NULL,0, /* call stack */
                BASIC_codeMemory,
                    sizeof(BASIC_codeMemory)/sizeof(BASIC_codeMemory[0]),1);
            if ((tbefore = time(NULL)) == (time_t)-1) {
                perror("time(NULL)");
            }
            if (gettimeofday(&tvbefore, NULL) == -1) {
                perror("gettimeofday");
            }
            if (times(&before) == (clock_t) -1) {
                perror("times(&before)");
            }
            for (j = 0 ; j < reps ; j++) {
                run_stepvmInC(vm,isdump);
            }
            if (times(&after) == (clock_t) -1) {
                perror("times(&after)");
            }
            if (gettimeofday(&tvafter, NULL) == -1) {
                perror("gettimeofday");
            }
            if ((tafter = time(NULL)) == (time_t)-1) {
                perror("time(NULL)");
            }
            utime = (after.tms_utime - before.tms_utime)
                / (double) sysconf(_SC_CLK_TCK);
            stime = (after.tms_stime - before.tms_stime)
                / (double) sysconf(_SC_CLK_TCK);
            /*
            fprintf(stderr, 
                "\trun_stepvmInC elapsed real time = %d secs\n",
                    (int)(tafter-tbefore));
            */
            fprintf(stderr, 
                "\trun_stepvmInC elapsed real time = %f secs\n",
                    (double)(tvafter.tv_sec - tvbefore.tv_sec)
                    + (double)(tvafter.tv_usec - tvbefore.tv_usec)
                        / 1000000.0);
            fprintf(stderr, 
                "\trun_stepvmInC user CPU time = %f secs\n", utime);
            fprintf(stderr, 
                "\trun_stepvmInC system CPU time = %f secs\n", stime);
        } else {
            fprintf(stderr, "Invalid command line arg: %s\n", argv[i]);
            exit(1);
        }
    }
    return 0 ;
}
