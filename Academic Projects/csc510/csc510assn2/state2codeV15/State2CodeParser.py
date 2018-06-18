# -----------------------------------------------------------------------------
# State2CodeParser.py   A translator that accepts a state machine definition
#               in textual format and emits one or more code translations
#               of that state machine. D. Parson, Fall 2013
# Updated 10/2014 to audit that an entry arc into a subgraph state matches
#               the event type of the subgraph init -> transition, and
#               that the subgraph's final action on the way to its accept
#               state has the same event on the outgoing transition in the
#               calling state machine.
# -----------------------------------------------------------------------------
# package state2codeV15
# V14 replaces has_key and sort() on keys() for preparation to move
# to Python 3 in V15. August 2017.

import sys
import copy
import re
import logging
from pprint import PrettyPrinter

if sys.version_info[0] >= 3:
    raw_input = input

class AbstractCodeGenerator(object):
    '''
    AbstractCodeGenerator is an abstract class that declares & documents
    the generate method for generating code for a state machine compiled
    by State2CodeParser.compile.
    '''
    def generate(self, parseTree, symboltableOfStateMachineObjects, objfile):
        '''
        Generate target-specific code for a collection of StateMachines.
        Parameters:

        self is an object of a class that subclasses AbstractCodeGenerator.
            AbstractCodeGenerator.generate by itself throws ValueError.

        parseTree is the parse tree from State2CodeParser.compile.

        symboltableOfStateMachineObjects is the symbol table from
            State2CodeParser.compile.

        objfile is the output file handle for the generated code
        '''
        raise ValueError("AbstractCodeGenerator is an abstract base class.")

# SYMBOL TABLE CLASSES

__STARTSTATE__ = 1      # bit field
__ACCEPTSTATE__ = 2     # bit field
__SUBGRAPH__ = 4        # bit field

# __StateMachineSymbolTable__ is a map from the name of each state machine
# to its collection of states.
__StateMachineSymbolTable__ = {}

class StateMachine(object):
    def __init__(self, name, states, variables, macros, eventSet):
        '''
        Construct a StateMachine object.
        Parameters:
            name : the unique name of the StateMachine object.
            states : a dictionary mapping state name to State object
                within this StateMachine.
            variables : a dictionary mapping state machine state-variables
                to their initial values.
            macros : a dictionary mapping state machine macro names
                to their verbatim replacement strings. Macros do not
                take parameters.
            eventSet : the set of all event names found on transitions
                in this state machine.
        '''
        if name in __StateMachineSymbolTable__.keys():
            terror(NameError, "ERROR, redefinition of state machine " + name
                + ".")
        self.name = name
        self.states = states
        self.variables = variables
        self.macros = macros
        self.eventSet = eventSet
        #sys.stderr.write("DEBUG SM " + name + " MACROS " + str(macros) + '\n')
        self.startstate = None
        for statename in states.keys():
            st = states[statename]
            if st.isstart:
                if self.startstate:
                    terror(NameError,                   \
                        "ERROR, multiple start states in machine "      \
                        + name + ": " + self.startstate.name + ", "     \
                        + statename)
                self.startstate = st
        if self.startstate is None:
            terror(NameError,"ERROR, no start states in machine "      \
                        + name)
    def __str__(self):
        return 'StateMachine:' + self.name + ':' + repr(self.states) + ':'  \
            + repr(self.variables) + ':' + repr(self.macros)
    def __repr__(self):
        return 'StateMachine:' + self.name + ':' + repr(self.states) + ':'  \
            + repr(self.variables) + ':' + repr(self.macros)

