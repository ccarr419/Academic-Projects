# CSC343Sim.py, D. Parson, Fall 2013
# This module defines some simulation classes
# for use in CSC 343 Operating Systems, beginning Fall 2013.
# http://faculty.kutztown.edu/parson
#
# package state2codeV15
#
# August 2015 sees a major overhaul of CSC343Sim.py to eliminate
# multithreading, which is expensive because of locks and other
# interactions with the O.S., which are not useful because
# both this run-time framework and the Python GIL enforce
# one-thread-at-a-time execution. Revised by making the run() methods
# of generated __scheduledObject__s be Python generators (which were previously
# thread run() methods). A run() generator yields whenever a
# blocking library call places its state machine into a suspended
# state. This is now a strictly single-threaded framework.
# D. Parson, V10 begun August 11, 2015.
# V14 replaces has_key and sort() on keys() for preparation to move
# to Python 3 in V15. August 2017.

# July 2017 port to Linux, only change:
# 1. In class class __simulationLogger__ log levels WERE:
#        Parameter loglevel is one of
#            0 (minimal),
#            1 (some logging),
#            2 (log as much information as possible),
#            3 adds internal debugging MSGs.
#    CHANGED TO THIS. Linux was *slow* when using flush() at level 2.
#        Parameter loglevel is one of
#            0 (minimal),
#            1 (some logging of required simulation progress),
#            2 (log simulation state info and msgs, but minimize flush() calls,
#            3 (log simulation state info and msgs, use flush() (slow on Linux),
#            4 adds internal debugging MSGs.
__LOGMIN__ = 0
''' 0 does minimal logging of simulation changes. '''
__LOGSOME__ = 1
''' 1 does almost minimal logging of simulation changes. '''
__LOGSIM__ = 2
''' 2 logs state changes & msgs, no flush() which is slow on Linux. '''
__LOGFLUSH__ = 3
''' 3 logs state changes & msgs with flush() for crash diagnostics. '''
__LOGINTERNAL__ = 4
''' 4 logs internal simulator debug info & flushes. '''
__DEBUGLEVEL__ = 4
''' msg() DEBUG messages >= __DEBUGLEVEL__ for internal simulator debugging.'''

# This is the run-time VM of the simulation system.
# See State2CodeParser.py for the compiler front end and
# State2CSC343Sim.py for the compiler back end, where the
# compiler translates UML-like state machine diagrams
# (in a textual, rule-based description language) into
# simulation code that uses CSC343Sim at simulation time.

import sys
import random
import heapq
import time
import copy


class __simulationScheduler__(object):
    '''
    A __simulationScheduler__ object acts like a gloried "sleep"
    server for all applications objects in the simulation. An object
    puts itself to sleep for some number of ticks within
    __simulationScheduler__.q scheduling queue by invoking sleep()
    on this object. sleep() returns immediately, and it is the
    responsibility of the __scheduledObject__ that invokes
    __simulationScheduler__.sleep(), either directly or indirectly,
    to yield from its run() generator. The state machine compiler
    handles generating yield for all blocking calls.
    '''
    __serialno__ = 0
    def __init__(self, logger, simtime):
        '''
        Initialize the scheduling q field and related state.
        Do not start the simulation; startup code must call __run__()
        on this object after inserting one or more __scheduledObject__
        objects into the scheduling queue via sleep() on this object.
        Parameter logger is the __simulationLogger__ object.
        Parameter simtime is the maximum simulation (clock) time.
        '''
        self.time = 0
        self.logger = logger
        self.simtime = simtime
        self.q = []
        # self.q is a heapq of n-tuples of the following fields
        # (time, serialNo, waitingObject, eventType, eventArg)
    def __run__(self):
        '''
        This single-threaded __run__ method runs until its self.q
        scheduling q is empty, at which point __run__ exits the process.
        The framework must place __scheduledObject__ objects into the
        self.q, e.g. by invoking sleep(), before invoking this __run__
        method. Invoking __run__ with an empty self.q exits immediately.
        This method never returns; it exits.
        '''
        statusTime = time.time()
        if len(self.q) == 0:
            sys.stderr.write('No INITIAL activity in this simulation (1). ' \
                + 'Consult log file.\n')
            self.msg("Scheduler exiting at time "            \
                + str(self.time) + ' within time limit '    \
                + str(self.simtime) + ' because of initial inactivity.')
            self.logger.flush()
            sys.exit(1)
        try:
            while len(self.q):
                tmptime, serialNo, waitingObject, eventType, eventArg      \
                    = heapq.heappop(self.q)
                waitingObject.waitingInQueue = False
                if self.logger.getLevel() >= __DEBUGLEVEL__:
                    self.msg("DEBUG SCHED POP "
                        + str((tmptime, serialNo, waitingObject, eventType,
                            eventArg))
                                + ' STK ' + str(len(self.q)) + '\n')
                self.time = tmptime
                if self.time >= self.simtime:
                    msg ="Simulation exiting at time "      \
                        + str(self.time) + ", which meets or exceeds limit " \
                        + str(self.simtime) + '.'
                    sys.stderr.write(msg + '\n')
                    self.msg(msg)
                    self.logger.flush()
                    sys.exit(0)
                waitingObject.__sleepResult__                           \
                    = (tmptime, eventType, eventArg)
                if self.logger.getLevel() >= __DEBUGLEVEL__:
                    self.msg("DEBUG SCHED REL " + str(waitingObject) + ' '
                        + ' STK ' + str(len(self.q)) + '\n')
                tttime = time.time()
                if (tttime - statusTime) >= 5:  # Write peanut to console.
                    sys.stderr.write('.')
                    sys.stderr.flush()
                    statusTime = tttime
                try:
                    waitingObject.__generator__.next()  # run() the model
                except StopIteration:
                    # the __scheduledObject__ is terminated
                    pass # Any pending calls raise StopIteration imemdiately.
                if (tttime - statusTime) >= 5:  # Write peanut to console.
                    sys.stderr.write('.')
                    sys.stderr.flush()
                    statusTime = tttime
        finally:
            sys.stderr.write('\n')
        msg = "Scheduler exiting at time "            \
                + str(self.time) + ' within time limit '    \
                + str(self.simtime) + ', simulation has finished.'
        sys.stderr.write(msg + '\n')
        self.msg(msg)
        self.logger.flush()
        sys.exit(0)
    def sleep(self, delay, waitingObject, eventType, eventArg):
        '''
        Place the invoking waitingObject on a wait self.q until its
        simulated delay has elapsed. The invoking thread returns
        after enqueuing waitingObject, since this is a single-threaded
        framework as of 8/2015.
        Parameters:
            self: this __simulationScheduler__ object.
            delay: the non-negative number of simulated ticks to
                elapse before the calling thread is awakened.
            waitingObject: a __scheduledObject__ object, a.k.a. model.
                waitingObject.__sleepResult__ must be defined as a field
                that sleep() initially sets to None, and then sets to
                (time, eventType, eventArg)
                when the delays elapses, where time is current time + delay.
                Also, waitingObject.__generator__ must be the Python
                generator created by waitingObject.run() at waitingObject
                construction time.
            eventType: event type returned via waitingObject.__sleepResult__,
                typically a string
            eventArg: event type returned via waitingObject.__sleepResult__,
                it can be any application-required type.
            Return value is the simulated time when waitingObject will awake.
        '''
        if type(delay) != int or delay < 0:
            raise ValueError("ERROR: Invalid delay to sleep: " + str(delay))
        waitingObject.__sleepResult__ = None
        later = self.time + delay
        serialNo = __simulationScheduler__.__serialno__
        __simulationScheduler__.__serialno__ += 1
        if self.logger.getLevel() >= __DEBUGLEVEL__:
            self.msg("DEBUG PREP BLK "
                + str((later, serialNo, waitingObject, eventType, eventArg))
                    + ' STK ' + str(len(self.q)) + '\n')
        waitingObject.waitingon = eventType
        waitingObject.exclusiveWait = True      # always true when in a queue
        waitingObject.waitingInQueue =  \
            "waiting on simulation scheduler (simulation sleep)"
        heapq.heappush(self.q, (later, serialNo, waitingObject, eventType,
            eventArg))
        # self.logger.file.write("PRE-SLEEP DEBUG\n")
        self.logger.log(waitingObject)
        # self.logger.file.write("POST-SLEEP DEBUG\n")
        if self.logger.getLevel() >= __DEBUGLEVEL__:
            self.msg("DEBUG SCHED BLK " + str(waitingObject) + ' ' + ' STK '
                + str(len(self.q)) + '\n')
    def yieldPrivate(self, waitingObject, eventType, isexclusive=False):
        '''
        yieldPrivate is like the "head of a sleep()" call that mutates
        __scheduledObject__ waitingObject to look like it is sleeping,
        but does not place it into this __simulationScheduler__'s queue.
        Restarting the waitingObject must occur elsewhere, e.g. in
        event delivery, which then calls unyieldPrivate() to place
        waitingObject into this __simulationScheduler__'s queue.
        Parameters:
            self: this __simulationScheduler__ object.
            waitingObject: an active application object, i.e.,
                running on the invoking thread. waitingObject.__sleepResult__
                must be defined as a field that yieldPrivate() initially sets
                to None; it also sets waitingObject.waitingon = eventType
            eventType: event type stored into waitingObject.waitingon,
                typically a string
            isexclusive when True means waitingObject will not respond to
                signalEvent for events other than eventType; default is False.
        '''
        waitingObject.__sleepResult__ = None
        waitingObject.waitingon = eventType
        waitingObject.exclusiveWait = isexclusive
        # self.logger.file.write("PRE-YIELD DEBUG\n")
        self.logger.log(waitingObject)
        # self.logger.file.write("POST-YIELD DEBUG\n")
        if self.logger.getLevel() >= __DEBUGLEVEL__:
            self.msg("DEBUG SCHED STALL " + str(waitingObject) + ' '
                + ' STK ' + str(len(self.q)) + '\n')
    def unyieldPrivate(self, waitingObject, eventType, eventArg):
        '''
        unyieldPrivate is the follow-up by a __scheduledObject__
        waitingObject that has called yieldPrivate, to reenter the simulation.
        The waitingObject simply reenters the scheduling queue with a time
        delay of 0. See yieldPrivate().
        Parameters:
            self: this __simulationScheduler__ object.
            waitingObject: a __scheduledObject__ object previously
                passed to yieldPrivate with no intervening calls to
                unyieldPrivate or __simulationScheduler__.sleep().
            eventType: event type returned via waitingObject.__sleepResult__,
                typically a string
            eventArg: event type returned via waitingObject.__sleepResult__,
                it can be any application-required type.
            Return value is the simulated time when unyieldPrivate will time out.
        '''
        waitingObject.__sleepResult__ = None
        later = self.time + 0
        serialNo = __simulationScheduler__.__serialno__
        __simulationScheduler__.__serialno__ += 1
        waitingObject.waitingon = eventType
        waitingObject.exclusiveWait = True      # always true when in a queue
        waitingObject.waitingInQueue =  \
            "waiting on simulation scheduler (simulation unyield)"
        heapq.heappush(self.q, (later, serialNo, waitingObject, eventType,
            eventArg))
        # self.logger.file.write("PRE-UNY DEBUG\n")
        # self.logger.log(waitingObject)
        # self.logger.file.write("POST-UNY DEBUG\n")
        if self.logger.getLevel() >= __DEBUGLEVEL__:
            self.msg("DEBUG SCHED UNSTALL " + str(waitingObject) + ' ' + ' STK '
                + str(len(self.q)) + '\n')
        return later
    def msg(self, message):
        '''
        Log text message from user code to log file.
        '''
        if self.logger.isOpen() and message:
            ttime = str('%012d' % self.time)
            f = self.logger.getFile()
            f.write(ttime + ",MSG,scheduler," + message + '\n')
            if self.logger.getLevel() >= __LOGFLUSH__:
                self.logger.flush()

