# 
# File:   disassembler.py
# Author: Kent D. Lee
# (c) 2013
# Created on February 12, 2013, 10:58 PM
# Description: This program, when called on a function disassembles it 
# producing a Python Virtual Machine description of the code. The format
# That this file produces corresponds to the grammar supported by the 
# CoCoVM virtual machine implementation that Kent developed for a
# course on Programming Languages.  
import dis
import types
import sys
from io import StringIO

if str(sys.version)[0:3] != "3.2":
    print("************************************************************")
    print("* WARNING: disassembler.py should be run using Python 3.2  *")
    print("*          You are running Python", str(sys.version)[0:3],(" "*20),"*")
    print("*          The disassembly may not be correct.             *")
    print("************************************************************")    

def f(x,y):
    def g(z):
        return z + y
    return g(x)+y

def get_code_object(obj, compilation_mode="exec"):
    if isinstance(obj, types.CodeType):
        return obj
    elif isinstance(obj, types.FrameType):
        return obj.f_code
    elif isinstance(obj, types.FunctionType):
        return obj.__code__
    elif isinstance(obj, str):
        try:
            return compile(obj, "<string>", compilation_mode)
        except SyntaxError as error:
            raise ValueError("syntax error in passed string") from error
    else:
        raise TypeError("get_code_object() can not handle '%s' objects" %
                        (type(obj).__name__,))
    
def disassemble(obj, indent=""):
    if type(obj) == type(type):
        print("Class:",obj.__name__)
        print("BEGIN")
        for x in obj.__dict__:
            if isinstance(obj.__dict__[x], types.FunctionType):
                disassemble(obj.__dict__[x],"    ")
        print("END")
    else:
        code = get_code_object(obj)
        theLocals = code.co_varnames
        theConsts = code.co_consts
        theGlobals = code.co_names
        theFreeVars = code.co_freevars
        theCellVars = code.co_cellvars
        theName = code.co_name
        theArgCount = code.co_argcount
                
        print(indent+"Function: "+theName+"/"+str(theArgCount))
        
        for val in theConsts:
            if type(val) == type(code): # meaning val is a code object
                newindent = indent+"    "
                disassemble(val,indent=newindent)
                
        if len(theConsts) > 0:  
            line = indent+"Constants: "
            for val in theConsts:
                if type(val) == str:
                    line+='"'+val+'"'+", "
                elif type(val) == type(code): # meaning this is a code object
                    line+="code("+val.co_name+"), "
                else:
                    line+=str(val)+", "
            
            print(line[:-2])
            
        if len(theLocals) > 0:
            line = indent+"Locals: "
            for val in theLocals:
                line+=val+", "
            
            print(line[:-2])  
            
        if len(theFreeVars) > 0:
            line = indent+"FreeVars: "
            for val in theFreeVars:
                line+=val+", "
            
            print(line[:-2])     
                
        if len(theCellVars) > 0:
            line = indent+"CellVars: "
            for val in theCellVars:
                line+=val+", "
            
            print(line[:-2]) 
                
        if len(theGlobals) > 0:
            line = indent+"Globals: "
            for val in theGlobals:
                line+=val+", "
            
            print(line[:-2])    
            
        print(indent+"BEGIN")
        oldstdout = sys.stdout
        sys.stdout = mystdout = StringIO()
        dis.dis(code)
        sys.stdout = oldstdout
        instructions = mystdout.getvalue().split("\n")
        label = 0
        
        #first find the labelled line in the file and mark them.
        targets = {}
        for line in instructions:
            if ">>" in line:
                lst = line[10:].split()
                address = lst[0]
                targets[address] = label
                label+=1
                
        # Now generate the output
        for line in instructions:
            t = line[10:].split()
            if len(t) >= 2:
                address = t[0]
                mnemonic = t[1]
                if len(t) > 2:
                    operand = t[2]
                else:
                    operand = ""
                
        
                if ">>" in line:
                    label = targets[address]
                    labelString = "label%02d"%label+":  "
                else:
                    labelString = " "*10
                    
                if mnemonic in ["SETUP_LOOP","JUMP_FORWARD","FOR_ITER","SETUP_EXCEPT","SETUP_FINALLY"] :
                    location = str(int(address) + int(operand) + 3)
                    inst = labelString + mnemonic + " "*(25-len(mnemonic)) + "label%02d"%targets[location]
                elif "JUMP" in mnemonic:
                    if operand in targets:
                        inst = labelString + mnemonic + " "*(25-len(mnemonic)) + "label%02d"%targets[operand]
    #                else:
    #                    inst = labelString + mnemonic + " "*(25-len(mnemonic)) + "     %2s"%operand
                elif len(operand) > 0:
                    inst = labelString + mnemonic + " "*(25-len(mnemonic)) + "%7d"%int(operand)
                else:
                    inst = labelString + mnemonic + " "*(25-len(mnemonic)) 
            
                print(indent+inst)
        print(indent+"END")
    
def main():
    disassemble(f)
    
if __name__ == "__main__":
    main()