def graphAudit(parsetree, symtab):
    '''
    After parsing call graphAudit with the parsetree and symtab of
    StateMachine name -> object mappings to audit connectivity.
    October 2014 added checks to ensure that transitions into a subgraph
    have a corresponding event time in the init transition of the subgraph,
    and that the final action going to a subgraph accept state matches an
    outgoing transition where the subgraph was called.
    '''
    def stateAudit(symtab, smachine, state, reachedstatenames):
        reachedstatenames.add(state.name)
        for xition in state.transitions:
            tostname = xition.destState
            if not tostname in reachedstatenames:
                stateAudit(symtab, smachine, smachine.states[tostname],     \
                    reachedstatenames)
    def subAudit(callername, callermachine, callerstate, callerstatenames,
            subname, submachine):
        # Find all transitions into callerstate and check their events.
        # CANNOT CHECK ACTIONS IN THIS MODULE. DUH!
        for frstname in callerstatenames:
            fromst = callermachine.states[frstname]
            for xition in fromst.transitions:
                tostname = xition.destState
                if tostname != subname:
                    continue
    allmachinenames = symtab.keys()
    for machinename in allmachinenames:
        smachine = symtab[machinename]
        # 1. Make sure that any subgraph state has a matching machine.
        #    Also warn if any single-out-transitions have guards;
        #    these could lead to missed events.
        allstatenames = set(smachine.states.keys())
        for statename in allstatenames:
            st = smachine.states[statename]
            if st.issubgraph:
                if not statename in allmachinenames:
                    terror(NameError, "ERROR, subgraph state " + statename 
                        + " in machine " + machinename 
                        + " has no matching machine.")
            if len(st.transitions) == 1 and st.transitions[0].guard:
                warnt = st.transitions[0]
                sys.stderr.write('\nWARNING, singleton transition for '
                    + warnt.sourceState + " -> " + warnt.destState
                    + " " + warnt.event + "(...)[@" + warnt.guard
                    + "@] will discard events not matched by the guard.\n\n")
        # 2. Make sure all states in a machine connect from start state.
        reachedstatenames = set([])
        stateAudit(symtab, smachine, smachine.startstate, reachedstatenames)
        if reachedstatenames != allstatenames:
            missing = allstatenames.difference(reachedstatenames)
            terror(NameError, "ERROR, following states in machine " \
                + machinename + " are unreachable from its start state " \
                + smachine.startstate.name + ": " + str(missing))

def printStateMachineToDAG(graphname, dagfile, ptree, symtab):
    def cleanup(rawstr):
        if type(rawstr) != str or rawstr.strip() == '':
            return ''
        result = rawstr.strip()
        if result[0] == "'" or result[0] == '"':
            result = result[1:]
        if result[-1] == "'" or result[-1] == '"':
            result = result[:-1]
        tmp = result.split('\n')
        if len(tmp) > 1:
            result = tmp[0].strip()
            for i in range(1, len(tmp)):
                result += (' ' + tmp[i].strip())
        # Replace double quotes with two single quotes in the string.
        dq = result.find('"')
        while dq >= 0:
            result = result[:dq] + "''" + result[dq+1:]
            dq = result.find('"')
        return result
    dagfile.write('digraph "' + graphname + '" {\n')
    sawmain = False
    # DOT seems to make the final machine the first in the graph.
    for mname in symtab.keys():
        machine = symtab[mname]
        dagfile.write('    subgraph "' + mname + '" {\n')
        for sname in machine.states.keys():
            state = machine.states[sname]
            snum = str(state.statenum)
            if state.isstart:
                shape = 'triangle'
            elif state.isaccept:
                shape = 'octagon'
            elif state.issubgraph:
                shape = 'diamond'
            else:
                shape = 'ellipse'
            # Include the machinename_statename as the state name to avoid
            # collisions on just the statename in the graph. 9/22/2013 Parson
            dagfile.write('        "' + mname + '_' + sname             \
                + '" [shape=' + shape \
                + ', label="' + mname + ':' + sname + ':' + snum + '"];\n')
        for sname in machine.states.keys():
            state = machine.states[sname]
            xitionix = -1
            for xition in state.transitions:
                xitionix += 1
                dagfile.write('        "' + mname + '_' + xition.sourceState \
                    + '" -> "' + mname + '_'        \
                    + xition.destState + '" [label = "')
                label = cleanup(xition.event) + '('                         \
                    + cleanup(xition.arguments) + ')['                      \
                    + cleanup(xition.guard) + ']/' + cleanup(xition.activity)
                if len(label) >= 9:
                    lbl = ''
                    for ccc in label:
                        if ccc.isalnum():
                            lbl = lbl + ccc
                        else:
                            break
                    label = lbl if len(lbl) else '???'
                label = label + ':' + str(xitionix)
                dagfile.write(label + '"];\n')
        dagfile.write('    }\n')
    dagfile.write('}\n')