class Queue(object):
    '''
    Queue can be either a FIFO queue or a min-priority queue implemented
    using library package heapq. Its FIFO versus min-priority queue is
    set when it is constructed.
    '''
    def __init__(self, ispriority):
        '''
        Construct a Queue, as a FIFO Queue if parameter ispriority is
        False, else construct a priority Queue using a min
        heap, i.e., where the enqueued entry with the smallest priority
        value has the highest priority.
        '''
        self.ispriority = True if ispriority else False
        self.q = []
        self.sequence = 0
        self.isDisorganized = False
    def clear(self):
        '''
        Clear (empty) this Queue, reinitializing it to an empty Queue.
        '''
        self.q = []
        self.sequence = 0
        self.isDisorganized = False
    def __copy__(self):
        '''
        Return a shallow copy of this Queue object, such that if references
        to objects reside in the source Queue, the same references to
        those objects reside in the returned copy.
        '''
        myclone = Queue(self.ispriority)
        myclone.q = copy.copy(self.q)
        myclone.sequence = self.sequence
        myclone.isDisorganized = self.isDisorganized
        return myclone
    def clone(self):
        '''
        Return a shallow copy of this Queue object, such that if references
        to objects reside in the source Queue, the same references to
        those objects reside in the returned copy.
        '''
        return self.__copy__()
    def len(self):
        '''
        Returns the number of elements in this queue, >= 0.
        '''
        return len(self.q)
    def __len__(self):
        '''
        Returns the number of elements in this queue, >= 0.
        '''
        return len(self.q)
    def enq(self, obj, priority=None):
        '''
        enq(obj, priority) enqueues the object pointed to by
            obj into this Queue, where priority must be None (default) for a
            FIFO queue, and must be any non-None value that can
            be compared in sort order to other priority values.
            The priority is typically a number, but it can be a tuple
            for numbers, for example, in the order:
            (mostSignificantKey, ... , leastSignificantKey).
            This is a min-queue, so use the "-" minus sign if
            necessary when a lrage value is the higher priority.
            RETURN value is an opaque handle that a client can pass
            to reprioritize() to change this obj's priority or to
            delete() to delete this entry from the queue.
        '''
        if (self.ispriority and priority is None):
            raise ValueError("ERROR, enq() requires a non-None priority: " \
                + str(priority))
        elif ((not self.ispriority) and not (priority is None)):
            raise ValueError("ERROR, FIFO enq() requires None priority: " \
                + str(priority))
        entry = (priority, self.sequence, obj)
        self.sequence += 1
        if self.ispriority and not self.isDisorganized:
            heapq.heappush(self.q, entry)
        else:
            self.q.append(entry)
        return entry
    def age(self, unaryAgingFunction, preservesOrder=False):
        '''
        age iterates through all elements in a priority Queue
        and applies the single-parameter function
        unaryAgingFunction to every priority, giving each
        element a new priority. If the caller determines
        that unaryAgingFunction preserves the relative order
        of the min-queue (all priority relationships stay the
        same), then the caller can set preservesOrder to True
        to avoid the overhead of resorting the Queue. The
        caller may pass preservesOrder=True only when
        unaryAgingFunction preserves relative comparison order
        of the priorities. Otherwise, preservesOrder must be
        its default value of False. This method raises
        ValueError when applied to a FIFO Queue.
        '''
        if not self.ispriority:
            raise ValueError("ERROR, age called on a FIFO")
        for i in xrange(0, len(self.q)):
            self.q[i] = (unaryAgingFunction(self.q[i][0]),
                self.q[i][1], self.q[i][2])
        if len(self.q) and not preservesOrder:
            self.isDisorganized = True
    def deq(self):
        '''
        deq() : obj dequeues and returns the obj at the front of the Queue.
        '''
        if self.isDisorganized:
            heapq.heapify(self.q)
            self.isDisorganized = False
        if self.ispriority:
            entry = heapq.heappop(self.q)
        else:
            entry = self.q[0]
            del self.q[0]
        o = entry[2]
        return o
    def gen(self, isDestructive):
        '''
        Return a generator that iterates over elements in the Queue
        in FIFO or priority order as set by the Queue constructor.
        Setting flag isDestructive=True modified the contents of
        this Queue, invoking deq() until 0 elements remain.
        Setting flag isDestructive=False invokes deq() on a clone()
        of this Queue object. Note that if the calling client code
        changes the contents of an isDestructive=True Queue after gen()
        returns a generator, the values returned by the generator
        are undefined and may be erroneous.
        '''
        qobj = self
        if not isDestructive:
            qobj = self.clone()
        while qobj.len() > 0:
            yield qobj.deq()
        return
    def peek(self):
        '''
        peek() : obj, returns the obj at the front of the queue without
            removing it from the queue.
        '''
        if self.isDisorganized:
            heapq.heapify(self.q)
            self.isDisorganized = False
        entry = self.q[0]
        o = entry[2]
        return o
    def reprioritize(self, handle, priority):
        '''
        Change the priority of a previously enqueued value to the
        priority parameter's value, where handle is a value previously
        returned by enq. This method throws an exception if
        this is a FIFO queue, or if the handle is no longer in this queue,
        or if priority is invalid according to the documentation for enq().
        RETURN value is the new handle; the previous one is no
        longer valid after this call.
        '''
        if not self.ispriority:
            raise ValueError("ERROR, reprioritize called on a FIFO")
        if priority is None:
            raise ValueError("ERROR, None priority: "  \
                + str(priority))
        if not handle in self.q:
            raise ValueError("ERROR, invalid handle: "  \
                + str(handle))
        self.isDisorganized = True
        ix = self.q.index(handle)
        del self.q[ix]
        entry = (priority, handle[1], handle[2])
        self.q.append(entry)
        return entry
    def delete(self, handle):
        '''
        Delete a previously enqueued value from the queue, where handle
        is a value previously returned by enq. This method throws an
        exception if the handle is no longer in this queue.
        This method applies to a FIFO or priority queue.
        RETURN value is the old, enqueued object value.
        '''
        if not handle in self.q:
            raise ValueError("ERROR, invalid handle: "  \
                + str(handle))
        ix = self.q.index(handle)
        del self.q[ix]
        if self.ispriority:
            self.isDisorganized = True
        return handle[2]

