/* 
 * File:   PyFrame.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 15, 2013, 5:35 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * PyFrame objects are the CoCo equivalent of an activation record on the 
 * run-time stack. A PyFunction object is created for each function defined
 * in the casm file. When a function is called, a PyFrame object is created 
 * with the information for the function, including the code, arguments,
 * and the globals, constants, and cellvars. The execute method of this class
 * is where the virtual machine instructions are executed. 
 * 
 * The opStack instance variable is a stack of PyObjects. It is where the 
 * virtual machine pushes operands that are used by the instructions. The 
 * CoCo is a stack machine (i.e. no registers). All operands are pushed on the
 * opStack prior to an operation being performed. 
 * 
 * The blockStack is a stack used to record blocks. A block is an integer 
 * which is pushed on a stack for a loop or a try except block. When in a loop
 * the break statement will exit the loop by popping the block stack to find 
 * the exit point for the program counter. For try except blocks the value 
 * pushed on the blockStack is -1*PC where PC is the exit point of the exception
 * handler. In this way we can distinguish between loop blocks and exception 
 * blocks. 
 */

#ifndef PYFRAME_H
#define	PYFRAME_H

#include "PyObject.h"
#include "PyCode.h"
#include "PyStack.h"
#include "PyCell.h"
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class PyFrame : public PyObject {
public:
    PyFrame(const PyCode& code, vector<PyObject*>* args, unordered_map<string,PyObject*>& globals, 
            const vector<PyObject*>& consts, unordered_map<string,PyCell*>& cellvars);
    virtual ~PyFrame();
    
    PyObject* execute();
    string getCellName(int index);
    const PyCode& getCode() const;
    int getPC() const;
    
private:
    const PyCode& code;
    int PC;
    unordered_map<string,PyObject*> locals;
    unordered_map<string,PyObject*>& globals;
    unordered_map<string,PyCell*>& cellvars;
    const vector<PyObject*>& consts;
    
    PyStack<PyObject*>* opStack;
    PyStack<int>* blockStack;
    PyObject* safetyPop();
};

void pushFrame(PyFrame* frame);
void popFrame();

#endif	/* PYFRAME_H */