class State(object):
    __serialno__ = 0
    def __init__(self, name, machineName, transitions, isstart=False,
            isaccept=False, issubgraph=False):
        '''
        Construct a State object.
        Parameters:
            name : the unique (within a StateMachine) name of the State object.
            machineName : the name of its StateMachine object.
            transitions : sequence of Transition objects in definition order.
            isstart : True if this is the sole start for its StateMachine.
            isaccept : True if this is an accept for its StateMachine.
            issubgraph : True if name is another StateMachine graph.
        '''
        self.name = name
        self.machineName = machineName
        self.transitions = transitions
        self.isstart = isstart
        self.isaccept = isaccept
        self.issubgraph = issubgraph
        self.statenum = State.__serialno__
        State.__serialno__ = self.statenum + 1
    def addTransition(self, transition):
        self.transitions = self.transitions + (transition,)
    def __str__(self):
        return 'State:' + self.name + ':' + str(self.statenum) + ':'    \
            + repr(self.transitions) + ':'  \
            + repr(self.isstart) + ':' + repr(self.isaccept) + ':'          \
            + repr(self.issubgraph)
    def __repr__(self):
        return 'State:' + self.name + ':' + str(self.statenum) + ':'    \
            + repr(self.transitions) + ':'  \
            + repr(self.isstart) + ':' + repr(self.isaccept) + ':'          \
            + repr(self.issubgraph)

class Transition(object):
    def __init__(self, machineName, sourceState, destState, event,      \
        arguments, guard, activity):
        '''
        Construct a Transition object.
        Parameters:
            machineName : the name of its StateMachine object.
            sourceState : the name of its source state.
            destState : the name of its destination state.
            event : application-specific event name.
            arguments : string containing argument names, may be empty string.
            guard : string containing boolean-valued expression in target VM,
                    empty string means guard should evaluate to true.
            activity : actions to run in target VM, may be empty string.
        '''
        self.machineName = machineName
        self.sourceState = sourceState
        self.destState = destState
        self.event = event
        self.arguments = arguments
        self.guard = guard
        self.activity = activity
    def __str__(self):
        return self.machineName + ':' + self.sourceState + '->' + ':'   \
            + self.destState + ',' + self.event + '(' + str(self.arguments)  \
            + ')[' + str(self.guard) + ']/' + str(self.activity)
    def __repr__(self):
        return self.machineName + ':' + self.sourceState + '->' + ':'   \
            + self.destState + ',' + self.event + '(' + str(self.arguments)  \
            + ')[' + str(self.guard) + ']/' + str(self.activity)

# Tokens

reserved = {        # Map the reserved lexeme to its TOKEN name.
    'machine' :             'MACHINE',
    'state' :               'STATE',
    'start' :               'START',
    'accept' :              'ACCEPT',
    'macro' :               'MACRO',
    'subgraph' :            'SUBGRAPH',
    'string_constant1' :    'STRING_CONSTANT1',
    'string_constant2' :    'STRING_CONSTANT2',
    'action_constant'  :    'ACTION_CONSTANT',
    'float_constant'   :    'FLOAT_CONSTANT',
    'int_constant'     :    'INT_CONSTANT'
}

tokens = (
    'ID', 'LBRACE', 'RBRACE', 'SEMIC', 'COMMA', 'EQ', 'ARROW',
    'SLASH', 'LPAREN', 'RPAREN', 'LBRACK', 'RBRACK', 'STAR'
) + tuple(reserved.values())    # append TOKENS for reserved words

def t_newline(t):
    r'\n+'
    global __global_line_number__
    t.lexer.lineno += t.value.count("\n")
    # print "DEBUG ADDING LINES", t.value.count("\n"), "TO", t.lexer.lineno
    # DEBUG __global_line_number__ = t.lexer.lineno
    __global_line_number__ += t.value.count("\n")

def t_STRING_CONSTANT1(t):
    "\\'[^']*\\'"
    rawvalue = str(t.value)
    t.value = rawvalue[1:-1]
    return t

def t_STRING_CONSTANT2(t):
    '\\"[^"]*\\"'
    rawvalue = str(t.value)
    t.value = rawvalue[1:-1]
    return t

def t_ACTION_CONSTANT(t):
    r'@[^@]*@'
    global __global_line_number__
    rawvalue = str(t.value)
    t.value = rawvalue
    __global_line_number__ += t.value.count("\n")
    return t