class PCB(object):
    '''
    PCB is the process control block. It is a data container for fields
    used by the processor and thread active objects. Each new process
    create by fork() gets its own  PCB object, which will maintain
    a virtual memory map and open I/O file handles for assignments 3 & 4.
    All threads running in a process go into the threads[] list.
    PCB presently defines the following fields:
        1. pid is the unique process ID.
        2. threads [] is a sequence of thread object references in their
           order of creation in this process, from thread[0] (the initial
           thread) through thread[N-1], where N == len(threads). <defunct>
           threads remain in this sequence until some thread in the process
           runs exit(), which kills all remaining threads in the process and
           removes the PCB.
        3. activeThreads is a counter that starts as 1 upon fork(); each spawn()
           must increment it. When a thread dies it must decrement it and
           release joiners. When activeThreads goes to 0 the triggering thread
           must release waiters.
        4. exitStatus is exit status of the PCB's process, initialized to 0.
        5. child [] is a list of processIDs forked by this process' threads.
        6. parent is the processor for a top-level process, or the parent
           PCB for a fork()ing process' thread.
    '''
    __count__ = 0
    def __init__(self, scheduler, parent):
        '''
        Parameter scheduler is the __simulationScheduler__ object.
        '''
        self.scheduler = scheduler
        self.pid = PCB.__count__
        PCB.__count__ += 1
        self.threads = []
        self.waiters = []       # thread object references
        self.child = []         # all child PIDs forked from this process
        self.activeThreads = 0  # initial fork() bumps this to 1
        self.exitStatus = None
        self.parent = parent
    def wait(self, callingobj, threadobj):
        '''
        Called to wait on this PCB's process' death, this is a blocking call
        that waits until termination of the last thread in this process.
        A thread in this process should not invoke wait(), because the
        invoking thread is not dead, so wait will never terminate.
        Parameter *callingobj* is the object making the blocking call,
        may be either a _Thread_ or a _SubGraph_ of a _Thread_.
        Parameter *threadobj* is the top-level _Thread_.
        Return value is the exit status.
        '''
        if self.activeThreads > 0:
            if threadobj in self.threads:
                msg = ("ERROR, thread '" + str(threadobj)
                    + "' called 'wait' on its own PCB, pid = "
                    + str(self.pid) + ".")
                sys.stderr.write(msg + '\n')
                raise RuntimeError(msg)
            self.waiters.append(callingobj)
            self.scheduler.yieldPrivate(callingobj, 'wait', isexclusive=True)
        else:
            self.scheduler.sleep(1,callingobj,'wait',
                0 if self.exitStatus == None else self.exitStatus)
    def exit(self, exitstatus):
        '''
        Exit this process, rudely aborting all threads.
        Do not release wait()ers -- the final thread does that when it dies
        by calling retire().
        '''
        if self.exitStatus == None or self.exitStatus == 0:
            # Set it only once, although override 0 status.
            self.exitStatus = exitstatus
        for t in self.threads:
            if not t.__isdead__:
                t.__isdead__ = True
                if not t.waitingInQueue:
                    self.scheduler.sleep(1,t,'exit',self.exitStatus)

