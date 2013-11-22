/* 
 * File:   PyCode.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 11, 2013, 10:53 AM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * PyCode objects hold the various parts of an assembly language function. Each
 * function has a name, a number of arguments, byte code, and several lists 
 * which are outlined below. 
 * 
 * Constants - Constant values that are used within the function.
 * 
 * Locals - The list of local variables used in the function. 
 * 
 * FreeVars - The list of variables not initialized in this function. They are
 * referenced from an enclosing scope. 
 * 
 * CellVars - The list of cell variables for local variables that are referenced
 * outside of this function.
 * 
 * Globals - The list of globals like "str" and other functions that are 
 * defined globally and used in this function.
 */

#ifndef PYCODE_H
#define	PYCODE_H

#include "PyByteCode.h"
#include "PyObject.h"
#include <string>
#include <vector>
using namespace std;

class PyCode : public PyObject {
public:
    PyCode(string name, vector<PyCode*>* nestedFunctions, vector<PyObject*>* consts,
            vector<string>* locals, vector<string>* freevars, vector<string>* cellVars,
            vector<string>* globals, vector<PyByteCode*>* code, int argcount);
    virtual ~PyCode();

    string getName() const;
    vector<string>& getLocals() const;
    vector<string>& getFreeVars() const;
    vector<string>& getCellVars() const;
    vector<string>& getGlobals() const;
    vector<PyObject*>& getConsts() const;
    vector<PyByteCode*>& getInstructions() const;
    vector<PyCode*>& getNestedFunctions() const;
    int getArgCount() const;
    int numLocals() const; 
    string toString();
    string prettyString(string indent,bool linenumbers) const;
    PyType* getType();
    
    PyObject* __str__(vector<PyObject*>* args);
    PyObject* __type__(vector<PyObject*>* args);
    
private:
    string name;
    vector<PyCode*>* nestedFunctions;
    vector<string>* locals;
    vector<string>* freevars;
    vector<string>* cellvars;
    vector<string>* globals;
    vector<PyObject*>* consts;
    vector<PyByteCode*>* instructions;
    int argcount;
};

#endif	/* PYCODE_H */

