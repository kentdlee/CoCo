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
#include "PyException.h"
#include <sstream>

 using namespace std;

PyBuiltInIter::PyBuiltInIter() : PyCallable() {
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
    ostringstream msg;
    
    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());   
    }
    
    x = (*args)[0];
    
    PyObject* result = x->callMethod("__iter__",iterArgs);
    
    return result;
}

string PyBuiltInIter::toString() {
    return "iter";
}