class __scheduledObject__(object):
    '''
    __scheduledObject__ is the base class for _Processor_, _IOunit_,
    _Thread_, _SubGraph_, and any other __scheduledObject__ object classes
    added to this simulation framework. It *is* a state machine model object.
    A subclass such as a concrete subclass of _Processor_ must define a run()
    method with no parameters that constructs the Python generator the state
    machine for that object.
    The compiler back end in State2CSC343Sim.py generates the run() method.
    The default run() method in this class raises AttributeError.
    The concrete subclass must store the generator returned from run()
    in the __generator__ field.
    The simulation scheduler sets __generator__ to None upon termination
    of the __scheduledObject__ state machine (a.k.a. model).
    '''
    __serial__ = 0
    def __init__(self, scheduler, logger, factory, seed=None):
        '''
        Initialize base class fields having to do with __generator__ &
        synchronization with __simulationScheduler__ after invoking
        the base class constructor. The __simulationScheduler__ object
        actually invokes __generator__.next() to run this __scheduledObject__.
        Parameter scheduler is the __simulationScheduler__ object.
        Parameter logger is the __simulationLogger__ object.
        Parameter factory is a map of  function references {
          'processor' : processorFactory,
          'thread' : threadFactory,
          'io' : iofactory),
        each taking the same non-self parameters as the constructors for
        _Processor_, _Thread_ and _IOunit_ respectively; each is a function
        that invokes a constructor for a derived class).
        Parameter *seed* is the seed for the random sampleGenerator,
        default None uses the current system time, OR seed can be an
        instance of random.Random borrowed from an active object calling
        an inactive object.
        Field __sleepResult__ is set to (time, 'init', None) -- all state
        machines take 'init' as the first event.
        The __generator__ field is set to None, and mist be initialized
        by the concrete class constructor. That code is in CSC343.template.txt.
        '''
        self.scheduler = scheduler
        self.logger = logger
        self.factory = factory
        self.__sleepResult__ = (scheduler.time, 'init', None)
        self.__generator__ = None
        if isinstance(seed, random.Random):
            # sys.stderr.write('DEBUG SUBGRAPH REUSES GEN\n')
            self.sampleGenerator = seed
            self.seed = None
        else:
            self.seed = seed
            self.sampleGenerator = random.Random()
            self.sampleGenerator.seed(seed)
        self.state = 'init'     # Mandatory start state is 'init'.
        self.waitingon = None   # Generated run() method sets waitingon.
        self.exclusiveWait = False
        self.waitingInQueue = False # Do not signal/interrupt sleep() or io()
        self.lastStateLogged = None
        self.globals = {}           # Placeholder for subclasses.
        self.locals = {}            # Placeholder for subclasses.
        # Each subclass must set self.__generator__ = self.run() at the
        # last step of construction. This code appears in CSC343.template.txt.
    def run(self):
        'Raise an AttributeError. A subclass must implement run(self).'
        raise AttributeError("INTERNAL ERROR, run() not defined.")
    def log(self, file, loglevel, tag=None):
        'Raise an AttributeError. A subclass must implement log.'
        raise AttributeError("INTERNAL ERROR, log() not defined.")
    def msg(self, message):
        'Raise an AttributeError. A subclass must implement log.'
        raise AttributeError("INTERNAL ERROR, msg() not defined.")
    def sample(self, lower, upper, distType, *parameters):
        '''
        Return an integer in the inclusive range [lower, upper] where
        lower and upper are integers, and distType and parameters covary
        as follows.
        distType = 'uniform' gives a uniform distribution in the range
            [lower, upper] with parameters ignored.
        distType = 'gaussian' gives a gaussian distribution in the range
            [lower, upper] with parameters (mu, sigma) where mu is
            an int or float withing the range [lower, upper] that is the
            distribution mean, and sigma is the standard deviation. Results
            outside the range are discarded until a valid value
            is found and returned.
        distType = 'exponential' gives a exponential distribution in the range
            [lower, upper] with parameter (mu,) where mu is
            an int or float withing the range [lower, upper] that is
            the mean; the closer it is to lower, the steeper the dropoff.
            Results outside the range are discarded until a valid value
            is found and returned.
        distType = 'revexponential' gives a reverse exponential distribution
            in the range [lower, upper] that grows towards upper, with
            parameter (mu,) where mu is an int or float withing the range
            [lower, upper] that is the mean; the closer it is to upper,
            the steeper the rise.
            Results outside the range are discarded until a valid value
            is found and returned.
        '''
        return __scheduledObject__.__sample__(lower, upper, distType,   \
            self.sampleGenerator, parameters)
    def assign(self, variable, value):
        '''
        assign the value parameter into the variable parameter, i.e.,
        variable = value, where variable is the string name of
        the variable. Returns a copy of the value.
        '''
        return __scheduledObject__.__help_assign__(variable, value,
            self.globals, self.locals)
    def waitForEvent(self, eventType, isexclusive=False):
        '''
        *waitForEvent(self, eventType, isexclusive) is the mechanism for
            waiting for an eventType delivered by another model (a.k.a.
            state machine) in the simulation, which is delivered by another
            model calling waitingobj.signalEvent(waitingobj,eventType,eventArgs)
            with the waitingobj simobj as the object parameter.
            Parameter isexclusive, if True, means respond only to that
            eventType; when False, respond to the arrival of any event.
        '''
        self.__sleepResult__ = None
        self.exclusiveWait = isexclusive
        self.scheduler.yieldPrivate(self, eventType)
        if self.logger.getLevel() >= __DEBUGLEVEL__:
            self.msg("DEBUG WAIT4EVT ENTER " + str(self)
                + ", cur eventType: "    \
                    + str(eventType)
                    + ", cur isexclusive: "    \
                    + str(isexclusive) + '\n')
    @staticmethod
    def signalEvent(waitingobj, eventType, *results):
        '''
        signalEvent(waitingobj, eventType, *results) signals the waitingobj
            waiting within waitForEvent with the eventType and optional results
            value(s). See waitForEvent. Note that if the waitingobj is
            blocked in a scheduling queue such as the main simulation
            scheduler or an IO unit, it will log an INFO MSG stating
            that it is ignoring the signaled event; state machine models
            cannot respond to signals while blocked in a scheduling queue;
            in such cases the model ignores the event, and the application
            state machine must provide other means than signals for
            ensuring no loss of data; being blocked in a queue means that
            the model is already scheduled for execution, and when it
            resumes executing, it can poll the signalled condition.
        '''
        if waitingobj.logger.getLevel() >= __DEBUGLEVEL__:
            waitingobj.msg("DEBUG SGNLEVT ENTER " + str(waitingobj)
                + ", cur __sleepResult__: " \
                    + str(waitingobj.__sleepResult__)
                    + ', PLAN __sleepResult__: ' \
                    + str([waitingobj.scheduler.time, eventType, results])
                    + '\n')
        if not eventType in waitingobj.__eventSet__:
            raise ValueError("Event type " + eventType
                + " not in event set " + str(waitingobj.__eventSet__)
                + " for this state machine.")
        if (waitingobj.waitingInQueue):
            waitingobj.msg("WARNING, signalEvent discards event type "
                + str(eventType) + " because model is waiting in queue: "
                + str(waitingobj.waitingInQueue)
                + " for model: "
                + str(waitingobj))
            return
        if (waitingobj.exclusiveWait and eventType != waitingobj.waitingon):
            waitingobj.msg("WARNING, signalEvent discards event type "
                + str(eventType) + ", it does not match exclusive type "
                + str(waitingobj.waitingon) + " for model "
                + str(waitingobj))
            return
        waitingobj.scheduler.unyieldPrivate(waitingobj, eventType, results)
        if waitingobj.logger.getLevel() >= __DEBUGLEVEL__:
            waitingobj.msg("DEBUG SGNLEVT RETURN "
                + str(waitingobj) + ", cur __sleepResult__: "
                + str(waitingobj.__sleepResult__) + ', PLAN __sleepResult__: '
                    + str([waitingobj.scheduler.time, eventType, results])
                    + '\n')
    @staticmethod
    def __help_assign__(variable, value, globals, locals):
        exec(variable + ' = ' + repr(value), globals, locals)
        return value
    @staticmethod
    def noop():
        '''
        noop() does nothing and returns None, it is useful as a
        default else in a conditional expression when no else value
        is needed.
        '''
        return None
    @staticmethod
    def __sample__(lower, upper, distType, sampleGenerator, parameters):
        ''' Helper static function for sample(). '''
        if type(lower) != int  or type(upper) != int or lower > upper:
            raise ValueError("Invalid range of values for sample: ["  \
                + str(lower) + ", " + str(upper) + "]")
        result = lower - 1
        flower = float(lower)
        fupper = float(upper)
        if len(parameters) > 0:
            mu = float(parameters[0])
            if mu < lower or mu > upper:
                raise ValueError("Invalid mu value " + str(mu)    \
                    + " for range of values for sample: ["  \
                    + str(lower) + ", " + str(upper) + "]")
        else:
            mu = None
        if distType in ['exponential', 'revexponential']            \
                and (lower < 0 or mu is None or mu <= 0.0 or mu >= upper):
                    raise ValueError("Invalid mu value " + str(mu)    \
                        + " or limit for range of values for sample: ["  \
                        + str(lower) + ", " + str(upper) + "]")
        while result < lower or result > upper:
            if distType == 'uniform':
                result = int(sampleGenerator.uniform(lower,upper+1))
            elif distType == 'gaussian':
                sigma = float(parameters[1])
                result = int(round(sampleGenerator.gauss(mu, sigma)))
            elif distType == 'exponential':
                result = int(round(sampleGenerator.expovariate(1.0/mu)))
            elif distType == 'revexponential':
                mymu = (upper - mu) + lower     # base the knee on upper bound
                result = int(round(sampleGenerator.expovariate(1.0/mymu)))
                if result >= lower and result <= upper:
                    result = upper - (result - lower)
            else:
                raise ValueError("Invalid distType for sample: " + str(distType))
        return result

class __ThreadRetireException__(Exception):
    '''
    A _Thread_ object invoking retire() raises this exception to terminate.
    It is not an error.
    '''
    pass

