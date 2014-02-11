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
#include <sstream>
using namespace std;

PyBool::PyBool() : PyObject() {
    val = false;
    
    dict["__float__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyBool::__float__);
    dict["__int__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyBool::__int__);
    dict["__bool__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyBool::__bool__);
    dict["__eq__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyBool::__eq__);
}

PyBool::PyBool(bool val) : PyBool() {
    this->val = val;
}

PyBool::PyBool(const PyBool& orig) : PyBool() {
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
    ostringstream msg; 

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());
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
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());    }
    
    if (this->getVal())
        return new PyFloat(1);
    
    return new PyFloat(0);
}

PyObject* PyBool::__int__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());    }
    
    if (this->getVal())
        return new PyInt(1);
    
    return new PyInt(0);
}

PyObject* PyBool::__bool__(vector<PyObject*>* args) {
    return this;
}

