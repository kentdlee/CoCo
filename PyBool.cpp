/* 
 * File:   PyBool.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 16, 2013, 4:05 PM
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

#include "PyBool.h"
#include "PyException.h"
#include "PyStr.h"
#include "PyInt.h"
#include "PyFloat.h"

#include <iostream>
using namespace std;

PyBool::PyBool() {
    val = false;
}

PyBool::PyBool(bool val) {
    this->val = val;
}

PyBool::PyBool(const PyBool& orig) {
    val = orig.val;
}

PyBool::~PyBool() {
}

string PyBool::toString() {
    if (val)
        return "True";

    return "False";
}

PyObject* PyBool::__eq__(vector<PyObject*>* args) {
    if (args->size() != 1) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Invalid number of arguments for bool equal op.");
    }

    PyBool* other = (PyBool*) (*args)[0];

    return new PyBool(val == other->val);
}

PyType* PyBool::getType() {
    return PyTypes[PyBoolType];
}

bool PyBool::getVal() {
    return val;
}


PyObject* PyBool::__float__(vector<PyObject*>* args) { 
    if (this->getVal())
        return new PyFloat(1);
    
    return new PyFloat(0);
}

PyObject* PyBool::__int__(vector<PyObject*>* args) {
    if (this->getVal())
        return new PyInt(1);
    
    return new PyInt(0);
}

PyObject* PyBool::__bool__(vector<PyObject*>* args) {
    return this;
}