class _Processor_(__scheduledObject__):
    '''
    _Processor_ extends __scheduledObject__ by adding the following fields:
        contextCount is the count of total hardware contexts.
        contextsFree is the count of available hardware contexts.
        fastio [] provides slots for _IOunit_ object references.
        msgbuf [] is reserved, currently unused.
        pcb {} is the set of current running processes, stored as a map
            {pid : PCB} (i.e., a map from pid to a PID object reference)
        child [] is a list of still-running PIDs (process IDs) forked by
            this _Processor_ object.
        number of the _Processor_ object, starting at 0.
        state defaults to None; it is set by the generated state machine.
        sampleGenerator resides in base class __scheduledObject__.
    _Processor_ defines these methods; * denotes an event-triggering method:
        *fork() : (processID, threadID): starts a new process and its initial
            thread and terminal, storing the pid in child[] and {pid : PCB}
            map, where PCB is a reference to a PCB object.
        *idle(ticks): delays the _Processor_ *ticks* ticks, useful for fork()ing
            processes at temporal intervals in the simulation.
        *trigger(ticks, event, *args) : (args ...) stalls the _Processor_
            for *ticks* ticks, and then delivers the named *event" to the
            _Processor_ object with the *args* tuple as arguments.
        time() : int returns the current, global simulation time in ticks.
        sample(*args): as defined in base class __scheduledObject__.
    '''
    __count__ = 0
    '''
    _Processor_.__count__ is the static count of the total number of
    Processors in the simulation, incremented by _Processor_ constructor.
    Access is not thread safe, and must occur before cross-thread
    interaction.
    '''
    def __init__(self, scheduler, logger, factory, seed=None):
        '''
        Construct the fields documented for this class.
        Parameter scheduler is the __simulationScheduler__ object.
        Parameter logger is the __simulationLogger__ object.
        Parameter factory is __scheduledObject__'s map of factory
            functions for _Processor_, _Thread_ and _IOunit_ in that order.
        Parameter seed is the seed for the random sampleGenerator,
        default None uses the current system time.
        '''
        tmpn = _Processor_.__count__
        __scheduledObject__.__init__(self, scheduler, logger, factory,
            seed=seed)
        _Processor_.__count__ += 1
        self.number = tmpn
        self.contextCount = 1       # Derived class can override this.
        self.contextsFree = 1        # Likewise.
        self.fastio = []
        self.msgbuf = []
        self.readyq = []
        self.readyqSerial = 0
        # self.sampleGenerator is in base class __scheduledObject__.
        self.pcb = {}
        self.child = []
        self.processor = self       # For calls into subgraphs.
        self.thread = None          # For calls into subgraphs.
        self.__eventSet__ = set([])
    def __str__(self):
        return ("Processor " + str(self.number) + ", state "            \
            + str(self.state) + ", waitingon " + str(self.waitingon)    \
            + ", __sleepResult__ " + str(self.__sleepResult__))
    def fork(self):
        '''
        *fork() : (processID, threadID): starts a new process and its initial
            thread and terminal, storing the pid in child[] and {pid : PCB}
            map, where PCB is a reference to a PCB object.
        '''
        terminal = self.factory['io'](self.scheduler, self.logger, self.factory,
            self.processor, False, seed=self.seed)
        mypcb = PCB(self.scheduler, self)
        pid = mypcb.pid
        tid = 0
        t = self.factory['thread'](self.scheduler, self.logger, self.factory,
            self, mypcb, pid, tid, terminal, seed=self.seed)
        self.child.append(pid)
        self.pcb[pid] = mypcb
        mypcb.threads.append(t)
        mypcb.activeThreads = 1
        # sleep() after updating all shared data structures.
        self.scheduler.sleep(1, t, 'init', None)
        self.scheduler.sleep(1, self, 'fork', (pid, tid))
        return ((pid, tid))
    def idle(self, ticks):
        '''
        *idle(ticks): delays the _Processor_ *ticks* ticks, useful for
            fork()ing processes at temporal intervals in the simulation.
        '''
        self.scheduler.sleep(ticks, self, 'idle', None)
    def trigger(self, ticks, event, *args):
        '''
        *trigger(ticks, event, *args) : (args ...) stalls the _Processor_
            for *ticks* ticks, and then delivers the named *event" to the
            _Processor_ object with the *args* tuple as arguments.
        '''
        if not event in self.__eventSet__:
            raise ValueError("Event type " + event
                + " not in event set " + str(self.__eventSet__)
                + " for this state machine.")
        self.scheduler.sleep(ticks, self, event, args)
    def time(self):
        '''
        time() : int returns the current, global simulation time in ticks.
        '''
        return self.scheduler.time
    def log(self, file, loglevel, tag=None):
        if loglevel:
            if loglevel == __LOGSOME__ and self.lastStateLogged == self.state:
                return
            ttime = str('%012d' % self.scheduler.time)
            if tag:
                file.write(ttime + ",LOG,processor " + str(self.number) \
                    + "," + str(self.state) + "," + tag + '\n')
            elif self.waitingon:
                file.write(ttime + ",LOG,processor " + str(self.number) \
                    + "," + str(self.state) + "," + self.waitingon + '\n')
            elif self.lastStateLogged != self.state:    # else:
                file.write(ttime + ",LOG,processor " + str(self.number) \
                    + "," + str(self.state) + ',?\n')
            self.lastStateLogged = self.state
    def msg(self, message):
        '''
        Log text message from user code to log file.
        '''
        if self.logger.isOpen() and message:
                ttime = str('%012d' % self.scheduler.time)
                f = self.logger.getFile()
                f.write(ttime + ",MSG,processor " + str(self.number) + "," \
                    + message + '\n')
                if self.logger.getLevel() >= __LOGFLUSH__:
                    self.logger.flush()

class _IOunit_(__scheduledObject__):
    '''
    _IOunit_ is a complete class that does not require a user-defined
        state machine to generate its run() method. It has a run() method
        to implement its service loop -- an _Iounit_ object is an active
        object with a service thread that services requests on its io() method.
        Other methods are intended for internal use only, to serve io()
        requests. The plan is to add means for students to write _IOunit_
        state machines later in the semester. For now a slow I/O request
        delays in a uniform distribution of 7000..8000 ticks, and a fast I/O
        request delays in a uniform distribution of 500..1000 ticks TIMES
        the number of preceding requests in the queue. The requestq is a
        heapq (priority queue); for assignment 1 all requests are priority 1.
    _IOunit_ extends __scheduledObject__ by adding the following fields:
        processor is the _Processor_ object for this simulation.
        number of the _IOunit_ object, starting at 0.
        isfast is True for fast I/O (e.g., disk) or False for slow
            (e.g., terminal) as set by the object constructor.
        state defaults to None; it is set by the generated state machine.
        sampleGenerator resides in base class __scheduledObject__.
        requestq [] is a simple FIFO of waiting _Thread_ objects at
            present. It may become a priority queue later in the semester.
    _IOunit_ defines these methods; * denotes an event-triggering method:
        *io(threadobj) requests I/O for _Thread_ reference threadobj,
            managing field access within this _IOunit_ object and using the
            global scheduler time manage the delay. This io() method is
            normally invoked by _Thread_.io(), and the latter method
            should schedule I/O only via calling this method.
        *trigger(ticks, event, *args) : (args ...) stalls the _IOunit_
            for *ticks* ticks, and then delivers the named *event" to the
            _IOunit_ object with the *args* tuple as arguments.
        __enqueue__(threadobj) enqueues the _Thread_ threadobj into requestq []
            in FIFO order.
        __dequeue()__ : threadobj dequeues and returns the _Thread_
            threadobj of the front-most thread in the queue,
            throwing an exception if the requestq is empty;
            use len(requestq) > 0 as a guard before __dequeue__() if necessary.
        __peekq__() : threadobj returns the _Thread_ threadobj of
            the front-most thread in the queue without dequeuing it,
            throwing an exception if the requestq is empty;
            use len(requestq) > 0 as a guard before __peekq__() if necessary.
        sample(*args): as defined in base class __scheduledObject__.
    '''
    __fastcount__ = 0
    '''
    _IOunit_.__fastcount__ is the static count of the total number of isfast
    IOunits in the simulation, incremented by _IOunit_ constructor.
    Access is not thread safe, and must occur before cross-thread
    interaction.
    '''
    __slowcount__ = -1
    '''
    _IOunit_.slowcount__ is the static count of the total number of (not isfast)
    (slow terminals) IOunits in the simulation, decremented by _IOunit_
    constructor. It always appears as a negative number starting at -1.
    Access is not thread safe, and must occur before cross-thread
    interaction.
    '''
    def __init__(self, scheduler, logger, factory, processor, isfast,
        seed=None):
        '''
        Construct the fields documented for this class.
        Parameter scheduler is the __simulationScheduler__ object.
        Parameter logger is the __simulationLogger__ object.
        Parameter factory is __scheduledObject__'s map of factory
            functions for _Processor_, _Thread_ and _IOunit_ in that order.
        Parameter processor is the _Processor_ object for this simulation.
        Parameter isfast is True for a fast IO device (e.g., disk), False
            for slow (e.g., terminal).
        Parameter *seed* is the seed for the random sampleGenerator,
        default None uses the current system time.
        '''
        if isfast:
            tmpn = _IOunit_.__fastcount__
            __scheduledObject__.__init__(self, scheduler, logger, factory,
                seed=seed)
            _IOunit_.__fastcount__ += 1
        else:
            tmpn = _IOunit_.__slowcount__
            __scheduledObject__.__init__(self, scheduler, logger, factory,
                seed=seed)
            _IOunit_.__slowcount__ -= 1
        # self.daemon = True
        self.number = tmpn
        self.processor = processor  # For calls into subgraphs.
        self.thread = None          # For calls into subgraphs.
        self.isfast = isfast
        self.requestq = []
        self.requestqSerial = 0
        self.__eventSet__ = set([])
        # self.sampleGenerator is in base class __scheduledObject__.
    def __str__(self):
        postfix = ''
        postfix = ' ... IN IO driver: NONE'
        dbgix = 0
        for qd in self.requestq:
            postfix += ' ... IN IO Q ' + str(dbgix) + ': ' + str(map(str, qd))
        return ("IOunit " + str(self.number) + ", state "            \
            + str(self.state) + ", waitingon " + str(self.waitingon)    \
            + ", __sleepResult__ " + str(self.__sleepResult__)          \
            + ", isfast " + str(self.isfast) + ", requestq "            \
            + str(len(self.requestq)) + postfix)
    def __enqueue__(self, threadobj):
        '''
        __enqueue__(threadobj) enqueues the threadobj into requestq []
            in FIFO order.
        '''
        # Even though this is a simple FIFO queue, this code uses a
        # priority queue (heapq) in anticipation of a later student
        # project that schedules according to device characteristics
        # and _Thread_ priority.
        triplet = (1, self.requestqSerial, threadobj)
        self.requestqSerial += 1
        threadobj.waitingInQueue = True
        threadobj.waitingInQueue =  \
            "waiting on iounit(" + str(self.number) + ")"
        heapq.heappush(self.requestq, triplet)
    def __dequeue__(self):
        '''
        __dequeue()__ : threadobj dequeues and returns the _Thread_
            threadobj of the front-most thread in the queue,
            throwing an exception if the requestq is empty;
            use len(requestq) > 0 as a guard before dequeue() if necessary.
        '''
        # Even though this is a simple FIFO queue, this code uses a
        # priority queue (heapq) in anticipation of a later student
        # project that schedules according to device characteristics
        # and _Thread_ priority.
        triplet = heapq.heappop(self.requestq)
        triplet[2].waitingInQueue = False
        return triplet[2]
    def __peekq__(self):
        '''
        __peekq__() : threadobj returns the _Thread_ threadobj of
            the front-most thread in the queue without dequeuing it,
            throwing an exception if the requestq is empty;
            use len(requestq) > 0 as a guard before __peekq__() if necessary.
        '''
        triplet = self.requestq[0]
        return triplet[2]
    def __getDelay__(self):
        if self.isfast:
            mydelay = self.sample(500, 1000, 'uniform')
        else:
            mydelay = self.sample(7000, 8000, 'uniform')
        return mydelay
    def io(self, threadobj):
        '''
        *io(threadobj) requests I/O for _Thread_ reference threadobj,
            managing field access within this _IOunit_ object and using the
            global scheduler time manage the delay. This io() method is
            normally invoked by _Thread_.io(), and the latter method
            should schedule I/O only via calling this method.
        '''
        self.__enqueue__(threadobj)
        self.scheduler.yieldPrivate(threadobj, 'io')    # mark as waiting
        threadobj.exclusiveWait = True
        if len(self.requestq) == 1:
            # This io unit has one request, schedule it to wake up.
            mydelay = self.__getDelay__()
            self.scheduler.sleep(mydelay, self, 'io', None)
    def trigger(self, ticks, event, *args):
        '''
        *trigger(ticks, event, (args...)) : (args ...) stalls the _IOunit_
            for *ticks* ticks, and then delivers the named *event" to the
            _IOunit_ object with the *args* tuple as arguments.
        '''
        self.scheduler.sleep(ticks, self, event, args)
    def run(self):
        '''
        _IOunit_.run() is a generator that runs in an infinite loop
        that processes IO for one waiting _Thread_ object per iteration,
        and when there are more waiting _Thread_ objects, schedules the
        next one.
        '''
        try:
            while True:
                if len(self.requestq) > 0:
                    threadobj = self.__dequeue__()
                    self.scheduler.sleep(0, threadobj, 'io', None)
                if len(self.requestq) > 0:
                    mydelay = self.__getDelay__()
                    self.scheduler.sleep(mydelay, self, 'io', None)
                yield None
        except Exception, xxx:
            if self.logger.isOpen():
                self.logger.log(self)
                self.state = '<defunct on Exception ' + str(xxx) + '>'
                self.logger.log(self)
                traceback.print_exc(file=self.logger.getFile())
                self.logger.flush()
                raise
    def time(self):
        '''
        time() : int returns the current, global simulation time in ticks.
        '''
        return self.scheduler.time
    def log(self, file, loglevel, tag=None):
        if loglevel:
            if loglevel == __LOGSOME__ and self.lastStateLogged == self.state:
                return
            ttime = str('%012d' % self.scheduler.time)
            if tag:
                file.write(ttime + ",LOG,iounit " + str(self.number)    \
                    + "," + str(self.state) + "," + tag + '\n')
            elif self.waitingon:
                file.write(ttime + ",LOG,iounit " + str(self.number)    \
                    + "," + str(self.state) + "," + self.waitingon + '\n')
            elif self.lastStateLogged != self.state:    # else:
                file.write(ttime + ",LOG,iounit " + str(self.number)    \
                    + "," + str(self.state) + ',?\n')
            self.lastStateLogged = self.state
    def msg(self, message):
        '''
        Log text message from user code to log file.
        '''
        if self.logger.isOpen() and message:
                ttime = str('%012d' % self.scheduler.time)
                f = self.logger.getFile()
                f.write(ttime + ",MSG,iounit " + str(self.number) + ","    \
                    + message + '\n')
                if self.logger.getLevel() >= __LOGFLUSH__:
                    self.logger.flush()

