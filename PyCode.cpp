/* 
 * File:   PyCode.cpp
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
 * See the associated header file for a description of the purpose of this 
 * class. Implementation details are provided here. Read below for 
 * any specific details. 
 * 
 */

#include "PyCode.h"
#include "PyType.h"
#include "PyStr.h"
#include <sstream>
using namespace std;

PyCode::PyCode(string name, vector<PyCode*>* nestedFuns, vector<PyObject*>* consts,
        vector<string>* locals, vector<string>* freevars, vector<string>* cellvars,
        vector<string>* globals, vector<PyByteCode*>* code, int argcount) :
        PyObject() {
    this->name = name;
    this->locals = locals;
    this->freevars = freevars;
    this->cellvars = cellvars;
    this->globals = globals;
    this->consts = consts;
    this->instructions = code;
    this->argcount = argcount;
    this->nestedFunctions = nestedFuns;
}

PyCode::~PyCode() {
    try {
        delete nestedFunctions;
    } catch (...) {}
    try {
        delete instructions;
    } catch (...) {}
    try {
        delete consts;
    } catch (...) {}
    try {
        delete globals;
    } catch (...) {}
    try {
        delete cellvars;
    } catch (...) {}
    try {
        delete freevars;
    } catch (...) {}
    try {
        delete locals;
    } catch (...) {}   
}

string PyCode::getName() const {
    return this->name;
}

vector<PyCode*>& PyCode::getNestedFunctions() const {
    return *nestedFunctions;
}

vector<string>& PyCode::getLocals() const {
    return *(this->locals);
}

vector<string>& PyCode::getFreeVars() const {
    return *(this->freevars);
}

vector<string>& PyCode::getCellVars() const {
    return *(this->cellvars);
}

vector<string>& PyCode::getGlobals() const {
    return *(this->globals);
}

vector<PyObject*>& PyCode::getConsts() const {
    return *(this->consts);
}

vector<PyByteCode*>& PyCode::getInstructions() const {
    return *(this->instructions);
}

int PyCode::getArgCount() const {
    return this->argcount;
}

int PyCode::numLocals() const {
    return this->locals->size();
}

string vectorValsToString(string name, vector<PyObject*>* lst) {
    string result = "";

    if (lst->size() > 0) {
        result += name;

        int i;


        for (i = 0; i < lst->size(); i++) {
            PyObject* obj = (*lst)[i];

            if (obj->getType()->typeId() == PyStrType)
                result += "'" + obj->toString() + "'";
            else
                result += (*lst)[i]->toString();

            if (i < lst->size() - 1)
                result += ", ";
        }

        result += "\n";
    }

    return result;
}

string vectorToString(string name, vector<string>* lst) {
    string result = "";

    if (lst->size() > 0) {
        result += name;

        int i;

        for (i = 0; i < lst->size(); i++) {
            result += (*lst)[i];

            if (i < lst->size() - 1)
                result += ", ";
        }

        result += "\n";
    }

    return result;
}

string PyCode::prettyString(string indent, bool linenumbers) const {
    stringstream ss;

    ss << indent << "Function: " << name << "/" << argcount << "\n";

    if (!linenumbers)
        for (int i = 0; i < nestedFunctions->size(); i++) {
            ss << (*nestedFunctions)[i]->prettyString(indent + "    ", linenumbers);
        }

    ss << vectorValsToString(indent + "Constants: ", consts);
    ss << vectorToString(indent + "Locals: ", locals);
    ss << vectorToString(indent + "FreeVars: ", freevars);
    ss << vectorToString(indent + "CellVars: ", cellvars);
    ss << vectorToString(indent + "Globals: ", globals);
    ss << indent << "BEGIN\n";

    int i;

    for (i = 0; i < instructions->size(); i++) {
        if (linenumbers) {
            ss << i << ": ";
            if (i < 10)
                ss << " ";
            if (i < 100)
                ss << " ";
        }

        ss << indent << (*instructions)[i]->toString() << "\n";
    }

    ss << indent + "END\n";

    return ss.str();
}

string PyCode::toString() {

    return "code(" + this->name + ")";
}

PyType* PyCode::getType() {
    return PyTypes[PyCodeType];
}

PyObject* PyCode::__type__(vector<PyObject*>* args) {
    return PyTypes[PyCodeType];
}

PyObject* PyCode::__str__(vector<PyObject*>* args) {
    return new PyStr(toString());
}