def t_FLOAT_CONSTANT(t):
    r'(-)?((\d*\.\d+)|(\d+\.\d*))'
    t.value = float(t.value)
    return t

def t_INT_CONSTANT(t):
    r'(-)?\d+'
    t.value = int(t.value)
    return t

def t_ARROW(t):
    '->'
    t.value = str(t.value)
    return t

def t_ID(t):
    r'[a-zA-Z][a-zA-Z0-9_]*'
    if (t.value in reserved):
        t.type = reserved[t.value]
    else:
        t.type = 'ID'
    return t
                                    # Operator TYPE requirements follow.
                                    # Numeric allows mix of int and float.
t_LBRACE =               "{"
t_RBRACE =               "}"
t_LPAREN =               "\\("
t_RPAREN =               "\\)"
t_LBRACK =               "\\["
t_RBRACK =               "]"
t_SEMIC =                ";"
t_COMMA =                ","
t_EQ =                   "="
t_SLASH =                "/"
t_STAR  =                "\\*"

# Token patterns. Those that overlap with t_ID
# are handled above, and do not appear in this group.
t_ignore =    ' \t'

__global_line_number__ = 1
# If __global_error__ is not yet set, then upon finding an error, 
# set it to one of the following and also set __global_error_string__.
# There errors are built-in Python error types.
#
# SyntaxError           on lexical or syntax error
# TypeError             on type mismatch or missing / extra argument
# NameError             symbol not in scope or redefined at same scope
# ValueError            linker raises this on invalid program memory entry
__global_error__ = None
__global_error_string__ = None

def t_error(t):
    global __global_error__
    global __global_error_string__
    print("Illegal character '%s'" % t.value[0], "near line",   \
        __global_line_number__)
    t.lexer.skip(1)
    if __global_error__ == None:
        __global_error_string__ =   \
            ("ERROR: Illegal character '%s'" % t.value[0]) + " near line "\
            + str( __global_line_number__)
        __global_error__ = SyntaxError
    
# Build the lexer
import ply.lex as lex
lex.lex()

# User this error reporing function for syntax and semantic errors.
def terror(ex, st, isprint=True, isthrow=False): # exception type and string
    global __global_error__
    global __global_error_string__
    if (isprint):
        print(st)
    if __global_error__ == None:
        __global_error_string__ = st
        __global_error__ = ex
    if isthrow:
        raise ex(st)

# Invokes terror with a forced throw
def horror(ex, st, isprint=True):
    terror(ex, st, isprint=isprint, isthrow=True)


# Parsing rules

precedence = (
    )

# The overall parse tree is an immutable sequence of statements.
# The return value is an ordered pair 1) sequence of StateMachine object
# references, and 2) the name of the entry machine.
def p_goal(p):
    'goal : machinelist ID'
    if not p[2] in __StateMachineSymbolTable__.keys():
        terror(ValueError, p[2] + " is not a valid entry machine name.")
    p[0] = (p[1], p[2])

def p_machinelist(p):
    '''machinelist : machinerest statemachine'''
    # Grow the sequence without mutation.
    p[0] = p[1] + (p[2],)

def p_machinerest(p):
    '''machinerest : machinerest statemachine
                | epsilon'''
    if p[1] == None:
        p[0] = ()
    else:
        p[0] = p[1] + (p[2],)