class _Thread_(__scheduledObject__):
    '''
    _Thread_ extends __scheduledObject__ by adding the following fields:
        processor is the _Processor_ object for this simulation.
        processNumber of the _Thread_ object.
        threadNumber of the _Thread_ object.
        state defaults to None; it is set by the generated state machine.
        terminal is the slow (isfast == False) _IOunit_ for the process.
        sampleGenerator resides in base class __scheduledObject__.
        pcb is a reference my this _Thread_'s pcb object.
        __isdead__ starts as False, goes to True when entering an accept state.
        __joiners__ [] is a set of threadobj references waiting to join()
            this thread.
    _Thread_ defines these methods; * denotes an event-triggering method:
        *fork() : (pid, threadid) starts the initial thread and terminal of a
            new child process, storing the pid in child[] and
            {pid : PCB} in processor.pcb, where PCB is a reference to a
            PCB object.
        *wait(pid) : status waits for process pid to terminate and returns
            its exit status.
        kill(pid,status) terminates a process, with an exit status of status.
            See exit() for additional details. Each thread will be aborted
            as soon as possible with scheduling constraints.
        exit(status) terminates all threads in this process.
            Note that in addition to terminating the current thread and
            scheduling an exit event that returns status, exit aborts each
            thread in the process as soon as possible.
        *spawn() : threadid starts another thread of the current process,
            updating this process' PCB.
        *join(threadobj) waits for thread threadid within the caller's process
            to terminate, when the latter invokes exit(), or retire() or is
            aborted via exit(), or otherwise terminates, e.g., due to an
            exception.
        retire() terminates this thread.
            It unblocks any threads waiting to join this thread, and, if this
            is the final thread in a process, retire() works the same as exit()
            with respect to releasing wait()ing threads.
        *cpu(ticks) requests ticks on a _Processor_ context.
        *io(index) requests I/O on fastio[index] or on terminal for index==-1.
        *sleep(ticks): delays the _Thread_ *ticks* ticks.
        *trigger(ticks, event, *args) : (args ...) stalls the _Thread_
            for *ticks* ticks, and then delivers the named *event" to the
            _Thread_ object with the *args* tuple as arguments.
        getid() : (machineid, processid, threadid) returns the 
           (_Processor_.number, processNumber, threadNumber) of this thread.
        sample(*args): as defined in base class __scheduledObject__.
    '''
    def __init__(self, scheduler, logger, factory, processor, pcb,
            processNumber, threadNumber, terminal, seed=None):
        '''
        Construct the fields documented for this class.
        Parameter scheduler is the __simulationScheduler__ object.
        Parameter logger is the __simulationLogger__ object.
        Parameter factory is __scheduledObject__'s map of factory
            functions for _Processor_, _Thread_ and _IOunit_ in that order.
        Parameter processor is the _Processor_ object for this simulation.
        Parameter processNumber is the process id of the _Thread_ object.
        Parameter pcb is a reference to this thread's process' PCB object.
        Parameter threadNumber is the thread id of the _Thread_ object.
        Parameter terminal is the slow (isfast == False) _IOunit_ for the
            process.
        Parameter seed is the seed for the random sampleGenerator,
        default None uses the current system time.
        '''
        __scheduledObject__.__init__(self, scheduler, logger, factory,
                seed=seed)
        self.processor = processor          # For calls into subgraphs.
        self.thread = self                  # For calls into subgraphs.
        self.pcb = pcb
        self.processNumber = processNumber
        self.threadNumber = threadNumber
        self.terminal = terminal
        self.__isdead__ = False
        self.__joiners__ = []
        self.__eventSet__ = set([])
    def __str__(self):
        return ("Thread pid " + str(self.processNumber) + ", tid "
            + str(self.threadNumber) + ", state "
            + str(self.state) + ", waitingon " + str(self.waitingon)
            + ", __sleepResult__ " + str(self.__sleepResult__) + ", __isdead__"
            + str(self.__isdead__))
    def getid(self):
        '''
        getid() : (machineid, processid, threadid) returns the 
           (_Processor_.number, processNumber, threadNumber) of this thread.
        '''
        return ((self.processor.number, self.processNumber,
            self.threadNumber))
    def fork(self):
        '''
        *fork() : (pid, threadid) starts the initial thread and terminal of a
            new child process, storing the pid in child[] and
            {pid : PCB} in processor.pcb, where PCB is a reference to
            a PCB object.
        '''
        mypcb = PCB(self.scheduler, self.pcb)
        pid = mypcb.pid
        tid = 0
        terminal = self.factory['io'](self.scheduler, self.logger, self.factory,
            self.processor, False, seed=self.seed)
        t = self.factory['thread'](self.scheduler, self.logger, self.factory,
            self.processor, mypcb, pid, tid, terminal, seed=self.seed)
        self.pcb.child.append(pid)
        self.processor.pcb[pid] = mypcb
        mypcb.threads.append(t)
        mypcb.activeThreads = 1
        # sleep() after updating all shared data structures.
        self.scheduler.sleep(1, t, 'init', None)
        self.scheduler.sleep(1, self, 'fork', (pid, tid))
        return ((pid, tid))
    def spawn(self):
        '''
        *spawn() : threadid starts another thread of the current process,
            updating this process' PCB.
        '''
        pid = self.processNumber
        pcb = self.pcb
        tid = len(pcb.threads)
        t = self.factory['thread'](self.scheduler, self.logger, self.factory,
            self.processor, pcb, pid, tid, self.terminal, seed=self.seed)
        pcb.threads.append(t)
        pcb.activeThreads += 1
        # sleep() after updating all shared data structures.
        self.scheduler.sleep(1, t, 'init', None)
        self.scheduler.sleep(1, self, 'spawn', (pid, tid))
        return ((pid, tid))
    def cpu(self, ticks):
        '''
        *cpu(ticks) requests ticks on a _Processor_ context.
        '''
        self.scheduler.sleep(ticks, self, 'cpu', None)
    def io(self, index):
        '''
        *io(index) requests I/O on fastio[index] or on terminal for index==-1.
        '''
        if index == -1:
            iodevice = self.terminal
        else:
            iodevice = self.processor.fastio[index]
        iodevice.io(self)
    def sleep(self, ticks):
        '''
        *sleep(ticks): delays the _Thread_ *ticks* ticks.
        '''
        self.scheduler.sleep(ticks, self, 'sleep', None)
    def yieldcpu(self):
        '''
        *yieldcpu delays the _Thread_ 0 ticks, giving another thread
        a chance to run in the simulation.
        '''
        self.scheduler.sleep(0, self, 'yieldcpu', None)
    def wait(self, pid):
        '''
        *wait(pid) : status waits for process pid to terminate and returns
            its exit status.
        '''
        if not pid in self.processor.pcb:
            msg = ("ERROR, wait() to processor '" + str(self.processor.number)
                + "' on invalid pid: " + str(pid) + ".")
            sys.stderr.write(msg + '\n')
            raise RuntimeError(msg)
        pcb = self.processor.pcb[pid]
        pcb.wait(self, self)
    def kill(self, pid, status):
        '''
        kill(pid,status) terminates a process, with an exit status of status.
            See exit() for additional details. Each thread will be aborted
            as soon as possible with scheduling constraints.
        '''
        if not pid in self.processor.pcb:
            msg = ("ERROR, kill() to processor '" + str(self.processor.number)
                + "' on invalid pid: " + str(pid) + ".")
            sys.stderr.write(msg + '\n')
            raise RuntimeError(msg)
        pcb = self.processor.pcb[pid]
        pcb.exit(status)
    def exit(self, status):
        self.pcb.exit(status)
    def join(self, threadobj):
        if threadobj.__isdead__:
            self.scheduler.sleep(0, self, 'join', None)
        elif (self is threadobj
                or (isinstance(self,_SubGraph_)
                    and self.thread is threadobj)):
            msg = ("ERROR, thread attempting to join itself: "
                + str(self))
            sys.stderr.write(msg + '\n')
            raise RuntimeError(msg)
        elif self.processNumber != threadobj.processNumber:
            msg = ("ERROR, thread in process " + str(self.processNumber)
                + " attempting to join thread in process "
                + str(threadobj.processNumber) + ".")
            sys.stderr.write(msg + '\n')
            raise RuntimeError(msg)
        else:
            if not self in threadobj.__joiners__:
                threadobj.__joiners__.append(self)
                self.scheduler.yieldPrivate(self, 'join', isexclusive=True)
    def retire(self):
        '''
        retire() terminates this thread.
            It unblocks any threads waiting to join this thread, and, if this
            is the final thread in a process, retire() works the same as exit()
            with respect to releasing wait()ing threads.
            retire() throws __ThreadRetireException__ unconditionally as its
            last step; it is intended to be used only by a retiring thread.
        '''
        self.__isdead__ = True
        for j in self.__joiners__:
            self.scheduler.unyieldPrivate(j, 'join', None)
        self.__joiners__ = []
        if self in self.pcb.threads:
            self.pcb.threads.remove(self)
            self.pcb.activeThreads -= 1
            if self.pcb.activeThreads <= 0:
                if self.pcb.exitStatus == None:
                    self.pcb.exitStatus = 0
                for w in self.pcb.waiters:
                    self.scheduler.unyieldPrivate(w, 'wait',
                        self.pcb.exitStatus)
                self.pcb.waiters = []
                if self.processNumber in self.pcb.parent.child:
                    self.pcb.parent.child.remove(self.processNumber)
                if self.processNumber in self.processor.pcb:
                    del self.processor.pcb[self.processNumber]
        msg = ("thread " + str(self.threadNumber) + " process "
            + str(self.processNumber) + " has called retire().")
        raise __ThreadRetireException__(msg)
    def trigger(self, ticks, event, *args):
        '''
        *trigger(ticks, event, (args...)) : (args ...) stalls the _Thread_
            for *ticks* ticks, and then delivers the named *event" to the
            _Thread_ object with the *args* tuple as arguments.
        '''
        if not event in self.__eventSet__:
            raise ValueError("Event type " + event
                + " not in event set " + str(self.__eventSet__)
                + " for this state machine.")
        self.scheduler.sleep(ticks, self, event, args)
    def time(self):
        '''
        time() : int returns the current, global simulation time in ticks.
        '''
        return self.scheduler.time
    def log(self, file, loglevel, tag=None):
        if loglevel:
            if loglevel == __LOGSOME__ and self.lastStateLogged == self.state:
                return
            ttime = str(self.scheduler.time)
            ttime = str('%012d' % self.scheduler.time)
            if tag:
                file.write(ttime + ",LOG,thread " + str(self.threadNumber) \
                    + " process " + str(self.processNumber) + "," \
                    + str(self.state) + "," + tag + '\n')
            elif self.waitingon:
                file.write(ttime + ",LOG,thread " + str(self.threadNumber) \
                    + " process " + str(self.processNumber) + "," \
                    + str(self.state) + "," + self.waitingon + '\n')
            elif self.lastStateLogged != self.state:    # else:
                file.write(ttime + ",LOG,thread " + str(self.threadNumber) \
                    + " process " + str(self.processNumber) + "," \
                    + str(self.state) + ',?\n')
            self.lastStateLogged = self.state
    def msg(self, message):
        '''
        Log text message from user code to log file.
        '''
        if self.logger.isOpen() and message:
                ttime = str('%012d' % self.scheduler.time)
                f = self.logger.getFile()
                f.write(ttime + ",MSG,thread " + str(self.threadNumber)
                    + ' process ' + str(self.processNumber) + "," 
                    + message + '\n')
                if self.logger.getLevel() >= __LOGFLUSH__:
                    self.logger.flush()

