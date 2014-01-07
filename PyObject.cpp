/*
 * PyObject.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on: Feb 3, 2013
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

#include "PyObject.h"
#include "PyException.h"
#include "PyStr.h"
#include <iostream>
#include "PyType.h"
using namespace std;

ostream &operator <<(ostream &os, PyObject &t) {
    return os << t.toString();
}

PyObject* PyObject::callMethod(string name, vector<PyObject*>* args) {
    PyObject* (PyObject::*mbr)(vector<PyObject*>*);
    if (dict.find(name) == dict.end()) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "TypeError: '"+ getType()->toString() + "' object has not attribute '" + name + "'");
    }
    
    mbr = dict[name];    
    return (this->*mbr)(args);
}

PyObject::PyObject() {
    dict["__str__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyObject::__str__);
    dict["__type__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyObject::__type__);
}

PyObject::~PyObject() {
}

PyType* PyObject::getType() {
    return NULL;
}

string PyObject::toString() {
    return "PyObject()";
}

void PyObject::incRef() {
    refCount++;
}

void PyObject::decRef() {
    refCount--;
}

int PyObject::getRefCount() const {
    return refCount;
}

bool PyObject::isCallable() const {
    return false;
}

PyObject* PyObject::__str__(vector<PyObject*>* args) {
    if (args->size() != 0) {
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,"TypeError: expected 0 arguments, got " + args->size());
    }
    
    return new PyStr(toString());
}

PyObject* PyObject::__type__(vector<PyObject*>* args) {
    if (args->size() != 0) {
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,"TypeError: expected 0 arguments, got " + args->size());
    }
    
    return (PyObject*)this->getType();
}