def p_statemachine(p):
    'statemachine : MACHINE ID LBRACE statevariables statedecls statemacros statetransitions RBRACE'
    vars = {}
    for opair in p[4]:
        if len(opair) == 0:
            continue
        variable = opair[0]
        initvalue = opair[1]
        if variable in vars.keys():
            terror(NameError, "ERROR, redefinition of variable " + variable
                + " in state machine " + p[2] + ".")
        else:
            vars[variable] = initvalue
    macros = {}
    for mpair in p[6]:
        if len(mpair) == 0:
            continue
        macroname = mpair[0]
        macrostring = mpair[1]
        if macroname in macros.keys():
            terror(NameError, "ERROR, redefinition of macro " + macroname
                + " in state machine " + p[2] + ".")
        elif macroname in vars.keys():
            terror(NameError, "ERROR, redefinition of variable " + macroname
                + " as a macro in state machine " + p[2] + ".")
        else:
            macros[macroname] = macrostring
    states = {}
    starter = None
    acceptors = ()
    subgraphs = ()
    for declpair in p[5]:
        if len(declpair) == 0:
            continue
        statetype = declpair[0]
        statename = declpair[1]
        bitflag = 0
        if statetype == 'start':
            if starter:
                terror(NameError, "ERROR, multiple start states " + starter \
                    + " and " + statename + " in state machine " + p[2] + ".")
            else:
                starter = statename
            bitflag = __STARTSTATE__
        elif statetype == 'accept':
            if not statename in acceptors:
                acceptors = acceptors + (statename,)
            bitflag = __ACCEPTSTATE__
        elif statetype == 'subgraph':
            if not statename in subgraphs:
                subgraphs = subgraphs + (statename,)
            bitflag = __SUBGRAPH__
        if statename in states.keys():
            states[statename] = states[statename] | bitflag
        else:
            states[statename] = bitflag
        if ((states[statename] & __SUBGRAPH__) != 0)                    \
                and ((states[statename] & ~ __SUBGRAPH__) != 0):
            terror(NameError, "ERROR, state " + statename               \
                + " is tagged as a subgraph and a start or accept state"    \
                + " in state machine " + p[2] + ".")
    if starter is None:
        terror(NameError, "ERROR, no start state in state machine "     \
            + p[2] + ".")
    if acceptors == ():
        terror(NameError, "ERROR, no accept state in state machine "     \
            + p[2] + ".")
    # Convert map from state name to state type, to map from name to State obj.
    for sname in states.keys():
        isstrt = (states[sname] & __STARTSTATE__) != 0
        isend = (states[sname] & __ACCEPTSTATE__) != 0
        issub = (states[sname] & __SUBGRAPH__) != 0
        states[sname] = State(sname, p[2], (), isstart=isstrt, isaccept=isend,
            issubgraph=issub)
    # TRANSITION: 6-tuple (from, to, event, args, guard, activity)
    # October 6, 2012: from may be '*' or a sequence of state names
    # to may be *. Make 2 passes as a macro preprocessor to clean them out.
    # August 2, 2014 the activity may include macros parsed above.
    # These parameter-less macros expand verbatim (DALE In the code generator?).
    transitionList = []
    for trans6tuple in p[7]:
        if len(trans6tuple) == 0:
            continue
        fromst = trans6tuple[0]
        fromStates = []
        if type(fromst) == tuple or type(fromst) == list:
            fromStates = list(fromst)
        elif fromst == '*':
            fromStates = states.keys()
        else:
            fromStates = [fromst]
        for sym in fromStates:
            t6 = (sym,) + trans6tuple[1:]
            transitionList.append(t6)
    eventSet = set([])
    for trans6tuple in transitionList:
        if len(trans6tuple) == 0:
            continue
        fromst = trans6tuple[0]
        tost = trans6tuple[1]
        if tost == '*':
            tost = fromst
        if not fromst in states.keys():
            terror(NameError, "ERROR, Invalid transition from state "   \
                + fromst + " -> " + tost + ", " + fromst + " not in machine " \
                + p[2] + ".")
        if not tost in states.keys():
            terror(NameError, "ERROR, Invalid transition from state "   \
                + fromst + " -> " + tost + ", " + tost + " not in machine " \
                + p[2] + ".")
        evt = trans6tuple[2]
        args = trans6tuple[3]
        guard = trans6tuple[4]
        activity = trans6tuple[5]
        xition = Transition(p[2], fromst, tost, evt, args, guard, activity)
        states[fromst].addTransition(xition)
        eventSet.add(evt)
    __StateMachineSymbolTable__[p[2]] = StateMachine(p[2],states,vars,macros,
        eventSet)
    p[0] = p[2]

def p_statedecls(p):
    '''statedecls : STATE ID statedeclsrest SEMIC
        | START ID statedeclsrest SEMIC
        | ACCEPT ID statedeclsrest SEMIC
        | SUBGRAPH ID statedeclsrest SEMIC'''
    p[0] = ((p[1], p[2]),) + p[3]