class _SubGraph_(_Thread_):
    '''
    _SubGraph_ is a base class for generated classes that the compiler
    generates from subgraphs in a STM program. _SubGraph_ serves as a
    sort of proxy _Thread_. Its constructor and run() generator
    run as subroutines of the invoking __scheduledObject__ object.
    '''
    def __init__(self,graphname,caller,processor,thread,__sleepResult__):
        '''
        Constructs a subgraph object.
        graphname is the textual name of this class.
        caller may be any subclass of _Thread_ that is making
            this call, including a calling _SubGraph_ object.
        processor is the _Processor_ derived object.
        thread is the calling _Thread_ object.
        __sleepResult__ is the triplet of (stime, eventType, eventArg)
            passed in from the calling graph's most recent blocking call
            upon its completion; that completed blocking call leads
            into this subgraph's init state.
        '''
        _Thread_.__init__(self,thread.scheduler,thread.logger,
            thread.factory,processor,thread.pcb, thread.processNumber,
            thread.threadNumber, thread.terminal)
        self.graphname = graphname
        self.caller = caller
        self.processor = processor
        self.thread = thread
        self.activeobj = thread
        self.__eventSet__ = self.activeobj.__eventSet__
        # Note: regardless of the event type in the calling graph that
        # leads into this subgraph, the arguments of that call get passed
        # into here as an 'init' event.
        self.__sleepResult__ = (__sleepResult__[0],
            'init',__sleepResult__[2])
        self.state = 'init'     # Mandatory start state is 'init'.
        self.globals = None
        self.scheduler = processor.scheduler
        self.logger = processor.logger
        self.waitingon = None   # Generated run() method sets waitingon.
        self.lastStateLogged = None
        self.logger.log(self, tag="APPROACH")
        self.logger.log(self, tag="ARRIVE")
    def __str__(self):
        '''
        Return a string consisting of this graphname/state (see __init__),
        preceded by any calling subgraph graphnames/states in a :
        separated path.
        '''
        result = self.graphname + '/' + self.state
        caller = self.caller
        while isinstance(caller, _SubGraph_):
            result = caller.graphname + '/' + callser.state + ':' + result
            caller = caller.caller
        return result
    def run():
        raise ValueError("run() must be defined in a subclass of _SubGraph_")
    def wait(self, pid):
        '''
        *wait(pid) : status waits for process pid to terminate and returns
            its exit status. _SubGraph_ must tarverse up to its top-level
            _Thread_ to perform some error checking.
        '''
        if not pid in self.processor.pcb:
            msg = ("ERROR, wait() to processor '" + str(self.processor.number)
                + "' on invalid pid: " + str(pid) + ".")
            sys.stderr.write(msg + '\n')
            raise RuntimeError(msg)
        pcb = self.processor.pcb[pid]
        pcb.wait(self, self.thread)
    def retire(self):
        '''
        retire() terminates this subgraph's top level thread.
            See _Thread_.retire.
        '''
        self.__isdead__ = True
        caller = self.caller
        while isinstance(caller, _SubGraph_):
            caller.__isdead__ = True
            caller = caller.caller
        if (isinstance(caller, _Thread_)):
            # caller.retire throws an exceptoion, so
            # schedule top level thread for termination before retire().
            caller.__isdead__ = True
            self.scheduler.sleep(1, caller, 'retire', None)
            caller.retire() # Retire the top level thread.
        msg = ("thread " + str(self.threadNumber) + " process "
                + str(self.processNumber) + " has called retire().")
        raise __ThreadRetireException__(msg)
    def log(self, file, loglevel, tag=None):
      if self.thread:       # Caller is a thread STM.
        if loglevel:
            if loglevel == __LOGSOME__ and self.lastStateLogged == self.state:
                return
            ttime = str(self.scheduler.time)
            ttime = str('%012d' % self.scheduler.time)
            if tag:
                file.write(ttime + ",LOG,thread "   \
                    + str(self.thread.threadNumber) \
                    + " process " + str(self.thread.processNumber) + "," \
                    + str(self) + "," + tag + '\n')
            elif self.waitingon:
                file.write(ttime + ",LOG,thread "       \
                    + str(self.thread.threadNumber) \
                    + " process " + str(self.thread.processNumber) + "," \
                    + str(self) + "," + self.waitingon + '\n')
            elif self.lastStateLogged != self.state:    # else:
                file.write(ttime + ",LOG,thread "           \
                    + str(self.thread.threadNumber) \
                    + " process " + str(self.thread.processNumber) + "," \
                    + str(self) + ',?\n')
            self.lastStateLogged = self.state
      else:     # Caller is a processor STM.
        if loglevel:
            if loglevel == __LOGSOME__ and self.lastStateLogged == self.state:
                return
            ttime = str('%012d' % self.scheduler.time)
            if tag:
                file.write(ttime + ",LOG,processor "        \
                    + str(self.processor.number) \
                    + "," + str(self) + "," + tag + '\n')
            elif self.waitingon:
                file.write(ttime + ",LOG,processor "        \
                    + str(self.processor.number) \
                    + "," + str(self) + "," + self.waitingon + '\n')
            elif self.lastStateLogged != self.state:    # else:
                file.write(ttime + ",LOG,processor "        \
                    + str(self.processor.number) \
                    + "," + str(self.state) + ',?\n')
            self.lastStateLogged = self.state
    def msg(self, message):
      '''
      Log text message from user code to log file.
      '''
      if self.thread:       # Report the calling thread.
        self.thread.msg(message)
      else:                 # Report the calling processor.
        self.processor.msg(message)

