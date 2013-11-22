/* 
 * File:   PyBuiltInIter.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 25, 2013, 10:17 AM
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

#include "PyBuiltInIter.h"

PyBuiltInIter::PyBuiltInIter() {
}

PyBuiltInIter::PyBuiltInIter(const PyBuiltInIter& orig) {
}

PyBuiltInIter::~PyBuiltInIter() {
}

PyType* PyBuiltInIter::getType() {
    return PyTypes[PyBuiltInType];
}

PyObject* PyBuiltInIter::__call__(vector<PyObject*>* args) {
    vector<PyObject*>* iterArgs = new vector<PyObject*>();
    PyObject* x;
    
    x = (*args)[0];
    
    PyType* selfType = x->getType();
    
    PyObject* result = selfType->call("__iter__",x,iterArgs);
    
    return result;
}

bool PyBuiltInIter::allowableArgCount(int count) {
    return count == 1;
}

string PyBuiltInIter::callName() {
    return "iter";
}

string PyBuiltInIter::toString() {
    return callName();
}