def p_statedeclsrest(p):
    '''statedeclsrest : COMMA STATE ID statedeclsrest
        | COMMA START ID statedeclsrest
        | COMMA ACCEPT ID statedeclsrest
        | COMMA SUBGRAPH ID statedeclsrest
        | epsilon'''
    if p[1] == None:
        p[0] = ()
    else:
        p[0] = ((p[2], p[3]),) + p[4]

def p_statetransitions(p):
    '''statetransitions : statetransitionsrest statetransition'''
    # 6-tuple (from, to, event, args, guard, activity)
    p[0] = p[1] + (p[2],)

def p_statetransition(p):
    '''statetransition : fromids ARROW toid ID LPAREN argstr RPAREN LBRACK guardstr RBRACK SLASH activitystr semic_option'''
    # 6-tuple (from, to, event, args, guard, activity)
    p[0] = (p[1], p[3], p[4], p[6], p[9], p[12])

def p_fromids(p):   # Return a string unless there are > 1 ID; allow *
    '''fromids : pre_fromids ID
        | STAR'''
    if p[1] == '*':
        p[0] = p[1]
    elif p[1]:
        p[0] = p[1] + (p[2],)       # Make it a tuple of IDs
    else:
        p[0] = p[2]                 # Not in a list

def p_pre_fromids(p):
    '''pre_fromids : pre_fromids ID COMMA
        | epsilon'''
    if p[1] is None:
        p[0] = ()
    else:
        p[0] = p[1] + (p[2],)

def p_toid(p):
    '''toid : ID
        | STAR'''
    p[0] = p[1]

def p_semic_option(p):
    '''semic_option : SEMIC
        | COMMA
        | epsilon'''
    p[0] = None

def p_statetransitionsrest(p):
    '''statetransitionsrest : statetransitionsrest statetransition
                | epsilon'''
    if p[1] == None:
        p[0] = ()
    else:
        p[0] = p[1] + (p[2],)

def p_argstr(p):
    '''argstr : argnamelist
            | epsilon'''
    if not (p[1] is None):
        p[0] = p[1].strip()
    else:
        p[0] = None

def p_argnamelist(p):
    '''argnamelist : ID argnamerest'''
    p[0] = p[1] + p[2]  # Concat a string for later cracking apart over ','

def p_argnamerest(p):
    '''argnamerest : COMMA ID argnamerest
            | epsilon'''
    if p[1] is None:
        p[0] = ''
    else:
        p[0] = ',' + p[2] + p[3]   # Keep the comma intact

def p_guardstr(p):
    '''guardstr : ACTION_CONSTANT
            | epsilon'''
    if not (p[1] is None):
        p[0] = p[1][1:-1].strip()               # discard the @@ delimiters
    else:
        p[0] = None

def p_activitystr(p):
    '''activitystr : ACTION_CONSTANT
            | epsilon'''
    if not (p[1] is None):
        p[0] = p[1][1:-1].strip()               # discard the @@ delimiters
    else:
        p[0] = None

def p_statevariables(p):
    '''statevariables : ID EQ anyconstant statevarrest SEMIC
                | epsilon'''
    if p[1] == None:
        p[0] = ()
    else:
        p[0] = ((p[1], p[3]),) + p[4]

def p_statevarrest(p):
    '''statevarrest : COMMA ID EQ anyconstant statevarrest
                | epsilon'''
    if p[1] == None:
        p[0] = ()
    else:
        p[0] = ((p[2], p[4]),) + p[5]

def p_anyconstant(p):
    '''anyconstant : stringcon
                | FLOAT_CONSTANT
                | INT_CONSTANT
                | action_value'''
    p[0] = p[1]

def p_statemacros(p):
    '''statemacros : statemacros MACRO ID ACTION_CONSTANT
        | epsilon'''
    if p[1] is None:
        p[0] = ()
    else:
        p[0] = p[1] + ((p[3],p[4][1:-1].strip()),)

def p_action_value(p):
    '''action_value : ACTION_CONSTANT'''
    p[0] = (p[1][1:-1].strip(),)                # discard @@ delimiters, house in a 1-tuple

def p_stringcon(p):
    '''stringcon : STRING_CONSTANT1
                | STRING_CONSTANT2'''
    p[0] = p[1]

def p_epsilon(p):
    'epsilon :'
    p[0] = None