class __simulationLogger__(object):
    '''
    This utility class logs states changes and other changes to a log file.
    '''
    def __init__(self, logFileName, loglevel):
        '''
        Construct the logger object by opening its log file for writing.
        Parameter logFileName is a file name that this constructor opens
            for writing, truncating any existing file.
        Parameter loglevel is one of
            0 (minimal),
            1 (some logging of required simulation progress),
            2 (log simulation state into and msgs, but minimize flush() calls,
            3 (log simulation state into and msgs, use flush() (slow on Linux),
            4 adds internal debugging MSGs.
        '''
        self.loglevel = loglevel
        self.logFileName = logFileName
        self.isopen = False
        self.file = open(logFileName, 'w')
        self.isopen = True
        self.scheduler = None
    def setScheduler(self,scheduler):
        '''
        Set this logger's scheduler object, typically a __simulationScheduler__.
        '''
        self.scheduler = scheduler
    def close(self):
        '''
        Close the logfile opened by the constructor. Any attempts to invoke
        log() on this object after closing results in an exception.
        '''
        self.file.close()
        self.isopen = False
    def flush(self):
        '''
        Flush the logfile opened by the constructor if it is still open.
        This flushes at any log level in case it is called on an error.
        '''
        if self.isopen:
            self.file.flush()
    def isOpen(self):
        '''
        Returns True if the file opened by the constructor is still open,
        else False if a call to close() has closed the file.
        '''
        return self.isopen
    def getLevel(self):
        '''
        Return the constructor's loglevel value.
        '''
        return self.loglevel
    def log(self, simobject, tag=None):
        '''
        Log the state of the simobject to the file opened by the
        constructor, throwing an exception if close() has closed the file.
        This method invokes simobject.log(filehandle, loglevel)
        with the opened file and log level 0..2 passed to the constructor,
        and lets the simobject parameter's object do the writing.
        The tag takes the place of reporting the event when non-None,
        typically for logging state ARRIVE and DEPART state changes.
        Log level __LOGFLUSH__ or higher flush()es the log file.
        '''
        simobject.log(self.file, self.loglevel, tag=tag)
        if self.isopen and self.loglevel >= __LOGFLUSH__:
            self.file.flush()
    def getFile(self):
        '''
        Method returns filehandle if the file is open None if not.
        '''
        if self.isopen:
            return self.file
        else:
            return None

# ad hoc test
def gentestSampleDistribution(filename, sampleCount, lower, upper, distType,
        mu=None, deviation=None):
    'See __scheduledObject__.sample(). This is a test of that method.'
    sg = random.Random()
    histogram = {}
    for i in range(0,sampleCount):
        if mu is None:
            value = __scheduledObject__.__sample__(lower, upper, distType, sg,
                ())
        elif deviation is None:
            value = __scheduledObject__.__sample__(lower, upper, distType, sg,
                (mu,))
        else:
            value = __scheduledObject__.__sample__(lower, upper, distType, sg,
                (mu, deviation))
        if value in histogram:
            histogram[value] += 1
        else:
            histogram[value] = 1
    f = open(filename, 'w')
    for value in range(lower, upper+1):
        if value in histogram:
            f.write(str(value) + ',' + str(histogram[value]) + '\n')
        else:
            f.write(str(value) + ',0\n')
    f.close()

if __name__ == '__main__':
    gentestSampleDistribution('uniform.csv',100000, 1, 100, 'uniform')
    gentestSampleDistribution('gauss.csv',100000, 1, 100, 'gaussian',
        (1.0+100.0)/2.0, 15.0)
    gentestSampleDistribution('exponential.csv',100000,1,100,
        'exponential',10.0)
    gentestSampleDistribution('revexponential.csv',100000,1,100,
        'revexponential', 90.0)
# original graphs used 25 and 75 instead of 10 and 90.
