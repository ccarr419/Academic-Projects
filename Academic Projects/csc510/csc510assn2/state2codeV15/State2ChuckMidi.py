from state2codeV15.State2CodeParser import AbstractCodeGenerator, horror

class State2ChuckMidi(AbstractCodeGenerator):
    def __init__(self):
        pass
    def generate(self, parseTree, symtab, objfile):
        def clean(string):
            result = string
            if len(result) and (result[0] == '"' or result[0] == "'"):
                result = result[1:]
            if len(result) and (result[-1] == '"' or result[-1] == "'"):
                result = result[:-1]
            return result
        startnum = None
        firststate = True ;
        if len(symtab.keys()) != 1:
            terror(ValueError,
                'State2ChuckMidi does not support multiple state machines.')
        sm = symtab[parseTree[1]]
        if len(sm.macros.keys()) != 0:
            terror(ValueError,
                'State2ChuckMidi does not support macros.')
        tmplfile = open('template.ck.txt', 'rU')
        line = tmplfile.readline()
        while line:
            objfile.write(line)
            line = tmplfile.readline()
        tmplfile.close()
        for vname in sm.variables.keys():
            vval = sm.variables[vname]
            # parser makes vval the correct type
            if type(vval) == str:
                if "'" in vval:
                    vval = '"' + vval + '"'
                else:
                    vval = "'" + vval + "'"
                objfile.write(str(vval) + ' => string ' + vname + ';\n')
            elif type(vval) == float:
                objfile.write(str(vval) + ' => float ' + vname + ';\n')
            else:
                objfile.write(str(vval) + ' => int ' + vname + ';\n')
        objfile.write('string stateName[' + str(len(sm.states.keys()))  \
            + '];\n')
        for statename in sm.states.keys():
            state = sm.states[statename]
            objfile.write('"' + statename + '" => stateName['       \
                + str(state.statenum) + '];\n')
        objfile.write(str(sm.startstate.statenum) + ' => stateIndex ;\n')
        objfile.write('fun void midiTranslator(MidiMsg msgin) {\n')
        objfile.write('    MidiMsg msgout;\n')
        objfile.write('    msgin.data1 => msgout.data1 ;\n')
        objfile.write('    msgin.data2 => msgout.data2 ;\n')
        objfile.write('    msgin.data3 => msgout.data3 ;\n')
        for statename in sm.states.keys():
            state = sm.states[statename]
            if firststate:
                objfile.write('    if (stateIndex == ' + str(state.statenum) \
                    + ') {\n')
                firststate = False
            else:
                objfile.write('    } else if (stateIndex == '               \
                    + str(state.statenum) + ') {\n')
            firsttrans = True
            for trans in state.transitions:
                if (not trans.event) or (trans.event != 'midi'):
                    raise ValueError('State2ChuckMidi supports only midi Transition: ' \
                            + str(trans))
                # print "DEBUG GUARD", str(trans)
                if (not trans.guard):
                    raise ValueError('State2ChuckMidi requires guard on Transition: ' \
                            + str(trans))
                if firsttrans:
                    objfile.write('        if (' + clean(trans.guard)   \
                        + ') {\n')
                    firsttrans = False
                else:
                    objfile.write('        } else if (' + clean(trans.guard)  \
                        + ') {\n')
                # Write the actions, as separated by ';' characters.
                # Default action is just a straight copy with state update.
                if trans.activity:
                    actions = trans.activity.strip().split(';')
                    for act in actions:
                        act = act.strip()
                        if act:
                            objfile.write('            ' + clean(act) + ';\n')
                tost = sm.states[trans.destState]
                objfile.write('            ' + str(tost.statenum)   \
                    + ' => stateIndex ;\n')
            if not firsttrans:
                objfile.write('        }\n')
        objfile.write('    }\n')
        objfile.write('    if (stateIndex != oldIndex) {\n')
        objfile.write('        <<< "Enter state index", stateIndex, stateName[stateIndex] >>>;\n')
        objfile.write('    }\n')
        objfile.write('}\n')
        objfile.write('<<< "Start in state index", stateIndex, stateName[stateIndex] >>>;\n')
        objfile.write('mainloop();\n')