def p_error(p):
    global __global_error__
    global __global_error_string__
    tmperrstring = None
    if p:
        print("Syntax error at '%s'" % p.value, "near line",    \
            __global_line_number__)
        tmperrstring = ("ERROR: Syntax error at '%s'" % p.value)    \
            + " near line " + str( __global_line_number__)
    else:
        print("Syntax error at EOF" )
        tmperrstring = "ERROR: Syntax error at EOF"
    if __global_error__ == None:
        __global_error__ = SyntaxError
        __global_error_string__ = tmperrstring

import ply.yacc as yacc
yacc.yacc()

def compile(source, dagfilename=None, debugflag=logging.DEBUG):
    # External hook to the parser.
    global __global_error__
    global __global_error_string__
    global __StateMachineSymbolTable__
    parsetree = yacc.parse(source,debug=debugflag)
    # Audit for full connectivity / no isolated states.
    # Ability to enter sub-state machines is via named subgraph states.
    # Also print out DAG file even if there are audit errors, for debugging.
    graphAudit(parsetree, __StateMachineSymbolTable__)
    if __global_error__:
        __printDebugTreeTable__(parsetree, __StateMachineSymbolTable__)
        tmperror = __global_error__
        tmpstring = __global_error_string__
        __global_error__ = None             # reset for next time
        __global_error_string__ = None
        raise tmperror(tmpstring)
    if dagfilename:
        dagfile = open(dagfilename, 'w')
        printStateMachineToDAG(dagfilename, dagfile, parsetree,
                __StateMachineSymbolTable__)
        dagfile.close()
    if __global_error__:
        __printDebugTreeTable__(parsetree, __StateMachineSymbolTable__)
        tmperror = __global_error__
        tmpstring = __global_error_string__
        __global_error__ = None             # reset for next time
        __global_error_string__ = None
        raise tmperror(tmpstring)
    return ((parsetree, copy.copy(__StateMachineSymbolTable__)))

def __printDebugTreeTable__(parsetree, symtab):
    sys.stdout.write('DEBUGGING DUMP OF PARSE TREE:\n')
    printer = PrettyPrinter(indent=4, width=80, stream=sys.stdout)
    printer.pprint(parsetree)
    sys.stdout.write('DEBUGGING DUMP OF SYMBOL TABLE:\n')
    printer.pprint(symtab)

__commentPattern__ = re.compile("^((\s*)|(\s*#.*))$")
def readStateMachineSource(filename):
    '''
    Read & return a string with all lines from parameter filename,
    substituting a line of only \n for any #-style comment line.
    '''
    srcfilehndl = open(filename, "rU") # portable linefeed handling
    line = srcfilehndl.readline()
    buffer = ''
    while (line):
        if (__commentPattern__.match(line)):
            line = "\n"     # Keep line number intact.
        buffer = buffer + line
        line = srcfilehndl.readline()
    srcfilehndl.close()
    return buffer

if __name__=='__main__':
    usage = \
      "python State2CodeParser.py INFILE DAGOUT [ CODEOUTFILE CODEGENMODULE CODEGENCLASS [ CODEGENARGSTRING ] ]"
    if len(sys.argv) == 1:           # Interactive testing
        while 1:
            try:
                s = raw_input('statemachine > ')
            except EOFError:
                break
            if not s: continue
            ptree, symtab = compile(s)
            __printDebugTreeTable__(ptree, symtab)
    elif len(sys.argv) < 3:
        sys.stderr.write(usage + '\n')
        sys.exit(1)
    else:
        source = readStateMachineSource(sys.argv[1])
        ptree, symtab = compile(source,dagfilename=sys.argv[2],debugflag=None)
        # __printDebugTreeTable__(ptree, symtab)
        if len(sys.argv) > 3:
            if len(sys.argv) != 6 and len(sys.argv) != 7:
                sys.stderr.write(usage + '\n')
                sys.exit(1)
            cgenmod = sys.argv[4].strip()
            cgenclass = sys.argv[5].strip()
            exec('from ' + cgenmod + ' import ' + cgenclass)
            if len(sys.argv) == 7:
                cgenarg = sys.argv[6].strip()
                genobj = eval(cgenclass + '("' + cgenarg + '")')
            else:
                genobj = eval(cgenclass + '()')
            objfile = open(sys.argv[3], 'w')
            genobj.generate(ptree, symtab, objfile)
            objfile.close()

